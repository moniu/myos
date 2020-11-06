#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "string.c"
#include "terminal.c"
#include "gdt.c"
#include "idt.c"



void kernel_main(void) 
{
	terminal_initialize();
	terminal_setcolor(VGA_COLOR_LIGHT_BLUE);
	terminal_writestring(" __       __                       ______            \n");
	terminal_writestring("|  \\     /  \\                     /      \\           \n");
	terminal_writestring("| $$\\   /  $$  ______   _______  |  $$$$$$\\  _______ \n");
	terminal_writestring("| $$$\\ /  $$$ /      \\ |       \\ | $$  | $$ /       \\\n");
	terminal_writestring("| $$$$\\  $$$$|  $$$$$$\\| $$$$$$$\\| $$  | $$|  $$$$$$$\n");
	terminal_writestring("| $$\\$$ $$ $$| $$  | $$| $$  | $$| $$  | $$ \\$$    \\ \n");
	terminal_writestring("| $$ \\$$$| $$| $$__/ $$| $$  | $$| $$__/ $$ _\\$$$$$$\\\n");
	terminal_writestring("| $$  \\$ | $$ \\$$    $$| $$  | $$ \\$$    $$|       $$\n");
	terminal_writestring(" \\$$      \\$$  \\$$$$$$  \\$$   \\$$  \\$$$$$$  \\$$$$$$$ \n");
	terminal_writestring("\n\n");
	terminal_setcolor(VGA_COLOR_LIGHT_GREY);

	terminal_writestring("Ostatnio zaimplementowane:\n");
	terminal_writestring("  >  printf\n");

	terminal_writestring("Obecnie pracuje nad:\n");
	terminal_writestring("  >  Tablica deskryptorow (chyba dziala, pomogl @hry)\n");
	terminal_writestring("  >  Tablica przerwan (chyba dziala, trzeba napisac rutyny)\n");

	terminal_writestring("\n\nPozdrawiam\n");

	asm("cli");
	gdt_setup();
	terminal_writestring("GDT_DONE\n");
	idt_setup();
	terminal_writestring("IDT_DONE\n");
	asm("sti");
}