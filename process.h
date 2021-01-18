#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#include "regs.h"

#define STACK_SIZE 0x2000
#define MAX_PROCESSES 4

struct process
{
    struct
    {
        uint32_t EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
        uint32_t CS, EFLAGS, EIP;
    } registers;
    uint8_t stack[STACK_SIZE];
    char name[10];
    uint8_t id;
    uint32_t time_created;
    enum
    {
        free,
        new,
        ready,
        running,
        dead
    } state;
};


void setup_processes();
void log_stack(struct process *p);
void save_regs(struct process *p, struct regs *r);
struct process* create_process(void* function, char* name);
struct process* allocate_process();
void switch_process(struct process* p);
void kill_process(struct process* p);
void kill_process_nr(int index);
void process_end();



int no_processes();
void process_revolver(struct regs *r);

void print_processes();


#endif