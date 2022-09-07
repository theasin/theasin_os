#pragma once
#include "display.h"
#include "types.h"
#include "util.h"
#include "kbd.h"
#include "kbmap.h"
#include "lckscr.h"
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
        term_print("---------- Changelog for this release of TheasIN_OS (prealpha_shF1) ------------", 0x0f);
        term_print("-> Fixed a bug with command not fully being erased\n", 0x0a);
        term_print("----------------------- Stuff changed in recent releases -----------------------", 0x0f);
        term_print("-> Fixed a bug related to keyboard not working on most VMs and real PCs\n", 0x0a);
        term_print("-> Added the BSoD feature caused by pressing Ctrl-D, or 'halt' cmd\n", 0x0a);
        term_print("-> Removed '0xdeath' command because it might scare some users\n", 0x04);
        term_print("------------------------ Stuff to be done in the future ------------------------", 0x0f);
        term_print("-> Add scrollback to display when it gets fully filled\n", 0x0d);
        term_print("-> more...\n", 0x08);

    }


    void actionMenu()
    {
        term_print("\nh - halt, l - lock, c - cancel, w - wipe memory ", 0x0a);
        update_cursor(term_col, term_row);
        while (true)
        {
            char a = getCh();
            if (a == 'h' || a == 'c' || a == 'w') term_putc(a, 0x0b);
            if(a == 'h')
                halt(0x2, "HALT_MENU");
            if(a == 'c')
            {
                break;
            }
			if(a == 'l')
			{
				term_init();
				term_col = 0;
				term_row = 0;
				term_print(lockScreen, 0x0f);
		        update_cursor(81, 61);
				getCh();
				break;
			}
            if(a == 'w')
			{
                term_print("\nATTENTION! The contents of RAM will be erased. Type 'muriatic acid' to continue\n", 0x04);
                char * a = getStr();
                if(!strcmp(a, "muriatic acid")) { extern void wipe(); wipe(); } else { return; }
			}
        }
    }

    void wipe()
    {
        term_print("\nWriting memory: start address ffffffff, end address 0, step -1, value ffffffff\n", 0x0b);
        update_cursor(81, 61);
        for(u32p x = (u32p)0xffffffff; x > (u32p)0; x--) *x = 0xffffffff;
    }

    void memWipe()
    {
        term_col, term_row = 0, 0;
        for(int i = 0; i < 80; i++)
            for(int j = 0; j < 60; j++)
                term_putc((char)0x0, 0x4f);
        term_col, term_row = 0, 0;
        term_print("WARNING! You are about to wipe the contents of RAM on this PC\nAre you sure? (y/n) ", 0x4f);
        update_cursor(term_col, term_row);
        while(true)
        {
            char a = getCh();
            
            if (a == 'y' || a == 'n') term_putc(a, 0x4f);
            if(a == 'y')
            {
                term_print("\nWriting memory: start address ffffffff, end address 0, step -1, value ff\n", 0x4b);
                update_cursor(81, 61);
                for(u32p x = (u32p)0xffffffff; x > (u32p)0x0; x--) *x = 0xff;
            }
            if(a == 'n')
            {
                term_init();
                update_cursor(0, 0);
                term_col = 0;
                term_row = 0;
                term_print("(cancelled)", 0x07);
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
        else if(!strcmp(cmd, "echo")) { term_print("Enter some text: ", 0x0f); char* a = getStr(); term_putc('\n', 0x07); term_print(a, 0x1f); }
        else if(!strcmp(cmd, "release-info")) { releaseInfo(); }
        else if(!strcmp(cmd, "menu")) { actionMenu(); }
        else if(!strcmp(cmd, "clear")) { term_init(); term_col = 0; term_row = 0; }
        else if(!strcmp(cmd, "memwipe")) { memWipe(); }
        else if(!strcmp(cmd, "")) {  }
        else { term_print("unknown cmd: ", 0x04); term_print(cmd, 0x04); }
        prompt();
    }

    void prompt()  
    {
        term_print("\n>\x01", 0x03);
        isPrompt == true;
        // getCh();
        // term_print("By pressing 'q' you will wipe the entire memory of this VM. Are you sure?", 0x4f);
        // if(getCh() == 'q' || getCh() == 'Q') for(u32p a = (u32p)0xffffffff; a > (u32p)0; a--) *a = 0xdeafbead;
        // while(true) getCh();
        parseCmd(getStr());
    }
}
#endif
