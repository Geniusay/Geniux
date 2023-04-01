#ifndef  _DEVICE_IOQUEUE_H
#define  _DEVICE_IOQUEUE_H
#include "stdint.h"
#include "thread.h"
#include "sync.h"

#define bufsize 64

struct ioqueue {
	struct lock lock;
	struct task_struct* producer;
	struct task_struct* consumer;
	char buf[bufsize];
	int32_t head;	//生产是头指针移动
	int32_t tail;	//消费时尾指针移动
};

void ioqueue_init(struct ioqueue* ioq);
int32_t next_pos(int32_t pos);
bool ioq_full(struct ioqueue* ioq);
bool ioq_empty(struct ioqueue* ioq);
void ioq_wait(struct task_struct** waiter);
void ioq_wakeup(struct task_struct** waiter);
char ioq_getchar(struct ioqueue* ioq);
void ioq_setchar(struct ioqueue* ioq, char byte);
#endif // ! _DEVICE_IOQUEUE_H
