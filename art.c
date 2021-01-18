#include "terminal.h"

void art_drawcolors(char* src)
{
    char c=*src;
    while(c!='\0')
    {

        switch(c)
        {
            case 'g':
                terminal_writestring_c("#",VGA_COLOR_GREEN);
                break;
            case 'G':
                terminal_writestring_c("#",VGA_COLOR_LIGHT_GREEN);
                break;
            case 'H':
                terminal_writestring_c("#",VGA_COLOR_WHITE);
                break;
            case 'h':
                terminal_writestring_c("#",VGA_COLOR_DARK_GREY);
                break;
            case 'r':
                terminal_writestring_c("#",VGA_COLOR_RED);
                break;
            case 'R':
                terminal_writestring_c("#",VGA_COLOR_LIGHT_RED);
                break;
            case 'C':
                terminal_writestring_c("#",VGA_COLOR_CYAN);
                break;
            case 'c':
                terminal_writestring_c("#",VGA_COLOR_LIGHT_CYAN);
                break;
            case 'B':
                terminal_writestring_c("#",VGA_COLOR_BLUE);
                break;
            case 'b':
                terminal_writestring_c("#",VGA_COLOR_LIGHT_BLUE);
                break;
            default:
                terminal_putchar(c);

        }

        src++;
        c=*src;
    }
}

void art_pepe(void)
{
    terminal_newline();
    art_drawcolors("    gggg gggg\n");
    art_drawcolors("   ggggggggggg\n");
    art_drawcolors("  ggggggggggggg\n");
    art_drawcolors(" gggHHHhHgHHHhH\n");
    art_drawcolors("gggggHHhhggHHhh");
    terminal_writestring("    feels good man\n");
    art_drawcolors("ggggggggggggggg\n");
    art_drawcolors("gggRRRRRRRRRRRR\n");
    art_drawcolors("gggRrrrrrrrrrrr\n");
    art_drawcolors("ggggRRRRRRRRRRR\n");
    art_drawcolors(" ggggggggggggg \n");
    art_drawcolors("  ggggggggggg \n");
    terminal_newline();
}