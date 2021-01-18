#include "process.h"
#include "string.h"
#include "serial.h"

#include <stdint.h>

struct process processes[MAX_PROCESSES];
int current_process=0;
int last_process=-1;

extern uint8_t stack_top;

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
        asm("sti");
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
        if (processes[i].state==free || processes[i].state==dead)
        {
            processes[i].state=new;
            return processes+i;
        }
    }
    return NULL; // nie znaleziono
}

void switch_process(struct process* p)
{
    // wspomagałem się tą stroną: 
    // http://www.osdever.net/tutorials/view/multitasking-howto

    p->state = running;

    asm("push %0" : : "g"(p->registers.ESP));
    asm("pop %esp");

    asm("push %0" : : "g"(p->registers.EFLAGS));
    asm("push %0" : : "g"(p->registers.CS));
    asm("push %0" : : "g"(p->registers.EIP)); // to zjada iret

    asm("push %0" : : "g"(p->registers.EAX));
    asm("push %0" : : "g"(p->registers.ECX));
    asm("push %0" : : "g"(p->registers.EDX));
    asm("push %0" : : "g"(p->registers.EBX));
    asm("push %0" : : "g"(p->registers.ESP));
    asm("push %0" : : "g"(p->registers.EBP));
    asm("push %0" : : "g"(p->registers.ESI));
    asm("push %0" : : "g"(p->registers.EDI)); // to zjada popa

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

    //memset(p->stack,0,STACK_SIZE);
    //p->state=free;
}

void kill_process_nr(int index)
{
    kill_process(processes+index);
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
    if (current_process>=MAX_PROCESSES)
        current_process=0;
    
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
        printf("ID: %d >> name: %s, age: %d, status:",i,processes[i].name,time_ticks-processes[i].time_created);
        switch (processes[i].state)
        {
        case ready:
            terminal_writestring_c("READY\n",VGA_COLOR_GREEN);
            break;
        case running:
            terminal_writestring_c("RUNNING\n",VGA_COLOR_LIGHT_GREEN);
            break;
        case new:
            terminal_writestring_c("NEW\n",VGA_COLOR_LIGHT_BLUE);
            break;
        case dead:
            terminal_writestring_c("DEAD\n",VGA_COLOR_RED);
            break;
        
        default:
            break;
        }
    }
}

void process_end() // najlepiej wrzucić to na koniec każdego procesu
{
    kill_process_nr(current_process);
    asm("push %0" : : "g"(&stack_top));
    asm("pop %esp");
    while(1)
        asm("hlt");
}