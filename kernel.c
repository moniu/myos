#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "string.c"
#include "terminal.c"
 
void kernel_main(void) 
{
	terminal_initialize();
	terminal_writestring("Welcome!\n");
	terminal_draw_art();
	printf("TEST1: %d\nTEST2: %c\nTEST3: %s\n",-123,'h',"Aezakmi");
}