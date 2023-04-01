#include "init.h"
#include "print.h"
#include "interrupt.h"
#include "../device/timer.h"
#include "memory.h"
#include "thread.h"
#include "console.h"
#include "keyboard.h"
#include "../userprog/tss.h"
#include "syscall-init.h"
#include "ide.h"
void init_all(void) {
	put_str("init all\n");
	idt_init();
	timer_init();
	mem_init();
	thread_init();
	console_init();
	keyboard_init();
	tss_init();
	syscall_init();
	ide_init();
}

