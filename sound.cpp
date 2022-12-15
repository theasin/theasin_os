// pcspkr impl from https://wiki.osdev.org/PC_Speaker
#include "headers/types.h"
#include "headers/util.h"

extern "C"
{
    void playSound(u32 freq) {
        u32 Div;
        u8 tmp;
        Div = 1193180 / freq;
        outb(0x43, 0xb6);
        outb(0x42, (u8) (Div) );
        outb(0x42, (u8) (Div >> 8));
        tmp = inb(0x61);
        if (tmp != (tmp | 3)) {
            outb(0x61, tmp | 3);
        }
    }
    void stopSound(void) {
        uint8_t tmp = inb(0x61) & 0xFC;
        outb(0x61, tmp);
    }
    
    void beep(void) {
        playSound(1000);
        // timer_wait(10);
        // nosound();
    }
}