#pragma once
#include "types.h"
#ifndef RELINFO_H
#define RELINFO_H
extern "C" {
    str relname = "cirno";
    str verstr = "0.06a";
    u32 vernum = 0x000601;
    str changelog_added = "-> [internal] Commands now split into tokens, that are storable in char* arrays\n"
                          "-> [internal] Implemented htoi (hex str to int) and atoi (str to int) for args\n"
                          "-> Added argument handler for commands\n"
                          "-> Added dec2hex, hex2dec commands for converting between numerical systems\n"
                          "-> Added GNU GPL Notice on startup\n"
                          "-> Replaced halt with phalt to prevent accepting args and messing up values\n";
    str changelog_tba = "-> Add sound support\n"
                        "-> Add scrollback to display\n";
    u8 accent = 0x0b;
}
#endif /* RELINFO_H */