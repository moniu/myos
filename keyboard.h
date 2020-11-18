#ifndef KEYBOARD_H
#define KEYBOARD_H 

#include "regs.h"
#include "idt.h"
#include "terminal.h"
#include "irq.h"


struct keyboard_event
{
    uint8_t key;
    union
    {
        struct {
            char lshift:1;
            char lctrl:1;
            char lalt:1;
            char rshift:1;
            char rctrl:1;
            char ralt:1;
        };
        uint8_t flags;
    };
};

struct keyboard_node
{
    struct keyboard_event event;
    struct keyboard_node *next;
};

struct keyboard_queue
{  
    struct keyboard_event event;
};

void keyboard_handler(struct regs *r);

#endif