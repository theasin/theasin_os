/** 
 @deprecated This header is deprecated. Use KBD functions instead.
**/
#pragma once
#include "types.h"
#include "display.h"
#include "util.h"
#include <stdbool.h>
#ifndef KBMAP_H
#define KBMAP_H
extern "C"
{
    extern bool ctrl, alt, super, shift, caps;
    extern u8 scale;
    extern char getKb(u32);
    extern char getCh();
}
#endif /* KBMAP_H */