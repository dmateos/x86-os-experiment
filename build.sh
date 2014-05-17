i686-elf-as src/boot.s -o bin/boot.o
i686-elf-gcc -c src/kernel.c -o bin/kernel.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/gdt.c -o bin/gdt.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/io.c -o bin/io.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T src/linker.ld -o bin/myos.bin -ffreestanding -O2 -nostdlib bin/boot.o bin/kernel.o bin/gdt.o bin/io.o -lgcc
cp bin/myos.bin isodir/boot/myos.bin
rm myos.iso
grub-mkrescue -o myos.iso isodir
