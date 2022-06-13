#pragma once
#include "types.h"
#ifndef DISPLAY_H
#define DISPLAY_H
extern "C" {
    extern u8 term_col, term_row;
    extern bool rtlo, insanity;
    extern str tochar(u64, str);
    extern void term_init();
    extern void term_putc(const char, u8);
    extern void term_puti(u8, u8);
    extern void term_print(str, u8);
    extern void term_printat(str, u8, u8, u8);
    extern void term_printnum(int, u8);
    extern void enable_cursor(u8, u8);
    extern void update_cursor(int, int);
}
#endif