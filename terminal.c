#include "terminal.h"
#include "string.h"



void terminal_initialize(void) 
{
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

void terminal_draw_art(void)
{
    if (terminal_column!=0)
        terminal_putchar('\n');
    unsigned int old_color = terminal_color;

    char art[16][18] = {
        "0000222222000",
        "2222222222222",
        "0077777777770",
        "0777777777777",
        "0771777771777",
        "7771777771777",
        "7777777777777",
        "0774777774777",
        "0777444447777",
        "0777777777777",
        "0077777777770",
        "0007700007700",
        "0007700007700",
        "0007700007700",
        "0077700077700",
        "0777700777700"
    };
    unsigned int x,y;
    char c;
    for (y=0;y<16;y++)
    {
        for(x=0;x<17;x++)
        {
            c = art[y][x];
            if (c>='A' && c<='F')
                c-='A' + 10;
            else
                c-='0';
            terminal_setcolor(c);
            terminal_putchar(219);
        }
        terminal_color = old_color;
        terminal_putchar('\n');
    }
    terminal_color = old_color;
}