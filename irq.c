#include <stdint.h>
#include "irq.h"

void irq_remap(void)
{
    // Tłumaczymy porty, ponieważ domyślna konfiguracja nie działa najlepiej w trybie chronionym
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

void irq_setup()
{
    terminal_writestring("IRQ :: SETUP BEGINS\n");
    irq_remap();
    terminal_writestring("IRQ :: REMAPING\n");
    
    idt_make_entry(idt+32, (uint32_t)irq0, 0x08, 0x8E);
    idt_make_entry(idt+33, (uint32_t)irq1, 0x08, 0x8E);
    idt_make_entry(idt+34, (uint32_t)irq2, 0x08, 0x8E);
    idt_make_entry(idt+35, (uint32_t)irq3, 0x08, 0x8E);
    idt_make_entry(idt+36, (uint32_t)irq4, 0x08, 0x8E);
    idt_make_entry(idt+37, (uint32_t)irq5, 0x08, 0x8E);
    idt_make_entry(idt+38, (uint32_t)irq6, 0x08, 0x8E);
    idt_make_entry(idt+39, (uint32_t)irq7, 0x08, 0x8E);
    idt_make_entry(idt+40, (uint32_t)irq8, 0x08, 0x8E);
    idt_make_entry(idt+41, (uint32_t)irq9, 0x08, 0x8E);
    idt_make_entry(idt+42, (uint32_t)irq10, 0x08, 0x8E);
    idt_make_entry(idt+43, (uint32_t)irq11, 0x08, 0x8E);
    idt_make_entry(idt+44, (uint32_t)irq12, 0x08, 0x8E);
    idt_make_entry(idt+45, (uint32_t)irq13, 0x08, 0x8E);
    idt_make_entry(idt+46, (uint32_t)irq14, 0x08, 0x8E);
    idt_make_entry(idt+47, (uint32_t)irq15, 0x08, 0x8E);

    irq_routines[0] = timer_handler;
    irq_routines[1] = keyboard_handler;
    terminal_writestring("IRQ :: SETUP COMPLETED\n");
}

void _irq_handler(struct regs *r)
{
    void (*handler)(struct regs *r);

    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }


    // Zwróć odpowiedź do PIC, jeśli odpowiedź idzie do drugiego kontrolera, pierwszy też musi dostać odpowiedź
    if (r->int_no >= 40)
    {
        outportb(0xA0, 0x20);
    }
    outportb(0x20, 0x20);
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}