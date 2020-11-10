#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "string.c"
#include "terminal.c"
#include "keyboard.c"
#include "timer.c"
#include "gdt.c"
#include "idt.c"
#include "isr.c"
#include "irq.c"

uint64_t system_time=0;

void kernel_main(void) 
{
	terminal_initialize();
	terminal_setcolor(VGA_COLOR_LIGHT_GREY);

	asm("cli");
	gdt_setup();
	idt_setup();
	isr_setup();
	irq_setup();
	asm("sti");
	
	terminal_writestring_c("oooo     oooo                                     ooooooo      oooooo  \n",VGA_COLOR_LIGHT_GREEN);
	terminal_writestring_c(" 8888o   888    ooooooo   oo oooooo             o888   888o  o8     8o \n",VGA_COLOR_GREEN);
	terminal_writestring_c(" 88 888o8 88  888     888  888   888  ooooooooo 888     888 888ooooooo \n",VGA_COLOR_LIGHT_GREEN);
	terminal_writestring_c(" 88  888  88  888     888  888   888            888o   o888         888\n",VGA_COLOR_GREEN);
	terminal_writestring_c("o88o  8  o88o   88ooo88   o888o o888o             88ooo88   88oooooo88 \n",VGA_COLOR_LIGHT_GREEN);
                                                             
	//terminal_setcolor(VGA_COLOR_LIGHT_GREY);
	terminal_writestring("Ostatnio zaimplementowane:\n");
	terminal_writestring("  >  Tablica deskryptorow ( chyba dziala, thx ");
	terminal_writestring_c("@hry",VGA_COLOR_RED);
	terminal_writestring(" & ");
	terminal_writestring_c("@qazxsw",VGA_COLOR_LIGHT_BLUE);
	terminal_writestring(" )\n");
	terminal_writestring("  >  IDT\n");
	terminal_writestring("  >  ISR - poki co wyswietla tylko nazwe bledu\n");
	terminal_writestring("  >  IRQ - powiedzmy ze zegar i klawiatura dzialaja, powinienem dodac obsluge\n          shifta, taba i backspacea\n");
	terminal_writestring("  <  Teraz chyba powinienem zaczac zabawe z pamiecia\n");

	terminal_writestring_c("Prosze zerknac w prawy gorny rog oraz sprobowac uzyc klawiatury", VGA_COLOR_LIGHT_MAGENTA);

	terminal_writestring("\n\nPozdrawiam\n");

	terminal_writestring("Test klawiatury:\n>> ");

	while(1) // KERNEL LOOP
	{
		asm("hlt");
	}
	

}