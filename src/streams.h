<<<<<<< HEAD
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto             -*- c++ -*-
// Copyright (c) 2009-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_STREAMS_H
#define BITCOIN_STREAMS_H

<<<<<<< HEAD
#include "support/allocators/zeroafterfree.h"
=======
#include "allocators.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "serialize.h"

#include <algorithm>
#include <assert.h>
#include <ios>
#include <limits>
#include <map>
#include <set>
#include <stdint.h>
<<<<<<< HEAD
#include <stdio.h>
#include <string>
#include <string.h>
=======
#include <string.h>
#include <string>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <utility>
#include <vector>

/** Double ended buffer combining vector and stream-like interfaces.
 *
 * >> and << read and write unformatted data using the above serialization templates.
 * Fills with data in linear time; some stringstream implementations take N^2 time.
 */
class CDataStream
{
protected:
    typedef CSerializeData vector_type;
    vector_type vch;
    unsigned int nReadPos;
<<<<<<< HEAD
=======

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
public:
    int nType;
    int nVersion;

<<<<<<< HEAD
    typedef vector_type::allocator_type   allocator_type;
    typedef vector_type::size_type        size_type;
    typedef vector_type::difference_type  difference_type;
    typedef vector_type::reference        reference;
    typedef vector_type::const_reference  const_reference;
    typedef vector_type::value_type       value_type;
    typedef vector_type::iterator         iterator;
    typedef vector_type::const_iterator   const_iterator;
=======
    typedef vector_type::allocator_type allocator_type;
    typedef vector_type::size_type size_type;
    typedef vector_type::difference_type difference_type;
    typedef vector_type::reference reference;
    typedef vector_type::const_reference const_reference;
    typedef vector_type::value_type value_type;
    typedef vector_type::iterator iterator;
    typedef vector_type::const_iterator const_iterator;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    typedef vector_type::reverse_iterator reverse_iterator;

    explicit CDataStream(int nTypeIn, int nVersionIn)
    {
        Init(nTypeIn, nVersionIn);
    }

    CDataStream(const_iterator pbegin, const_iterator pend, int nTypeIn, int nVersionIn) : vch(pbegin, pend)
    {
        Init(nTypeIn, nVersionIn);
    }

<<<<<<< HEAD
=======
#if !defined(_MSC_VER) || _MSC_VER >= 1300
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    CDataStream(const char* pbegin, const char* pend, int nTypeIn, int nVersionIn) : vch(pbegin, pend)
    {
        Init(nTypeIn, nVersionIn);
    }
<<<<<<< HEAD
=======
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    CDataStream(const vector_type& vchIn, int nTypeIn, int nVersionIn) : vch(vchIn.begin(), vchIn.end())
    {
        Init(nTypeIn, nVersionIn);
    }

    CDataStream(const std::vector<char>& vchIn, int nTypeIn, int nVersionIn) : vch(vchIn.begin(), vchIn.end())
    {
        Init(nTypeIn, nVersionIn);
    }

    CDataStream(const std::vector<unsigned char>& vchIn, int nTypeIn, int nVersionIn) : vch(vchIn.begin(), vchIn.end())
    {
        Init(nTypeIn, nVersionIn);
    }

<<<<<<< HEAD
    template <typename... Args>
    CDataStream(int nTypeIn, int nVersionIn, Args&&... args)
    {
        Init(nTypeIn, nVersionIn);
        ::SerializeMany(*this, nType, nVersion, std::forward<Args>(args)...);
    }

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void Init(int nTypeIn, int nVersionIn)
    {
        nReadPos = 0;
        nType = nTypeIn;
        nVersion = nVersionIn;
    }

    CDataStream& operator+=(const CDataStream& b)
    {
        vch.insert(vch.end(), b.begin(), b.end());
        return *this;
    }

    friend CDataStream operator+(const CDataStream& a, const CDataStream& b)
    {
        CDataStream ret = a;
        ret += b;
        return (ret);
    }

    std::string str() const
    {
        return (std::string(begin(), end()));
    }


