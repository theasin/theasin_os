#!/bin/bash
if [ ! -d ./tmp ]; then
  mkdir -p ./tmp;
fi
i686-elf-gcc -std=gnu11 -ffreestanding -g -c startReal.s -o ./tmp/start.o --verbose -fpermissive
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c kernel.cpp -o ./tmp/kernel.o   -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive -Wno-write-strings -Wno-trigraphs
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c kbd.cpp -o ./tmp/kbd.o   -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive -Wno-write-strings -Wno-trigraphs
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c kutil.cpp -o ./tmp/kutil.o  -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive -Wno-write-strings -Wno-trigraphs
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c display.cpp -o ./tmp/display.o  -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive -Wno-write-strings -Wno-trigraphs
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c kb.cpp -o ./tmp/kb.o  -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive -Wno-write-strings -Wno-trigraphs
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c sound.cpp -o ./tmp/sound.o  -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive -Wno-write-strings -Wno-trigraphs
i686-elf-gcc -std=gnu++11 -ffreestanding -g -c v86.cpp -o ./tmp/v86.o  -fno-exceptions -fno-rtti -Wfatal-errors -fpermissive -Wno-write-strings -Wno-trigraphs
#i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld start.o kernel.o -o mykernel.elf --verbose -fno-use-linker-plugin
objcopy -O elf32-i386 -B i386 -I binary font.psf ./tmp/font.o
i686-elf-gcc -T linker.ld -o ./thos.bin -ffreestanding -O2 -nostdlib ./tmp/v86.o ./tmp/start.o ./tmp/kernel.o ./tmp/display.o ./tmp/kbd.o ./tmp/kutil.o ./tmp/kb.o ./tmp/sound.o ./tmp/font.o -lgcc -fno-use-linker-plugin -Wfatal-errors -fpermissive
