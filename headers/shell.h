#pragma once
#include "display.h"
#include "types.h"
#include "util.h"
#include "kbd.h"
#include "kbmap.h"
#ifndef SHELL_H
#define SHELL_H
extern "C" 
{
    extern bool isPrompt;
    bool ctrl, alt, super, shift, caps = false;
    extern int read_cmos_seconds(void);
    extern int read_key(int* c);
    //extern void aint();
    extern char kbd_us[];

    static void releaseInfo()
    {
        term_init();
        term_row = 0;
        term_col = 0;
        term_print("----------- Changelog for this release of TheasIN_OS (prealpha_sh) -------------", 0x0f);
        term_print("-> Added 'echo' command to demonstrate new functionality\n", 0x0a);
        term_print("-> Removed '0xdeath' command because it might scare some users\n", 0x04);
        term_print("----------------------- Stuff changed in recent releases -----------------------", 0x0f);
        term_print("-> Fixed a bug related to keyboard not working on most VMs and real PCs\n", 0x0a);
        term_print("-> Added command interpreter\n", 0x0a);
        term_print("-> Added the BSoD feature caused by pressing Ctrl-D, or 'halt' cmd\n", 0x0a);
        term_print("------------------------ Stuff to be done in the future ------------------------", 0x0f);
        term_print("-> Fix a bug with command not fully being erased\n", 0x0d);
        term_print("-> Add scrollback to display when it gets fully filled\n", 0x0d);
        term_print("-> more...\n", 0x08);
    }

    void actionMenu()
    {
        term_print("\ns - shut down, h - halt, c - cancel ", 0x0a);
        update_cursor(term_col, term_row);
        while (true)
        {
            char a = getCh();
            if (a == 's' || a == 'h' || a == 'c') term_putc(a, 0x0b);
            if(a == 's')
            {
                term_print("\nACPI support not yet implemented!\n", 0x0b);
                break;
            }
            if(a == 'h')
                halt(0x2, "HALT_MENU");
            if(a == 'c')
            {
                break;
            }
        }
    }

    static void parseCmd(char * cmd) 
    {
        extern void prompt();
        term_putc('\n', 0x07);
        if(!strcmp(cmd, "halt")) halt(0x0001, "HALT_CMD");
        else if(!strcmp(cmd, "mode13h")) { enterMode13h(); draw_x(); }
        else if(!strcmp(cmd, "mode12h")) { enterMode12h(); draw_x(); }
        else if(!strcmp(cmd, "0xdeath")) { /* death(); */  term_print("this cmd has been removed", 0x0e); }
        else if(!strcmp(cmd, "echo")) { term_print("Enter some text: ", 0x0f); char* a = getStr(); term_putc('\n', 0x07); term_print(a, 0x1f); }
        else if(!strcmp(cmd, "release-info")) { releaseInfo(); }
        else if(!strcmp(cmd, "2plus2")) { term_print("...is equal to 5", 0x0f); }
        else if(!strcmp(cmd, "crimea")) { term_print("...is Russian", 0x0f); }
        else if(!strcmp(cmd, "menu")) { actionMenu(); }
        else if(!strcmp(cmd, "")) {  }
        else { term_print("unknown cmd: ", 0x04); term_print(cmd, 0x04); }
        prompt();
    }

    void prompt()  
    {
        term_print("\n>\e", 0x03);
        isPrompt == true;
        // getCh();
        // term_print("By pressing 'q' you will wipe the entire memory of this VM. Are you sure?", 0x4f);
        // if(getCh() == 'q' || getCh() == 'Q') for(u32p a = (u32p)0xffffffff; a > (u32p)0; a--) *a = 0xdeafbead;
        // while(true) getCh();
        parseCmd(getStr());
    }
}
#endif