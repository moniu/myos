#ifndef TERMINAL_H
#define TERMINAL_H 

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "irq.h"

extern const size_t VGA_WIDTH;
extern const size_t VGA_HEIGHT;

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};


 


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 

 
void terminal_initialize(void);

void terminal_setcolor(uint8_t color);
void terminal_putentryat(uint8_t c, uint8_t color, size_t x, size_t y);
void terminal_putchar(uint8_t c);
 
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_writestring_c(const char* data, enum vga_color color);
void terminal_scroll(void);
void terminal_clear(void);
void terminal_newline(void);
void terminal_process();

void terminal_command_putchar(char c);
void terminal_command_execute(void);

#endif