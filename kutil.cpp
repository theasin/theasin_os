#include "headers/types.h"
#include "headers/util.h"
#include "headers/display.h"
#include <cpuid.h>
#define PIC1 0x20
#define PIC2 0xa0
#define ICW1 0x11
#define ICW4 0x01
extern "C" 
{
	void setAL(unsigned char _val) { asm volatile ("movb %0, %%al" : "=a" (_val)); }
	void setAH(unsigned char _val) { asm volatile ("movb %0, %%ah" : "=a" (_val)); }
	void setAX(unsigned short _val) { asm volatile ("movw %0, %%ax" : "=a" (_val)); }
	void setBL(unsigned char _val) { asm volatile ("movb %0, %%bl" : "=a" (_val)); }
	void setBH(unsigned char _val) { asm volatile ("movb %0, %%bh" : "=a" (_val)); }
	void setBX(unsigned short _val) { asm volatile ("movw %0, %%bx" : "=a" (_val)); }
	void setCL(unsigned char _val) { asm volatile ("movb %0, %%cl" : "=a" (_val)); }
	void setCH(unsigned char _val) { asm volatile ("movb %0, %%ch" : "=a" (_val)); }
	void setCX(unsigned short _val) { asm volatile ("movw %0, %%cx" : "=a" (_val)); }
	void setDL(unsigned char _val) { asm volatile ("movb %0, %%dl" : "=a" (_val)); }
	void setDH(unsigned char _val) { asm volatile ("movb %0, %%dh" : "=a" (_val)); }
	void setDX(unsigned short _val) { asm volatile ("movw %0, %%dx" : "=a" (_val)); }

	int strcmp(const char * l, const char * r) {
		for (; *l == *r && *l; l++, r++);
		return *(unsigned char *)l - *(unsigned char *)r;
	}

	char * strchr(const char * s, int c) {
		while (*s) {
			if (*s == c) {
				return (char *)s;
			}
			s++;
		}
		return 0;
	}

	unsigned long strlen(const char *s) {
		unsigned long out = 0;
		while (*s) {
			out++;
			s++;
		}
		return out;
	}

	char * strcat(char *dest, const char *src) {
		char * end = dest;
		while (*end != '\0') {
			++end;
		}
		while (*src) {
			*end = *src;
			end++;
			src++;
		}
		*end = '\0';
		return dest;
	}

	void init_pics(int pic1, int pic2)
	{
			/* send ICW1 */
		outb(PIC1, ICW1);
		outb(PIC2, ICW1);

		/* send ICW2 */
		outb(PIC1 + 1, pic1);   
		outb(PIC2 + 1, pic2);   

		/* send ICW3 */
		outb(PIC1 + 1, 4);   
		outb(PIC2 + 1, 2);

		/* send ICW4 */
		outb(PIC1 + 1, ICW4);
		outb(PIC2 + 1, ICW4);

		/* disable all IRQs */
		outb(PIC1 + 1, 0xFF);
	}
	u16 ax()
	{
		u16 result;
		asm("movw %%ax,%0" : "=a"(result));
		return result;
	}
	u16 bx()
	{
		u16 result;
		asm("movw %%bx,%0" : "=a"(result));
		return result;
	}
	u16 cx()
	{
		u16 result;
		asm("movw %%cx,%0" : "=a"(result));
		return result;
	}
	u16 dx()
	{
		u16 result;
		asm("movw %%dx,%0" : "=a"(result));
		return result;
	}
	u16 si()
	{
		u16 result;
		asm("movw %%si,%0" : "=a"(result));
		return result;
	}
	u16 bp()
	{
		u16 result;
		asm("movw %%bp,%0" : "=a"(result));
		return result;
	}
	u16 sp()
	{
		u16 result;
		asm("movw %%sp,%0" : "=a"(result));
		return result;
	}
	
	u16 di()
	{
		u16 result;
		asm("movw %%di,%0" : "=a"(result));
		return result;
	}

 	void death()
	{
		font512();
		term_row, term_col = 0;
		enable_cursor(0, 0);
		update_cursor(81, 61);
		for(int x = 0; x <= 80; x++)
			for(int y = 0; y <= 60; y++)
				term_putc('\0', 0x40);
		term_row = 0;
		term_col = 0;
 		term_print("\n*** HALT! 0x????", 0x40);
 		term_print("\nThe system has been killed because of [UNKNOWN]\n\n", 0x40);
		char * c = (char*)0xf0500;
		for (u16 a = 0; a < 80 * 18; a++) term_puti((int)*(c + a), 0x40);
 		__asm__("hlt");
	}

 	void halt(u16 code, const char* message)
	{ 	
		u16 a = ax();
		u16 b = bx();
		u16 c = cx(); 
		u16 d = dx();
		u16 s = si();
		u16 d2 = di();
		u16 b2 = bp();
		u16 s2 = sp();
		font512();  
		term_row, term_col = 0;
		enable_cursor(0, 0);
		update_cursor(81, 61);
		for(int x = 0; x <= 80; x++)
			for(int y = 0; y <= 60; y++)
				term_putc('\0', 0x1f);
		term_row = 0;
		term_col = 0;
 		term_print("\n*** HALT! 0x", 0x1f);
 		term_printhex(code, 0x1f);
 		term_print(" ", 0x1f);
		term_print("(0x", 0x1f);
		term_printhex(a, 0x1f);
		term_print(",0x", 0x1f);
		term_printhex(b, 0x1f);
		term_print(",0x", 0x1f);
		term_printhex(c, 0x1f);
		term_print(",0x", 0x1f);
		term_printhex(d, 0x1f);
		term_print(",0x", 0x1f);
		term_printhex(s, 0x1f);
		term_print(",0x", 0x1f);
		term_printhex(b2, 0x1f);
		term_print(",0x", 0x1f);
		term_printhex(s2, 0x1f);
		term_print(",0x", 0x1f);
		term_printhex(d2, 0x1f);
		term_print(")\n", 0x1f);
 		term_print(message, 0x1f);
		term_print("\n\n      #:::::-=***==----+--::..:::::-+=    \n      %::-+***+=-:......::-==+=:.::::+=   \n     :++++:...........        .-=-::::*:  \n     :-  ..............          .+=:::*  \n   .-    ...............           +=.:+. \n  .-       .........==.             +:.=. \n .-                 :@*:...    .+:  .+-=. \n =        .#:.......:%=**=:.....:*    ...:\n.=       .:@%-......-%+=.-**-...:#.-.    -\n.+      ..-#=#=.....+*-*#- .=++-.#..+.   -\n +     ...=#=-+#=..-#:  -#*.   -+#*.-*:+*-\n -:    ...+*+#:.+*+#:     =*:--::-#*=%*-:.\n  +    ...+*.:#+. ..       =:+-..-#@@+:::.\n   =:  ...+@+. =#+.        :-. .+*=::-*+::\n    .:=:..+%@#. .:..      .  :++.      +%:\n      =-=*#=-+#+ =:.    :-::+*::      .#+-\n    :-    .   ++.       :+#++#+.  .-+++-:-\n   ::.:=   . .-=-:::-==+=:...-+#=:::      \n       .:=...:      .:  .-=++:            \n   ..             ...:--..                \n", 0x1f);
 		__asm__("hlt");
	}
}
