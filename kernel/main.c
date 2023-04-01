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
	void* addr1 = sys_malloc(256);
	void* addr2 = sys_malloc(255);
	void* addr3 = sys_malloc(254);
	console_put_str(" thread_a malloc addr:0x");
	console_put_int((int)addr1);
	console_put_char(',');
	console_put_int((int)addr2);
	console_put_char(',');
	console_put_int((int)addr3);
	console_put_char('\n');
	int cpu_delay = 100000;
	while (cpu_delay-- > 0);
	sys_free(addr1);
	sys_free(addr2);
	sys_free(addr3);
	while (1);
}

void test_thread2(void* arg)
{
	void* addr1 = sys_malloc(256);
	void* addr2 = sys_malloc(255);
	void* addr3 = sys_malloc(254);
	console_put_str(" thread_b malloc addr:0x");
	console_put_int((int)addr1);
	console_put_char(',');
	console_put_int((int)addr2);
	console_put_char(',');
	console_put_int((int)addr3);
	console_put_char('\n');
	int cpu_delay = 100000;
	while (cpu_delay-- > 0);
	sys_free(addr1);
	sys_free(addr2);
	sys_free(addr3);
	while (1);

}

void u_prog_a(void)
{
	void* addr1 = malloc(256);
	void* addr2 = malloc(255);
	void* addr3 = malloc(254);
	printf(" prog_a malloc addr:0x%x, 0x%x, 0x%x\n", (int)addr1, (int)addr2, (int)addr3);
	int cpu_delay = 100000;
	while (cpu_delay-- > 0);
	free(addr1);
	free(addr2);
	free(addr3);
	while (1);
}

void u_prog_b(void)
{
	void* addr1 = malloc(256);
	void* addr2 = malloc(255);
	void* addr3 = malloc(254);
	printf(" prog_b malloc addr:0x%x, 0x%x, 0x%x\n", (int)addr1, (int)addr2, (int)addr3);
	int cpu_delay = 100000;
	while (cpu_delay-- > 0);
	free(addr1);
	free(addr2);
	free(addr3);
	while (1);
}
