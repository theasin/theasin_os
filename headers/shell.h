#pragma once
#include "display.h"
#include "types.h"
#include "util.h"
#include "kbd.h"
#include "kbmap.h"
#include "types.h"
#include "lckscr.h"
#include "release-info.h"
#include "sound.h"
#include "vm86.h"
#include "../img.h"
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
    int argc_max = 32;
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

    void megaCool() {
        u16 width = 1024;
        u16 height = 768;
        u32 seq = 0;
        for (u16 x = 0; x < width; x++)
            for (u16 y = 0; y < height; y++)
            {
                int pitch = *((u32p)(0x10060));
                // int frbuf = (u32)(*((u64p)(*mbootAddr + 88)));
                int frbuf = *((u64p)(0x10058));
                // *((u8p)(y * pitch + (x * 3) + frbuf)) = 0xffffffff;
                *((u32p)(y * pitch + (x * 3) + frbuf)) = 0;
                // *((u32p)((u32)(*((u32p)((*mbootAddr + 88)) + ((width * y) + x))))) = x | y;
                // *((u32p)(y * *((u32p)(*mbootAddr + 96)) + (x * 3) + *((u32p)(*mbootAddr + 88)))) = 0xffffffff;

                // y * pitch + (x * (bpp/8)) + frame
            }
        for (u16 y = 0; y < height; y++)
            for (u16 x = 0; x < width; x++)
            {
                int pitch = *((u32p)(0x10060));
                // int frbuf = (u32)(*((u64p)(*mbootAddr + 88)));
                int frbuf = *((u64p)(0x10058));
                // *((u8p)(y * pitch + (x * 3) + frbuf)) = 0xffffffff;
                u32 r, g, b;
                r = (((header_data[seq] - 33) << 2) | ((header_data[seq + 1] - 33) >> 4));
                g = ((((header_data[seq + 1] - 33) & 0xF) << 4) | ((header_data[seq + 2] - 33) >> 2));
                b = ((((header_data[seq + 2] - 33) & 0x3) << 6) | ((header_data[seq + 3] - 33)));
                // *((u32p)(y * pitch + (x * 4) + frbuf)) = (0x00 << 24) | (r << 16) | (g << 8)| (b);
                *((u32p)(y * pitch + (x * 4) + frbuf)) = (r << 16) | (g << 8)| (b);

                seq += 4;
                // *((u32p)((u32)(*((u32p)((*mbootAddr + 88)) + ((width * y) + x))))) = x | y;
                // *((u32p)(y * *((u32p)(*mbootAddr + 96)) + (x * 3) + *((u32p)(*mbootAddr + 88)))) = 0xffffffff;

                // y * pitch + (x * (bpp/8)) + frame
            }
        // *((u32p)((u32)mbootAddr + 109)) = 1;
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

    static int parseCmd(char * cmd) 
    {
        cmd_tok[0] = ""; // clear 1st element of array before using it, will prevent junk appearing in the future
        extern void prompt();
        int cmd_argc;
        string_split(cmd, " ", cmd_tok, 32, &cmd_argc);
        term_putc('\n', 0x07);
        if(!strcmp(cmd, "halt")) phalt();
        else if(!strcmp(cmd_tok[0], "mode13h")) { enterMode13h(); draw_x(); }
        else if(!strcmp(cmd_tok[0], "mode12h")) { enterMode12h(); draw_x(); }
        // else if(!strcmp(cmd_tok[0], "echo"))
        //     if(cmd_tok[1] != NULL) 
        //         { 
        //         // for (u8 argc = 1; argc < cmd_argc; argc++)
        //         term_print(cmdBackup, 0x07); 
        //         term_putc('\n', 0x07); 
        //         }
        //     else
        //         return 2;
        else if(!strcmp(cmd_tok[0], "release-info")) { releaseInfo(); }
        else if(!strcmp(cmd_tok[0], "menu")) { actionMenu(); }
        else if(!strcmp(cmd_tok[0], "clear")) { term_init(); term_col = 0; term_row = 0; }
        else if(!strcmp(cmd_tok[0], "memwipe")) { memWipe(); }
        else if(!strcmp(cmd_tok[0], "epilepsy")) { epilepsy(); }
        else if(!strcmp(cmd_tok[0], "segfault")) { segfault(); }
    	else if(!strcmp(cmd_tok[0], "what")) { term_col= 0; term_row = 0; for (u8 a = 0; a < 80; a++) { for (u8 b = 0; b < 25; b++) { term_putc(0xeb, a | b); } } }
        else if(!strcmp(cmd_tok[0], "strspl")) {
            for (int a = 0; a < cmd_argc; ++a)
            {
                term_print("\"", 0x07);
                term_print(cmd_tok[a], 0x07);
                term_print("\"; ", 0x07);
            }
        }
        else if(!strcmp(cmd_tok[0], "dec2hex")) {
            int res = atoi(cmd_tok[1]);
            term_print(cmd_tok[1], 0xb);
            term_print(" -> 0x", 0xb);
            term_printhex(res, 0xb);
            term_putc('\n', 0x07);
        }
        else if(!strcmp(cmd_tok[0], "hex2dec")) {
            term_print("0x", 0xb);
            term_printhex(htoi(cmd_tok[1]), 0xb);
            term_print(" -> ", 0xb);
            term_printnum(htoi(cmd_tok[1]), 0xb);
            term_putc('\n', 0x07);
        }
        else if(!strcmp(cmd_tok[0], "pokeb"))
            *((u8*)htoi(cmd_tok[1])) = htoi(cmd_tok[2]);
        else if(!strcmp(cmd_tok[0], "pokew"))
            *((u16*)htoi(cmd_tok[1])) = htoi(cmd_tok[2]);
        else if(!strcmp(cmd_tok[0], "pokel"))
            *((u32*)htoi(cmd_tok[1])) = htoi(cmd_tok[2]);
        else if(!strcmp(cmd_tok[0], "pokeq"))
            *((u64*)htoi(cmd_tok[1])) = htoi(cmd_tok[2]);
        else if(!strcmp(cmd_tok[0], "peekb"))
            { term_print("0x", 0x07); term_printhex(*((u8*)htoi(cmd_tok[1])), 0x07); term_putc('\n', 0x07); }
        else if(!strcmp(cmd_tok[0], "peekw"))
            { term_print("0x", 0x07); term_printhex(*((u16*)htoi(cmd_tok[1])), 0x07); term_putc('\n', 0x07); }
        else if(!strcmp(cmd_tok[0], "peekl"))
            { term_print("0x", 0x07); term_printhex(*((u32*)htoi(cmd_tok[1])), 0x07); term_putc('\n', 0x07); }
        else if(!strcmp(cmd_tok[0], "peekq"))
            { term_print("0x", 0x07); term_printhex(*((u64*)htoi(cmd_tok[1])), 0x07); term_putc('\n', 0x07); }
        else if(!strcmp(cmd_tok[0], "mega"))
            megaCool();
        else if(!strcmp(cmd_tok[0], "")) { }
        else { 
            // term_print("no such command: ", 0x04);
            // term_print(cmd_tok[0], 0x04);
            return -1;
        }
        // prompt();
        return 0;
    }

    void prompt()  
    {
        term_print(">\x01", accent);
        isPrompt == true;
        // getCh();
        // term_print("By pressing 'q' you will wipe the entire memory of this VM. Are you sure?", 0x4f);
        // if(getCh() == 'q' || getCh() == 'Q') for(u32p a = (u32p)0xffffffff; a > (u32p)0; a--) *a = 0xdeafbead;
        // while(true) getCh();
        int st = parseCmd(getStr());
        if (st == -1) {
            term_print("error: no such command: ", 0x4);
            term_print(cmd_tok[0], 0x04);
            term_putc('\n', 0x7);
        }
        else if (st == -2)
            term_print("error: command failed\n", 0x4);
        else if (st >= 1)
            { term_print("command returned ", 0x8); term_printnum(st, 0x8); term_print(" (0x",0x8); term_printnum(st, 0x8); term_print(")\n",0x8); }
        for (u8 argc = 0; argc < argc_max; argc++)
            cmd_tok[argc] = "";
        // term_putc('\n', 0x07);
        prompt();
    }
}
#endif
