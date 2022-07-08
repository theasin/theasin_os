#pragma once
#include "types.h"
#include "asm.h"
#ifndef SERIAL_H
#define SERIAL_H
extern "C" {
    #define COM1 0x3f8
    #define COM2 0x2f8
    #define COM3 0x3e8
    #define COM4 0x2e8
    #define COM5 0x5f8
    #define COM6 0x4f8
    #define COM7 0x5e8
    #define COM8 0x4e8

    int initSerial(u16 port) 
    { 
        outb(port + 1, 0x00);
        outb(port + 3, 0x80);
        outb(port + 0, 0x03);
        outb(port + 1, 0x00);
        outb(port + 3, 0x03);
        outb(port + 2, 0xC7);
        outb(port + 4, 0x0B);
        outb(port + 4, 0x1E);
        outb(port + 0, 0xAE);
        if(inb(port + 0) != 0xAE) {
            return 1;
        }
        outb(PORT + 4, 0x0F);
        return 0;
    }
    char read_serial(u16 port) 
    {
        while ((inb(port + 5) & 1) == 0)
        {
            return inb(port);
        }
    }
    int is_transmit_empty(u16 port) {
        return inb(port + 5) & 0x20;
    }
    void write_serial(u16 port, char a) {
        while (is_transmit_empty() == 0);
        outb(port,a);
    }
}
#endif /* SERIAL_H */