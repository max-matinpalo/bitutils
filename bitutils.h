#include <stdint.h>
#include <stdio.h>


// 1. Basic Bit Operations
#define SET_BIT(x, n)		((x) | (1ULL << (n)))
#define CLEAR_BIT(x, n)		((x) & ~(1ULL << (n)))
#define TOGGLE_BIT(x, n)	((x) ^ (1ULL << (n)))
#define TEST_BIT(x, n)		(((x) & (1ULL << (n))) != 0)


/*
	Note: _Generic requires explicit matching for 'unsigned long' because C treats it 
	as a distinct type from 'unsigned int' and 'unsigned long long', even if 
	its bit-width matches one of them on the target architecture.
	Explicit 'unsigned long' match prevents compilation failure when passing 
	standard types like 'uint64_t' that alias to 'unsigned long' on LP64 systems.
*/


// 2. Count Leading Zeros
#define CLZ32(x) ({ \
	unsigned int _x = (x); \
	_x == 0 ? 32 : __builtin_clz(_x); \
})
#define CLZ64(x) ({ \
	unsigned long long _x = (x); \
	_x == 0 ? 64 : __builtin_clzll(_x); \
})
#define CLZLONG(x) ({ \
	unsigned long _x = (x); \
	_x == 0 ? (int)(sizeof(long) * 8) : __builtin_clzl(_x); \
})
#define CLZ(x) _Generic((x), \
	unsigned int: CLZ32(x), \
	unsigned long: CLZLONG(x), \
	unsigned long long: CLZ64(x) \
)


// 3. Count Trailing Zeros
#define CTZ32(x) ({ \
	unsigned int _x = (x); \
	_x == 0 ? 32 : __builtin_ctz(_x); \
})
#define CTZ64(x) ({ \
	unsigned long long _x = (x); \
	_x == 0 ? 64 : __builtin_ctzll(_x); \
})
#define CTZLONG(x) ({ \
	unsigned long _x = (x); \
	_x == 0 ? (int)(sizeof(long) * 8) : __builtin_ctzl(_x); \
})
#define CTZ(x) _Generic((x), \
	unsigned int: CTZ32(x), \
	unsigned long: CTZLONG(x), \
	unsigned long long: CTZ64(x) \
)


// 4. Population Count
#define POPCNT32(x)		__builtin_popcount(x)
#define POPCNT64(x)		__builtin_popcountll(x)
#define POPCNTLONG(x)	__builtin_popcountl(x)
#define POPCNT(x) _Generic((x), \
	unsigned int: POPCNT32(x), \
	unsigned long: POPCNTLONG(x), \
	unsigned long long: POPCNT64(x) \
)


// 5. Bit Scan Reverse (Highest Set Bit Index)
// Returns -1 if x is 0 to avoid ambiguity with bit index 0 (which means x == 1).
#define BSR32(x) ({ \
	unsigned int _x = (x); \
	_x == 0 ? -1 : 31 - __builtin_clz(_x); \
})
#define BSR64(x) ({ \
	unsigned long long _x = (x); \
	_x == 0 ? -1 : 63 - __builtin_clzll(_x); \
})
#define BSRLONG(x) ({ \
	unsigned long _x = (x); \
	_x == 0 ? -1 : (int)(sizeof(long) * 8 - 1) - __builtin_clzl(_x); \
})
#define BSR(x) _Generic((x), \
	unsigned int: BSR32(x), \
	unsigned long: BSRLONG(x), \
	unsigned long long: BSR64(x) \
)


// 6. Clear lowest or highest bit and returns its index or -1 if empty.
#define POPLSB64(p) ({ \
	uint64_t *_p = (p); \
	uint64_t _v = *_p; \
	int _b = _v ? CTZ64(_v) : -1; \
	if (_v) *_p = _v & (_v - 1); \
	_b; \
})
#define POPMSB64(p) ({ \
	uint64_t *_p = (p); \
	uint64_t _v = *_p; \
	int _b = _v ? BSR64(_v) : -1; \
	if (_v) *_p = _v & ~(1ULL << _b); \
	_b; \
})



static inline void logbits_width(uint64_t x, int n)
{
	while (n--)
		putchar("X-"[!(x & (1ULL << n))]), n && !(n & 7) ? putchar(' ') : 0;
	putchar('\n');
}

#define LOGBITS(x) logbits_width((uint64_t)(x), sizeof(x) * 8)