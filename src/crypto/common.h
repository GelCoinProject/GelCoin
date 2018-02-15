<<<<<<< HEAD
// Copyright (c) 2014 The Bitcoin Core developers
=======
// Copyright (c) 2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CRYPTO_COMMON_H
#define BITCOIN_CRYPTO_COMMON_H

<<<<<<< HEAD
#if defined(HAVE_CONFIG_H)
#include "gelcoin-config.h"
#endif

#include <stdint.h>

#include "compat/endian.h"

uint16_t static inline ReadLE16(const unsigned char* ptr)
{
    return le16toh(*((uint16_t*)ptr));
}

uint32_t static inline ReadLE32(const unsigned char* ptr)
{
    return le32toh(*((uint32_t*)ptr));
=======
#include <stdint.h>

#if defined(HAVE_ENDIAN_H)
#include <endian.h>
#endif

uint32_t static inline ReadLE32(const unsigned char* ptr)
{
#if HAVE_DECL_LE32TOH == 1
    return le32toh(*((uint32_t*)ptr));
#elif !defined(WORDS_BIGENDIAN)
    return *((uint32_t*)ptr);
#else
    return ((uint32_t)ptr[3] << 24 | (uint32_t)ptr[2] << 16 | (uint32_t)ptr[1] << 8 | (uint32_t)ptr[0]);
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

uint64_t static inline ReadLE64(const unsigned char* ptr)
{
<<<<<<< HEAD
    return le64toh(*((uint64_t*)ptr));
}

void static inline WriteLE16(unsigned char* ptr, uint16_t x)
{
    *((uint16_t*)ptr) = htole16(x);
=======
#if HAVE_DECL_LE64TOH == 1
    return le64toh(*((uint64_t*)ptr));
#elif !defined(WORDS_BIGENDIAN)
    return *((uint64_t*)ptr);
#else
    return ((uint64_t)ptr[7] << 56 | (uint64_t)ptr[6] << 48 | (uint64_t)ptr[5] << 40 | (uint64_t)ptr[4] << 32 |
            (uint64_t)ptr[3] << 24 | (uint64_t)ptr[2] << 16 | (uint64_t)ptr[1] << 8 | (uint64_t)ptr[0]);
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void static inline WriteLE32(unsigned char* ptr, uint32_t x)
{
<<<<<<< HEAD
    *((uint32_t*)ptr) = htole32(x);
=======
#if HAVE_DECL_HTOLE32 == 1
    *((uint32_t*)ptr) = htole32(x);
#elif !defined(WORDS_BIGENDIAN)
    *((uint32_t*)ptr) = x;
#else
    ptr[3] = x >> 24;
    ptr[2] = x >> 16;
    ptr[1] = x >> 8;
    ptr[0] = x;
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void static inline WriteLE64(unsigned char* ptr, uint64_t x)
{
<<<<<<< HEAD
    *((uint64_t*)ptr) = htole64(x);
=======
#if HAVE_DECL_HTOLE64 == 1
    *((uint64_t*)ptr) = htole64(x);
#elif !defined(WORDS_BIGENDIAN)
    *((uint64_t*)ptr) = x;
#else
    ptr[7] = x >> 56;
    ptr[6] = x >> 48;
    ptr[5] = x >> 40;
    ptr[4] = x >> 32;
    ptr[3] = x >> 24;
    ptr[2] = x >> 16;
    ptr[1] = x >> 8;
    ptr[0] = x;
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

uint32_t static inline ReadBE32(const unsigned char* ptr)
{
<<<<<<< HEAD
    return be32toh(*((uint32_t*)ptr));
=======
#if HAVE_DECL_BE32TOH == 1
    return be32toh(*((uint32_t*)ptr));
#else
    return ((uint32_t)ptr[0] << 24 | (uint32_t)ptr[1] << 16 | (uint32_t)ptr[2] << 8 | (uint32_t)ptr[3]);
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

uint64_t static inline ReadBE64(const unsigned char* ptr)
{
<<<<<<< HEAD
    return be64toh(*((uint64_t*)ptr));
=======
#if HAVE_DECL_BE64TOH == 1
    return be64toh(*((uint64_t*)ptr));
#else
    return ((uint64_t)ptr[0] << 56 | (uint64_t)ptr[1] << 48 | (uint64_t)ptr[2] << 40 | (uint64_t)ptr[3] << 32 |
            (uint64_t)ptr[4] << 24 | (uint64_t)ptr[5] << 16 | (uint64_t)ptr[6] << 8 | (uint64_t)ptr[7]);
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void static inline WriteBE32(unsigned char* ptr, uint32_t x)
{
<<<<<<< HEAD
    *((uint32_t*)ptr) = htobe32(x);
=======
#if HAVE_DECL_HTOBE32 == 1
    *((uint32_t*)ptr) = htobe32(x);
#else
    ptr[0] = x >> 24;
    ptr[1] = x >> 16;
    ptr[2] = x >> 8;
    ptr[3] = x;
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void static inline WriteBE64(unsigned char* ptr, uint64_t x)
{
<<<<<<< HEAD
    *((uint64_t*)ptr) = htobe64(x);
=======
#if HAVE_DECL_HTOBE64 == 1
    *((uint64_t*)ptr) = htobe64(x);
#else
    ptr[0] = x >> 56;
    ptr[1] = x >> 48;
    ptr[2] = x >> 40;
    ptr[3] = x >> 32;
    ptr[4] = x >> 24;
    ptr[5] = x >> 16;
    ptr[6] = x >> 8;
    ptr[7] = x;
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

#endif // BITCOIN_CRYPTO_COMMON_H
