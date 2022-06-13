#include "./headers/types.h"
#include "./headers/util.h"
#include "./headers/display.h"
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
 	void halt(u16 code, char* message)
 	{
 		term_putc('\n', 0x07);
 		term_print("System halted! Code: ", 0x3f);
 		term_printnum(code, 0x3f);
 		term_print(" (", 0x3f);
 		term_print(message, 0x3f);
 		term_print(")\n", 0x3f);
		term_print("ax: ", 0x3f);
		term_printnum(ax(), 0x3f);
		term_print("; bx: ", 0x3f);
		term_printnum(bx(), 0x3f);
		term_print("; cx: ", 0x3f);
		term_printnum(cx(), 0x3f);
		term_print("; dx: ", 0x3f);
		term_printnum(dx(), 0x3f);
		term_print("; si: ", 0x3f);
		term_printnum(si(), 0x3f);
		term_print("; bp: ", 0x3f);
		term_printnum(bp(), 0x3f);
		term_print(" sp: ", 0x3f);
		term_printnum(sp(), 0x3f);
		term_print("; di: ", 0x3f);
		term_printnum(di(), 0x3f);
		
 		__asm__("hlt");
	}
}