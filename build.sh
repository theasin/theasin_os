#!/bin/bash
pkill qemu-system-i386
if [ ! -d ./tmp ]; then
  mkdir -p ./tmp;
fi
i686-elf-gcc -std=gnu11 -ffreestanding -g -c start.s -o ./tmp/start.o --verbose -fpermissive
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c kernel.cpp -o ./tmp/kernel.o   -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c kbd.cpp -o ./tmp/kbd.o   -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c kutil.cpp -o ./tmp/kutil.o  -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c display.cpp -o ./tmp/display.o  -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c kb.cpp -o ./tmp/kb.o  -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive
#i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld start.o kernel.o -o mykernel.elf --verbose -fno-use-linker-plugin
i686-elf-gcc -T linker.ld -o ./thos.bin -ffreestanding -O2 -nostdlib ./tmp/start.o ./tmp/kernel.o ./tmp/display.o ./tmp/kbd.o ./tmp/kutil.o ./tmp/kb.o -lgcc -fno-use-linker-plugin -Wfatal-errors -fpermissive
