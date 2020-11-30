global _idt_set
extern _idtr
_idt_set:
	lidt [_idtr]
	ret