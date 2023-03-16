#include "print.h"
#include "init.h"
#include "debug.h"
#include "thread.h"
#include "console.h"
#include "keyboard.h"
#include "ioqueue.h"
#include "interrupt.h"
#include "process.h"
#include "../lib/user/syscall.h"
#include "../userprog/syscall-init.h"
#include "stdio.h"
void test_thread1(void* arg);
void test_thread2(void* arg);
void u_prog_a(void);
void u_prog_b(void);


void main(void) {

	put_str("Hello GeniusOS\n");
	put_int(2023);
	put_str("\n");
	init_all();
	//process_execute(u_prog_a, "user_prog_a");
	//process_execute(u_prog_b, "user_prog_b");
	intr_enable();

	console_put_str(" main_pid:0x");
	console_put_int(sys_getpid());
	console_put_char('\n');

	thread_start("kernel_thread_a", 31, test_thread1, " thread_A:0x");
	thread_start("kernel_thread_b", 31, test_thread2, " thread_B:0x");

	while (1) {
	}
}

void test_thread1(void* arg)
{
	console_put_str((char*)arg);
	console_put_int(getpid());
	void* addr = sys_malloc(33);
	console_put_str(" thread_a ,sys_malloc(33),addr is 0x");
	console_put_int((int)addr);
	console_put_char('\n');
	while (1);
}

void test_thread2(void* arg)
{
	console_put_str((char*)arg);
	console_put_int(getpid());
	void* addr = sys_malloc(63);
	console_put_str(" thread_b ,sys_malloc(63),addr is 0x");
	console_put_int((int)addr);
	console_put_char('\n');
	while (1);
}

void u_prog_a(void)
{
	printf(" prog_a_pid:0x%x\n", getpid());
	while (1);
}

void u_prog_b(void)
{
	printf(" prog_b_pid:0x%x\n", getpid());
	while (1);
}
