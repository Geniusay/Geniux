#ifndef  _THREAD_SYNC_H
#define	 _THREAD_SYNC_H
#include "list.h"
#include "stdint.h"
#include "thread.h"


struct semaphore {
	uint8_t value;
	struct list waiters;
};

struct lock {
	struct task_struct* holder;
	struct semaphore semaphore;
	uint32_t holder_repeat_nr;
};
void lock_init(struct lock* plock);
void try_lock(struct lock* plock);
void try_release(struct lock* plock);
#endif // ! _THREAD_SYNC_H
