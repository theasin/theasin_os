#include "headers/types.h"
#include "headers/util.h"
extern "C" {
    void enterV86(void) {
        
        __asm__(
            "movl %esp, %ebp"
        );
        __asm__(
            "push 4(%ebp)"
        );
        __asm__(
            "push 8(%ebp)"
        );
        __asm__("pushfl");
        __asm__(
            "orl $(1 << 17), (%esp)"
        );
        __asm__(
            "push 12(%ebp)"
        );
        __asm__(
            "push 16(%ebp)"
        );
        __asm__("iret");
        return;
    }
}