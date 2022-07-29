#pragma once
#ifndef UTIL_H
#define UTIL_H
extern "C" {
static inline unsigned short ins(unsigned short _port) {
	unsigned short rv;
	asm volatile ("inw %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

static inline void outs(unsigned short _port, unsigned short _data) {
	asm volatile ("outw %1, %0" : : "dN" (_port), "a" (_data));
}

static inline unsigned int inl(unsigned short _port) {
	unsigned int rv;
	asm volatile ("inl %%dx, %%eax" : "=a" (rv) : "dN" (_port));
	return rv;
}

static inline void outl(unsigned short _port, unsigned int _data) {
	asm volatile ("outl %%eax, %%dx" : : "dN" (_port), "a" (_data));
}

static inline unsigned char inb(unsigned short _port) {
	unsigned char rv;
	asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

static inline void outb(unsigned short _port, unsigned char _data) {
	asm volatile ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

static inline void insm(unsigned short port, unsigned char * data, unsigned long size) {
	asm volatile ("rep insw" : "+D" (data), "+c" (size) : "d" (port) : "memory");
}

extern void setAL(unsigned char);
extern void setAH(unsigned char);
extern void setAX(unsigned short);
extern void setBL(unsigned char);
extern void setBH(unsigned char);
extern void setBX(unsigned short);
extern void setCL(unsigned char);
extern void setCH(unsigned char);
extern void setCX(unsigned short);
extern void setDL(unsigned char);
extern void setDH(unsigned char);
extern void setDX(unsigned short);
extern void death(void);
extern void halt(uint16_t, const char*);
/* void * memcpy(void * restrict dest, const void * restrict src, long n); */
extern void * memset(void * dest, int c, long n);
extern int strcmp(const char * l, const char * r);
extern char * strchr(const char * s, int c);
extern char * strcat(char *dest, const char *src);
extern void copy_sectors(unsigned long lba, unsigned char * buf, int sectors);
extern void copy_sector(unsigned long lba, unsigned char * buf);
extern unsigned long strlen(const char *s);

extern u16 ax();
extern u16 bx();
extern u16 cx();
extern u16 dx();
extern u16 si();
extern u16 bp();
extern u16 sp();
extern u16 di();

#define DATA_LOAD_BASE 0x4000000
}
#endif