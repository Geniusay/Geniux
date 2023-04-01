#include "debug.h"
#include "ioqueue.h"
#include "interrupt.h"

void ioqueue_init(struct ioqueue* ioq) {
	lock_init(&ioq->lock);
	ioq->producer = ioq->consumer = NULL;
	ioq->head = ioq->tail = 0;
}

int32_t next_pos(int32_t pos) {
	return (pos + 1) % bufsize;
}

bool ioq_full(struct ioqueue* ioq) {
	ASSERT(intr_get_status() == INTR_OFF);
	return (ioq->tail - ioq->head) == 1;
}

bool ioq_empty(struct ioqueue* ioq) {
	ASSERT(intr_get_status() == INTR_OFF);
	return ioq->head == ioq->tail;
}

//使当前的生产者或消费之在缓冲区上等待
void ioq_wait(struct task_struct** waiter) {
	ASSERT(*waiter == NULL && waiter != NULL);
	*waiter == running_thread();
	thread_block(TASK_BLOCKED);
}

//唤醒生产者或消费者
void ioq_wakeup(struct task_struct** waiter) {
	ASSERT(*waiter != NULL);
	thread_unblock(*waiter);
	*waiter = NULL;
}

char ioq_getchar(struct ioqueue* ioq) {
	//先判断是否关闭中断
	ASSERT(intr_get_status() == INTR_OFF);

	//判断是否为空，如果为空消费者需要休眠等待
	while (ioq_empty(ioq)) {
		try_lock(&ioq->lock);
		ioq_wait(&ioq->consumer);
		try_release(&ioq->lock);
	}

	//获取buf中的数据
	char ch = ioq->buf[ioq->tail];
	ioq->tail = next_pos(ioq->tail);

	if (ioq->producer != NULL) {
		ioq_wakeup(&ioq->producer);
	}

	return ch;
}

void ioq_setchar(struct ioqueue* ioq, char byte) {
	//先判断是否关闭中断
	ASSERT(intr_get_status() == INTR_OFF);

	//判断是否满缓冲区，如果满了生产需要休眠等待
	while (ioq_full(ioq)) {
		try_lock(&ioq->lock);
		ioq_wait(&ioq->producer);
		try_release(&ioq->lock);
	}

	//获取buf中的数据
	ioq->buf[ioq->head]=byte;
	ioq->head = next_pos(ioq->head);

	if (ioq->consumer != NULL) {
		ioq_wakeup(&ioq->consumer);
	}

	return byte;
}


