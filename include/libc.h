/* vim: tabstop=4 shiftwidth=4 noexpandtab
 */
#ifndef __LIBC_H
#define __LIBC_H
#include <stddef.h>

#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))

#ifndef LITTLE_ENDIAN
	#ifndef BIG_ENDIAN
	#error "Dont defined architecute endian type (arch.h)"
	#endif
#endif
#ifdef LITTLE_ENDIAN
	#ifdef BIG_ENDIAN
	#error "Multiple endian type defined (?)"
#endif
#endif

#define __bswap_16(x) 	((x>>8) | (x<<8))
#define	__bswap_32(x) 	(((x>>24)&0xff)		|\
                    	((x<<8) &0xff0000)	|\
                    	((x>>8) &0xff00)	|\
                    	((x<<24)&0xff000000))



void 	*malloc			(size_t);
int		free			(void *);
//void 	*memcpy			(void *, const void *, size_t);
//void 	*memset			(void *, char, size_t);

extern void * memcpy(void * restrict dest, const void * restrict src, size_t n);
extern void * memset(void * dest, int c, size_t n);
extern void * memchr(const void * src, int c, size_t n);
extern void * memrchr(const void * m, int c, size_t n);
extern void * memmove(void *dest, const void *src, size_t n);

extern int 	  memcmp(const void *vl, const void *vr, size_t n);

extern char	* strdup(const char * s);
extern char	* stpcpy(char * restrict d, const char * restrict s);
extern char	* strcpy(char * restrict dest, const char * restrict src);
extern char * strncpy(char *dest, const char *src, size_t n);
extern char	* strchrnul(const char * s, int c);
extern char	* strchr(const char * s, int c);
extern char	* strrchr(const char * s, int c);
extern char	* strpbrk(const char * s, const char * b);
extern char	* strstr(const char * h, const char * n);

extern int 	  strcmp(const char * l, const char * r);

extern size_t strcspn(const char * s, const char * c);
extern size_t strspn(const char * s, const char * c);
extern size_t strlen(const char * s);

extern int 	  atoi(const char * s);

/* Non-standard broken strtok_r */
extern char * strtok_r(char * str, const char * delim, char ** saveptr);

#endif
