<<<<<<< HEAD
// Copyright (c) 2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
=======
// Copyright (c) 2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_NETWORKSTYLE_H
#define BITCOIN_QT_NETWORKSTYLE_H

#include <QIcon>
#include <QPixmap>
#include <QString>

/* Coin network-specific GUI style information */
class NetworkStyle
{
public:
    /** Get style associated with provided BIP70 network id, or 0 if not known */
<<<<<<< HEAD
    static const NetworkStyle *instantiate(const QString &networkId);

    const QString &getAppName() const { return appName; }
    const QIcon &getAppIcon() const { return appIcon; }
    const QPixmap &getSplashImage() const { return splashImage; }
    const QIcon &getTrayAndWindowIcon() const { return trayAndWindowIcon; }
    const QString &getTitleAddText() const { return titleAddText; }

private:
    NetworkStyle(const QString &appName, const int iconColorHueShift, const int iconColorSaturationReduction, const char *titleAddText);

    QString appName;
    QIcon appIcon;
    QPixmap splashImage;
    QIcon trayAndWindowIcon;
    QString titleAddText;

    void rotateColors(QImage& img, const int iconColorHueShift, const int iconColorSaturationReduction);
=======
    static const NetworkStyle* instantiate(const QString& networkId);

    const QString& getAppName() const { return appName; }
    const QIcon& getAppIcon() const { return appIcon; }
    const QString& getTitleAddText() const { return titleAddText; }
    const QPixmap& getSplashImage() const { return splashImage; }

private:
    NetworkStyle(const QString& appName, const QString& appIcon, const char* titleAddText, const QString& splashImage);

    QString appName;
    QIcon appIcon;
    QString titleAddText;
    QPixmap splashImage;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_NETWORKSTYLE_H
