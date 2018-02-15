<<<<<<< HEAD
// Copyright (c) 2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_WINSHUTDOWNMONITOR_H
#define BITCOIN_QT_WINSHUTDOWNMONITOR_H

#ifdef WIN32
#include <QByteArray>
#include <QString>

#if QT_VERSION >= 0x050000
#include <windef.h> // for HWND

#include <QAbstractNativeEventFilter>

class WinShutdownMonitor : public QAbstractNativeEventFilter
{
public:
    /** Implements QAbstractNativeEventFilter interface for processing Windows messages */
<<<<<<< HEAD
    bool nativeEventFilter(const QByteArray &eventType, void *pMessage, long *pnResult);
=======
    bool nativeEventFilter(const QByteArray& eventType, void* pMessage, long* pnResult);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Register the reason for blocking shutdown on Windows to allow clean client exit */
    static void registerShutdownBlockReason(const QString& strReason, const HWND& mainWinId);
};
#endif
#endif

#endif // BITCOIN_QT_WINSHUTDOWNMONITOR_H
