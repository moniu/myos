    mov ax,0x0013
    int 0x10

%include "asm/gdt.asm"
%include "asm/idt.asm"
%include "asm/isr.asm"
%include "asm/irq.asm"