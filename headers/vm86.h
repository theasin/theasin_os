/* Header for Virtual 8086 mode */
#pragma once
#include "types.h"
#ifndef VM86_H
#define VM86_H
extern "C" {
    extern void enterV86(void);
    extern void exitV86(void);
}
#endif