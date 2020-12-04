#include "terminal.h"
#include "art.c"
#include "process.h"
#include "timer.h"
#include "port.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

char myheap[0x0010000];

char command_buffer[128];
int command_buffer_size;

extern int clock_enabled;

void terminal_initialize(void) 
{
    outportb(0x3D4, 0x0A);
	outportb(0x3D5, 0x20);
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
    terminal_clear();

    
}

void terminal_clear(void)
{
    terminal_row = 0;
	terminal_column = 0;
    for (size_t y = 0; y < VGA_HEIGHT; y++) 
    {
		for (size_t x = 0; x < VGA_WIDTH; x++)
        {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

inline void terminal_newline(void) { terminal_putchar('\n');}
 
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
    asm("cli");
    if (c=='\n')
    {
        terminal_row++;
        terminal_column=0;
    }
    else if (c=='\b')
    {
        if (terminal_column == 0)
        {
            terminal_column = VGA_WIDTH-1;
            if (terminal_row!=0)
                terminal_row--;
        }
        else
            terminal_column--;

        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
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
    asm("sti");
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

void terminal_command_putchar(char c)
{
    switch(c)
    {
        case '\b':
            if(command_buffer_size>0)
            {
                command_buffer[--command_buffer_size] = '\0';
                terminal_putchar('\b');
            }
            break;
        case '\n':
            terminal_putchar('\n');
            terminal_command_execute();
            memset(command_buffer,0,128);
            command_buffer_size=0;
            terminal_writestring_c(" user > ",VGA_COLOR_GREEN);
            break;
        default:
            if(command_buffer_size<127)
            {
                terminal_putchar(c);
                command_buffer[command_buffer_size++] = c;
            }
            break;
    }
}

void terminal_command_execute(void)
{
    if (strcmpwc(command_buffer,"help")==0)
    {
        printf("Dostepne komendy:\n");
        printf(" help\n");
        printf(" clr\n");
        printf(" art\n");
        printf(" duzepepe\n");
        printf(" timer\n");
        printf(" generalnie\n");
    }
    else if (strcmpwc(command_buffer, "clr")==0)
    {
        terminal_clear();
    }
    else if (strcmpwc(command_buffer, "art")==0)
    {
        art_pepe2();
    }
    else if (strcmpwc(command_buffer, "duzepepe")==0)
    {
        art_pepe();
    }
    else if (strcmpwc(command_buffer, "timer1")==0)
    {
        terminal_writestring_c("Uruchamiam timer 1\n",VGA_COLOR_LIGHT_BLUE);
        if(create_process(timer1,"timer1"))
            terminal_writestring_c("SUKCES!\n",VGA_COLOR_LIGHT_GREEN);
        else
            terminal_writestring_c("PORAZKA!\n",VGA_COLOR_LIGHT_RED);

    }
    else if (strcmpwc(command_buffer, "timer2")==0)
    {
        terminal_writestring_c("Uruchamiam timer 2\n",VGA_COLOR_LIGHT_BLUE);
        if(create_process(timer2,"timer2"))
            terminal_writestring_c("SUKCES!\n",VGA_COLOR_LIGHT_GREEN);
        else
            terminal_writestring_c("PORAZKA!\n",VGA_COLOR_LIGHT_RED);
    }
    else if(strcmpwc(command_buffer, "processes")==0 )
    {
        print_processes();
    }
    else if (strcmpwc(command_buffer,"set")==0)
    {
        char *carg1 = memchr(command_buffer,' ',strlen(command_buffer));
        if (carg1==NULL)
        {
            terminal_writestring_c("Niewystarczajaca liczba argumentow\n",VGA_COLOR_LIGHT_RED);
            return;
        }
        carg1++;
        int arg1 = atoi(carg1);
        if (arg1<=0)
        {
            terminal_writestring_c("Nieprawidlowy argument\n", VGA_COLOR_LIGHT_RED);
            return;
        }
        char *carg2 = memchr(carg1,' ',strlen(carg1));
        if (carg2==NULL)
        {
            terminal_writestring_c("Niewystarczajaca liczba argumentow\n",VGA_COLOR_LIGHT_RED);
            return;
        }
        carg2++;
        int arg2 = atoi(carg2);

        printf("Ustawiam komorke %d na %d\n",arg1,arg2);
        myheap[arg1] = arg2;
    }
    else if (strcmpwc(command_buffer,"read")==0)
    {
        char *carg1 = memchr(command_buffer,' ',strlen(command_buffer));
        if (carg1==NULL)
        {
            terminal_writestring_c("Niewystarczajaca liczba argumentow\n",VGA_COLOR_LIGHT_RED);
            return;
        }
        carg1++;
        int arg1 = atoi(carg1);
        if (arg1<0)
        {
            terminal_writestring_c("Nieprawidlowy argument\n", VGA_COLOR_LIGHT_RED);
            return;
        }

        printf("Wartosc komorki %d wynosi %d\n",arg1,myheap[arg1]);
    }
    else if (strcmpwc(command_buffer,"")==0);
    else
    {
        printf("Nieznana komenda ");
        terminal_writestring_c(command_buffer,VGA_COLOR_LIGHT_RED);
        terminal_newline();
    }
    return;
}

void terminal_process()
{
    for(;;sleep(1))
        keyboard_queue_handler(terminal_command_putchar);
    
}