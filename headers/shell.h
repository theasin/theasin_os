#pragma once
#include "display.h"
#include "types.h"
#include "util.h"
#include "kbd.h"
#include "kbmap.h"
#include "types.h"
#include "lckscr.h"
#include "release-info.h"
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
    char *cmd_tok[32];

    static int segfault() // dereference the NULL pointer!
    {
        char * a = NULL;
	    *a = 0;
    }

    void string_split (char *src, char *delim, char *destv[], int destc, int *cc) // split a string into an array of strings (up to `destc` entries)
    {
	    char *ptr = strtok(src, delim);
        int curc = 0; // current array entry in destv array
	    while (ptr != NULL && curc < destc)
        {
            destv[curc++] = ptr;
            ptr = strtok(NULL, delim);
        }
        *cc = curc;
    }

    static void releaseInfo()
    {
        term_init();
        term_row = 0;
        term_col = 0;
        term_print("-- Changelog for this release of TheasIN_OS (", 0x0f);
        term_print(verstr, 0x0f);
        term_print(" \"", 0x0f);
        term_print(relname, 0x0f);
        term_print("\") --\n", 0x0f);
        term_print(changelog_added, 0x0a);
        term_print("-- Stuff to be done in the future --\n", 0x0f);
        term_print(changelog_tba, 0x0d);
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
                phalt();
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

    void epilepsy() {
        term_print("\nWARNING! You are about to trigger epilepsy mode with fast blinking colors which is MOST PROBABLE to trigger seizures for people who are prone to it.", 0x0e);
        term_print("\nEnter \"do as i say\" to continue (graphics mode will be switched): ", 0x0d);
        str conf = getStr();
        if(!strcmp(conf, "do as i say")) 
        {
            enterMode13h();
            u8 col = 0;
            while(true) 
            {
                int offs = 0;
                for(u8p i = (u8p)0xa0000; i < (u8p)0xc0000; i++)
                {
                    *i = col;
                    if(i == (u8p)0xbffff && col < 0x20) { col++; } else if (col>=0x20) { col=0x00; }
                }
                for (int a = 0; a < 128; a++) { outb(0x80, 0x00); }
            }
        } else
            return;
    }

    static void parseCmd(char * cmd) 
    {
        cmd_tok[0] = ""; // clear 1st element of array before using it, will prevent junk appearing in the future
        extern void prompt();
        int cmd_argc;
        string_split(cmd, " ", cmd_tok, 32, &cmd_argc);
        term_putc('\n', 0x07);
        if(!strcmp(cmd, "halt")) phalt();
        else if(!strcmp(cmd_tok[0], "mode13h")) { enterMode13h(); draw_x(); }
        else if(!strcmp(cmd_tok[0], "mode12h")) { enterMode12h(); draw_x(); }
        else if(!strcmp(cmd_tok[0], "echo")) { term_print("Enter some text: ", 0x0f); char* a = getStr(); term_putc('\n', 0x07); term_print(a, 0x1f); }
        else if(!strcmp(cmd_tok[0], "release-info")) { releaseInfo(); }
        else if(!strcmp(cmd_tok[0], "menu")) { actionMenu(); }
        else if(!strcmp(cmd_tok[0], "clear")) { term_init(); term_col = 0; term_row = 0; }
        else if(!strcmp(cmd_tok[0], "memwipe")) { memWipe(); }
        else if(!strcmp(cmd_tok[0], "epilepsy")) { epilepsy(); }
        else if(!strcmp(cmd_tok[0], "segfault")) { segfault(); }
    	else if(!strcmp(cmd_tok[0], "what")) { term_col= 0; term_row = 0; for (u8 a = 0; a < 80; a++) { for (u8 b = 0; b < 25; b++) { term_puti(0xeb, a | b); } } }
        else if(!strcmp(cmd_tok[0], "strspl")) {
            for (int a = 0; a < cmd_argc; ++a)
            {
                term_print("\"", 0x07);
                term_print(cmd_tok[a], 0x07);
                term_print("\"; ", 0x07);
            }
        }
        else if(!strcmp(cmd_tok[0], "dec2hex")) {
            term_printnum(atoi(cmd_tok[1]), 0xb);
            term_print(" -> 0x", 0xb);
            term_printhex(atoi(cmd_tok[1]), 0xb);
        }
        else if(!strcmp(cmd_tok[0], "hex2dec")) {
            term_print("0x", 0xb);
            term_printhex(htoi(cmd_tok[1]), 0xb);
            term_print(" -> ", 0xb);
            term_printnum(htoi(cmd_tok[1]), 0xb);
        }
        else if(!strcmp(cmd_tok[0], "setmem")) { 
            *((u16*)htoi(cmd_tok[1])) = htoi(cmd_tok[2]);
        }
        else if(!strcmp(cmd_tok[0], "")) { }
        else { 
            term_print("no such command: ", 0x04);
            term_print(cmd_tok[0], 0x04);
        }
        cmd_tok[0] = "";
        prompt();
    }

    void prompt()  
    {
        term_print("\n>\x01", accent);
        isPrompt == true;
        // getCh();
        // term_print("By pressing 'q' you will wipe the entire memory of this VM. Are you sure?", 0x4f);
        // if(getCh() == 'q' || getCh() == 'Q') for(u32p a = (u32p)0xffffffff; a > (u32p)0; a--) *a = 0xdeafbead;
        // while(true) getCh();
        parseCmd(getStr());
    }
}
#endif
