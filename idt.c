#include <stdint.h>
#include "idt.h"

struct idt_gate idt[256];
struct idt_idtr _idtr;

extern void _idt_set(void);

void idt_make_entry(struct idt_gate *idt, uint32_t offset, uint16_t selector, uint8_t type_attr)
{
    idt->offset_low = (offset & 0xFFFF);
    idt->offset_high = (offset >> 16) &0xFFFF;

    idt->selector = selector;
    idt->type_attr = type_attr;
    idt->zero = 0x00;
}
void idt_setup(void)
{
    _idtr.limit = (sizeof(struct idt_gate ) * 256) - 1;
    _idtr.base = (uint32_t)&idt;

    //Tutaj chyba można umieszczać wpisy do tablicy

    _idt_set();
}