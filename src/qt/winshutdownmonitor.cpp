<<<<<<< HEAD
// Copyright (c) 2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "winshutdownmonitor.h"

#if defined(Q_OS_WIN) && QT_VERSION >= 0x050000
#include "init.h"
#include "util.h"

#include <windows.h>

#include <QDebug>

#include <openssl/rand.h>

// If we don't want a message to be processed by Qt, return true and set result to
// the value that the window procedure should return. Otherwise return false.
<<<<<<< HEAD
bool WinShutdownMonitor::nativeEventFilter(const QByteArray &eventType, void *pMessage, long *pnResult)
{
       Q_UNUSED(eventType);

       MSG *pMsg = static_cast<MSG *>(pMessage);

       // Seed OpenSSL PRNG with Windows event data (e.g.  mouse movements and other user interactions)
       if (RAND_event(pMsg->message, pMsg->wParam, pMsg->lParam) == 0) {
            // Warn only once as this is performance-critical
            static bool warned = false;
            if (!warned) {
                LogPrintf("%s: OpenSSL RAND_event() failed to seed OpenSSL PRNG with enough data.\n", __func__);
                warned = true;
            }
       }

       switch(pMsg->message)
       {
           case WM_QUERYENDSESSION:
           {
               // Initiate a client shutdown after receiving a WM_QUERYENDSESSION and block
               // Windows session end until we have finished client shutdown.
               StartShutdown();
               *pnResult = FALSE;
               return true;
           }

           case WM_ENDSESSION:
           {
               *pnResult = FALSE;
               return true;
           }
       }

       return false;
=======
bool WinShutdownMonitor::nativeEventFilter(const QByteArray& eventType, void* pMessage, long* pnResult)
{
    Q_UNUSED(eventType);

    MSG* pMsg = static_cast<MSG*>(pMessage);

    // Seed OpenSSL PRNG with Windows event data (e.g.  mouse movements and other user interactions)
    if (RAND_event(pMsg->message, pMsg->wParam, pMsg->lParam) == 0) {
        // Warn only once as this is performance-critical
        static bool warned = false;
        if (!warned) {
            LogPrint("%s: OpenSSL RAND_event() failed to seed OpenSSL PRNG with enough data.\n", __func__);
            warned = true;
        }
    }

    switch (pMsg->message) {
    case WM_QUERYENDSESSION: {
        // Initiate a client shutdown after receiving a WM_QUERYENDSESSION and block
        // Windows session end until we have finished client shutdown.
        StartShutdown();
        *pnResult = FALSE;
        return true;
    }

    case WM_ENDSESSION: {
        *pnResult = FALSE;
        return true;
    }
    }

    return false;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void WinShutdownMonitor::registerShutdownBlockReason(const QString& strReason, const HWND& mainWinId)
{
<<<<<<< HEAD
    typedef BOOL (WINAPI *PSHUTDOWNBRCREATE)(HWND, LPCWSTR);
=======
    typedef BOOL(WINAPI * PSHUTDOWNBRCREATE)(HWND, LPCWSTR);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    PSHUTDOWNBRCREATE shutdownBRCreate = (PSHUTDOWNBRCREATE)GetProcAddress(GetModuleHandleA("User32.dll"), "ShutdownBlockReasonCreate");
    if (shutdownBRCreate == NULL) {
        qWarning() << "registerShutdownBlockReason: GetProcAddress for ShutdownBlockReasonCreate failed";
        return;
    }

    if (shutdownBRCreate(mainWinId, strReason.toStdWString().c_str()))
        qWarning() << "registerShutdownBlockReason: Successfully registered: " + strReason;
    else
        qWarning() << "registerShutdownBlockReason: Failed to register: " + strReason;
}
#endif
