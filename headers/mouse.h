#pragma once
#include "types.h"
#ifndef MOUSE_H
#define MOUSE_H 
extern "C"
{
    extern void mouse_install(), mouse_handler();
    extern u8 mouse_read();
    extern i8 mouse_x, mouse_y;
}
#endif