    //
    // Vector subset
    //
<<<<<<< HEAD
    const_iterator begin() const                     { return vch.begin() + nReadPos; }
    iterator begin()                                 { return vch.begin() + nReadPos; }
    const_iterator end() const                       { return vch.end(); }
    iterator end()                                   { return vch.end(); }
    size_type size() const                           { return vch.size() - nReadPos; }
    bool empty() const                               { return vch.size() == nReadPos; }
    void resize(size_type n, value_type c=0)         { vch.resize(n + nReadPos, c); }
    void reserve(size_type n)                        { vch.reserve(n + nReadPos); }
    const_reference operator[](size_type pos) const  { return vch[pos + nReadPos]; }
    reference operator[](size_type pos)              { return vch[pos + nReadPos]; }
    void clear()                                     { vch.clear(); nReadPos = 0; }
    iterator insert(iterator it, const char& x=char()) { return vch.insert(it, x); }
    void insert(iterator it, size_type n, const char& x) { vch.insert(it, n, x); }
    value_type* data()                               { return vch.data() + nReadPos; }
    const value_type* data() const                   { return vch.data() + nReadPos; }

    void insert(iterator it, std::vector<char>::const_iterator first, std::vector<char>::const_iterator last)
    {
        if (last == first) return;
        assert(last - first > 0);
        if (it == vch.begin() + nReadPos && (unsigned int)(last - first) <= nReadPos)
        {
            // special case for inserting at the front when there's room
            nReadPos -= (last - first);
            memcpy(&vch[nReadPos], &first[0], last - first);
        }
        else
            vch.insert(it, first, last);
    }

    void insert(iterator it, const char* first, const char* last)
    {
        if (last == first) return;
        assert(last - first > 0);
        if (it == vch.begin() + nReadPos && (unsigned int)(last - first) <= nReadPos)
        {
            // special case for inserting at the front when there's room
            nReadPos -= (last - first);
            memcpy(&vch[nReadPos], &first[0], last - first);
        }
        else
            vch.insert(it, first, last);
    }

