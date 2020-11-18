#include <stdint.h>
#include "idt.h"


struct idt_gate idt[256];
struct idt_idtr _idtr;


void idt_make_entry(struct idt_gate *idt_ent, uint32_t offset, uint16_t selector, uint8_t type_attr)
{
    idt_ent->offset_low = (offset & 0xFFFF);
    idt_ent->offset_high = (offset >> 16) & 0xFFFF;

    idt_ent->selector = selector;
    idt_ent->type_attr = type_attr;
    idt_ent->zero = 0x00;
}
void idt_setup(void)
{
    terminal_writestring("IDT :: STARTING SETUP\n");
    _idtr.limit = (sizeof(struct idt_gate ) * 256) - 1;
    _idtr.base = (uint32_t)&idt;

    memset(idt,0,sizeof(struct idt_gate)*256);
    terminal_writestring("IDT :: COMMITING CHANGES\n");

    _idt_set(_idtr);

    terminal_writestring("IDT :: SETUP COMPLETED\n");
}
