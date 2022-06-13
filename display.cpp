#include "./headers/types.h"
#include "./headers/util.h"
#include "./headers/display.h"
extern "C" {
    volatile u16p vga_buffer = (u16p)0xb8000; //beginning address of vga textbuffer
    const int VGA_COLS = 80;
    const int VGA_ROWS = 25;
    u8 term_col = 0;
    u8 term_row = 0;
    u8 defcol = 0x07;
    bool rtlo, insanity = false;
    str tochar(u64 i, char *p)
    {
        if (i / 10 == 0) {
            // No more digits.
            *p++ = i + '0';
            *p = '\0';
            return p;
        }

        p = tochar(i / 10, p);
        *p++ = i % 10 + '0';
        *p = '\0';
        return p;
    }

    void term_init()
    {
        for (int col = 0; col < VGA_COLS; col++)
        {
            for (int row = 0; row < VGA_ROWS; row++)
            {
                const size_t index = (VGA_COLS * row) + col;
                vga_buffer[index] = ((u16)defcol << 8) | ' ';
            }
        }
    }

    void term_putc(const char c, u8 cl)
    {
        switch(c)
        {   
            case '\v':
                break;
            case '\t':
                term_col += 4;
                break;
            case '\b':
                if(term_col > 0)
                {
                    term_col--;
                    term_putc('\0', 0x0f);
                    term_col--;
                    break;
                } else {         
                    break;
                }
            case '\r':
            {
                const size_t r = (VGA_COLS * term_row) + term_col;
                 vga_buffer[r] = ((u16)term_row * term_col << 8) | 0xff;
            }
            case '\n':
            {
                term_col = 0;
                term_row++;
                break;
            }

            default:
            {
                const size_t index = (VGA_COLS * term_row) + term_col;
                vga_buffer[index] = ((u16)cl << 8) | c;
                if(!rtlo) { term_col++; } else { term_col--; }
            }
            if (term_col >= VGA_COLS)
            {
                term_col = 0;
                term_row++;
            }
            if (term_row >= VGA_ROWS || term_row < 0)
            {
                term_col = 0;
                term_row = 0;
            }
            if (term_row < 0 && term_col >= 0)
            {
                term_row = 0;
                term_col = 0;
            }
            if (term_col == 0) { term_col = 0; }
        }
    }

    void term_puti(u8 c, u8 cl)
    {
        switch(c)
        {   
            case '\v':
                break;
            case '\t':
                term_col += 4;
                break;
            case '\b':
                if(term_col > 0)
                {
                    term_col--;
                    term_putc('\0', 0x0f);
                    term_col--;
                    break;
                } else {         
                    break;
                }
            case '\r':
            {
                const size_t r = (VGA_COLS * term_row) + term_col;
                 vga_buffer[r] = ((u16)term_row * term_col << 8) | 0xff;
            }
            case '\n':
            {
                term_col = 0;
                term_row++;
                break;
            }

            default:
            {
                const size_t index = (VGA_COLS * term_row) + term_col;
                vga_buffer[index] = ((u16)cl << 8) | c;
                if(!rtlo) { term_col++; } else { term_col--; }
            }
            if (term_col >= VGA_COLS)
            {
                term_col = 0;
                term_row++;
            }
    }
    }
    void term_print(str string, uint8_t cl)
    {
        for (size_t i = 0; string[i] != '\0'; i++)
            term_putc(string[i], cl);
    }


    void term_printat(str st, uint8_t cl, uint8_t x, uint8_t y)
    {
        uint8_t buff_x = term_col;
        uint8_t buff_y = term_row;

        term_col = x;
        term_row = y;

        term_print(st, cl);

        term_col = buff_x;
        term_row = buff_y;
    }

    void term_printnum(int n, uint8_t cl)
    {
        char* buffer;
        tochar(n, buffer);
        term_print(buffer, cl);    
    }


    void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
    {
        outb(0x3D4, 0x0A);
        outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
    
        outb(0x3D4, 0x0B);
        outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
    }

    void update_cursor(int x, int y)
    {
        uint16_t pos = y * VGA_COLS + x;
    
        outb(0x3D4, 0x0F);
        outb(0x3D5, (uint8_t) (pos & 0xFF));
        outb(0x3D4, 0x0E);
        outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
    }
}
