export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
export DISPLAY=0:0

#i686-elf-as boot.s -o ofiles/boot.o
nasm -felf32 asm/boot.asm -o ofiles/boot.o
i686-elf-gcc -g -c kernel.c -o ofiles/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -g -c gdt.c -o ofiles/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -g -c idt.c -o ofiles/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -g -c irq.c -o ofiles/irq.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -g -c isr.c -o ofiles/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -g -c keyboard.c -o ofiles/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -g -c string.c -o ofiles/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -g -c terminal.c -o ofiles/terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -g -c timer.c -o ofiles/timer.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -g -c paging.c -o ofiles/paging.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -g -c memory.c -o ofiles/memory.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

i686-elf-gcc -g -T linker.ld -o monos.bin -ffreestanding -O2 -nostdlib ofiles/boot.o ofiles/paging.o ofiles/memory.o ofiles/timer.o ofiles/terminal.o ofiles/string.o ofiles/keyboard.o ofiles/isr.o ofiles/irq.o ofiles/idt.o ofiles/gdt.o ofiles/kernel.o -lgcc

qemu-system-i386 -monitor stdio -s -S -kernel monos.bin