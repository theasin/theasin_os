#include "headers/types.h"
#include "headers/display.h"
#include "headers/util.h"
// #include "headers/kbmap.h"
#include <stdbool.h>

extern "C"
{
    extern bool ctrl, alt, super, shift, caps;
    u8 scale = 1;
    char getKb(u32 a)
    {
        switch(a)
        {
            case 0x02020202:
                return '1';
                break;
            case 0x03030303:
                return '2';
                break;
            case 0x04040404:
                return '3';
                break;
            case 0x05050505:
                return '4';
                break;
            case 0x06060606:
                return '5';
                break;
            case 0x07070707:
                return '6';
                break;
            case 0x08080808:
                return '7';
                break;
            case 0x09090909:
                return '8';
                break;
            case 0x0a0a0a0a:
                return '9';
                break;
            case 0x0b0b0b0b:
                return '0';
                break;
            case 0x0c0c0c0c:
                return '-';
                break;
            case 0x0d0d0d0d:
                return '=';
                break;
            case 0x0e0e0e0e:
                if(term_col != 0)
                    return '\b';
                else
                    return '\v';
                break;
            case 0x1e1e1e1e:
                if(!caps)
                    return 'a';
                else
                    return 'A';
                break;
            case 0x30303030:
                if(!caps)
                    return 'b';
                else
                    return 'B';
                break;
            case 0x2e2e2e2e:
                if(!caps)
                    return 'c';
                else
                    return 'C';
                break;
            case 0x20202020:
                if(!caps)
                    return 'd';
                else
                    return 'D';
                break;
            case 0x12121212:
                if(!caps)
                    return 'e';
                else
                    return 'E';
                break;
            case 0x21212121:
                if(!caps)
                    return 'f';
                else
                    return 'F';
                    break;
            case 0x22222222:
                if(!caps)
                    return 'g';
                else
                    return 'G';
                break;
            case 0x23232323:
                if(!caps)
                    return 'h';
                else
                    return 'H';
                break;
            case 0x17171717:
                if(!caps)
                    return 'i';
                else
                    return 'I';                
                break;
            case 0x24242424:
                if(!caps)
                    return 'j';
                else
                    return 'J';
                break;
            case 0x25252525:
                if(!caps)
                    return 'k';
                else
                    return 'K';
                break;
            case 0x26262626:
                if(!caps)
                    return 'l';
                else
                    return 'L';
                break;
            case 0x32323232:
                if(!caps)
                    return 'm';
                else
                    return 'M';
                break;
            case 0x31313131:
                if(!caps)
                    return 'n';
                else
                    return 'N';
                break;
            case 0x18181818:
                if(!caps)
                    return 'o';
                else
                    return 'O';
                break;
            case 0x19191919:
                if(!caps)
                    return 'p';
                else
                    return 'P';
                break;
            case 0x10101010:
                if(!caps)
                    return 'q';
                else
                    return 'Q';                
                break;
            case 0x13131313:
                if(!caps)
                    return 'r';
                else
                    return 'R';
                break;
            case 0x1f1f1f1f:
                scale--;
                if(!caps)
                    return 's';
                else
                    return 'S';                
                break;
            case 0x14141414:
                if(!caps)
                    return 't';
                else
                    return 'T';                
                break;
            case 0x16161616:
                if(!caps)
                    return 'u';
                else
                    return 'U';                
                break;
            case 0x2f2f2f2f:
                if(!caps)
                    return 'v';
                else
                    return 'V';
                break;
            case 0x11111111:
                scale++;
                if(!caps)
                    return 'w';
                else
                    return 'W';
                break;
            case 0x2d2d2d2d:
                if(!caps)
                    return 'x';
                else
                    return 'X';
                break;
            case 0x15151515:
                if(!caps)
                    return 'y';
                else
                    return 'Y';
                break;
            case 0x2c2c2c2c:
                if(!caps)
                    return 'z';
                else
                    return 'Z';                
                break;
            case 0x0f0f0f0f:
                return ' ';
                break;
            case 0x1c1c1c1c:
                return '\n';
                break;
            case 0x29292929:
                return '`';
                break;
            case 0x35353535:
                return '/';
                break;
            case 0x28282828:
                return '\'';
                break;
            case 0x1a1a1a1a:
                return '[';
                break;
            case 0x1b1b1b1b:
                return ']';
                break;
            case 0x34343434:
                return '.';
                break;
            case 0x33333333:
                return ',';
                break;
            case 0x2b2b2b2b:
                return '\\';
                break;
            case 0x27272727:
                return ';';
                break;
            case 0x01010101:
                term_col = 0x00;
                term_row = 0x00;
                term_init();
                term_print("You have cleared the terminal!", 0x0b);
                return '\n';
                break;
            case 0x39393939:
                return ' ';
                break;
            case 0x3a3a3a3a:
                caps = !caps;
                return '\v';
                break;
            case 0x4b4b4b4b:
                // if(term_col != 0)
                //     term_col--;
                if(scale > 0)
                    scale--;
                return '\v';
                break;
            case 0x4d4d4d4d:
                // term_col++;
                if(scale != 0xff)
                    scale++;
                return '\v';
                break;
            case 0x48484848:
                term_row--;
                return '\v';
                break;
            case 0x50505050:
                term_row++;
                return '\v';
                break;
            case 0x3c3c3c3c:
                return '\v';
                break;
            case 0x58585858:
                setDX(0xffff);
                halt(0xffff, "User-initiated halt");
            default:
            /*
                char* buffer;
                tochar((int)a, buffer);
                term_putc(' ', 0x0b);
                term_print(buffer, 0x0b);
                term_putc(' ', 0x0b);
            */
                return '\v';
                break;
        }
    }
    char getCh()
    {
        u8 sc = 0x00;
        if(sc != inl(0x60))
        {
            char a = getKb(sc);
            return a;
        }
    }
}

