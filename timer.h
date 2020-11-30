#ifndef TIMER_H
#define TIMER_H 

#include "regs.h"
#include "idt.h"
#include "terminal.h"

void terminal_display_time(int seconds);
void timer_handler(struct regs *r);
void time_to_clock(char* dest, uint64_t t);

#endif