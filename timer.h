#ifndef TIMER_H
#define TIMER_H 

#include "regs.h"
#include "idt.h"
#include "terminal.h"
#include "process.h"

void terminal_display_time(int seconds,int x, int y);
void timer_handler(struct regs *r);
void time_to_clock(char* dest, uint64_t t);
void sleep(uint32_t ticks);

void timer1();
void timer2();

#endif