    iterator erase(iterator it)
    {
        if (it == vch.begin() + nReadPos)
        {
            // special case for erasing from the front
            if (++nReadPos >= vch.size())
            {
=======
    const_iterator begin() const { return vch.begin() + nReadPos; }
    iterator begin() { return vch.begin() + nReadPos; }
    const_iterator end() const { return vch.end(); }
    iterator end() { return vch.end(); }
    size_type size() const { return vch.size() - nReadPos; }
    bool empty() const { return vch.size() == nReadPos; }
    void resize(size_type n, value_type c = 0) { vch.resize(n + nReadPos, c); }
    void reserve(size_type n) { vch.reserve(n + nReadPos); }
    const_reference operator[](size_type pos) const { return vch[pos + nReadPos]; }
    reference operator[](size_type pos) { return vch[pos + nReadPos]; }
    void clear()
    {
        vch.clear();
        nReadPos = 0;
    }
    iterator insert(iterator it, const char& x = char()) { return vch.insert(it, x); }
    void insert(iterator it, size_type n, const char& x) { vch.insert(it, n, x); }

    void insert(iterator it, std::vector<char>::const_iterator first, std::vector<char>::const_iterator last)
    {
        assert(last - first >= 0);
        if (it == vch.begin() + nReadPos && (unsigned int)(last - first) <= nReadPos) {
            // special case for inserting at the front when there's room
            nReadPos -= (last - first);
            memcpy(&vch[nReadPos], &first[0], last - first);
        } else
            vch.insert(it, first, last);
    }

#if !defined(_MSC_VER) || _MSC_VER >= 1300
    void insert(iterator it, const char* first, const char* last)
    {
        assert(last - first >= 0);
        if (it == vch.begin() + nReadPos && (unsigned int)(last - first) <= nReadPos) {
            // special case for inserting at the front when there's room
            nReadPos -= (last - first);
            memcpy(&vch[nReadPos], &first[0], last - first);
        } else
            vch.insert(it, first, last);
    }
#endif

    iterator erase(iterator it)
    {
        if (it == vch.begin() + nReadPos) {
            // special case for erasing from the front
            if (++nReadPos >= vch.size()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                // whenever we reach the end, we take the opportunity to clear the buffer
                nReadPos = 0;
                return vch.erase(vch.begin(), vch.end());
            }
            return vch.begin() + nReadPos;
<<<<<<< HEAD
        }
        else
=======
        } else
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return vch.erase(it);
    }

    iterator erase(iterator first, iterator last)
    {
<<<<<<< HEAD
        if (first == vch.begin() + nReadPos)
        {
            // special case for erasing from the front
            if (last == vch.end())
            {
                nReadPos = 0;
                return vch.erase(vch.begin(), vch.end());
            }
            else
            {
                nReadPos = (last - vch.begin());
                return last;
            }
        }
        else
=======
        if (first == vch.begin() + nReadPos) {
            // special case for erasing from the front
            if (last == vch.end()) {
                nReadPos = 0;
                return vch.erase(vch.begin(), vch.end());
            } else {
                nReadPos = (last - vch.begin());
                return last;
            }
        } else
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return vch.erase(first, last);
    }

    inline void Compact()
    {
        vch.erase(vch.begin(), vch.begin() + nReadPos);
        nReadPos = 0;
    }

    bool Rewind(size_type n)
    {
        // Rewind by n characters if the buffer hasn't been compacted yet
        if (n > nReadPos)
            return false;
        nReadPos -= n;
        return true;
    }


    //
    // Stream subset
    //
<<<<<<< HEAD
    bool eof() const             { return size() == 0; }
    CDataStream* rdbuf()         { return this; }
    int in_avail()               { return size(); }

    void SetType(int n)          { nType = n; }
    int GetType()                { return nType; }
    void SetVersion(int n)       { nVersion = n; }
    int GetVersion()             { return nVersion; }
    void ReadVersion()           { *this >> nVersion; }
    void WriteVersion()          { *this << nVersion; }

    CDataStream& read(char* pch, size_t nSize)
    {
        if (nSize == 0) return (*this);

        // Read from the beginning of the buffer
        unsigned int nReadPosNext = nReadPos + nSize;
        if (nReadPosNext >= vch.size())
        {
            if (nReadPosNext > vch.size())
            {
                throw std::ios_base::failure("CDataStream::read(): end of data");
=======
    bool eof() const { return size() == 0; }
    CDataStream* rdbuf() { return this; }
    int in_avail() { return size(); }

    void SetType(int n) { nType = n; }
    int GetType() { return nType; }
    void SetVersion(int n) { nVersion = n; }
    int GetVersion() { return nVersion; }
    void ReadVersion() { *this >> nVersion; }
    void WriteVersion() { *this << nVersion; }

    CDataStream& read(char* pch, size_t nSize)
    {
        // Read from the beginning of the buffer
        unsigned int nReadPosNext = nReadPos + nSize;
        if (nReadPosNext >= vch.size()) {
            if (nReadPosNext > vch.size()) {
                throw std::ios_base::failure("CDataStream::read() : end of data");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            }
            memcpy(pch, &vch[nReadPos], nSize);
            nReadPos = 0;
            vch.clear();
            return (*this);
        }
        memcpy(pch, &vch[nReadPos], nSize);
        nReadPos = nReadPosNext;
        return (*this);
    }

    CDataStream& ignore(int nSize)
    {
        // Ignore from the beginning of the buffer
<<<<<<< HEAD
        if (nSize < 0) {
            throw std::ios_base::failure("CDataStream::ignore(): nSize negative");
        }
        unsigned int nReadPosNext = nReadPos + nSize;
        if (nReadPosNext >= vch.size())
        {
            if (nReadPosNext > vch.size())
                throw std::ios_base::failure("CDataStream::ignore(): end of data");
=======
        assert(nSize >= 0);
        unsigned int nReadPosNext = nReadPos + nSize;
        if (nReadPosNext >= vch.size()) {
            if (nReadPosNext > vch.size())
                throw std::ios_base::failure("CDataStream::ignore() : end of data");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            nReadPos = 0;
            vch.clear();
            return (*this);
        }
        nReadPos = nReadPosNext;
        return (*this);
    }

    CDataStream& write(const char* pch, size_t nSize)
    {
        // Write to the end of the buffer
        vch.insert(vch.end(), pch, pch + nSize);
        return (*this);
    }

<<<<<<< HEAD
    template<typename Stream>
=======
    template <typename Stream>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void Serialize(Stream& s, int nType, int nVersion) const
    {
        // Special case: stream << stream concatenates like stream += stream
        if (!vch.empty())
            s.write((char*)&vch[0], vch.size() * sizeof(vch[0]));
    }

<<<<<<< HEAD
    template<typename T>
=======
    template <typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    unsigned int GetSerializeSize(const T& obj)
    {
        // Tells the size of the object if serialized to this stream
        return ::GetSerializeSize(obj, nType, nVersion);
    }

<<<<<<< HEAD
    template<typename T>
=======
    template <typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    CDataStream& operator<<(const T& obj)
    {
        // Serialize to this stream
        ::Serialize(*this, obj, nType, nVersion);
        return (*this);
    }

<<<<<<< HEAD
    template<typename T>
=======
    template <typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    CDataStream& operator>>(T& obj)
    {
        // Unserialize from this stream
        ::Unserialize(*this, obj, nType, nVersion);
        return (*this);
    }

<<<<<<< HEAD
    void GetAndClear(CSerializeData &data) {
        data.insert(data.end(), begin(), end());
        clear();
    }

    /**
     * XOR the contents of this stream with a certain key.
     *
     * @param[in] key    The key used to XOR the data in this stream.
     */
    void Xor(const std::vector<unsigned char>& key)
    {
        if (key.size() == 0) {
            return;
        }

        for (size_type i = 0, j = 0; i != size(); i++) {
            vch[i] ^= key[j++];

            // This potentially acts on very many bytes of data, so it's
            // important that we calculate `j`, i.e. the `key` index in this
            // way instead of doing a %, which would effectively be a division
            // for each byte Xor'd -- much slower than need be.
            if (j == key.size())
                j = 0;
        }
    }
};










=======
    void GetAndClear(CSerializeData& data)
    {
        data.insert(data.end(), begin(), end());
        clear();
    }
};


>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
/** Non-refcounted RAII wrapper for FILE*
 *
 * Will automatically close the file when it goes out of scope if not null.
 * If you're returning the file pointer, return file.release().
 * If you need to close the file early, use file.fclose() instead of fclose(file).
 */
class CAutoFile
{
private:
    // Disallow copies
    CAutoFile(const CAutoFile&);
    CAutoFile& operator=(const CAutoFile&);

    int nType;
    int nVersion;
<<<<<<< HEAD
	
    FILE* file;	
=======

    FILE* file;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

public:
    CAutoFile(FILE* filenew, int nTypeIn, int nVersionIn)
    {
        file = filenew;
        nType = nTypeIn;
        nVersion = nVersionIn;
    }

    ~CAutoFile()
    {
        fclose();
    }

    void fclose()
    {
        if (file) {
            ::fclose(file);
            file = NULL;
        }
    }

    /** Get wrapped FILE* with transfer of ownership.
     * @note This will invalidate the CAutoFile object, and makes it the responsibility of the caller
     * of this function to clean up the returned FILE*.
     */
<<<<<<< HEAD
    FILE* release()             { FILE* ret = file; file = NULL; return ret; }
=======
    FILE* release()
    {
        FILE* ret = file;
        file = NULL;
        return ret;
    }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Get wrapped FILE* without transfer of ownership.
     * @note Ownership of the FILE* will remain with this class. Use this only if the scope of the
     * CAutoFile outlives use of the passed pointer.
     */
<<<<<<< HEAD
    FILE* Get() const           { return file; }

    /** Return true if the wrapped FILE* is NULL, false otherwise.
     */
    bool IsNull() const         { return (file == NULL); }
=======
    FILE* Get() const { return file; }

    /** Return true if the wrapped FILE* is NULL, false otherwise.
     */
    bool IsNull() const { return (file == NULL); }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    //
    // Stream subset
    //
<<<<<<< HEAD
    void SetType(int n)          { nType = n; }
    int GetType()                { return nType; }
    void SetVersion(int n)       { nVersion = n; }
    int GetVersion()             { return nVersion; }
    void ReadVersion()           { *this >> nVersion; }
    void WriteVersion()          { *this << nVersion; }
=======
    void SetType(int n) { nType = n; }
    int GetType() { return nType; }
    void SetVersion(int n) { nVersion = n; }
    int GetVersion() { return nVersion; }
    void ReadVersion() { *this >> nVersion; }
    void WriteVersion() { *this << nVersion; }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    CAutoFile& read(char* pch, size_t nSize)
    {
        if (!file)
<<<<<<< HEAD
            throw std::ios_base::failure("CAutoFile::read: file handle is NULL");
        if (fread(pch, 1, nSize, file) != nSize)
            throw std::ios_base::failure(feof(file) ? "CAutoFile::read: end of file" : "CAutoFile::read: fread failed");
        return (*this);
    }

    CAutoFile& ignore(size_t nSize)
    {
        if (!file)
            throw std::ios_base::failure("CAutoFile::ignore: file handle is NULL");
        unsigned char data[4096];
        while (nSize > 0) {
            size_t nNow = std::min<size_t>(nSize, sizeof(data));
            if (fread(data, 1, nNow, file) != nNow)
                throw std::ios_base::failure(feof(file) ? "CAutoFile::ignore: end of file" : "CAutoFile::read: fread failed");
            nSize -= nNow;
        }
=======
            throw std::ios_base::failure("CAutoFile::read : file handle is NULL");
        if (fread(pch, 1, nSize, file) != nSize)
            throw std::ios_base::failure(feof(file) ? "CAutoFile::read : end of file" : "CAutoFile::read : fread failed");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return (*this);
    }

    CAutoFile& write(const char* pch, size_t nSize)
    {
        if (!file)
<<<<<<< HEAD
            throw std::ios_base::failure("CAutoFile::write: file handle is NULL");
        if (fwrite(pch, 1, nSize, file) != nSize)
            throw std::ios_base::failure("CAutoFile::write: write failed");
        return (*this);
    }

    template<typename T>
=======
            throw std::ios_base::failure("CAutoFile::write : file handle is NULL");
        if (fwrite(pch, 1, nSize, file) != nSize)
            throw std::ios_base::failure("CAutoFile::write : write failed");
        return (*this);
    }

    template <typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    unsigned int GetSerializeSize(const T& obj)
    {
        // Tells the size of the object if serialized to this stream
        return ::GetSerializeSize(obj, nType, nVersion);
    }

<<<<<<< HEAD
    template<typename T>
=======
    template <typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    CAutoFile& operator<<(const T& obj)
    {
        // Serialize to this stream
        if (!file)
<<<<<<< HEAD
            throw std::ios_base::failure("CAutoFile::operator<<: file handle is NULL");
=======
            throw std::ios_base::failure("CAutoFile::operator<< : file handle is NULL");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ::Serialize(*this, obj, nType, nVersion);
        return (*this);
    }

<<<<<<< HEAD
    template<typename T>
=======
    template <typename T>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    CAutoFile& operator>>(T& obj)
    {
        // Unserialize from this stream
        if (!file)
<<<<<<< HEAD
            throw std::ios_base::failure("CAutoFile::operator>>: file handle is NULL");
=======
            throw std::ios_base::failure("CAutoFile::operator>> : file handle is NULL");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ::Unserialize(*this, obj, nType, nVersion);
        return (*this);
    }
};

/** Non-refcounted RAII wrapper around a FILE* that implements a ring buffer to
 *  deserialize from. It guarantees the ability to rewind a given number of bytes.
 *
 *  Will automatically close the file when it goes out of scope if not null.
 *  If you need to close the file early, use file.fclose() instead of fclose(file).
 */
class CBufferedFile
{
private:
    // Disallow copies
    CBufferedFile(const CBufferedFile&);
    CBufferedFile& operator=(const CBufferedFile&);

    int nType;
    int nVersion;

<<<<<<< HEAD
    FILE *src;            // source file
    uint64_t nSrcPos;     // how many bytes have been read from source
    uint64_t nReadPos;    // how many bytes have been read from this
    uint64_t nReadLimit;  // up to which position we're allowed to read
    uint64_t nRewind;     // how many bytes we guarantee to rewind
=======
    FILE* src;                // source file
    uint64_t nSrcPos;         // how many bytes have been read from source
    uint64_t nReadPos;        // how many bytes have been read from this
    uint64_t nReadLimit;      // up to which position we're allowed to read
    uint64_t nRewind;         // how many bytes we guarantee to rewind
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    std::vector<char> vchBuf; // the buffer

protected:
    // read data from the source to fill the buffer
<<<<<<< HEAD
    bool Fill() {
=======
    bool Fill()
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        unsigned int pos = nSrcPos % vchBuf.size();
        unsigned int readNow = vchBuf.size() - pos;
        unsigned int nAvail = vchBuf.size() - (nSrcPos - nReadPos) - nRewind;
        if (nAvail < readNow)
            readNow = nAvail;
        if (readNow == 0)
            return false;
        size_t read = fread((void*)&vchBuf[pos], 1, readNow, src);
        if (read == 0) {
<<<<<<< HEAD
            throw std::ios_base::failure(feof(src) ? "CBufferedFile::Fill: end of file" : "CBufferedFile::Fill: fread failed");
=======
            throw std::ios_base::failure(feof(src) ? "CBufferedFile::Fill : end of file" : "CBufferedFile::Fill : fread failed");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        } else {
            nSrcPos += read;
            return true;
        }
    }

public:
<<<<<<< HEAD
    CBufferedFile(FILE *fileIn, uint64_t nBufSize, uint64_t nRewindIn, int nTypeIn, int nVersionIn) :
        nSrcPos(0), nReadPos(0), nReadLimit((uint64_t)(-1)), nRewind(nRewindIn), vchBuf(nBufSize, 0)
=======
    CBufferedFile(FILE* fileIn, uint64_t nBufSize, uint64_t nRewindIn, int nTypeIn, int nVersionIn) : nSrcPos(0), nReadPos(0), nReadLimit((uint64_t)(-1)), nRewind(nRewindIn), vchBuf(nBufSize, 0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        src = fileIn;
        nType = nTypeIn;
        nVersion = nVersionIn;
    }

    ~CBufferedFile()
    {
        fclose();
    }

    void fclose()
    {
        if (src) {
            ::fclose(src);
            src = NULL;
        }
    }

    // check whether we're at the end of the source file
<<<<<<< HEAD
    bool eof() const {
=======
    bool eof() const
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return nReadPos == nSrcPos && feof(src);
    }

    // read a number of bytes
<<<<<<< HEAD
    CBufferedFile& read(char *pch, size_t nSize) {
=======
    CBufferedFile& read(char* pch, size_t nSize)
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (nSize + nReadPos > nReadLimit)
            throw std::ios_base::failure("Read attempted past buffer limit");
        if (nSize + nRewind > vchBuf.size())
            throw std::ios_base::failure("Read larger than buffer size");
        while (nSize > 0) {
            if (nReadPos == nSrcPos)
                Fill();
            unsigned int pos = nReadPos % vchBuf.size();
            size_t nNow = nSize;
            if (nNow + pos > vchBuf.size())
                nNow = vchBuf.size() - pos;
            if (nNow + nReadPos > nSrcPos)
                nNow = nSrcPos - nReadPos;
            memcpy(pch, &vchBuf[pos], nNow);
            nReadPos += nNow;
            pch += nNow;
            nSize -= nNow;
        }
        return (*this);
    }

    // return the current reading position
<<<<<<< HEAD
    uint64_t GetPos() {
=======
    uint64_t GetPos()
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return nReadPos;
    }

    // rewind to a given reading position
<<<<<<< HEAD
    bool SetPos(uint64_t nPos) {
=======
    bool SetPos(uint64_t nPos)
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        nReadPos = nPos;
        if (nReadPos + nRewind < nSrcPos) {
            nReadPos = nSrcPos - nRewind;
            return false;
        } else if (nReadPos > nSrcPos) {
            nReadPos = nSrcPos;
            return false;
        } else {
            return true;
        }
    }

<<<<<<< HEAD
    bool Seek(uint64_t nPos) {
=======
    bool Seek(uint64_t nPos)
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        long nLongPos = nPos;
        if (nPos != (uint64_t)nLongPos)
            return false;
        if (fseek(src, nLongPos, SEEK_SET))
            return false;
        nLongPos = ftell(src);
        nSrcPos = nLongPos;
        nReadPos = nLongPos;
        return true;
    }

    // prevent reading beyond a certain position
    // no argument removes the limit
<<<<<<< HEAD
    bool SetLimit(uint64_t nPos = (uint64_t)(-1)) {
=======
    bool SetLimit(uint64_t nPos = (uint64_t)(-1))
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (nPos < nReadPos)
            return false;
        nReadLimit = nPos;
        return true;
    }

<<<<<<< HEAD
    template<typename T>
    CBufferedFile& operator>>(T& obj) {
=======
    template <typename T>
    CBufferedFile& operator>>(T& obj)
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Unserialize from this stream
        ::Unserialize(*this, obj, nType, nVersion);
        return (*this);
    }

    // search for a given byte in the stream, and remain positioned on it
<<<<<<< HEAD
    void FindByte(char ch) {
=======
    void FindByte(char ch)
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        while (true) {
            if (nReadPos == nSrcPos)
                Fill();
            if (vchBuf[nReadPos % vchBuf.size()] == ch)
                break;
            nReadPos++;
        }
    }
};

#endif // BITCOIN_STREAMS_H
