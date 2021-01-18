#ifndef KEYBOARD_H
#define KEYBOARD_H 

#include "regs.h"
#include "idt.h"
#include "terminal.h"
#include "irq.h"


struct keyboard_event_t
{
    uint8_t key;
    union
    {
        struct {
            uint8_t used:1; // 0 - puste zdarzenie 
            uint8_t keydown:1; // 0 - klawisz podniesiony, 1 - klawisz wsciśnięty
        };
        uint8_t flags;
    };
};

struct keyboard_queue_t
{  
    struct keyboard_event_t *events;
    int start;
    int end;
    int size;
    uint8_t full;
};

void keyboard_setup();
void keyboard_handler(struct regs *r);

struct keyboard_event_t keyboard_pop(void);
void keyboard_push(struct keyboard_event_t);
void keyboard_queue_handler(void (handler)(char));

#endif