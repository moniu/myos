#include <stdint.h>
#include "gdt.h"

struct gdt_entry gdt[3];
struct gdt_ptr _gp;

extern void _gdt_flush();

void gdt_make_entry(struct gdt_entry *gdt, uint32_t limit, uint32_t base, uint8_t access, uint8_t granularity)
{
    gdt->base_low = (base & 0xFFFF);
    gdt->base_middle = (base >> 16) & 0xFF;
    gdt->base_high = (base >> 24) & 0xFF;

    gdt->limit_low = (limit & 0xFFFF);
    gdt->granularity = ((limit >> 16) & 0x0F) | (granularity & 0xF0);

    gdt->access = access;

}

void gdt_setup()
{
    _gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    _gp.base = (uint32_t)&gdt;

    gdt_make_entry(gdt+0,0,0,0,0); //NULL
    gdt_make_entry(gdt+1,0,0xFFFFFFFF,0x9A,0xCF); //CODE
    gdt_make_entry(gdt+2,0,0xFFFFFFFF,0x92,0xCF); //DATA

    _gdt_flush();

}