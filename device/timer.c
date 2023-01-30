#include "timer.h"
#include "io.h"
#include "print.h"

#define IRQ0_FREQUENCY 100
#define INPUT_FREQUENCY 1193180
#define COUNTER0_VALUE INPUT_FREQUENCY/IRQ0_FREQUENCY
#define COUNTER0_PORT 0x40
#define COUNTER0_NO 0
#define COUNTER_MODE 2
#define READ_WRITE_LATCH 3
#define PIT_CONTROL_PORT 0x43

/** 初始化频率 **/
static void frequency_set(uint8_t counter_port,
	uint8_t counter_no,
	uint8_t rw,
	uint8_t mode,
	uint16_t counter_value) {
	outb(PIT_CONTROL_PORT, (uint8_t)(counter_no<<6 | rw<<4 |mode<<1)); //规定PIT的工作模式
	outb(counter_port, (uint8_t)counter_value);
	outb(counter_port, (uint8_t)counter_value >> 8);
}

/** 初始化timer **/
void timer_init() {
	put_str("timer_init start\n");
	frequency_set(COUNTER0_PORT,
		COUNTER0_NO,
		READ_WRITE_LATCH,
		COUNTER_MODE,
		COUNTER0_VALUE);
	put_str("timer_init done\n");
}