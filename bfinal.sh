#!/bin/bash
sh ./build.sh
if [ ! -d ./isoroot/boot/grub ]; then
  mkdir -p isoroot/boot/grub;
fi
cp thos.bin isoroot/boot/thos.bin
cp grub.cfg isoroot/boot/grub/grub.cfg
grub-mkrescue ./isoroot/ -o os.iso
7z a theasinos.7z os.iso
