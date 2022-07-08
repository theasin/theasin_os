"C:\Program Files\gcc\bin\i686-elf-gcc" -std=gnu11 -ffreestanding -g -c start.s -o ./tmp/start.o --verbose
"C:\Program Files\gcc\bin\i686-elf-gcc" -std=gnu++11 -ffreestanding -g -c kernel.cpp -o tmp/kernel.o -Wall -Wextra -fno-exceptions -fno-rtti
"C:\Program Files\gcc\bin\i686-elf-gcc" -std=gnu++11 -ffreestanding -g -c kbd.cpp -o tmp/kbd.o  -Wall -Wextra -fno-exceptions -fno-rtti
"C:\Program Files\gcc\bin\i686-elf-gcc" -std=gnu++11 -ffreestanding -g -c kutil.cpp -o tmp/kutil.o -Wall -Wextra -fno-exceptions -fno-rtti
"C:\Program Files\gcc\bin\i686-elf-gcc" -std=gnu++11 -ffreestanding -g -c display.cpp -o tmp/display.o -Wall -Wextra -fno-exceptions -fno-rtti
"C:\Program Files\gcc\bin\i686-elf-gcc" -std=gnu++11 -ffreestanding -g -c mouse.cpp -o tmp/mouse.o -Wall -Wextra -fno-exceptions -fno-rtti
"C:\Program Files\gcc\bin\i686-elf-gcc" -std=gnu++11 -ffreestanding -g -c kb_legacy.cpp -o tmp/kb_legacy.o -Wall -Wextra -fno-exceptions -fno-rtti
"C:\Program Files\gcc\bin\i686-elf-gcc" -T linker.ld -o ./mykernel.bin -ffreestanding -O2 -nostdlib ./tmp/start.o ./tmp/kernel.o ./tmp/display.o ./tmp/kbd.o ./tmp/kutil.o ./tmp/mouse.o ./tmp/kb_legacy.o -lgcc -fno-use-linker-plugin 
"C:\Program Files\qemu\qemu-system-i386" -kernel mykernel.bin