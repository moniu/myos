#include "process.h"
#include "string.h"
#include "serial.h"

#include <stdint.h>

extern uint64_t time_ticks;

struct process processes[MAX_PROCESSES];
int current_process=0;
int last_process=-1;

void log_stack(struct process *p)
{
    int i;
    serial_printf("\n\n\n::BEGIN::\n");
    for (i=0;i<32;i++)
    {
        serial_printf("%h %h %h %h\n",p->stack[4*i+0],p->stack[4*i+1],p->stack[4*i+2],p->stack[4*i+3]);
    }
    serial_printf("::END::\n\n\n");

}

void log_regs(struct process *p)
{
    asm("cli");
    serial_printf("Printing regs of process %d\n",(int)p);
    serial_printf("EDI: %d\n", p->registers.EDI);
    serial_printf("ESI: %d\n", p->registers.ESI);
    serial_printf("EBP: %d\n", p->registers.EBP);
    serial_printf("ESP: %d\n", p->registers.ESP);
    serial_printf("EBX: %d\n", p->registers.EBX);
    serial_printf("EDX: %d\n", p->registers.EDX);
    serial_printf("ECX: %d\n", p->registers.ECX);
    serial_printf("EAX: %d\n", p->registers.EAX);
    serial_printf("CS: %d\n", p->registers.CS);
    serial_printf("EFLAGS: %d\n", p->registers.EFLAGS);
    serial_printf("EIP: %d\n", p->registers.EIP);

    serial_printf("\n\n");
    asm("sti");
}

void save_regs(struct process *p, struct regs *r)
{
    p->registers.EDI = r->edi;
    p->registers.ESI = r->esi;
    p->registers.EBP = r->ebp;
    p->registers.ESP = r->esp+20;
    p->registers.EBX = r->ebx;
    p->registers.EDX = r->edx;
    p->registers.ECX = r->ecx;
    p->registers.EAX = r->eax;
    p->registers.CS = r->cs;
    p->registers.EFLAGS = r->eflags;
    p->registers.EIP = r->eip;

    //serial_printf("%d\n",current_process);

    //log_regs(p);

    //printf(">>%d\n",p->registers.ESP);
}

void setup_processes()
{
    int i;
    struct process* p;
    for (i=0;i<MAX_PROCESSES;i++)
    {
        p = processes+i;
        p->state=free;
        memset(p->stack,0,STACK_SIZE);
        memset(&(p->registers),0,sizeof(p->registers));
    }
}

struct process* create_process(void* function,char* name)
{
    asm("cli");
    serial_printf("Tworze proces...\n");
    struct process* p = allocate_process();
    if (p==NULL)
    {
        serial_printf("No porazka panie...\n");
        return NULL;
    }

    memcpy(p->name,name,10);
    p->name[9]='\0';

    p->time_created = time_ticks;

    p->registers.EDI = 0;
    p->registers.ESI = 0;
    p->registers.EBP = 0;
    p->registers.EBX = 0;
    p->registers.EDX = 0;
    p->registers.ECX = 0;
    p->registers.EAX = 0;

    p->registers.ESP = (uint32_t) (p->stack+STACK_SIZE)-4;
    //p->registers.ESP = (uint32_t) p->stack;
    p->registers.EIP = (uint32_t) function;
    p->registers.CS = 0x08;
    p->registers.EFLAGS = 0x200;

    memset(p->stack,0,STACK_SIZE);

    p->state=ready;

    serial_printf("Proces utworzony!\n");
    asm("sti");
    return p;
}

struct process* allocate_process() // funkcja zaklepuje puste miejsce na proces
{
    int i;
    for (i=0;i<MAX_PROCESSES;i++)
    {
        if (processes[i].state==free)
        {
            processes[i].state=new;
            return processes+i;
        }
    }
    return NULL; // nie znaleziono
}

void switch_process(struct process* p)
{
    p->state = running;


    // czarna magia od @hry

    asm("push %0" : : "g"(p->registers.ESP));
    asm("pop %esp"); // co?

    asm("push %0" : : "g"(p->registers.EFLAGS));
    asm("push %0" : : "g"(p->registers.CS));
    asm("push %0" : : "g"(p->registers.EIP));

    asm("push %0" : : "g"(p->registers.EAX));
    asm("push %0" : : "g"(p->registers.ECX));
    asm("push %0" : : "g"(p->registers.EDX));
    asm("push %0" : : "g"(p->registers.EBX));
    asm("push %0" : : "g"(p->registers.ESP));
    asm("push %0" : : "g"(p->registers.EBP));
    asm("push %0" : : "g"(p->registers.ESI));
    asm("push %0" : : "g"(p->registers.EDI)); // nwo tutaj to wiadomo co się dzieje

    //printf("Rejestry:\n");
    //printf("ESP: %H    EFLAGS: %H    CS: %H    EIP: %H\n",p->registers.ESP,p->registers.EFLAGS,p->registers.CS,p->registers.EIP);
    //printf("EAX: %H    ECX: %H    EDX: %H    EBX: %H\n",p->registers.EAX,p->registers.ECX,p->registers.EDX,p->registers.EBX);
    //printf("EBP: %H    ESI: %H    EDI: %H\n",p->registers.EBP,p->registers.ESI,p->registers.EDI);

    asm("popa");
    asm("iret"); 
}

void kill_process(struct process* p)
{
    p->state=dead;

    memset(p->stack,0,STACK_SIZE);
    p->state=free;
}

void process_revolver(struct regs *r)
{
    
    if (processes[current_process].state==running)
        save_regs(processes+current_process, r);

    if (no_processes())
        return;
    while(processes[current_process].state==free)
    {
        if (++current_process>=MAX_PROCESSES)
            current_process=0;
    }

    //printf("%d ",current_process);
    current_process++;
    if (current_process>=MAX_PROCESSES) current_process=0;
    
    struct process* p;
    int legit=0;
    while(legit==0)
    {
        p = processes+current_process;
        switch (p->state)
        {
            case running:
            case ready:
                switch_process(p);
                legit=1;
                break;
            default:
                legit=0; //to jest problem??
                if (++current_process>=MAX_PROCESSES) current_process=0;
        }
    }
}

int no_processes()
{
    int i;
    for(i=0;i<MAX_PROCESSES;i++)
        if (processes[i].state!=free)
            return 0;
    return 1;
}

void print_processes()
{
    int i;
    for (i=0;i<MAX_PROCESSES;i++)
    {
        if (processes[i].state==free)
            continue;
        printf("Nr. %d >> name: %s, age: %d,   status:",i,processes[i].name,time_ticks-processes[i].time_created);
        switch (processes[i].state)
        {
        case ready:
            printf("READY\n");
            break;
        case running:
            printf("RUNNING\n");
            break;
        case new:
            printf("NEW\n");
            break;
        case dead:
            printf("DEAD\n");
            break;
        
        default:
            break;
        }
    }
}