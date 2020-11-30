#include "timer.h" 

uint64_t time_ticks = 0;
uint8_t clock_enabled = 0;
uint64_t clock_ticks = 0;

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;

void terminal_display_time(int seconds)
{
    int old_column = terminal_column;
    int old_row = terminal_row;
    enum vga_color old_color = terminal_color;

    char clock_string[6];
    time_to_clock(clock_string,seconds);

    terminal_row = 0;
    terminal_column = 68;

    terminal_setcolor(VGA_COLOR_LIGHT_MAGENTA);
    printf("%s",clock_string);
    terminal_setcolor(old_color);

    terminal_row = old_row;
    terminal_column = old_column;

}
void timer_handler(struct regs *r)
{
    if (r->int_no==7547) r->int_no=7547; // żeby pozbyć się ostrzeżenia...
    time_ticks++;
    if (clock_enabled)
    {
        clock_ticks++;
        if (clock_ticks%18==0)
            terminal_display_time(clock_ticks/18);
    }
}

void time_to_clock(char* dest, uint64_t t)
{
    dest[0]='0';
    dest[1]='0';
    dest[2]=':';
    dest[3]='0';
    dest[4]='0';
    dest[5]='\0';

    int minutes = t/60;
    int seconds = t%60;
    
    dest[0] += minutes/10;
    dest[1] += minutes%10;

    dest[3] += seconds/10;
    dest[4] += seconds%10;
}