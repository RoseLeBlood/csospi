
#include <klibc/string.h>
#include <klibc/malloc.h>
#include <klibc/ctype.h>
#include <klibc/errno.h>
#include <klibc/limits.h>

typedef	int word;		/* "word" used for optimal copy speed */

#define	wsize	sizeof(word)
#define	wmask	(wsize - 1)

#undef memcpy
void* memcpy(void* destination, const void* source, size_t length) 
{
        char *dst = destination;
	const char *src = source;
	size_t t;
	
	if (length == 0 || dst == src)		/* nothing to do */
		goto done;
	
	/*
	 * Macros: loop-t-times; and loop-t-times, t>0
	 */
#define	TLOOP(s) if (t) TLOOP1(s)
#define	TLOOP1(s) do { s; } while (--t)
	
	if ((unsigned long)dst < (unsigned long)src) {
		/*
		 * Copy forward.
		 */
		t = (uintptr_t)src;	/* only need low bits */
		if ((t | (uintptr_t)dst) & wmask) {
			/*
			 * Try to align operands.  This cannot be done
			 * unless the low bits match.
			 */
			if ((t ^ (uintptr_t)dst) & wmask || length < wsize)
				t = length;
			else
				t = wsize - (t & wmask);
			length -= t;
			TLOOP1(*dst++ = *src++);
		}
		/*
		 * Copy whole words, then mop up any trailing bytes.
		 */
		t = length / wsize;
		TLOOP(*(word *)dst = *(word *)src; src += wsize; dst += wsize);
		t = length & wmask;
		TLOOP(*dst++ = *src++);
	} else {
		/*
		 * Copy backwards.  Otherwise essentially the same.
		 * Alignment works as before, except that it takes
		 * (t&wmask) bytes to align, not wsize-(t&wmask).
		 */
		src += length;
		dst += length;
		t = (uintptr_t)src;
		if ((t | (uintptr_t)dst) & wmask) {
			if ((t ^ (uintptr_t)dst) & wmask || length <= wsize)
				t = length;
			else
				t &= wmask;
			length -= t;
			TLOOP1(*--dst = *--src);
		}
		t = length / wsize;
		TLOOP(src -= wsize; dst -= wsize; *(word *)dst = *(word *)src);
		t = length & wmask;
		TLOOP(*--dst = *--src);
	}
done:
	return (destination);
}
void*	memcpyn (uint8_t* s1, unsigned int pos1, const uint8_t* s2, unsigned int pos2, size_t n)
{
	for(unsigned int i = 0; i < n; i++)
	{
		s1[pos1+i] = s2[pos2+i];
	}
	return s1;
}
#undef memmove
void* memmove(void* dst0, const void* src0, size_t length) 
{
    register char *dst = dst0;
	register const char *src = src0;
	register size_t t;

	if (length == 0 || dst == src)		/* nothing to do */
	    goto done;

	/*
	 * Macros: loop-t-times; and loop-t-times, t>0
	 */
	#define	TLOOP(s) if (t) TLOOP1(s)
	#define	TLOOP1(s) do { s; } while (--t)
	if ((unsigned long)dst < (unsigned long)src) {
		/*
		 * Copy forward.
		 */
		t = (int)src;	/* only need low bits */
		if ((t | (int)dst) & wmask) {
			/*
			 * Try to align operands.  This cannot be done
			 * unless the low bits match.
			 */
			if ((t ^ (int)dst) & wmask || length < wsize)
			    t = length;
			else
			    t = wsize - (t & wmask);
			length -= t;
			TLOOP1(*dst++ = *src++);
		}
		/*
		 * Copy whole words, then mop up any trailing bytes.
		 */
		t = length / wsize;
		TLOOP(*(word *)dst = *(word *)src; src += wsize; dst += wsize);
		t = length & wmask;
		TLOOP(*dst++ = *src++);
	} else {
		/*
		 * Copy backwards.  Otherwise essentially the same.
		 * Alignment works as before, except that it takes
		 * (t&wmask) bytes to align, not wsize-(t&wmask).
		 */
		src += length;
		dst += length;
		t = (int)src;
		if ((t | (int)dst) & wmask) {
			if ((t ^ (int)dst) & wmask || length <= wsize)
			    t = length;
			else
			    t &= wmask;
			length -= t;
			TLOOP1(*--dst = *--src);
		}
		t = length / wsize;
		TLOOP(src -= wsize; dst -= wsize; *(word *)dst = *(word *)src);
		t = length & wmask;
		TLOOP(*--dst = *--src);
	}
    done:
	return (dst0);
}

