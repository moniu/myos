#include "timer.h"    
void terminal_display_time(int seconds)
{
    int old_column = terminal_column;
    int old_row = terminal_row;
    enum vga_color old_color = terminal_color;

    terminal_row = 0;
    terminal_column = 68;
    terminal_writestring("            ");

    terminal_row = 0;
    terminal_column = 68;
    terminal_setcolor(VGA_COLOR_LIGHT_MAGENTA);
    printf("%d",seconds);
    terminal_setcolor(old_color);

    terminal_row = old_row;
    terminal_column = old_column;

}
void timer_handler(struct regs *r)
{
    time_ticks++;
    if (time_ticks%18==0)
        terminal_display_time(time_ticks/18);
}


