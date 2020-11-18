#ifndef IDT_H
#define IDT_H
#include "regs.h"
#include <stdint.h>
#include "string.h"
#include "terminal.h"

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





void idt_make_entry(struct idt_gate *idt, uint32_t offset, uint16_t selector, uint8_t type_attr);
void idt_setup(void);

extern void _idt_set(struct idt_idtr idtr);


#endif