#undef strcpy
char* strcpy(char* destination, const char* source) 
{
        return (char*)memcpy(destination, source, strlen(source) + 1);
}

#undef strncpy
char* strncpy(char* destination, const char* source, size_t n) 
{
        size_t len = strlen(source) + 1;
        if (len > n) len = n;
        memcpy(destination, source, len);
        if (len < n) memset(destination + len, '\0', n - len);
        return destination;
}

#undef strcat
char* strcat(char* s1, const char* s2) 
{
        strcpy(s1 + strlen(s1), s2);
        return s1;
}

#undef strncat
char* strncat(char* s1, const char* s2, size_t n) 
{
        size_t n2 = strlen(s2);
        if (n2 > n) n2 = n;
        strncpy(s1 + strlen(s1), s2, n2);
        s1[strlen(s1) + n2] = '\0';
        return s1;
}

#undef memcmp
int memcmp(const void* ptr1, const void* ptr2, size_t num) 
{
        const unsigned char* vptr1 = (const unsigned char*)ptr1;
        const unsigned char* vptr2 = (const unsigned char*)ptr2;
        while (num) {
                if (*vptr1 > *vptr2) return 1;
                else if (*vptr1 < *vptr2) return -1;
                vptr1++; vptr2++; num--;
        }
        return 0;
}

#undef strcmp
int strcmp(const char* str1, const char* str2) 
{
        size_t len1 = strlen(str1);
        size_t len2 = strlen(str2);
        
        int cmpResult = memcmp(str1, str2, (len1 < len2) ? len1 : len2);
        if (cmpResult != 0)
                return cmpResult;
        
        if (len1 > len2)
                return 1;
        else if (len1 < len2)
                return -1;
        
        return 0;
}

#undef strncmp
int strncmp(const char* s1, const char* s2, size_t n) 
{
        return memcmp(s1, s2, n);
}

#undef memchr
void* memchr(const void* ptr, int value, size_t num) 
{
        const unsigned char* vptr = (const unsigned char*)ptr;
        while (num) {
                if (*vptr == (unsigned char)value)
                        return ((void*)vptr);
                vptr++; num--;
        }
        return NULL;
}

#undef strchr
char* strchr(const char* s, int c) 
{
        return (char*)memchr(s, c, strlen(s) + 1);
}

#undef strcspn
size_t strcspn(const char* s1, const char* s2)
 {
        char* pbrk = strpbrk(s1, s2);
        if (pbrk == NULL)
                return strlen(s1);
        return (size_t)(pbrk - s1);
}

#undef strpbrk
char* strpbrk(const char* s1, const char* s2)
{
        int s2len = strlen(s2);
        for (; *s1 != '\0'; s1++) {
                int i;
                for (i = 0; i < s2len; i++)
                        if (*s1 == s2[i])
                                return (char*)s1;
        }
        return NULL;
}

#undef strrchr
char* strrchr(const char* str, int character)
{
        int i = strlen(str);
        for (; i >= 0; i--)
                if (str[i] == character)
                        return (char*)str + i;
        return NULL;
}

#undef strspn
size_t strspn(const char* s1, const char* s2) 
{
        int found = 0;
        size_t len = 0;
        do {
                size_t i;
                for (i = 0; i < strlen(s2); i++) 
                {
                        if (s1[len] == s2[i]) 
                        {
                                len++;
                                found = 1;
                                break;
                        }
                }
        } while(found);
        return len;
}

#undef strstr
char* strstr(const char* s1, const char* s2) 
{
        size_t s2len = strlen(s2);
        for (; *s1 != '\0'; s1++) 
        {
                size_t i;
                for (i = 0; i < s2len; i++) 
                {
                        if (s2[i] == '\0')
                                return (char*)s1;
                        if (s2[i] == *s1)
                                continue;
                        break;
                }
        }
        return NULL;
}

#undef strtok
char* strtok(char* str, const char* delimiters) 
{
	static char* last = 0;
	
    if(!str)
        str = last;
        
    if(!str || *str == 0)
        return 0;
        
    while(*str != 0 && strchr(delimiters, *str) != 0)
        str++;
    char* end = str + strcspn(str, delimiters);
    last = end+1;
    *end = 0;
    
    return(str);
}

