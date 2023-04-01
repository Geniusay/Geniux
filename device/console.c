#include "console.h"
#include "stdint.h"
#include "sync.h"
#include "print.h"
static struct lock console_lock;

void console_init() {
	lock_init(&console_lock);
	put_str("\nconsole init done!\n");
}

void console_acquire() {
	try_lock(&console_lock);
}

void console_release() {
	try_release(&console_lock);
}

void console_put_str(char* str) {
	console_acquire();
	put_str(str);
	console_release();
}

void console_put_char(uint8_t ch) {
	console_acquire();
	put_char(ch);
	console_release();
}

void console_put_int(uint32_t num) {
	console_acquire();
	put_int(num);
	console_release();
}
