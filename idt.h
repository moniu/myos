#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#pragma pack(push,1)
struct idt_gate {
   uint16_t offset_low;
   uint16_t selector;
   uint8_t zero;
   uint8_t type_attr;
   uint16_t offset_high;
} __attribute__((packed));
#pragma pack(pop)

#pragma pack(push,1)
struct idt_idtr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
#pragma pack(pop)

struct regs
{
    uint32_t gs, fs, es, ds;      /* pushed the segs last */
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    uint32_t int_no, err_code;    /* our 'push byte #' and ecodes do this */
    uint32_t eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

struct idt_gate idt[256];
struct idt_idtr _idtr;

void idt_make_entry(struct idt_gate *idt, uint32_t offset, uint16_t selector, uint8_t type_attr);
void idt_setup(void);




#endif