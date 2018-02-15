<<<<<<< HEAD
// Copyright (c) 2009-2014 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
<<<<<<< HEAD
#include "config/gelcoin-config.h"
#endif

#include <cstring>

#if HAVE_DECL_STRNLEN == 0
size_t strnlen( const char *start, size_t max_len)
=======
#include "config/lux-config.h"
#endif

#include <cstring>
// OSX 10.6 is missing strnlen at runtime, but builds targetting it will still
// succeed. Define our own version here to avoid a crash.
size_t strnlen_int( const char *start, size_t max_len)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    const char *end = (const char *)memchr(start, '\0', max_len);

    return end ? (size_t)(end - start) : max_len;
}
<<<<<<< HEAD
#endif // HAVE_DECL_STRNLEN
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
