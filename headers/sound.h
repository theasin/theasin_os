#pragma once
#include "types.h"
#ifndef SOUND_H
#define SOUND_H
extern "C"
{
    extern void playSound(u32 freq);
    extern void stopSound(void);
    extern void beep(void);
}
#endif /* SOUND_H */