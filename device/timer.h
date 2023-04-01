#ifndef _DEVICE_TIMER_H
#define _DEVICE_TIMER_H
#include "stdint.h"

void timer_init();
void mtime_sleep(uint32_t m_seconds);
void ticks_to_sleep(uint32_t sleep_ticks);
#endif
