#!/bin/bash
pkill qemu-system-i386
sh ./build.sh
qemu-system-i386 -kernel ./thos.bin