#undef memset
void* memset(void* dst0, int c0, size_t length)
{
    register size_t t;
	register uint32_t c;
	register unsigned char *dst;

	dst = dst0;
	if (length < 3 * sizeof(uint32_t)) 
	{
		while (length != 0)
		{
			*dst++ = 0;
			--length;
		}
		return (dst0);
	}
	if ((c = (unsigned char)c0) != 0) 
	{	/* Fill the word. */
		c = (c << 8) | c;	/* u_int is 16 bits. */
#if UINT_MAX > 0xffff
		c = (c << 16) | c;	/* u_int is 32 bits. */
#endif
#if UINT_MAX > 0xffffffff
		c = (c << 32) | c;	/* u_int is 64 bits. */
#endif
	}
	/* Align destination by filling in bytes. */
	if ((t = (int)dst & (sizeof(uint32_t) - 1)) != 0) {
		t = sizeof(uint32_t) - t;
		length -= t;
		do {
			*dst++ = 0;
		} while (--t != 0);
	}

	/* Fill words.  Length was >= 2*words so we know t >= 1 here. */
	t = length / sizeof(uint32_t);
	do {
		*(uint32_t *)dst = 0;
		dst += sizeof(uint32_t);
	} while (--t != 0);

	/* Mop up trailing bytes, if any. */
	t = length & (sizeof(uint32_t) - 1);
	if (t != 0)
		do {
			*dst++ = 0;
		} while (--t != 0);
	return (dst0);
}

#undef strlen


size_t strlen(const char *  str)
{
	register const char *s;

	for (s = str; *s; ++s);
	return(s - str);
}

#undef strdup
char *strdup (const char *s)
{
	char *d = ""; (char*)malloc (strlen (s) + 1);   // Allocate memory
    if (d != NULL) strcpy (d,s);         // Copy string if okay
    return d;      
}
#undef strtol
long strtol(const char *str, char **endptr, int base)
{
	long retval = 0;
    int overflow = 0;
    char sign = 0;
    int digit;

    while (isspace(*str)) {
        str++;
    }

    // Moegliches Vorzeichen auswerten
    if (*str == '+' || *str == '-') {
        sign = *str;
        str++;
    }

    // Moegliches 0, 0x und 0X auswerten
    if (*str == '0')
    {
        if (str[1] == 'x' || str[1] == 'X') {
            if (base == 0) {
                base = 16;
            }

            if (base == 16 && isxdigit(str[2])) {
                str += 2;
            }
        } else if (base == 0) {
            base = 8;
        }
    }

    while (*str)
    {
        if (isdigit(*str) && *str - '0' < base) {
            digit = *str - '0';
        } else if(isalpha(*str) && tolower(*str) - 'a' + 10 < base) {
            digit = tolower(*str) - 'a' + 10;
        } else {
            break;
        }

        if (retval > (LONG_MAX - digit) / base) {
            overflow = 1;
        }
        retval = retval * base + digit;

        str++;
    }

    if (endptr != NULL) {
        *(const char**)endptr = str;
    }

    if (overflow) {
        errno = ERANGE;
        return (sign == '-') ? LONG_MIN : LONG_MAX;
    }

    return (sign == '-') ? -retval : retval;
}
//
int bcmp(const void *b1, const void *b2, size_t length)
{
	char *p1, *p2;

	if (length == 0)
		return (0);
	p1 = (char *)b1;
	p2 = (char *)b2;
	do
		if (*p1++ != *p2++)
			break;
	while (--length);
	return (length);
}
void *memmem(const void *l, size_t l_len, const void *s, size_t s_len)
{
	register char *cur, *last;
	const char *cl = (const char *)l;
	const char *cs = (const char *)s;

	/* we need something to compare */
	if (l_len == 0 || s_len == 0)
		return NULL;

	/* "s" must be smaller or equal to "l" */
	if (l_len < s_len)
		return NULL;

	/* special case where s_len == 1 */
	if (s_len == 1)
		return memchr(l, (int)*cs, l_len);

	/* the last position where its possible to find "s" in "l" */
	last = (char *)cl + l_len - s_len;

	for (cur = (char *)cl; cur <= last; cur++)
		if (cur[0] == cs[0] && memcmp(cur, cs, s_len) == 0)
			return cur;

	return NULL;
}


