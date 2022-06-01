#!/bin/bash
i686-elf-gcc -std=gnu99 -ffreestanding -g -c start.s -o start.o 
i686-elf-c++ -std=gnu99 -ffreestanding -g -c kernel.c -o kernel.o --verbose
i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld start.o kernel.o -o mykernel.elf --verbose -fno-use-linker-plugin