#pragma once
#include "types.h"
#ifndef DISPLAY_H
#define DISPLAY_H
extern "C" {
    extern u8 term_col, term_row, currcol;
    extern bool rtlo, insanity;
    extern char buf[80 * 25];
    extern str tochar(u64, str);
    extern void term_init();
    extern void term_putc(const char, u8);
    extern void term_puti(u8, u8);
    extern void term_print(const char*, u8);
    extern void term_printh(const char*, u8);
    extern void term_printat(const str, u8, u8, u8);
    extern void term_printnum(int, u8);
    extern void term_printhex(u64, u8);
    extern void enable_cursor(u8, u8);
    extern void update_cursor(int, int);
    extern void font512(void), draw_x(void), enterMode13h(void), enterMode12h(void), enterModeText(void);
    extern void enterMode(u8);
    extern unsigned char g_40x25_text[], g_40x50_text[], g_80x25_text[], g_80x50_text[], g_90x30_text[], g_90x60_text[], g_640x480x2[], g_320x200x4[], g_640x480x16[], g_720x480x16[], g_320x200x256[], g_320x200x256_modex[];
}
#endif
