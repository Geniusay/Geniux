#include "sync.h"
#include "stdint.h"
#include "list.h"
#include "thread.h"
#include "interrupt.h"
#include "debug.h"
void sema_init(struct semaphore* psema, uint8_t value) {
	psema->value = value;
	list_init(&psema->waiters);
}

void lock_init(struct lock* plock) {
	plock->holder = NULL;
	plock->holder_repeat_nr = 0;
	sema_init(&plock->semaphore,1);
}

void sema_down(struct semaphore* psema) {
	enum intr_status old_status = intr_disable();
	while (psema->value == 0) {
		//检测当前线程是否在等待队列中，在的话则报错
		if (find(&psema->waiters, &running_thread()->general_tag)) {
			PANIC("sema_down: thread blocked has been in waiter");
		}
		append(&psema->waiters, &running_thread()->general_tag);
		thread_block(TASK_BLOCKED);
	}
	--psema->value;
	ASSERT(psema->value == 0);
	intr_set_status(old_status);
}

void sema_up(struct semaphore* psema) {
	enum intr_status old_status = intr_disable();
	//从waiter队列中唤醒第一个线程
	if (!empty(&psema->waiters)) {
		struct task_struct* thread_blocked = elem2entry(struct task_struct, general_tag, pop(&psema->waiters));
		thread_unblock(thread_blocked);
	}
	++psema->value;
	ASSERT(psema->value == 1);
	intr_set_status(old_status);
}

void try_lock(struct lock* plock) {
	
	if (plock->holder != running_thread()) {
		sema_down(&plock->semaphore);
		
		plock->holder = running_thread();
		ASSERT(plock->holder_repeat_nr == 0);
		plock->holder_repeat_nr = 1;
		
	}
	else {
		++plock->holder_repeat_nr;
	}
}

void try_release(struct lock* plock) {
	ASSERT(plock->holder == running_thread());

	if (plock->holder_repeat_nr > 1) {
		--plock->holder_repeat_nr;
		return;
	}

	ASSERT(plock->holder_repeat_nr == 1);

	plock->holder = NULL;
	plock->holder_repeat_nr = 0;
	sema_up(&plock->semaphore);
}