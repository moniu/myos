prefix = "../opt/cross/bin/"
gcc = $(prefix)"i686-elf-gcc"
o = "ofiles/"
cfiles := gdt.c idt.c irq.c isr.c kernel.c keyboard.c process.c string.c terminal.c timer.c serial.c port.c mutex.c graphics.c math.c vga.c
asmfiles := boot.asm gdt.asm idt.asm irq.asm isr.asm setup.asm
asmfiles := $(addprefix asm/, $(asmfiles))
ofiles := $(cfiles:.c=.o)
ofiles := $(addprefix ofiles/, $(ofiles)) 

monos.bin: $(ofiles) ofiles/boot.o
	$(gcc) -g -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

ofiles/boot.o: $(asmfiles)
	nasm -felf32 $< -o $@

ofiles/kernel.o: kernel.c
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/gdt.o: gdt.c gdt.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/graphics.o: graphics.c graphics.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	
ofiles/idt.o: idt.c idt.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/irq.o: irq.c irq.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/isr.o: isr.c isr.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/keyboard.o: keyboard.c keyboard.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/math.o: math.c math.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/mutex.o: mutex.c mutex.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/process.o: process.c process.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/port.o: port.c port.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/serial.o: serial.c serial.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/string.o: string.c string.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/terminal.o: terminal.c terminal.h font.c
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/timer.o: timer.c timer.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ofiles/vga.o: vga.c vga.h
	$(gcc) -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

.PHONY: clean

clean:
	-rm $(ofiles)