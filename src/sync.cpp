<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "sync.h"

#include "util.h"
#include "utilstrencodings.h"

#include <stdio.h>

#include <boost/foreach.hpp>
#include <boost/thread.hpp>

#ifdef DEBUG_LOCKCONTENTION
void PrintLockContention(const char* pszName, const char* pszFile, int nLine)
{
<<<<<<< HEAD
    LogPrintf("LOCKCONTENTION: %s Locker: %s:%d\n", pszName, pszFile, nLine);
=======
    LogPrintf("LOCKCONTENTION: %s\n", pszName);
    LogPrintf("Locker: %s:%d\n", pszFile, nLine);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
#endif /* DEBUG_LOCKCONTENTION */

#ifdef DEBUG_LOCKORDER
//
// Early deadlock detection.
// Problem being solved:
//    Thread 1 locks  A, then B, then C
//    Thread 2 locks  D, then C, then A
//     --> may result in deadlock between the two threads, depending on when they run.
// Solution implemented here:
// Keep track of pairs of locks: (A before B), (A before C), etc.
// Complain if any thread tries to lock in a different order.
//

struct CLockLocation {
<<<<<<< HEAD
    CLockLocation(const char* pszName, const char* pszFile, int nLine, bool fTryIn)
=======
    CLockLocation(const char* pszName, const char* pszFile, int nLine)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        mutexName = pszName;
        sourceFile = pszFile;
        sourceLine = nLine;
<<<<<<< HEAD
        fTry = fTryIn;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    std::string ToString() const
    {
<<<<<<< HEAD
        return mutexName + "  " + sourceFile + ":" + itostr(sourceLine) + (fTry ? " (TRY)" : "");
=======
        return mutexName + "  " + sourceFile + ":" + itostr(sourceLine);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    std::string MutexName() const { return mutexName; }

<<<<<<< HEAD
    bool fTry;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
private:
    std::string mutexName;
    std::string sourceFile;
    int sourceLine;
};

typedef std::vector<std::pair<void*, CLockLocation> > LockStack;

static boost::mutex dd_mutex;
static std::map<std::pair<void*, void*>, LockStack> lockorders;
static boost::thread_specific_ptr<LockStack> lockstack;


static void potential_deadlock_detected(const std::pair<void*, void*>& mismatch, const LockStack& s1, const LockStack& s2)
{
<<<<<<< HEAD
    // We attempt to not assert on probably-not deadlocks by assuming that
    // a try lock will immediately have otherwise bailed if it had
    // failed to get the lock
    // We do this by, for the locks which triggered the potential deadlock,
    // in either lockorder, checking that the second of the two which is locked
    // is only a TRY_LOCK, ignoring locks if they are reentrant.
    bool firstLocked = false;
    bool secondLocked = false;
    bool onlyMaybeDeadlock = false;
    std::string strOutput = "";

    strOutput += "POTENTIAL DEADLOCK DETECTED\n";
    strOutput += "Previous lock order was:\n";
    BOOST_FOREACH (const PAIRTYPE(void*, CLockLocation) & i, s2) {
        if (i.first == mismatch.first) {
            strOutput += " (1)";
            if (!firstLocked && secondLocked && i.second.fTry)
                onlyMaybeDeadlock = true;
            firstLocked = true;
        }
        if (i.first == mismatch.second) {
            strOutput += " (2)";
            if (!secondLocked && firstLocked && i.second.fTry)
                onlyMaybeDeadlock = true;
            secondLocked = true;
        }
        strOutput += strprintf(" %s\n", i.second.ToString().c_str());
    }
    firstLocked = false;
    secondLocked = false;
    strOutput += "Current lock order is:\n";
    BOOST_FOREACH (const PAIRTYPE(void*, CLockLocation) & i, s1) {
        if (i.first == mismatch.first) {
            strOutput += " (1)";
            if (!firstLocked && secondLocked && i.second.fTry)
                onlyMaybeDeadlock = true;
            firstLocked = true;
        }
        if (i.first == mismatch.second) {
            strOutput += " (2)";
            if (!secondLocked && firstLocked && i.second.fTry)
                onlyMaybeDeadlock = true;
            secondLocked = true;
        }
        strOutput += strprintf(" %s\n", i.second.ToString().c_str());
    }
    if(!onlyMaybeDeadlock) {
        printf("%s\n", strOutput.c_str());
        LogPrintf("%s\n", strOutput.c_str());
    }
    assert(onlyMaybeDeadlock);
=======
    LogPrintf("POTENTIAL DEADLOCK DETECTED\n");
    LogPrintf("Previous lock order was:\n");
    BOOST_FOREACH (const PAIRTYPE(void*, CLockLocation) & i, s2) {
        if (i.first == mismatch.first)
            LogPrintf(" (1)");
        if (i.first == mismatch.second)
            LogPrintf(" (2)");
        LogPrintf(" %s\n", i.second.ToString());
    }
    LogPrintf("Current lock order is:\n");
    BOOST_FOREACH (const PAIRTYPE(void*, CLockLocation) & i, s1) {
        if (i.first == mismatch.first)
            LogPrintf(" (1)");
        if (i.first == mismatch.second)
            LogPrintf(" (2)");
        LogPrintf(" %s\n", i.second.ToString());
    }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

static void push_lock(void* c, const CLockLocation& locklocation, bool fTry)
{
    if (lockstack.get() == NULL)
        lockstack.reset(new LockStack);

<<<<<<< HEAD
=======
    LogPrint("lock", "Locking: %s\n", locklocation.ToString());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    dd_mutex.lock();

    (*lockstack).push_back(std::make_pair(c, locklocation));

    if (!fTry) {
        BOOST_FOREACH (const PAIRTYPE(void*, CLockLocation) & i, (*lockstack)) {
            if (i.first == c)
                break;

            std::pair<void*, void*> p1 = std::make_pair(i.first, c);
            if (lockorders.count(p1))
                continue;
            lockorders[p1] = (*lockstack);

            std::pair<void*, void*> p2 = std::make_pair(c, i.first);
<<<<<<< HEAD
            if (lockorders.count(p2))
                potential_deadlock_detected(p1, lockorders[p2], lockorders[p1]);
=======
            if (lockorders.count(p2)) {
                potential_deadlock_detected(p1, lockorders[p2], lockorders[p1]);
                break;
            }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }
    dd_mutex.unlock();
}

static void pop_lock()
{
<<<<<<< HEAD
=======
    if (fDebug) {
        const CLockLocation& locklocation = (*lockstack).rbegin()->second;
        LogPrint("lock", "Unlocked: %s\n", locklocation.ToString());
    }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    dd_mutex.lock();
    (*lockstack).pop_back();
    dd_mutex.unlock();
}

void EnterCritical(const char* pszName, const char* pszFile, int nLine, void* cs, bool fTry)
{
<<<<<<< HEAD
    push_lock(cs, CLockLocation(pszName, pszFile, nLine, fTry), fTry);
=======
    push_lock(cs, CLockLocation(pszName, pszFile, nLine), fTry);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void LeaveCritical()
{
    pop_lock();
}

std::string LocksHeld()
{
    std::string result;
    BOOST_FOREACH (const PAIRTYPE(void*, CLockLocation) & i, *lockstack)
        result += i.second.ToString() + std::string("\n");
    return result;
}

void AssertLockHeldInternal(const char* pszName, const char* pszFile, int nLine, void* cs)
{
    BOOST_FOREACH (const PAIRTYPE(void*, CLockLocation) & i, *lockstack)
        if (i.first == cs)
            return;
    fprintf(stderr, "Assertion failed: lock %s not held in %s:%i; locks held:\n%s", pszName, pszFile, nLine, LocksHeld().c_str());
    abort();
}

#endif /* DEBUG_LOCKORDER */
