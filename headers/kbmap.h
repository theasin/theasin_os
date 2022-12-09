#pragma once
#include "types.h"
#ifndef KBMAP_H
#define KBMAP_H
extern "C"
{
    extern char getKb(u8 a);
    extern char getCh(void);
    extern char * getStr();
}
#endif /* KBMAP_H */
