#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"

#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "string.h"
#include "terminal.h"
#include "keyboard.h"
#include "timer.h"
#include "paging.h"
#include "process.h"
#include "serial.h"

uint64_t system_time=0;
extern int time_ticks;

void kernel_main(void) 
{
	terminal_initialize();
	terminal_setcolor(VGA_COLOR_LIGHT_GREY);

	asm("cli");
	gdt_setup();
	idt_setup();
	isr_setup();
	irq_setup();
	setup_processes();
	keyboard_setup();
	init_serial();
	//paging_setup();

	terminal_writestring_c("\n\n\nSystem will start soon...\n",VGA_COLOR_DARK_GREY);

	//sleep(180);
	terminal_clear();
	terminal_newline();
	terminal_writestring_c("oooo     oooo                                     ooooooo      oooooo  \n",VGA_COLOR_LIGHT_GREEN);
	terminal_writestring_c(" 8888o   888    ooooooo   oo oooooo             o888   888o  o8     8o \n",VGA_COLOR_GREEN);
	terminal_writestring_c(" 88 888o8 88  888     888  888   888  ooooooooo 888     888 888ooooooo \n",VGA_COLOR_LIGHT_GREEN);
	terminal_writestring_c(" 88  888  88  888     888  888   888            888o   o888         888\n",VGA_COLOR_GREEN);
	terminal_writestring_c("o88o  8  o88o   88ooo88   o888o o888o             88ooo88   88oooooo88 \n",VGA_COLOR_LIGHT_GREEN);
                                                             
	terminal_newline();
	terminal_newline();


	create_process(terminal_process,"terminal");
	terminal_writestring("Test konsoli:\n");

	terminal_writestring_c(" user > ",VGA_COLOR_GREEN);
	asm("sti");



	while(1) // KERNEL LOOP
	{
		//keyboard_queue_handler(terminal_command_putchar);
		
		asm("hlt");
	}

	
}