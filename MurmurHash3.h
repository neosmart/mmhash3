//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#ifndef _MURMURHASH3_H_
#define _MURMURHASH3_H_

//-----------------------------------------------------------------------------
// Platform-specific functions and macros

// Microsoft Visual Studio

#if defined(_MSC_VER) && (_MSC_VER < 1600)

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

// Other compilers

#else	// defined(_MSC_VER)

#include <stdint.h>

#endif // !defined(_MSC_VER)

//-----------------------------------------------------------------------------

void MurmurHash3_x86_32(const void * key, int len, uint32_t seed, void * out);

void MurmurHash3_x86_128(const void * key, int len, uint32_t seed, void * out);

inline void MurmurHash3_x86_64(const void * key, int len, uint32_t seed, void * out)
{
	uint64_t temp[2];
	MurmurHash3_x86_128(key, len, seed, &temp);
	((uint64_t *) out)[0] = temp[0];
}

void MurmurHash3_x64_128(const void * key, int len, uint32_t seed, void * out);

inline void MurmurHash3_x64_64(const void * key, int len, uint32_t seed, void * out)
{
	uint64_t temp[2];
	MurmurHash3_x64_128(key, len, seed, &temp);
	((uint64_t *) out)[0] = temp[0];
}

#if defined(_WIN64) || defined(__x86_64__ ) || defined(__ppc64__)
inline void MurmurHash3_128(const void * key, int len, uint32_t seed, void *out)
{
	return MurmurHash3_x64_128(key, len, seed, out);
}
inline void MurmurHash3_64(const void * key, int len, uint32_t seed, void *out)
{
	return MurmurHash3_x64_64(key, len, seed, out);
}
#else
inline void MurmurHash3_128(const void * key, int len, uint32_t seed, void *out)
{
	return MurmurHash3_x86_128(key, len, seed, out);
}
inline void MurmurHash3_64(const void * key, int len, uint32_t seed, void *out)
{
	return MurmurHash3_x86_64(key, len, seed, out);
}
#endif

//-----------------------------------------------------------------------------

#endif // _MURMURHASH3_H_
