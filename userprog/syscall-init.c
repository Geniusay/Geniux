#include "thread.h"
#include "memory.h"
#include "syscall-init.h"
#define syscall_n 32
typedef void* syscall;
syscall syscall_table[syscall_n];

uint32_t sys_getpid(void) {
	return running_thread()->pid;
}

uint32_t sys_write(char* str) {
	console_put_str(str);
	return strlen(str);
}

void syscall_init(void) {
	put_str("syscall_init start\n");
	syscall_table[SYS_GETPID] = sys_getpid;
	syscall_table[SYS_WRITE] = sys_write;
	syscall_table[SYS_MALLOC] = sys_malloc;
	syscall_table[SYS_FREE] = sys_free;
	put_str("syscall_init done\n");
}