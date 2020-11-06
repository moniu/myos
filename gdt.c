#include <stdint.h>
#include "gdt.h"

unsigned long long gdt[5];
struct gdt_ptr _gp;

extern void _gdt_flush(struct gdt_ptr* ptr);
/*
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
    _gp.limit = sizeof(gdt);
    _gp.base = (uint32_t)(gdt);

    gdt_make_entry(gdt+0,0,0,0,0); //NULL
    gdt_make_entry(gdt+1,0,0xFFFFFFFF,0x9A,0xCF); //KERNEL CODE
    gdt_make_entry(gdt+2,0,0xFFFFFFFF,0x92,0xCF); //KERNEL DATA
    gdt_make_entry(gdt+3,0,0xFFFFFFFF,0xFA,0xCF); //USER DATA
    gdt_make_entry(gdt+4,0,0xFFFFFFFF,0xF2,0xCF); //USER DATA

    terminal_writestring("GDT");
    _gdt_flush(&_gp);
    terminal_writestring("GDT");

}

*/

void gdt_setup()
{
    _gp.limit = sizeof(gdt);
    _gp.base = (uint32_t)(gdt);

    gdt[0] = 0x0000000000000000;
    gdt[1]=0x00CF9A000000FFFF;
    gdt[2]=0x00CF92000000FFFF;
    gdt[3]=0x00CFFA000000FFFF;
    gdt[4]=0x00CFF2000000FFFF;
    _gdt_flush(&_gp);

    
}