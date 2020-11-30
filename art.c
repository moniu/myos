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
                terminal_writestring_c("#",VGA_COLOR_LIGHT_GREY);
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
    art_drawcolors("          gggggggg     gggggg\n");
    art_drawcolors("         gGGGGGGGGgg ggGGGGGGg\n");
    art_drawcolors("        gGGGGGGGGGGGgGGGGGGGGGg\n");
    art_drawcolors("       gGGGGGGGgggGGGgGGGGGGGGGg\n");
    art_drawcolors("       gGGGGgggGGGgggGgGGGggggGg\n");
    art_drawcolors("      gGGGggGGGGGGGGgggGggGGGGgg\n");
    art_drawcolors("     gGGGGGGGGGGGGGGGGGgGGGGGGGGggg\n");
    art_drawcolors("    gGGGGGGGGGGGGGggggggGGGGGggggGGg\n");
    art_drawcolors("    gGGGGGGGGGgggggGGGggggGGggGGggGGg\n");
    art_drawcolors("   ggGGGGGGGgggGGGGGGGGGGgGGGGGGGGggg\n");
    art_drawcolors("  gGGGGGGGGGGGGGGgggggggggGGggggggggg\n");
    art_drawcolors(" gGGGGGGGGGGhhhhh hhhhHHHhhhhHhhhhhHHHh\n");
    art_drawcolors(" gGGGGGGGGGGhHHHHHHhHhhhHHhHHHHHhhhHhHHHh\n");
    art_drawcolors("gGGGGGGGGGGGGhHHHhhhhHhhhhHHHHhhhhhhhgg\n");
    art_drawcolors("GGGGGGGGGGGGGgggggggggGGGggggggggGGGg\n");
    art_drawcolors("GGGGGGGGGGGGGGGGgGGGGGgGGGGGGGGGGGGg\n");
    art_drawcolors("GGGGGGGGGGGGGGGGGGGGggGGGGgGGGGGGgg\n");
    art_drawcolors("GGGGGGGGGGGGGGGGGGggGGGGGGGggggggg\n");
    art_drawcolors("GGGGGGGGGGGGGGGGggGGGGGGGGGGgGGGGGg\n");
    art_drawcolors("GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGg\n");
    art_drawcolors("GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGg\n");
    art_drawcolors("GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGg\n");
    art_drawcolors("GGGGGGGGGGGrrrrrrrrrGGGGGGGGGGGGGGrr\n");
    art_drawcolors("GGGGGGGGGGrRRRRRRRRrrrrrrrrrrrrrrrRRr\n");
    art_drawcolors("GGGGGGGGGrRRrrrrrrrRRRRRRRRRRRRRRRRRr\n");
    art_drawcolors("GGGGGGGGGrRRRRRRRRRrrrrrrrrrrrrrrrrr\n");
    art_drawcolors("GGGGGGGGGGrrrrrrrrRRRRRRRRRRRRRRRRRRr\n");
    art_drawcolors("GGGGGGGGGGGGGGGGGGrrrrrrrrrrrrrrrrrr\n");
    art_drawcolors("GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGg\n");
    art_drawcolors("bbGGGGGGGGGGGGGGGGGGGGGGGGGGGgg\n");
    art_drawcolors("BbbGGGGGGGGGGGGGGGGGGGGGGGGgg\n");
    art_drawcolors("BBBbbbGGGGGGGGGGGGGGGGGGGGg\n");
    art_drawcolors("BBBBBBbbbGGGGGGGGGGGGGGGgg\n");
    art_drawcolors("BBBBBBBBBbbbbbbbbbbbbbbbBBb\n");
    art_drawcolors("BBBBBBBBBBBBBBBBBBBBBBBBBBBbb\n");
    art_drawcolors("BBBBBBBBBBBBBBBBBBBBBBBBBBBBb\n");
    art_drawcolors("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBb\n");
    // a psia kość za wysoki
    // feels bad
}

void art_pepe2(void)
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