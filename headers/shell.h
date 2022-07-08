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
    extern bool ctrl, alt, super, shift, caps;
    extern int read_cmos_seconds(void);
    extern int read_key(int* c);
    //extern void aint();
    extern char kbd_us[];
    void prompt()  
    {
        isPrompt == true;
        u32 sc = 0x00;
        while(isPrompt)
        {
            if(sc != inl(0x60))
            {
                term_putc(getKb(sc), 0x07);
                update_cursor(term_col, term_row);
                sc = inl(0x60);
            }
        }
    }

}   
#endif