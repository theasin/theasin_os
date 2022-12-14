/* 
* This (along with all other included headers/linked files) is a part of TheasIN_OS
*
* TheasIN_OS is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
* 
* TheasIN_OS is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with TheasIN_OS.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright (c) Konstantin Mochalov "TheasIN", 2022
*/

#include "headers/all-headers.h" // include all needed headers

#define INT_DISABLE 0
#define INT_ENABLE 0x200

#if defined(__linux__)
    #error "You have to use a cross-compiler. Terminated!"
#elif !defined(__i386__)
    #error "You have to use x86-elf compiler. Terminated!"
#endif

bool isPrompt = true; // redundancy

extern "C" void init(u32 multiboot)
{
    mbootAddr = (u32p)(*((int*)0x7e00));
    term_init(); // initialize VGA framebuffer: set everything from 0xb8000 to (whatever 0xb8000+(80*25*2) is) to 0
    vbe_init();
	// font512(); // load VGA bitmap font, TODO: move it to new file
    // enable_cursor(13, 16); // enable cursor for scanlines 13~16
	term_print("init: ready\n", 0x07);
    term_print("\nWelcome to TheasIN_OS ", 0x0f);
    term_print(verstr, 0x0f);
    term_print(" \"", 0x0f);
    term_print(relname, accent);
    term_print("\"!\n", 0x0f);
    term_print("\nFor info on this release, enter ", 0x07);
    term_print("release-info", 0x0f);
    term_print(" command.\n\nFor help on commands, enter ", 0x07);
    term_print("help", 0x0f);
    term_print(" command.\n", 0x07);
    term_print("\nTheasIN_OS is free software licensed under GNU GPL license version 2 and comes\n"
               "with ABSOLUTELY no warranty. For details, view LICENSE file in the source code.\n\n", 0x0f);
    term_print("\nRunning at resolution of ", 0x07);
    term_printnum(res_x, 0x0f); term_putc('*', 0x0f); term_printnum(res_y, 0x0f); term_putc('@', 0x0f); term_printnum(bpp, 0x0f);term_print("bpp ", 0x0f); term_print("(defined in code)\n\n", 0x08);
    // term_printhex();
    // playSound(1000);
    prompt(); // start console
}

