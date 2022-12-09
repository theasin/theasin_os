#include "headers/types.h"
#include "headers/display.h"
#include "headers/util.h"
#include <stdbool.h>
extern "C"
{
    extern bool ctrl, alt, super, shift, caps;
    char getKb(u8 a)
    {
        switch(a)
        {
            case 0x02:
                return '1';
                break;
            case 0x03:
                return '2';
                break;
            case 0x04:
                return '3';
                break;
            case 0x05:
                return '4';
                break;
            case 0x06:
                return '5';
                break;
            case 0x07:
                return '6';
                break;
            case 0x08:
                return '7';
                break;
            case 0x09:
                return '8';
                break;
            case 0x0a:
                return '9';
                break;
            case 0x0b:
                return '0';
                break;
            case 0x0c:
                return '-';
                break;
            case 0x0d:
                return '=';
                break;
            case 0x0e:
                if(term_col >= 0 && buf[(term_row * 80 + term_col) - 1] != '\e')
                    return '\b';
                else
                    return '\v';
                break;
            case 0x1e:
                if(!caps)
                    return 'a';
                else
                    return 'A';
                break;
            case 0x30:
                if(!caps)
                    return 'b';
                else
                    return 'B';
                break;
            case 0x2e:
                if(!caps)
                    return 'c';
                else
                    return 'C';
                break;
			case 0x20:
			{
                if(!caps && !ctrl)
					return 'd';
                else if(!ctrl)
					return 'D';
				if(ctrl)
					phalt();
	            break;
			}
            case 0x12:
                if(!caps)
                    return 'e';
                else
                    return 'E';
                break;
            case 0x21:
                if(!caps)
                    return 'f';
                else
                    return 'F';
                    break;
            case 0x22:
                if(!caps)
                    return 'g';
                else
                    return 'G';
                break;
            case 0x23:
                if(!caps)
                    return 'h';
                else
                    return 'H';
                break;
            case 0x17:
                if(!caps)
                    return 'i';
                else
                    return 'I';                
                break;
            case 0x24:
                if(!caps)
                    return 'j';
                else
                    return 'J';
                break;
            case 0x25:
                if(!caps)
                    return 'k';
                else
                    return 'K';
                break;
            case 0x26:
                if(!caps)
                    return 'l';
                else
                    return 'L';
                break;
            case 0x32:
                if(!caps)
                    return 'm';
                else
                    return 'M';
                break;
            case 0x31:
                if(!caps)
                    return 'n';
                else
                    return 'N';
                break;
            case 0x18:
                if(!caps)
                    return 'o';
                else
                    return 'O';
                break;
            case 0x19:
                if(!caps)
                    return 'p';
                else
                    return 'P';
                break;
            case 0x10:
                if(!caps)
                    return 'q';
                else
                    return 'Q';                
                break;
            case 0x13:
                if(!caps)
                    return 'r';
                else
                    return 'R';
                break;
            case 0x1f:
                if(!caps)
                    return 's';
                else
                    return 'S';                
                break;
            case 0x14:
                if(!caps)
                    return 't';
                else
                    return 'T';                
                break;
            case 0x16:
                if(!caps)
                    return 'u';
                else
                    return 'U';                
                break;
            case 0x2f:
                if(!caps)
                    return 'v';
                else
                    return 'V';
                break;
            case 0x11:
                if(!caps)
                    return 'w';
                else
                    return 'W';
                break;
            case 0x2d:
                if(!caps)
                    return 'x';
                else
                    return 'X';
                break;
            case 0x15:
                if(!caps)
                    return 'y';
                else
                    return 'Y';
                break;
            case 0x2c:
                if(!caps)
                    return 'z';
                else
                    return 'Z';                
                break;
            case 0x0f:
                return ' ';
                break;
            case 0x1c:
                return '\n';
                break;
            case 0x29:
                return '`';
                break;
            case 0x35:
                return '/';
                break;
            case 0x28:
                return '\'';
                break;
            case 0x1a:
                return '[';
                break;
            case 0x1b:
                return ']';
                break;
            case 0x34:
                return '.';
                break;
            case 0x33:
                return ',';
                break;
            case 0x2b:
                return '\\';
                break;
            case 0x27:
                return ';';
                break;
            case 0x01:
                term_col = 0x00;
                term_row = 0x00;
                term_init();
                term_print("You have cleared the terminal!", 0x0b);
                return '\n';
                break;
            case 0x39:
                return ' ';
                break;
            case 0x3a:
                caps = !caps;
                return '\v';
                break;
            case 0x3c:
                return '\v';
                break;
            case 0x58:
                halt(0xdead, "USER_INITIATED_HALT");
			case 0x1d:
			{
				ctrl = true;
				return '\v';
			}
			case 0x9d:
			{
				ctrl = false;
				return '\v';
			}
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
        return getKb(a);
    }
    char getCh()
    {
        u8 sc = inl(0x60);
        bool a = true;
        char ret;
        while(a) 
        {
            if(sc != inb(0x60))
            {
                ret = getKb(sc);
                break;
                sc = inb(0x60);
            }
        }
        return ret;
    }
    char * getStr()
    {
        u8 sc = 0x00;
        char cmd[256];
        u8 cmdPos = 0;
        char *ret;
        // u8 curPos = 0;
        // char st[256];
        // while(true)
        // {
        //     if(getCh() != '\n') { term_putc(getCh(), 0x07); update_cursor(term_col, term_row); }
        //     if(getCh() != '\e' && getCh() != '\v' && getCh() != '\b') { st[curPos++] = getCh(); }
        //     if(getCh() == '\b') { if(curPos > 0) { st[--curPos] = '\0'; } else { st[0] = '\0'; } }
        //     if(getCh() == '\n') { st[++curPos] = '\0'; break; }
        // } 
        // return &st[0];
        while (true) if(sc != inb(0x60))
        {
            if(getKb(sc) != '\n') term_putc(getKb(sc), 0x07);
            if(getKb(sc) != '\e' && getKb(sc) != '\v' && getKb(sc) != '\b' && getKb(sc) != '\n') { cmd[cmdPos++] = getKb(sc); }
            if(getKb(sc) == '\b') { 
            if(cmdPos > 0)
            {
                cmd[cmdPos--] = ' '; 
            }
            }
            if(getKb(sc) == '\n') {  
                cmd[cmdPos] = '\0';
                ret = &(cmd[0]);
                break;
            }
            update_cursor(term_col, term_row);
            sc = inb(0x60);
        }
        return ret;
    }
}
