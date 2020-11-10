#ifndef TIMER_H
#define TIMER_H

#include "idt.h"
#include "terminal.h"

uint64_t time_ticks = 0;

void terminal_display_time(int seconds);
void timer_handler(struct regs *r);

#endif