#pragma once
#include "types.h"
#ifndef RELINFO_H
#define RELINFO_H
extern "C" {
    str relname = "mokou";
    str verstr = "0.07~beta_VBE";
    u32 vernum = 0x0007fd;
    str changelog_added = "-> [major] Revamped display driver! Now using VBE instead of VGA framebuffer.\n"
                          "   - Now able to output full-color images to the screen (what a \"mega\"-cool feature!)\n"
                          "   - term_putc() is now compatible with the new vbe_putc() function (though, with limited colour)\n"
                          "   - Support for PSF fonts which can be linked at build time.\n"
                          "-> Fixed bugs related to dec2hex command\n"
                          "-> Added GNU GPL notice in kernel.cpp source file\n";
    str changelog_bugs = "-> Lack of video support on legacy VGA systems\n"
                        "-> Inability to fully erase a command (though it's only visual)\n"
                        "-> Other unexpected bugs because of version control\n";
    str changelog_note = "NOTE: This release might be more unstable than usual because of trying to move source code to a new branch.\nIf you experience problems (like serious bugs or anything like that), feel free to reach out to me or create an issue.\n";
    str changelog_tba = "-> Add sound support\n"
                        "-> Add scrollback to display\n";
    u8 accent = 0x06;
}
#endif /* RELINFO_H */