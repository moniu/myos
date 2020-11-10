#include "terminal.h"
#include "string.h"



void terminal_initialize(void) 
{

    outportb(0x3D4, 0x0A);
	outportb(0x3D5, 0x20);
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
    if (c=='\n')
    {
        terminal_row++;
        terminal_column=0;
    }
    else
    {
	    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        terminal_column++;
    }
	if (terminal_column == VGA_WIDTH)
    {
		terminal_column = 0;
        terminal_row++;
    }
	if (terminal_row == VGA_HEIGHT)
    {

		terminal_row--;
        terminal_column = 0;
        terminal_scroll();
    }
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}
void terminal_writestring_c(const char* data, enum vga_color color)
{
    enum vga_color old = terminal_color;
    terminal_setcolor(color);
    terminal_writestring(data);
    terminal_setcolor(old);
}

void terminal_scroll(void)
{
    unsigned int i;
    unsigned int j;
    for (i=0;i<VGA_HEIGHT-1;i++)
    {
        for (j=0;j<VGA_WIDTH;j++)
            terminal_buffer[i*VGA_WIDTH+j] = terminal_buffer[i*VGA_WIDTH+j+VGA_WIDTH];
    }
    for (i=0;i<VGA_WIDTH;i++)
        terminal_buffer[VGA_WIDTH*(VGA_HEIGHT-1) + i] = vga_entry(' ', terminal_color);
    
    terminal_column = 0;
}

