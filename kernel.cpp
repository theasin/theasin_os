#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "./headers/types.h"
#include "./headers/kbmap.h"
#include "./headers/display.h"
#include "./headers/asm.h"
#include "./headers/math.h"
#include "./headers/shell.h"
// #include "./headers/serial.h"
#include "./headers/mouse.h"

#define INT_DISABLE 0
#define INT_ENABLE 0x200

#if defined(__linux__)
    #error "You have to use a cross-compiler. Terminated!"
#elif !defined(__i386__)
    #error "You have to use x86-elf compiler. Terminated!"
#endif

bool isPrompt = true;
bool ctrl, alt, super, shift, caps = false;

class BuildInfo {
    public:
        str version;
        str name;
};

extern "C" void kernel_main(void)
{
    BuildInfo binfo;
    binfo.name = "THOS";
    binfo.version = "prealpha-halt";
    term_init();
    enable_cursor(13, 16);
    update_cursor(0, 0);
    term_print("init: terminal initialized\n", 0x07);
    // enterModeGraph();
    // term_print("This is ", 0x07);
    // term_print(binfo.name, 0x0f);
    // term_print(" version ", 0x07);
    // term_print(binfo.version, 0x0f);
    // term_print("\n", 0x0f);
    // for(u8 a = 0x00; a<=0x0f; ++a){
    //     term_puti(0xdb, a);
    //     term_puti(0xdb, a);
    //     if(a == 0x07) { term_putc('\n', 0x07); }
    // }
    // term_print("\n", 0x07);
    // font512();
    // mouse_install();
    // draw_x();
    // prompt();
}

