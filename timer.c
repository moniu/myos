#include "timer.h" 

uint32_t time_ticks = 0;


extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;

extern uint8_t stack_top;

struct mutex_t timer_mutex = {0,-1};

void terminal_display_time(int seconds,int x, int y)
{
    mutex_get(&timer_mutex);
    int old_column = terminal_column;
    int old_row = terminal_row;
    enum vga_color old_color = terminal_color;

    char clock_string[6];
    time_to_clock(clock_string,seconds);

    terminal_row = x;
    terminal_column = y;

    terminal_setcolor(VGA_COLOR_LIGHT_MAGENTA);
    printf("%s",clock_string);
    terminal_setcolor(old_color);

    terminal_row = old_row;
    terminal_column = old_column;
    mutex_free(&timer_mutex);

}
void timer_handler(struct regs *r)
{
    (void)r;
    time_ticks++;
    process_revolver(r);

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

void sleep(uint32_t ticks)
{
    uint64_t before = time_ticks+1;
    while(time_ticks<=(before+ticks))
    {
        asm("pause");
    }
    return;
}

void timer1()
{
    uint32_t clock_ticks = 0;
    for(;;)
    {
        sleep(IRQ_FREQUENCY);
        clock_ticks++;
        if (clock_ticks>=3600) clock_ticks=0;
        terminal_display_time(clock_ticks,0, VGA_WIDTH-6);
    }
}
void timer2()
{
    uint32_t clock_ticks = 0;
    for(;clock_ticks<10;)
    {
        sleep(IRQ_FREQUENCY);
        clock_ticks++;
        if (clock_ticks>=3600) clock_ticks=0;
        terminal_display_time(clock_ticks,1, VGA_WIDTH-6);
    }

    process_end();
    
}