#include "./headers/types.h"
#include "./headers/util.h"
#define PIC1 0x20
#define PIC2 0xa0
#define ICW1 0x11
#define ICW4 0x01

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