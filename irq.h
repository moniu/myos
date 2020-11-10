#ifndef IRQ_H
#define IRQ_H

#include "string.h"
#include "idt.h"
#include "timer.h"
#include "keyboard.h"

void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void outportb (unsigned short _port, unsigned char _data);
unsigned char inportb (unsigned short _port);
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
void _irq_handler(struct regs *r);
void irq_remap(void);

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif