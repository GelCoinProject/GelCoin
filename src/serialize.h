<<<<<<< HEAD
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto                     -*- c++ -*-
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SERIALIZE_H
#define BITCOIN_SERIALIZE_H

<<<<<<< HEAD
#include "compat/endian.h"

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <algorithm>
#include <assert.h>
#include <ios>
#include <limits>
<<<<<<< HEAD
#include <list>
#include <map>
#include <set>
#include <stdint.h>
#include <string>
#include <string.h>
#include <utility>
#include <vector>

#include "prevector.h"
=======
#include <map>
#include <set>
#include <stdint.h>
#include <string.h>
#include <string>
#include <utility>
#include <vector>

class CScript;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

static const unsigned int MAX_SIZE = 0x02000000;

/**
 * Used to bypass the rule against non-const reference to temporary
 * where it makes sense with wrappers such as CFlatData or CTxDB
 */
<<<<<<< HEAD
template<typename T>
=======
template <typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
inline T& REF(const T& val)
{
    return const_cast<T&>(val);
}

/**
 * Used to acquire a non-const pointer "this" to generate bodies
 * of const serialization operations from a template
 */
<<<<<<< HEAD
template<typename T>
=======
template <typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
inline T* NCONST_PTR(const T* val)
{
    return const_cast<T*>(val);
}

/** 
 * Get begin pointer of vector (non-const version).
 * @note These functions avoid the undefined case of indexing into an empty
 * vector, as well as that of indexing after the end of the vector.
 */
<<<<<<< HEAD
template <typename V>
inline typename V::value_type* begin_ptr(V& v)
=======
template <class T, class TAl>
inline T* begin_ptr(std::vector<T, TAl>& v)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return v.empty() ? NULL : &v[0];
}
/** Get begin pointer of vector (const version) */
<<<<<<< HEAD
template <typename V>
inline const typename V::value_type* begin_ptr(const V& v)
=======
template <class T, class TAl>
inline const T* begin_ptr(const std::vector<T, TAl>& v)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return v.empty() ? NULL : &v[0];
}
/** Get end pointer of vector (non-const version) */
<<<<<<< HEAD
template <typename V>
inline typename V::value_type* end_ptr(V& v)
=======
template <class T, class TAl>
inline T* end_ptr(std::vector<T, TAl>& v)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return v.empty() ? NULL : (&v[0] + v.size());
}
/** Get end pointer of vector (const version) */
<<<<<<< HEAD
template <typename V>
inline const typename V::value_type* end_ptr(const V& v)
=======
template <class T, class TAl>
inline const T* end_ptr(const std::vector<T, TAl>& v)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return v.empty() ? NULL : (&v[0] + v.size());
}

<<<<<<< HEAD
/*
 * Lowest-level serialization and conversion.
 * @note Sizes of these types are verified in the tests
 */
template<typename Stream> inline void ser_writedata8(Stream &s, uint8_t obj)
{
    s.write((char*)&obj, 1);
}
template<typename Stream> inline void ser_writedata16(Stream &s, uint16_t obj)
{
    obj = htole16(obj);
    s.write((char*)&obj, 2);
}
template<typename Stream> inline void ser_writedata32(Stream &s, uint32_t obj)
{
    obj = htole32(obj);
    s.write((char*)&obj, 4);
}
template<typename Stream> inline void ser_writedata32be(Stream &s, uint32_t obj)
{
    obj = htobe32(obj);
    s.write((char*)&obj, 4);
}
template<typename Stream> inline void ser_writedata64(Stream &s, uint64_t obj)
{
    obj = htole64(obj);
    s.write((char*)&obj, 8);
}
template<typename Stream> inline uint8_t ser_readdata8(Stream &s)
{
    uint8_t obj;
    s.read((char*)&obj, 1);
    return obj;
}
template<typename Stream> inline uint16_t ser_readdata16(Stream &s)
{
    uint16_t obj;
    s.read((char*)&obj, 2);
    return le16toh(obj);
}
template<typename Stream> inline uint32_t ser_readdata32(Stream &s)
{
    uint32_t obj;
    s.read((char*)&obj, 4);
    return le32toh(obj);
}
template<typename Stream> inline uint32_t ser_readdata32be(Stream &s)
{
    uint32_t obj;
    s.read((char*)&obj, 4);
    return be32toh(obj);
}
template<typename Stream> inline uint64_t ser_readdata64(Stream &s)
{
    uint64_t obj;
    s.read((char*)&obj, 8);
    return le64toh(obj);
}
inline uint64_t ser_double_to_uint64(double x)
{
    union { double x; uint64_t y; } tmp;
    tmp.x = x;
    return tmp.y;
}
inline uint32_t ser_float_to_uint32(float x)
{
    union { float x; uint32_t y; } tmp;
    tmp.x = x;
    return tmp.y;
}
inline double ser_uint64_to_double(uint64_t y)
{
    union { double x; uint64_t y; } tmp;
    tmp.y = y;
    return tmp.x;
}
inline float ser_uint32_to_float(uint32_t y)
{
    union { float x; uint32_t y; } tmp;
    tmp.y = y;
    return tmp.x;
}


/////////////////////////////////////////////////////////////////
//
// Templates for serializing to anything that looks like a stream,
// i.e. anything that supports .read(char*, size_t) and .write(char*, size_t)
//

enum
{
    // primary actions
    SER_NETWORK         = (1 << 0),
    SER_DISK            = (1 << 1),
    SER_GETHASH         = (1 << 2),
};

#define READWRITE(obj)      (::SerReadWrite(s, (obj), nType, nVersion, ser_action))
#define READWRITEMANY(...)      (::SerReadWriteMany(s, nType, nVersion, ser_action, __VA_ARGS__))

/** 
 * Implement three methods for serializable objects. These are actually wrappers over
 * "SerializationOp" template, which implements the body of each class' serialization
 * code. Adding "ADD_SERIALIZE_METHODS" in the body of the class causes these wrappers to be
 * added as members. 
 */
#define ADD_SERIALIZE_METHODS                                                          \
    size_t GetSerializeSize(int nType, int nVersion) const {                         \
        CSizeComputer s(nType, nVersion);                                            \
        NCONST_PTR(this)->SerializationOp(s, CSerActionSerialize(), nType, nVersion);\
        return s.size();                                                             \
    }                                                                                \
    template<typename Stream>                                                        \
    void Serialize(Stream& s, int nType, int nVersion) const {                       \
        NCONST_PTR(this)->SerializationOp(s, CSerActionSerialize(), nType, nVersion);\
    }                                                                                \
    template<typename Stream>                                                        \
    void Unserialize(Stream& s, int nType, int nVersion) {                           \
        SerializationOp(s, CSerActionUnserialize(), nType, nVersion);                \
    }

/*
 * Basic Types
 */
inline unsigned int GetSerializeSize(char a,      int, int=0) { return 1; }
inline unsigned int GetSerializeSize(int8_t a,    int, int=0) { return 1; }
inline unsigned int GetSerializeSize(uint8_t a,   int, int=0) { return 1; }
inline unsigned int GetSerializeSize(int16_t a,   int, int=0) { return 2; }
inline unsigned int GetSerializeSize(uint16_t a,  int, int=0) { return 2; }
inline unsigned int GetSerializeSize(int32_t a,   int, int=0) { return 4; }
inline unsigned int GetSerializeSize(uint32_t a,  int, int=0) { return 4; }
inline unsigned int GetSerializeSize(int64_t a,   int, int=0) { return 8; }
inline unsigned int GetSerializeSize(uint64_t a,  int, int=0) { return 8; }
inline unsigned int GetSerializeSize(float a,     int, int=0) { return 4; }
inline unsigned int GetSerializeSize(double a,    int, int=0) { return 8; }

template<typename Stream> inline void Serialize(Stream& s, char a,         int, int=0) { ser_writedata8(s, a); } // TODO Get rid of bare char
template<typename Stream> inline void Serialize(Stream& s, int8_t a,       int, int=0) { ser_writedata8(s, a); }
template<typename Stream> inline void Serialize(Stream& s, uint8_t a,      int, int=0) { ser_writedata8(s, a); }
template<typename Stream> inline void Serialize(Stream& s, int16_t a,      int, int=0) { ser_writedata16(s, a); }
template<typename Stream> inline void Serialize(Stream& s, uint16_t a,     int, int=0) { ser_writedata16(s, a); }
template<typename Stream> inline void Serialize(Stream& s, int32_t a,      int, int=0) { ser_writedata32(s, a); }
template<typename Stream> inline void Serialize(Stream& s, uint32_t a,     int, int=0) { ser_writedata32(s, a); }
template<typename Stream> inline void Serialize(Stream& s, int64_t a,      int, int=0) { ser_writedata64(s, a); }
template<typename Stream> inline void Serialize(Stream& s, uint64_t a,     int, int=0) { ser_writedata64(s, a); }
template<typename Stream> inline void Serialize(Stream& s, float a,        int, int=0) { ser_writedata32(s, ser_float_to_uint32(a)); }
template<typename Stream> inline void Serialize(Stream& s, double a,       int, int=0) { ser_writedata64(s, ser_double_to_uint64(a)); }

template<typename Stream> inline void Unserialize(Stream& s, char& a,      int, int=0) { a = ser_readdata8(s); } // TODO Get rid of bare char
template<typename Stream> inline void Unserialize(Stream& s, int8_t& a,    int, int=0) { a = ser_readdata8(s); }
template<typename Stream> inline void Unserialize(Stream& s, uint8_t& a,   int, int=0) { a = ser_readdata8(s); }
template<typename Stream> inline void Unserialize(Stream& s, int16_t& a,   int, int=0) { a = ser_readdata16(s); }
template<typename Stream> inline void Unserialize(Stream& s, uint16_t& a,  int, int=0) { a = ser_readdata16(s); }
template<typename Stream> inline void Unserialize(Stream& s, int32_t& a,   int, int=0) { a = ser_readdata32(s); }
template<typename Stream> inline void Unserialize(Stream& s, uint32_t& a,  int, int=0) { a = ser_readdata32(s); }
template<typename Stream> inline void Unserialize(Stream& s, int64_t& a,   int, int=0) { a = ser_readdata64(s); }
template<typename Stream> inline void Unserialize(Stream& s, uint64_t& a,  int, int=0) { a = ser_readdata64(s); }
template<typename Stream> inline void Unserialize(Stream& s, float& a,     int, int=0) { a = ser_uint32_to_float(ser_readdata32(s)); }
template<typename Stream> inline void Unserialize(Stream& s, double& a,    int, int=0) { a = ser_uint64_to_double(ser_readdata64(s)); }

inline unsigned int GetSerializeSize(bool a, int, int=0)                          { return sizeof(char); }
template<typename Stream> inline void Serialize(Stream& s, bool a, int, int=0)    { char f=a; ser_writedata8(s, f); }
template<typename Stream> inline void Unserialize(Stream& s, bool& a, int, int=0) { char f=ser_readdata8(s); a=f; }




=======
/////////////////////////////////////////////////////////////////
//
// Templates for serializing to anything that looks like a stream,
// i.e. anything that supports .read(char*, size_t) and .write(char*, size_t)
//

enum {
    // primary actions
    SER_NETWORK = (1 << 0),
    SER_DISK = (1 << 1),
    SER_GETHASH = (1 << 2),
};

#define READWRITE(obj) (::SerReadWrite(s, (obj), nType, nVersion, ser_action))

/** 
 * Implement three methods for serializable objects. These are actually wrappers over
 * "SerializationOp" template, which implements the body of each class' serialization
 * code. Adding "ADD_SERIALIZE_METHODS" in the body of the class causes these wrappers to be
 * added as members. 
 */
#define ADD_SERIALIZE_METHODS                                                         \
    size_t GetSerializeSize(int nType, int nVersion) const                            \
    {                                                                                 \
        CSizeComputer s(nType, nVersion);                                             \
        NCONST_PTR(this)->SerializationOp(s, CSerActionSerialize(), nType, nVersion); \
        return s.size();                                                              \
    }                                                                                 \
    template <typename Stream>                                                        \
    void Serialize(Stream& s, int nType, int nVersion) const                          \
    {                                                                                 \
        NCONST_PTR(this)->SerializationOp(s, CSerActionSerialize(), nType, nVersion); \
    }                                                                                 \
    template <typename Stream>                                                        \
    void Unserialize(Stream& s, int nType, int nVersion)                              \
    {                                                                                 \
        SerializationOp(s, CSerActionUnserialize(), nType, nVersion);                 \
    }


/*
 * Basic Types
 */
#define WRITEDATA(s, obj) s.write((char*)&(obj), sizeof(obj))
#define READDATA(s, obj) s.read((char*)&(obj), sizeof(obj))

inline unsigned int GetSerializeSize(char a, int, int = 0)
{
    return sizeof(a);
}
inline unsigned int GetSerializeSize(signed char a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(unsigned char a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(signed short a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(unsigned short a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(signed int a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(unsigned int a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(signed long a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(unsigned long a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(signed long long a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(unsigned long long a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(float a, int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(double a, int, int = 0) { return sizeof(a); }

template <typename Stream>
inline void Serialize(Stream& s, char a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, signed char a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, unsigned char a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, signed short a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, unsigned short a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, signed int a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, unsigned int a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, signed long a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, unsigned long a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, signed long long a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, unsigned long long a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, float a, int, int = 0)
{
    WRITEDATA(s, a);
}
template <typename Stream>
inline void Serialize(Stream& s, double a, int, int = 0)
{
    WRITEDATA(s, a);
}

template <typename Stream>
inline void Unserialize(Stream& s, char& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, signed char& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, unsigned char& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, signed short& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, unsigned short& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, signed int& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, unsigned int& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, signed long& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, unsigned long& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, signed long long& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, unsigned long long& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, float& a, int, int = 0)
{
    READDATA(s, a);
}
template <typename Stream>
inline void Unserialize(Stream& s, double& a, int, int = 0)
{
    READDATA(s, a);
}

inline unsigned int GetSerializeSize(bool a, int, int = 0) { return sizeof(char); }
template <typename Stream>
inline void Serialize(Stream& s, bool a, int, int = 0)
{
    char f = a;
    WRITEDATA(s, f);
}
template <typename Stream>
inline void Unserialize(Stream& s, bool& a, int, int = 0)
{
    char f;
    READDATA(s, f);
    a = f;
}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3


/**
 * Compact Size
 * size <  253        -- 1 byte
 * size <= USHRT_MAX  -- 3 bytes  (253 + 2 bytes)
 * size <= UINT_MAX   -- 5 bytes  (254 + 4 bytes)
 * size >  UINT_MAX   -- 9 bytes  (255 + 8 bytes)
 */
inline unsigned int GetSizeOfCompactSize(uint64_t nSize)
{
<<<<<<< HEAD
    if (nSize < 253)             return sizeof(unsigned char);
    else if (nSize <= std::numeric_limits<unsigned short>::max()) return sizeof(unsigned char) + sizeof(unsigned short);
    else if (nSize <= std::numeric_limits<unsigned int>::max())  return sizeof(unsigned char) + sizeof(unsigned int);
    else                         return sizeof(unsigned char) + sizeof(uint64_t);
}

template<typename Stream>
void WriteCompactSize(Stream& os, uint64_t nSize)
{
    if (nSize < 253)
    {
        ser_writedata8(os, nSize);
    }
    else if (nSize <= std::numeric_limits<unsigned short>::max())
    {
        ser_writedata8(os, 253);
        ser_writedata16(os, nSize);
    }
    else if (nSize <= std::numeric_limits<unsigned int>::max())
    {
        ser_writedata8(os, 254);
        ser_writedata32(os, nSize);
    }
    else
    {
        ser_writedata8(os, 255);
        ser_writedata64(os, nSize);
=======
    if (nSize < 253)
        return sizeof(unsigned char);
    else if (nSize <= std::numeric_limits<unsigned short>::max())
        return sizeof(unsigned char) + sizeof(unsigned short);
    else if (nSize <= std::numeric_limits<unsigned int>::max())
        return sizeof(unsigned char) + sizeof(unsigned int);
    else
        return sizeof(unsigned char) + sizeof(uint64_t);
}

template <typename Stream>
void WriteCompactSize(Stream& os, uint64_t nSize)
{
    if (nSize < 253) {
        unsigned char chSize = nSize;
        WRITEDATA(os, chSize);
    } else if (nSize <= std::numeric_limits<unsigned short>::max()) {
        unsigned char chSize = 253;
        unsigned short xSize = nSize;
        WRITEDATA(os, chSize);
        WRITEDATA(os, xSize);
    } else if (nSize <= std::numeric_limits<unsigned int>::max()) {
        unsigned char chSize = 254;
        unsigned int xSize = nSize;
        WRITEDATA(os, chSize);
        WRITEDATA(os, xSize);
    } else {
        unsigned char chSize = 255;
        uint64_t xSize = nSize;
        WRITEDATA(os, chSize);
        WRITEDATA(os, xSize);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
    return;
}

<<<<<<< HEAD
template<typename Stream>
uint64_t ReadCompactSize(Stream& is)
{
    uint8_t chSize = ser_readdata8(is);
    uint64_t nSizeRet = 0;
    if (chSize < 253)
    {
        nSizeRet = chSize;
    }
    else if (chSize == 253)
    {
        nSizeRet = ser_readdata16(is);
        if (nSizeRet < 253)
            throw std::ios_base::failure("non-canonical ReadCompactSize()");
    }
    else if (chSize == 254)
    {
        nSizeRet = ser_readdata32(is);
        if (nSizeRet < 0x10000u)
            throw std::ios_base::failure("non-canonical ReadCompactSize()");
    }
    else
    {
        nSizeRet = ser_readdata64(is);
=======
template <typename Stream>
uint64_t ReadCompactSize(Stream& is)
{
    unsigned char chSize;
    READDATA(is, chSize);
    uint64_t nSizeRet = 0;
    if (chSize < 253) {
        nSizeRet = chSize;
    } else if (chSize == 253) {
        unsigned short xSize;
        READDATA(is, xSize);
        nSizeRet = xSize;
        if (nSizeRet < 253)
            throw std::ios_base::failure("non-canonical ReadCompactSize()");
    } else if (chSize == 254) {
        unsigned int xSize;
        READDATA(is, xSize);
        nSizeRet = xSize;
        if (nSizeRet < 0x10000u)
            throw std::ios_base::failure("non-canonical ReadCompactSize()");
    } else {
        uint64_t xSize;
        READDATA(is, xSize);
        nSizeRet = xSize;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (nSizeRet < 0x100000000ULL)
            throw std::ios_base::failure("non-canonical ReadCompactSize()");
    }
    if (nSizeRet > (uint64_t)MAX_SIZE)
<<<<<<< HEAD
        throw std::ios_base::failure("ReadCompactSize(): size too large");
=======
        throw std::ios_base::failure("ReadCompactSize() : size too large");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    return nSizeRet;
}

/**
 * Variable-length integers: bytes are a MSB base-128 encoding of the number.
 * The high bit in each byte signifies whether another digit follows. To make
 * sure the encoding is one-to-one, one is subtracted from all but the last digit.
 * Thus, the byte sequence a[] with length len, where all but the last byte
 * has bit 128 set, encodes the number:
 * 
 *  (a[len-1] & 0x7F) + sum(i=1..len-1, 128^i*((a[len-i-1] & 0x7F)+1))
 * 
 * Properties:
 * * Very small (0-127: 1 byte, 128-16511: 2 bytes, 16512-2113663: 3 bytes)
 * * Every integer has exactly one encoding
 * * Encoding does not depend on size of original integer type
 * * No redundancy: every (infinite) byte sequence corresponds to a list
 *   of encoded integers.
 * 
 * 0:         [0x00]  256:        [0x81 0x00]
 * 1:         [0x01]  16383:      [0xFE 0x7F]
 * 127:       [0x7F]  16384:      [0xFF 0x00]
 * 128:  [0x80 0x00]  16511: [0x80 0xFF 0x7F]
 * 255:  [0x80 0x7F]  65535: [0x82 0xFD 0x7F]
 * 2^32:           [0x8E 0xFE 0xFE 0xFF 0x00]
 */

<<<<<<< HEAD
template<typename I>
inline unsigned int GetSizeOfVarInt(I n)
{
    int nRet = 0;
    while(true) {
=======
template <typename I>
inline unsigned int GetSizeOfVarInt(I n)
{
    int nRet = 0;
    while (true) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        nRet++;
        if (n <= 0x7F)
            break;
        n = (n >> 7) - 1;
    }
    return nRet;
}

<<<<<<< HEAD
template<typename Stream, typename I>
void WriteVarInt(Stream& os, I n)
{
    unsigned char tmp[(sizeof(n)*8+6)/7];
    int len=0;
    while(true) {
=======
template <typename Stream, typename I>
void WriteVarInt(Stream& os, I n)
{
    unsigned char tmp[(sizeof(n) * 8 + 6) / 7];
    int len = 0;
    while (true) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        tmp[len] = (n & 0x7F) | (len ? 0x80 : 0x00);
        if (n <= 0x7F)
            break;
        n = (n >> 7) - 1;
        len++;
    }
    do {
<<<<<<< HEAD
        ser_writedata8(os, tmp[len]);
    } while(len--);
}

template<typename Stream, typename I>
I ReadVarInt(Stream& is)
{
    I n = 0;
    while(true) {
        unsigned char chData = ser_readdata8(is);
=======
        WRITEDATA(os, tmp[len]);
    } while (len--);
}

template <typename Stream, typename I>
I ReadVarInt(Stream& is)
{
    I n = 0;
    while (true) {
        unsigned char chData;
        READDATA(is, chData);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        n = (n << 7) | (chData & 0x7F);
        if (chData & 0x80)
            n++;
        else
            return n;
    }
}

#define FLATDATA(obj) REF(CFlatData((char*)&(obj), (char*)&(obj) + sizeof(obj)))
#define VARINT(obj) REF(WrapVarInt(REF(obj)))
<<<<<<< HEAD
#define COMPACTSIZE(obj) REF(CCompactSize(REF(obj)))
#define LIMITED_STRING(obj,n) REF(LimitedString< n >(REF(obj)))
=======
#define LIMITED_STRING(obj, n) REF(LimitedString<n>(REF(obj)))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

/** 
 * Wrapper for serializing arrays and POD.
 */
class CFlatData
{
protected:
    char* pbegin;
    char* pend;
<<<<<<< HEAD
public:
    CFlatData(void* pbeginIn, void* pendIn) : pbegin((char*)pbeginIn), pend((char*)pendIn) { }
    template <class T, class TAl>
    explicit CFlatData(std::vector<T,TAl> &v)
    {
        pbegin = (char*)begin_ptr(v);
        pend = (char*)end_ptr(v);
    }
    template <unsigned int N, typename T, typename S, typename D>
    explicit CFlatData(prevector<N, T, S, D> &v)
=======

public:
    CFlatData(void* pbeginIn, void* pendIn) : pbegin((char*)pbeginIn), pend((char*)pendIn) {}
    template <class T, class TAl>
    explicit CFlatData(std::vector<T, TAl>& v)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        pbegin = (char*)begin_ptr(v);
        pend = (char*)end_ptr(v);
    }
    char* begin() { return pbegin; }
    const char* begin() const { return pbegin; }
    char* end() { return pend; }
    const char* end() const { return pend; }

<<<<<<< HEAD
    unsigned int GetSerializeSize(int, int=0) const
=======
    unsigned int GetSerializeSize(int, int = 0) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        return pend - pbegin;
    }

<<<<<<< HEAD
    template<typename Stream>
    void Serialize(Stream& s, int, int=0) const
=======
    template <typename Stream>
    void Serialize(Stream& s, int, int = 0) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        s.write(pbegin, pend - pbegin);
    }

<<<<<<< HEAD
    template<typename Stream>
    void Unserialize(Stream& s, int, int=0)
=======
    template <typename Stream>
    void Unserialize(Stream& s, int, int = 0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        s.read(pbegin, pend - pbegin);
    }
};

<<<<<<< HEAD
template<typename I>
class CVarInt
{
protected:
    I &n;
public:
    CVarInt(I& nIn) : n(nIn) { }

    unsigned int GetSerializeSize(int, int) const {
        return GetSizeOfVarInt<I>(n);
    }

    template<typename Stream>
    void Serialize(Stream &s, int, int) const {
        WriteVarInt<Stream,I>(s, n);
    }

    template<typename Stream>
    void Unserialize(Stream& s, int, int) {
        n = ReadVarInt<Stream,I>(s);
    }
};

class CCompactSize
{
protected:
    uint64_t &n;
public:
    CCompactSize(uint64_t& nIn) : n(nIn) { }

    unsigned int GetSerializeSize(int, int) const {
        return GetSizeOfCompactSize(n);
    }

    template<typename Stream>
    void Serialize(Stream &s, int, int) const {
        WriteCompactSize<Stream>(s, n);
    }

    template<typename Stream>
    void Unserialize(Stream& s, int, int) {
        n = ReadCompactSize<Stream>(s);
    }
};

template<size_t Limit>
=======
template <typename I>
class CVarInt
{
protected:
    I& n;

public:
    CVarInt(I& nIn) : n(nIn) {}

    unsigned int GetSerializeSize(int, int) const
    {
        return GetSizeOfVarInt<I>(n);
    }

    template <typename Stream>
    void Serialize(Stream& s, int, int) const
    {
        WriteVarInt<Stream, I>(s, n);
    }

    template <typename Stream>
    void Unserialize(Stream& s, int, int)
    {
        n = ReadVarInt<Stream, I>(s);
    }
};

template <size_t Limit>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class LimitedString
{
protected:
    std::string& string;
<<<<<<< HEAD
public:
    LimitedString(std::string& string) : string(string) {}

    template<typename Stream>
    void Unserialize(Stream& s, int, int=0)
=======

public:
    LimitedString(std::string& string) : string(string) {}

    template <typename Stream>
    void Unserialize(Stream& s, int, int = 0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        size_t size = ReadCompactSize(s);
        if (size > Limit) {
            throw std::ios_base::failure("String length limit exceeded");
        }
        string.resize(size);
        if (size != 0)
            s.read((char*)&string[0], size);
    }

<<<<<<< HEAD
    template<typename Stream>
    void Serialize(Stream& s, int, int=0) const
=======
    template <typename Stream>
    void Serialize(Stream& s, int, int = 0) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        WriteCompactSize(s, string.size());
        if (!string.empty())
            s.write((char*)&string[0], string.size());
    }

<<<<<<< HEAD
    unsigned int GetSerializeSize(int, int=0) const
=======
    unsigned int GetSerializeSize(int, int = 0) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        return GetSizeOfCompactSize(string.size()) + string.size();
    }
};

<<<<<<< HEAD
template<typename I>
CVarInt<I> WrapVarInt(I& n) { return CVarInt<I>(n); }
=======
template <typename I>
CVarInt<I> WrapVarInt(I& n)
{
    return CVarInt<I>(n);
}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

/**
 * Forward declarations
 */

/**
 *  string
 */
<<<<<<< HEAD
template<typename C> unsigned int GetSerializeSize(const std::basic_string<C>& str, int, int=0);
template<typename Stream, typename C> void Serialize(Stream& os, const std::basic_string<C>& str, int, int=0);
template<typename Stream, typename C> void Unserialize(Stream& is, std::basic_string<C>& str, int, int=0);

/**
 * prevector
 * prevectors of unsigned char are a special case and are intended to be serialized as a single opaque blob.
 */
template<unsigned int N, typename T> unsigned int GetSerializeSize_impl(const prevector<N, T>& v, int nType, int nVersion, const unsigned char&);
template<unsigned int N, typename T, typename V> unsigned int GetSerializeSize_impl(const prevector<N, T>& v, int nType, int nVersion, const V&);
template<unsigned int N, typename T> inline unsigned int GetSerializeSize(const prevector<N, T>& v, int nType, int nVersion);
template<typename Stream, unsigned int N, typename T> void Serialize_impl(Stream& os, const prevector<N, T>& v, int nType, int nVersion, const unsigned char&);
template<typename Stream, unsigned int N, typename T, typename V> void Serialize_impl(Stream& os, const prevector<N, T>& v, int nType, int nVersion, const V&);
template<typename Stream, unsigned int N, typename T> inline void Serialize(Stream& os, const prevector<N, T>& v, int nType, int nVersion);
template<typename Stream, unsigned int N, typename T> void Unserialize_impl(Stream& is, prevector<N, T>& v, int nType, int nVersion, const unsigned char&);
template<typename Stream, unsigned int N, typename T, typename V> void Unserialize_impl(Stream& is, prevector<N, T>& v, int nType, int nVersion, const V&);
template<typename Stream, unsigned int N, typename T> inline void Unserialize(Stream& is, prevector<N, T>& v, int nType, int nVersion);

/**
 * vector
 * vectors of unsigned char are a special case and are intended to be serialized as a single opaque blob.
 */
template<typename T, typename A> unsigned int GetSerializeSize_impl(const std::vector<T, A>& v, int nType, int nVersion, const unsigned char&);
template<typename T, typename A, typename V> unsigned int GetSerializeSize_impl(const std::vector<T, A>& v, int nType, int nVersion, const V&);
template<typename T, typename A> inline unsigned int GetSerializeSize(const std::vector<T, A>& v, int nType, int nVersion);
template<typename Stream, typename T, typename A> void Serialize_impl(Stream& os, const std::vector<T, A>& v, int nType, int nVersion, const unsigned char&);
template<typename Stream, typename T, typename A, typename V> void Serialize_impl(Stream& os, const std::vector<T, A>& v, int nType, int nVersion, const V&);
template<typename Stream, typename T, typename A> inline void Serialize(Stream& os, const std::vector<T, A>& v, int nType, int nVersion);
template<typename Stream, typename T, typename A> void Unserialize_impl(Stream& is, std::vector<T, A>& v, int nType, int nVersion, const unsigned char&);
template<typename Stream, typename T, typename A, typename V> void Unserialize_impl(Stream& is, std::vector<T, A>& v, int nType, int nVersion, const V&);
template<typename Stream, typename T, typename A> inline void Unserialize(Stream& is, std::vector<T, A>& v, int nType, int nVersion);
=======
template <typename C>
unsigned int GetSerializeSize(const std::basic_string<C>& str, int, int = 0);
template <typename Stream, typename C>
void Serialize(Stream& os, const std::basic_string<C>& str, int, int = 0);
template <typename Stream, typename C>
void Unserialize(Stream& is, std::basic_string<C>& str, int, int = 0);

/**
 * vector
 * vectors of unsigned char are a special case and are intended to be serialized as a single opaque blob.
 */
template <typename T, typename A>
unsigned int GetSerializeSize_impl(const std::vector<T, A>& v, int nType, int nVersion, const unsigned char&);
template <typename T, typename A, typename V>
unsigned int GetSerializeSize_impl(const std::vector<T, A>& v, int nType, int nVersion, const V&);
template <typename T, typename A>
inline unsigned int GetSerializeSize(const std::vector<T, A>& v, int nType, int nVersion);
template <typename Stream, typename T, typename A>
void Serialize_impl(Stream& os, const std::vector<T, A>& v, int nType, int nVersion, const unsigned char&);
template <typename Stream, typename T, typename A, typename V>
void Serialize_impl(Stream& os, const std::vector<T, A>& v, int nType, int nVersion, const V&);
template <typename Stream, typename T, typename A>
inline void Serialize(Stream& os, const std::vector<T, A>& v, int nType, int nVersion);
template <typename Stream, typename T, typename A>
void Unserialize_impl(Stream& is, std::vector<T, A>& v, int nType, int nVersion, const unsigned char&);
template <typename Stream, typename T, typename A, typename V>
void Unserialize_impl(Stream& is, std::vector<T, A>& v, int nType, int nVersion, const V&);
template <typename Stream, typename T, typename A>
inline void Unserialize(Stream& is, std::vector<T, A>& v, int nType, int nVersion);

/**
 * others derived from vector
 */
extern inline unsigned int GetSerializeSize(const CScript& v, int nType, int nVersion);
template <typename Stream>
void Serialize(Stream& os, const CScript& v, int nType, int nVersion);
template <typename Stream>
void Unserialize(Stream& is, CScript& v, int nType, int nVersion);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

/**
 * pair
 */
<<<<<<< HEAD
template<typename K, typename T> unsigned int GetSerializeSize(const std::pair<K, T>& item, int nType, int nVersion);
template<typename Stream, typename K, typename T> void Serialize(Stream& os, const std::pair<K, T>& item, int nType, int nVersion);
template<typename Stream, typename K, typename T> void Unserialize(Stream& is, std::pair<K, T>& item, int nType, int nVersion);
=======
template <typename K, typename T>
unsigned int GetSerializeSize(const std::pair<K, T>& item, int nType, int nVersion);
template <typename Stream, typename K, typename T>
void Serialize(Stream& os, const std::pair<K, T>& item, int nType, int nVersion);
template <typename Stream, typename K, typename T>
void Unserialize(Stream& is, std::pair<K, T>& item, int nType, int nVersion);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

/**
 * map
 */
<<<<<<< HEAD
template<typename K, typename T, typename Pred, typename A> unsigned int GetSerializeSize(const std::map<K, T, Pred, A>& m, int nType, int nVersion);
template<typename Stream, typename K, typename T, typename Pred, typename A> void Serialize(Stream& os, const std::map<K, T, Pred, A>& m, int nType, int nVersion);
template<typename Stream, typename K, typename T, typename Pred, typename A> void Unserialize(Stream& is, std::map<K, T, Pred, A>& m, int nType, int nVersion);
=======
template <typename K, typename T, typename Pred, typename A>
unsigned int GetSerializeSize(const std::map<K, T, Pred, A>& m, int nType, int nVersion);
template <typename Stream, typename K, typename T, typename Pred, typename A>
void Serialize(Stream& os, const std::map<K, T, Pred, A>& m, int nType, int nVersion);
template <typename Stream, typename K, typename T, typename Pred, typename A>
void Unserialize(Stream& is, std::map<K, T, Pred, A>& m, int nType, int nVersion);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

/**
 * set
 */
<<<<<<< HEAD
template<typename K, typename Pred, typename A> unsigned int GetSerializeSize(const std::set<K, Pred, A>& m, int nType, int nVersion);
template<typename Stream, typename K, typename Pred, typename A> void Serialize(Stream& os, const std::set<K, Pred, A>& m, int nType, int nVersion);
template<typename Stream, typename K, typename Pred, typename A> void Unserialize(Stream& is, std::set<K, Pred, A>& m, int nType, int nVersion);



=======
template <typename K, typename Pred, typename A>
unsigned int GetSerializeSize(const std::set<K, Pred, A>& m, int nType, int nVersion);
template <typename Stream, typename K, typename Pred, typename A>
void Serialize(Stream& os, const std::set<K, Pred, A>& m, int nType, int nVersion);
template <typename Stream, typename K, typename Pred, typename A>
void Unserialize(Stream& is, std::set<K, Pred, A>& m, int nType, int nVersion);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3


/**
 * If none of the specialized versions above matched, default to calling member function.
 * "int nType" is changed to "long nType" to keep from getting an ambiguous overload error.
 * The compiler will only cast int to long if none of the other templates matched.
 * Thanks to Boost serialization for this idea.
 */
<<<<<<< HEAD
template<typename T>
=======
template <typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
inline unsigned int GetSerializeSize(const T& a, long nType, int nVersion)
{
    return a.GetSerializeSize((int)nType, nVersion);
}

<<<<<<< HEAD
template<typename Stream, typename T>
=======
template <typename Stream, typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
inline void Serialize(Stream& os, const T& a, long nType, int nVersion)
{
    a.Serialize(os, (int)nType, nVersion);
}

<<<<<<< HEAD
template<typename Stream, typename T>
=======
template <typename Stream, typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
inline void Unserialize(Stream& is, T& a, long nType, int nVersion)
{
    a.Unserialize(is, (int)nType, nVersion);
}


<<<<<<< HEAD



/**
 * string
 */
template<typename C>
=======
/**
 * string
 */
template <typename C>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
unsigned int GetSerializeSize(const std::basic_string<C>& str, int, int)
{
    return GetSizeOfCompactSize(str.size()) + str.size() * sizeof(str[0]);
}

<<<<<<< HEAD
template<typename Stream, typename C>
=======
template <typename Stream, typename C>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Serialize(Stream& os, const std::basic_string<C>& str, int, int)
{
    WriteCompactSize(os, str.size());
    if (!str.empty())
        os.write((char*)&str[0], str.size() * sizeof(str[0]));
}

<<<<<<< HEAD
template<typename Stream, typename C>
=======
template <typename Stream, typename C>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Unserialize(Stream& is, std::basic_string<C>& str, int, int)
{
    unsigned int nSize = ReadCompactSize(is);
    str.resize(nSize);
    if (nSize != 0)
        is.read((char*)&str[0], nSize * sizeof(str[0]));
}


<<<<<<< HEAD

/**
 * prevector
 */
template<unsigned int N, typename T>
unsigned int GetSerializeSize_impl(const prevector<N, T>& v, int nType, int nVersion, const unsigned char&)
{
    return (GetSizeOfCompactSize(v.size()) + v.size() * sizeof(T));
}

template<unsigned int N, typename T, typename V>
unsigned int GetSerializeSize_impl(const prevector<N, T>& v, int nType, int nVersion, const V&)
{
    unsigned int nSize = GetSizeOfCompactSize(v.size());
    for (typename prevector<N, T>::const_iterator vi = v.begin(); vi != v.end(); ++vi)
        nSize += GetSerializeSize((*vi), nType, nVersion);
    return nSize;
}

template<unsigned int N, typename T>
inline unsigned int GetSerializeSize(const prevector<N, T>& v, int nType, int nVersion)
{
    return GetSerializeSize_impl(v, nType, nVersion, T());
}


template<typename Stream, unsigned int N, typename T>
void Serialize_impl(Stream& os, const prevector<N, T>& v, int nType, int nVersion, const unsigned char&)
{
    WriteCompactSize(os, v.size());
    if (!v.empty())
        os.write((char*)&v[0], v.size() * sizeof(T));
}

template<typename Stream, unsigned int N, typename T, typename V>
void Serialize_impl(Stream& os, const prevector<N, T>& v, int nType, int nVersion, const V&)
{
    WriteCompactSize(os, v.size());
    for (typename prevector<N, T>::const_iterator vi = v.begin(); vi != v.end(); ++vi)
        ::Serialize(os, (*vi), nType, nVersion);
}

template<typename Stream, unsigned int N, typename T>
inline void Serialize(Stream& os, const prevector<N, T>& v, int nType, int nVersion)
{
    Serialize_impl(os, v, nType, nVersion, T());
}


template<typename Stream, unsigned int N, typename T>
void Unserialize_impl(Stream& is, prevector<N, T>& v, int nType, int nVersion, const unsigned char&)
{
    // Limit size per read so bogus size value won't cause out of memory
    v.clear();
    unsigned int nSize = ReadCompactSize(is);
    unsigned int i = 0;
    while (i < nSize)
    {
        unsigned int blk = std::min(nSize - i, (unsigned int)(1 + 4999999 / sizeof(T)));
        v.resize(i + blk);
        is.read((char*)&v[i], blk * sizeof(T));
        i += blk;
    }
}

template<typename Stream, unsigned int N, typename T, typename V>
void Unserialize_impl(Stream& is, prevector<N, T>& v, int nType, int nVersion, const V&)
{
    v.clear();
    unsigned int nSize = ReadCompactSize(is);
    unsigned int i = 0;
    unsigned int nMid = 0;
    while (nMid < nSize)
    {
        nMid += 5000000 / sizeof(T);
        if (nMid > nSize)
            nMid = nSize;
        v.resize(nMid);
        for (; i < nMid; i++)
            Unserialize(is, v[i], nType, nVersion);
    }
}

template<typename Stream, unsigned int N, typename T>
inline void Unserialize(Stream& is, prevector<N, T>& v, int nType, int nVersion)
{
    Unserialize_impl(is, v, nType, nVersion, T());
}



/**
 * vector
 */
template<typename T, typename A>
=======
/**
 * vector
 */
template <typename T, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
unsigned int GetSerializeSize_impl(const std::vector<T, A>& v, int nType, int nVersion, const unsigned char&)
{
    return (GetSizeOfCompactSize(v.size()) + v.size() * sizeof(T));
}

<<<<<<< HEAD
template<typename T, typename A, typename V>
=======
template <typename T, typename A, typename V>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
unsigned int GetSerializeSize_impl(const std::vector<T, A>& v, int nType, int nVersion, const V&)
{
    unsigned int nSize = GetSizeOfCompactSize(v.size());
    for (typename std::vector<T, A>::const_iterator vi = v.begin(); vi != v.end(); ++vi)
        nSize += GetSerializeSize((*vi), nType, nVersion);
    return nSize;
}

<<<<<<< HEAD
template<typename T, typename A>
=======
template <typename T, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
inline unsigned int GetSerializeSize(const std::vector<T, A>& v, int nType, int nVersion)
{
    return GetSerializeSize_impl(v, nType, nVersion, T());
}


<<<<<<< HEAD
template<typename Stream, typename T, typename A>
=======
template <typename Stream, typename T, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Serialize_impl(Stream& os, const std::vector<T, A>& v, int nType, int nVersion, const unsigned char&)
{
    WriteCompactSize(os, v.size());
    if (!v.empty())
        os.write((char*)&v[0], v.size() * sizeof(T));
}

<<<<<<< HEAD
template<typename Stream, typename T, typename A, typename V>
=======
template <typename Stream, typename T, typename A, typename V>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Serialize_impl(Stream& os, const std::vector<T, A>& v, int nType, int nVersion, const V&)
{
    WriteCompactSize(os, v.size());
    for (typename std::vector<T, A>::const_iterator vi = v.begin(); vi != v.end(); ++vi)
        ::Serialize(os, (*vi), nType, nVersion);
}

<<<<<<< HEAD
template<typename Stream, typename T, typename A>
=======
template <typename Stream, typename T, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
inline void Serialize(Stream& os, const std::vector<T, A>& v, int nType, int nVersion)
{
    Serialize_impl(os, v, nType, nVersion, T());
}


<<<<<<< HEAD
template<typename Stream, typename T, typename A>
=======
template <typename Stream, typename T, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Unserialize_impl(Stream& is, std::vector<T, A>& v, int nType, int nVersion, const unsigned char&)
{
    // Limit size per read so bogus size value won't cause out of memory
    v.clear();
    unsigned int nSize = ReadCompactSize(is);
    unsigned int i = 0;
<<<<<<< HEAD
    while (i < nSize)
    {
=======
    while (i < nSize) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        unsigned int blk = std::min(nSize - i, (unsigned int)(1 + 4999999 / sizeof(T)));
        v.resize(i + blk);
        is.read((char*)&v[i], blk * sizeof(T));
        i += blk;
    }
}

<<<<<<< HEAD
template<typename Stream, typename T, typename A, typename V>
=======
template <typename Stream, typename T, typename A, typename V>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Unserialize_impl(Stream& is, std::vector<T, A>& v, int nType, int nVersion, const V&)
{
    v.clear();
    unsigned int nSize = ReadCompactSize(is);
    unsigned int i = 0;
    unsigned int nMid = 0;
<<<<<<< HEAD
    while (nMid < nSize)
    {
=======
    while (nMid < nSize) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        nMid += 5000000 / sizeof(T);
        if (nMid > nSize)
            nMid = nSize;
        v.resize(nMid);
        for (; i < nMid; i++)
            Unserialize(is, v[i], nType, nVersion);
    }
}

<<<<<<< HEAD
template<typename Stream, typename T, typename A>
=======
template <typename Stream, typename T, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
inline void Unserialize(Stream& is, std::vector<T, A>& v, int nType, int nVersion)
{
    Unserialize_impl(is, v, nType, nVersion, T());
}


<<<<<<< HEAD
=======
/**
 * others derived from vector
 */
inline unsigned int GetSerializeSize(const CScript& v, int nType, int nVersion)
{
    return GetSerializeSize((const std::vector<unsigned char>&)v, nType, nVersion);
}

template <typename Stream>
void Serialize(Stream& os, const CScript& v, int nType, int nVersion)
{
    Serialize(os, (const std::vector<unsigned char>&)v, nType, nVersion);
}

template <typename Stream>
void Unserialize(Stream& is, CScript& v, int nType, int nVersion)
{
    Unserialize(is, (std::vector<unsigned char>&)v, nType, nVersion);
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

/**
 * pair
 */
<<<<<<< HEAD
template<typename K, typename T>
=======
template <typename K, typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
unsigned int GetSerializeSize(const std::pair<K, T>& item, int nType, int nVersion)
{
    return GetSerializeSize(item.first, nType, nVersion) + GetSerializeSize(item.second, nType, nVersion);
}

<<<<<<< HEAD
template<typename Stream, typename K, typename T>
=======
template <typename Stream, typename K, typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Serialize(Stream& os, const std::pair<K, T>& item, int nType, int nVersion)
{
    Serialize(os, item.first, nType, nVersion);
    Serialize(os, item.second, nType, nVersion);
}

<<<<<<< HEAD
template<typename Stream, typename K, typename T>
=======
template <typename Stream, typename K, typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Unserialize(Stream& is, std::pair<K, T>& item, int nType, int nVersion)
{
    Unserialize(is, item.first, nType, nVersion);
    Unserialize(is, item.second, nType, nVersion);
}


<<<<<<< HEAD

/**
 * map
 */
template<typename K, typename T, typename Pred, typename A>
=======
/**
 * map
 */
template <typename K, typename T, typename Pred, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
unsigned int GetSerializeSize(const std::map<K, T, Pred, A>& m, int nType, int nVersion)
{
    unsigned int nSize = GetSizeOfCompactSize(m.size());
    for (typename std::map<K, T, Pred, A>::const_iterator mi = m.begin(); mi != m.end(); ++mi)
        nSize += GetSerializeSize((*mi), nType, nVersion);
    return nSize;
}

<<<<<<< HEAD
template<typename Stream, typename K, typename T, typename Pred, typename A>
=======
template <typename Stream, typename K, typename T, typename Pred, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Serialize(Stream& os, const std::map<K, T, Pred, A>& m, int nType, int nVersion)
{
    WriteCompactSize(os, m.size());
    for (typename std::map<K, T, Pred, A>::const_iterator mi = m.begin(); mi != m.end(); ++mi)
        Serialize(os, (*mi), nType, nVersion);
}

<<<<<<< HEAD
template<typename Stream, typename K, typename T, typename Pred, typename A>
=======
template <typename Stream, typename K, typename T, typename Pred, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Unserialize(Stream& is, std::map<K, T, Pred, A>& m, int nType, int nVersion)
{
    m.clear();
    unsigned int nSize = ReadCompactSize(is);
    typename std::map<K, T, Pred, A>::iterator mi = m.begin();
<<<<<<< HEAD
    for (unsigned int i = 0; i < nSize; i++)
    {
=======
    for (unsigned int i = 0; i < nSize; i++) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        std::pair<K, T> item;
        Unserialize(is, item, nType, nVersion);
        mi = m.insert(mi, item);
    }
}


<<<<<<< HEAD

/**
 * set
 */
template<typename K, typename Pred, typename A>
=======
/**
 * set
 */
template <typename K, typename Pred, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
unsigned int GetSerializeSize(const std::set<K, Pred, A>& m, int nType, int nVersion)
{
    unsigned int nSize = GetSizeOfCompactSize(m.size());
    for (typename std::set<K, Pred, A>::const_iterator it = m.begin(); it != m.end(); ++it)
        nSize += GetSerializeSize((*it), nType, nVersion);
    return nSize;
}

<<<<<<< HEAD
template<typename Stream, typename K, typename Pred, typename A>
=======
template <typename Stream, typename K, typename Pred, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Serialize(Stream& os, const std::set<K, Pred, A>& m, int nType, int nVersion)
{
    WriteCompactSize(os, m.size());
    for (typename std::set<K, Pred, A>::const_iterator it = m.begin(); it != m.end(); ++it)
        Serialize(os, (*it), nType, nVersion);
}

<<<<<<< HEAD
template<typename Stream, typename K, typename Pred, typename A>
=======
template <typename Stream, typename K, typename Pred, typename A>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void Unserialize(Stream& is, std::set<K, Pred, A>& m, int nType, int nVersion)
{
    m.clear();
    unsigned int nSize = ReadCompactSize(is);
    typename std::set<K, Pred, A>::iterator it = m.begin();
<<<<<<< HEAD
    for (unsigned int i = 0; i < nSize; i++)
    {
=======
    for (unsigned int i = 0; i < nSize; i++) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        K key;
        Unserialize(is, key, nType, nVersion);
        it = m.insert(it, key);
    }
}

<<<<<<< HEAD
/**
 * list
 */
template<typename T, typename A>
unsigned int GetSerializeSize(const std::list<T, A>& l, int nType, int nVersion)
{
    unsigned int nSize = GetSizeOfCompactSize(l.size());
    for (typename std::list<T, A>::const_iterator it = l.begin(); it != l.end(); ++it)
        nSize += GetSerializeSize((*it), nType, nVersion);
    return nSize;
}

template<typename Stream, typename T, typename A>
void Serialize(Stream& os, const std::list<T, A>& l, int nType, int nVersion)
{
    WriteCompactSize(os, l.size());
    for (typename std::list<T, A>::const_iterator it = l.begin(); it != l.end(); ++it)
        Serialize(os, (*it), nType, nVersion);
}

template<typename Stream, typename T, typename A>
void Unserialize(Stream& is, std::list<T, A>& l, int nType, int nVersion)
{
    l.clear();
    unsigned int nSize = ReadCompactSize(is);
    for (unsigned int i = 0; i < nSize; i++)
    {
        T val;
        Unserialize(is, val, nType, nVersion);
        l.push_back(val);
    }
}


=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

/**
 * Support for ADD_SERIALIZE_METHODS and READWRITE macro
 */
<<<<<<< HEAD
struct CSerActionSerialize
{
    bool ForRead() const { return false; }
};
struct CSerActionUnserialize
{
    bool ForRead() const { return true; }
};

template<typename Stream, typename T>
=======
struct CSerActionSerialize {
    bool ForRead() const { return false; }
};
struct CSerActionUnserialize {
    bool ForRead() const { return true; }
};

template <typename Stream, typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
inline void SerReadWrite(Stream& s, const T& obj, int nType, int nVersion, CSerActionSerialize ser_action)
{
    ::Serialize(s, obj, nType, nVersion);
}

<<<<<<< HEAD
template<typename Stream, typename T>
=======
template <typename Stream, typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
inline void SerReadWrite(Stream& s, T& obj, int nType, int nVersion, CSerActionUnserialize ser_action)
{
    ::Unserialize(s, obj, nType, nVersion);
}


<<<<<<< HEAD







=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class CSizeComputer
{
protected:
    size_t nSize;

public:
    int nType;
    int nVersion;

    CSizeComputer(int nTypeIn, int nVersionIn) : nSize(0), nType(nTypeIn), nVersion(nVersionIn) {}

<<<<<<< HEAD
    CSizeComputer& write(const char *psz, size_t nSize)
=======
    int GetType() const { return nType; }
    int GetVersion() const { return nVersion; }

    CSizeComputer& write(const char* psz, size_t nSize)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        this->nSize += nSize;
        return *this;
    }

<<<<<<< HEAD
    template<typename T>
=======
    template <typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    CSizeComputer& operator<<(const T& obj)
    {
        ::Serialize(*this, obj, nType, nVersion);
        return (*this);
    }

<<<<<<< HEAD
    size_t size() const {
=======
    size_t size() const
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return nSize;
    }
};

<<<<<<< HEAD
template<typename Stream>
void SerializeMany(Stream& s, int nType, int nVersion)
{
}

template<typename Stream, typename Arg>
void SerializeMany(Stream& s, int nType, int nVersion, Arg&& arg)
{
    ::Serialize(s, std::forward<Arg>(arg), nType, nVersion);
}

template<typename Stream, typename Arg, typename... Args>
void SerializeMany(Stream& s, int nType, int nVersion, Arg&& arg, Args&&... args)
{
    ::Serialize(s, std::forward<Arg>(arg), nType, nVersion);
    ::SerializeMany(s, nType, nVersion, std::forward<Args>(args)...);
}

template<typename Stream>
inline void UnserializeMany(Stream& s, int nType, int nVersion)
{
}

template<typename Stream, typename Arg>
inline void UnserializeMany(Stream& s, int nType, int nVersion, Arg& arg)
{
    ::Unserialize(s, arg, nType, nVersion);
}

template<typename Stream, typename Arg, typename... Args>
inline void UnserializeMany(Stream& s, int nType, int nVersion, Arg& arg, Args&... args)
{
    ::Unserialize(s, arg, nType, nVersion);
    ::UnserializeMany(s, nType, nVersion, args...);
}

template<typename Stream, typename... Args>
inline void SerReadWriteMany(Stream& s, int nType, int nVersion, CSerActionSerialize ser_action, Args&&... args)
{
    ::SerializeMany(s, nType, nVersion, std::forward<Args>(args)...);
}

template<typename Stream, typename... Args>
inline void SerReadWriteMany(Stream& s, int nType, int nVersion, CSerActionUnserialize ser_action, Args&... args)
{
    ::UnserializeMany(s, nType, nVersion, args...);
}

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif // BITCOIN_SERIALIZE_H
