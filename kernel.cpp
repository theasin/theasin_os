#include "headers/all-headers.h" // include all needed headers

#define INT_DISABLE 0
#define INT_ENABLE 0x200

#if defined(__linux__)
    #error "You have to use a cross-compiler. Terminated!"
#elif !defined(__i386__)
    #error "You have to use x86-elf compiler. Terminated!"
#endif

bool isPrompt = true; // redundancy

extern "C" void init(void)
{
    u32 caddr;
    term_init(); // initialize VGA framebuffer: set everything from 0xb8000 to (whatever 0xb8000+(80*25*2) is) to 0
	font512(); // load VGA bitmap font, TODO: move it to new file
    enable_cursor(13, 16); // enable cursor for scanlines 13~16
	term_print("init: ready\n", 0x07);
    term_print("\nWelcome to TheasIN_OS ", 0x0f);
    term_print(verstr, 0x0f);
    term_print(" \"", 0x0f);
    term_print(relname, 0x0b);
    term_print("\"!\n", 0x0f);
    term_print("\nFor info on this release, enter ", 0x07);
    term_print("release-info", 0x0f);
    term_print(" command.\n", 0x07);
    term_print("\nTheasIN_OS is free software licensed under GNU GPL license version 2 and comes\n"
               "with ABSOLUTELY no warranty. For details, view LICENSE file in the source code.\n", 0x0f);
    prompt(); // start console
}

