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
#include "process.h"
#include "serial.h"
#include "graphics.h"
#include "vga.h"


uint64_t system_time=0;

void kernel_main(void) 
{
	terminal_initialize();
	vga_initialize();
	terminal_setcolor(VGA_COLOR_LIGHT_GREY);

	asm("cli");

	gdt_setup();
	idt_setup();
	isr_setup();
	irq_setup();
	setup_processes();
	keyboard_setup();
	init_serial();
	asm("sti");
	//paging_setup();

	terminal_writestring_c("\n\n\nSystem will start soon",VGA_COLOR_DARK_GREY);
	sleep(SECOND/3);
	terminal_writestring_c(".",VGA_COLOR_DARK_GREY);
	sleep(SECOND/3);
	terminal_writestring_c(".",VGA_COLOR_DARK_GREY);
	sleep(SECOND/3);
	terminal_writestring_c(".",VGA_COLOR_DARK_GREY);
	//sleep(SECOND*2);


	terminal_clear();
	terminal_newline();
	terminal_writestring_c("  __  __              ____      \n",VGA_COLOR_LIGHT_GREEN);
	terminal_writestring_c(" |  \\/  |            / __ \\     \n",VGA_COLOR_GREEN);
	terminal_writestring_c(" | \\  / | ___  _ __ | |  | |___ \n",VGA_COLOR_LIGHT_GREEN);
	terminal_writestring_c(" | |\\/| |/ _ \\| '_ \\| |  | / __|\n",VGA_COLOR_GREEN);
	terminal_writestring_c(" | |  | | (_) | | | | |__| \\__ \\\n",VGA_COLOR_LIGHT_GREEN);
	terminal_writestring_c(" |_|  |_|\\___/|_| |_|\\____/|___/\n",VGA_COLOR_GREEN);
                                                            

	terminal_writestring("Test konsoli:\n");

	terminal_writestring_c(" user > ",VGA_COLOR_GREEN);

	create_process(terminal_process,"terminal");
	while(1) // KERNEL LOOP
	{
		serial_printf("%d",5);
		asm("hlt");
	}

	
}