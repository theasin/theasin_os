#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "./headers/types.h"
#include "./headers/kbmap.h"
#include "./headers/display.h"
#include "./headers/asm.h"
#include "./headers/math.h"
#include "./headers/shell.h"

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
    binfo.name = "GensoOS";
    binfo.version = "prealpha-post-refactor";
    term_init();
    term_print("This is ", 0x07);
    term_print(binfo.name, 0x0f);
    term_print(" version ", 0x07);
    term_print(binfo.version, 0x0f);
    term_print("\n", 0x0f);
    enable_cursor(13, 16);
    for(uint8_t a = 0x01; a<=0x0f; a = a + 0x01){
        term_print("@", a);
        term_print(" ", 0x07);
    }
    term_print("\n", 0x0f);
    setAH(0);
    for(int i = 0; i < VGA_COLS; i++)
    {
        for(int j = 0; j < VGA_ROWS; j++)
        {
            term_putc(i, j);
        }
    }
    prompt();
}

