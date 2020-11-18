#include <stdint.h>
#include "isr.h"

extern struct idt_gate idt[256];

const char* exception_messages[] = {
   "0: Division by zero",
   "1: Debug",
   "2: Non-maskable Interrupt",
   "Breakpoint",
   "Overflow",
   "Bound Range Exceeded",
   "Invalid Opcode",
   "Device Not Available",
   "Double Fault",
   "Coprocessor Segment Overrun",
   "Invalid TSS",
   "Segment Not Present",
   "Stack-Segment Fault",
   "General Protection Fault",
   "Page Fault",
   "Reserved",
   "x87 Floating-Point Exception",
   "Alignment Check",
   "Machine Check",
   "SIMD Floating-Point Exception",
   "Virtualization Exception",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Security Exception",
   "Reserved"
};

void isr_setup(void)
{
        terminal_writestring("ISR :: STARTING SETUP\n");

        idt_make_entry(idt+0,  (uint32_t)isr0,  0x08, 0x8E);
        idt_make_entry(idt+1,  (uint32_t)isr1,  0x08, 0x8E);
        idt_make_entry(idt+2,  (uint32_t)isr2,  0x08, 0x8E);
        idt_make_entry(idt+3,  (uint32_t)isr3,  0x08, 0x8E);
        idt_make_entry(idt+4,  (uint32_t)isr4,  0x08, 0x8E);
        idt_make_entry(idt+5,  (uint32_t)isr5,  0x08, 0x8E);
        idt_make_entry(idt+6,  (uint32_t)isr6,  0x08, 0x8E);
        idt_make_entry(idt+7,  (uint32_t)isr7,  0x08, 0x8E);

        idt_make_entry(idt+8,  (uint32_t)isr8,  0x08, 0x8E);
        idt_make_entry(idt+9,  (uint32_t)isr9,  0x08, 0x8E);
        idt_make_entry(idt+10, (uint32_t)isr10, 0x08, 0x8E);
        idt_make_entry(idt+11, (uint32_t)isr11, 0x08, 0x8E);
        idt_make_entry(idt+12, (uint32_t)isr12, 0x08, 0x8E);
        idt_make_entry(idt+13, (uint32_t)isr13, 0x08, 0x8E);
        idt_make_entry(idt+14, (uint32_t)isr14, 0x08, 0x8E);
        idt_make_entry(idt+15, (uint32_t)isr15, 0x08, 0x8E);

        idt_make_entry(idt+16, (uint32_t)isr16, 0x08, 0x8E);
        idt_make_entry(idt+17, (uint32_t)isr17, 0x08, 0x8E);
        idt_make_entry(idt+18, (uint32_t)isr18, 0x08, 0x8E);
        idt_make_entry(idt+19, (uint32_t)isr19, 0x08, 0x8E);
        idt_make_entry(idt+20, (uint32_t)isr20, 0x08, 0x8E);
        idt_make_entry(idt+21, (uint32_t)isr21, 0x08, 0x8E);
        idt_make_entry(idt+22, (uint32_t)isr22, 0x08, 0x8E);
        idt_make_entry(idt+23, (uint32_t)isr23, 0x08, 0x8E);

        idt_make_entry(idt+24, (uint32_t)isr24, 0x08, 0x8E);
        idt_make_entry(idt+25, (uint32_t)isr25, 0x08, 0x8E);
        idt_make_entry(idt+26, (uint32_t)isr26, 0x08, 0x8E);
        idt_make_entry(idt+27, (uint32_t)isr27, 0x08, 0x8E);
        idt_make_entry(idt+28, (uint32_t)isr28, 0x08, 0x8E);
        idt_make_entry(idt+29, (uint32_t)isr29, 0x08, 0x8E);
        idt_make_entry(idt+30, (uint32_t)isr30, 0x08, 0x8E);
        idt_make_entry(idt+31, (uint32_t)isr31, 0x08, 0x8E);

        terminal_writestring("ISR :: SETUP COMPLETED\n");
}

void _fault_handler(struct regs *r)
{
    if(r->int_no <32)
    {
        terminal_writestring_c("\n>>>>> Exception!",VGA_COLOR_RED);

        terminal_writestring_c("\n>>>>> ",VGA_COLOR_RED);
        terminal_writestring_c(exception_messages[r->int_no],VGA_COLOR_LIGHT_RED);


        terminal_writestring_c("\n>>>>> ",VGA_COLOR_RED);
        terminal_writestring_c("System halted...   \n",VGA_COLOR_LIGHT_RED);
    }
}
