#!/bin/bash
pkill qemu-system-i386
bash ./biso.sh
qemu-system-i386 -cdrom ./os.iso
