global _gdt_flush              
_gdt_flush:
	mov eax, [esp+4]
    lgdt [eax]
	jmp 0x8:complete_flush
complete_flush:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret