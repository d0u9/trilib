#ifndef _TRI_CORE_H
#define _TRI_CORE_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef _Bool		bool;

typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;
typedef int8_t		s8;
typedef int16_t		s16;
typedef int32_t		s32;
typedef int64_t		s64;

#undef TRUE
#define TRUE		(1 == 1)
#undef FALSE
#define FALSE		(1 == 0)

#define U8_MAX		((u8)~0U)
#define S8_MAX		((s8)(U8_MAX>>1))
#define S8_MIN		((s8)(-S8_MAX - 1))
#define U16_MAX		((u16)~0U)
#define S16_MAX		((s16)(U16_MAX>>1))
#define S16_MIN		((s16)(-S16_MAX - 1))
#define U32_MAX		((u32)~0U)
#define S32_MAX		((s32)(U32_MAX>>1))
#define S32_MIN		((s32)(-S32_MAX - 1))
#define U64_MAX		((u64)~0ULL)
#define S64_MAX		((s64)(U64_MAX>>1))
#define S64_MIN		((s64)(-S64_MAX - 1))

#if __WORDSIZE == 64
# define BITS_PER_LONG	64
#else
# define BITS_PER_LONG	32
#endif

#define BTS_PER_BYTE	8

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0])

#define __round_mask(x, y) ((__typeof__(x))((y)-1))
#define round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)
#define round_down(x, y) ((x) & ~__round_mask(x, y))

#define FIELD_SIZEOF(t, f) (sizeof(((t*)0)->f))
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define DIV_ROUND_UP_ULL(ll,d) \
	({ unsigned long long _tmp = (ll)+(d)-1; do_div(_tmp, d); _tmp; })

#if BITS_PER_LONG == 32
# define DIV_ROUND_UP_SECTOR_T(ll,d) DIV_ROUND_UP_ULL(ll, d)
#else
# define DIV_ROUND_UP_SECTOR_T(ll,d) DIV_ROUND_UP(ll,d)
#endif

/* The `const' in roundup() prevents gcc-3.3 from calling __divdi3 */
#define roundup(x, y) (					\
{							\
	const typeof(y) __y = y;			\
	(((x) + (__y - 1)) / __y) * __y;		\
}							\
)
#define rounddown(x, y) (				\
{							\
	typeof(x) __x = (x);				\
	__x - (__x % (y));				\
}							\
)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

/*
 * swap - swap value of @a and @b
 */
#define swap(a, b) \
	do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)

extern const char hex_asc[];
#define hex_asc_lo(x)	hex_asc[((x) & 0x0f)]
#define hex_asc_hi(x)	hex_asc[((x) & 0xf0) >> 4]

static inline char *hex_byte_pack(char *buf, u8 byte)
{
	*buf++ = hex_asc_hi(byte);
	*buf++ = hex_asc_lo(byte);
	return buf;
}

extern const char hex_asc_upper[];
#define hex_asc_upper_lo(x)	hex_asc_upper[((x) & 0x0f)]
#define hex_asc_upper_hi(x)	hex_asc_upper[((x) & 0xf0) >> 4]

static inline char *hex_byte_pack_upper(char *buf, u8 byte)
{
	*buf++ = hex_asc_upper_hi(byte);
	*buf++ = hex_asc_upper_lo(byte);
	return buf;
}

/*
 * min()/max()/clamp() macros that also do
 * strict type-checking.. See the
 * "unnecessary" pointer comparison.
 */
#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })

#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })

#define min3(x, y, z) min((typeof(x))min(x, y), z)
#define max3(x, y, z) max((typeof(x))max(x, y), z)

/**
 * min_not_zero - return the minimum that is _not_ zero, unless both are zero
 * @x: value1
 * @y: value2
 */
#define min_not_zero(x, y) ({			\
	typeof(x) __x = (x);			\
	typeof(y) __y = (y);			\
	__x == 0 ? __y : ((__y == 0) ? __x : min(__x, __y)); })

/**
 * clamp - return a value clamped to a given range with strict typechecking
 * @val: current value
 * @lo: lowest allowable value
 * @hi: highest allowable value
 *
 * This macro does strict typechecking of lo/hi to make sure they are of the
 * same type as val.  See the unnecessary pointer comparisons.
 */
#define clamp(val, lo, hi) min((typeof(val))max(val, lo), hi)

/* Indirect stringification.  Doing two levels allows the parameter to be a
 * macro itself.  For example, compile with -DFOO=bar, __stringify(FOO)
 * converts to "bar".
 */
#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

#endif /* _TRI_CORE_H */

