#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "headers/types.h"
#include "headers/kbmap.h"
#include "headers/display.h"
#include "headers/asm.h"
#include "headers/math.h"
#include "headers/shell.h"
#include "headers/util.h"

#define INT_DISABLE 0
#define INT_ENABLE 0x200

#if defined(__linux__)
    #error "You have to use a cross-compiler. Terminated!"
#elif !defined(__i386__)
    #error "You have to use x86-elf compiler. Terminated!"
#endif

bool isPrompt = true;

class BuildInfo {
    public:
        str version;
        str name;
};

extern "C" void kernel_main(void)
{
    term_init();
	term_print("init: terminal initialized\n", 0x07);
	font512();
	term_print("init: font updated\n", 0x07);
    // halt(0xffff, "Something has gone wrong");
    // enterMode13h();
    enable_cursor(13, 16);
	term_print("init: enabled cursor\n", 0x07);
    // enterMode13h();
	// draw_x();
	term_print("init: ready\n", 0x07);
    term_print("\nWelcome to TheasIN_OS!\n", 0x0f);
    term_print("\nFor info on this release, enter ", 0x07);
    term_print("release-info", 0x0f);
    term_print(" command.\n", 0x07);
    // term_print("\nWARNING! You are running an UNREGISTERED version of TheasIN_OS\n", 0x0c);
    prompt();
}

