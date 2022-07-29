#!/bin/bash
pkill qemu-system-i386
i686-elf-gcc -std=gnu2x -ffreestanding -g -c start.s -o ./tmp/start.o --verbose
i686-elf-gcc -std=gnu++20 -ffreestanding -g -c kernel.cpp -o ./tmp/kernel.o  -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-gcc -std=gnu++20 -ffreestanding -g -c kbd.cpp -o ./tmp/kbd.o  -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-gcc -std=gnu++20 -ffreestanding -g -c kutil.cpp -o ./tmp/kutil.o -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-gcc -std=gnu++20 -ffreestanding -g -c display.cpp -o ./tmp/display.o -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-gcc -std=gnu++20 -ffreestanding -g -c kb.cpp -o ./tmp/kb.o -Wall -Wextra -fno-exceptions -fno-rtti
#i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld start.o kernel.o -o mykernel.elf --verbose -fno-use-linker-plugin
i686-elf-gcc -T linker.ld -o ./mykernel.bin -ffreestanding -O2 -nostdlib ./tmp/start.o ./tmp/kernel.o ./tmp/display.o ./tmp/kbd.o ./tmp/kutil.o ./tmp/kb.o -lgcc -fno-use-linker-plugin 
cp mykernel.bin isoroot/boot/mykernel.bin
grub-mkrescue ~/os/isoroot/ -o os.iso
7z a theasinos.7z os.iso