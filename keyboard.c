#include "keyboard.h"
#include "irq.h"

void keyboard_handler(struct regs *r)
{
    unsigned char scancode;
    scancode = inportb(0x60);
    if (scancode & 0x80) // Klawisz podniesiony
    {
        ;
    }
    else    //Klawisz wciśnięty
    {
        terminal_putchar(kbdus[scancode]);
    }
}


