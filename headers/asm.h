#pragma once
/*
#include "types.h"
#include "util.h"
#ifndef ASM_H
#define ASM_H
extern "C" {
#define PIC1 0x20
#define PIC2 0xa0
#define ICW1 0x11
#define ICW4 0x01
void outb( u16 port, u8 val )
{
    __asm__ __volatile__ ("outb %0, %1" : : "a"(val), "Nd"(port) );
}
static __inline u8 inb (u16 port)
{
    u8 _v;
    __asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (port));
    return _v;
}
*/