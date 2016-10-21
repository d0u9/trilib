#ifndef _TRI_BITMAP_H
#define _TRI_BITMAP_H

#include <string.h>
#include <strings.h>
#include "core.h"

extern unsigned long find_first_bit(const unsigned long *addr,
				    unsigned long size);
extern unsigned long find_first_zero_bit(const unsigned long *addr,
					 unsigned long size);
extern void bitmap_set(unsigned long *map, unsigned int start, int len);
extern void bitmap_clear(unsigned long *map, unsigned int start, int len);
extern int __bitmap_and(unsigned long *dst, const unsigned long *bitmap1,
			const unsigned long *bitmap2, unsigned int nbits);
extern void __bitmap_or(unsigned long *dst, const unsigned long *bitmap1,
			const unsigned long *bitmap2, unsigned int nbits);
extern void __bitmap_xor(unsigned long *dst, const unsigned long *bitmap1,
			 const unsigned long *bitmap2, unsigned int nbits);
extern int __bitmap_equal(const unsigned long *bitmap1,
			  const unsigned long *bitmap2, unsigned int nbits);

#define ffz(x)		ffs(~(x))

#define BITS_PER_BYTE		8
#define BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#define BIT_WORD(nr)		((nr) / BITS_PER_LONG)

#define BITMAP_FIRST_WORD_MASK(start) (~0UL << ((start) & (BITS_PER_LONG - 1)))
#define BITMAP_LAST_WORD_MASK(nbits) (~0UL >> (-(nbits) & (BITS_PER_LONG - 1)))

#define small_const_nbits(nbits) \
	(__builtin_constant_p(nbits) && (nbits) <= BITS_PER_LONG)

#define DECLARE_BITMAP(name,bits) \
	unsigned long name[BITS_TO_LONGS(bits)]

static inline void bitmap_zero(unsigned long *dst, int nbits)
{
	if (small_const_nbits(nbits))
		*dst = 0UL;
	else {
		int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);
		memset(dst, 0, len);
	}
}

static inline void bitmap_fill(unsigned long *dst, int nbits)
{
	size_t nlongs = BITS_TO_LONGS(nbits);
	if (!small_const_nbits(nbits)) {
		int len = (nlongs - 1) * sizeof(unsigned long);
		memset(dst, 0xff,  len);
	}
	dst[nlongs - 1] = BITMAP_LAST_WORD_MASK(nbits);
}

static inline void bitmap_copy(unsigned long *dst, const unsigned long *src,
			       unsigned int nbits)
{
	if (small_const_nbits(nbits))
		*dst = *src;
	else {
		unsigned int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);
		memcpy(dst, src, len);
	}
}

static inline int bitmap_and(unsigned long *dst, const unsigned long *src1,
			     const unsigned long *src2, unsigned int nbits)
{
	if (small_const_nbits(nbits))
		return (*dst = *src1 & *src2 & BITMAP_LAST_WORD_MASK(nbits)) != 0;
	return __bitmap_and(dst, src1, src2, nbits);
}

static inline void bitmap_or(unsigned long *dst, const unsigned long *src1,
			     const unsigned long *src2, unsigned int nbits)
{
	if (small_const_nbits(nbits))
		*dst = *src1 | *src2;
	else
		__bitmap_or(dst, src1, src2, nbits);
}

static inline void bitmap_xor(unsigned long *dst, const unsigned long *src1,
			      const unsigned long *src2, unsigned int nbits)
{
	if (small_const_nbits(nbits))
		*dst = *src1 ^ *src2;
	else
		__bitmap_xor(dst, src1, src2, nbits);
}

static inline int bitmap_equal(const unsigned long *src1,
			       const unsigned long *src2, unsigned int nbits)
{
	if (small_const_nbits(nbits))
		return ! ((*src1 ^ *src2) & BITMAP_LAST_WORD_MASK(nbits));
	else
		return __bitmap_equal(src1, src2, nbits);
}

static inline int bitmap_empty(const unsigned long *src, unsigned nbits)
{
	if (small_const_nbits(nbits))
		return ! (*src & BITMAP_LAST_WORD_MASK(nbits));

	return find_first_bit(src, nbits) == nbits;
}

static inline int bitmap_full(const unsigned long *src, unsigned int nbits)
{
	if (small_const_nbits(nbits))
		return ! (~(*src) & BITMAP_LAST_WORD_MASK(nbits));

	return find_first_zero_bit(src, nbits) == nbits;
}

static inline void set_bit(unsigned long nr, volatile void *addr)
{
	volatile unsigned long *a = addr;
	unsigned long mask;

#if BITS_PER_LONG == 32
	a += nr >> 5;
	mask = 1UL << (nr & 31);
#else
	a += nr >> 6;
	mask = 1UL << (nr & 63);
#endif
	*a |= mask;
}

static inline void clear_bit(unsigned long nr, volatile void *addr)
{
	volatile unsigned long *a = addr;
	unsigned long mask;

#if BITS_PER_LONG == 32
	a += nr >> 5;
	mask = 1UL << (nr & 31);
#else
	a += nr >> 6;
	mask = 1UL << (nr & 63);
#endif
	*a &= ~mask;
}

static inline bool test_bit(unsigned long nr, volatile void *addr)
{
	volatile unsigned long *a = addr;
	unsigned long mask;

#if BITS_PER_LONG == 32
	a += nr >> 5;
	mask = 1UL << (nr & 31);
#else
	a += nr >> 6;
	mask = 1UL << (nr & 63);
#endif
	return ((*a & mask) != 0);
}

#endif
