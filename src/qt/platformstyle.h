// Copyright (c) 2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_PLATFORMSTYLE_H
#define BITCOIN_QT_PLATFORMSTYLE_H

#include <QIcon>
#include <QPixmap>
#include <QString>

/* Coin network-specific GUI style information */
class PlatformStyle
{
public:
    /** Get style associated with provided platform name, or 0 if not known */
<<<<<<< HEAD
    static const PlatformStyle *instantiate(const QString &platformId);

    const QString &getName() const { return name; }
=======
    static const PlatformStyle* instantiate(const QString& platformId);

    const QString& getName() const { return name; }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    bool getImagesOnButtons() const { return imagesOnButtons; }
    bool getUseExtraSpacing() const { return useExtraSpacing; }

    QColor TextColor() const { return textColor; }
    QColor SingleColor() const { return singleColor; }

    /** Colorize an image (given filename) with the icon color */
    QImage SingleColorImage(const QString& filename) const;

    /** Colorize an icon (given filename) with the icon color */
    QIcon SingleColorIcon(const QString& filename) const;

    /** Colorize an icon (given object) with the icon color */
    QIcon SingleColorIcon(const QIcon& icon) const;

    /** Colorize an icon (given filename) with the text color */
    QIcon TextColorIcon(const QString& filename) const;

    /** Colorize an icon (given object) with the text color */
    QIcon TextColorIcon(const QIcon& icon) const;

private:
<<<<<<< HEAD
    PlatformStyle(const QString &name, bool imagesOnButtons, bool colorizeIcons, bool useExtraSpacing);
=======
    PlatformStyle(const QString& name, bool imagesOnButtons, bool colorizeIcons, bool useExtraSpacing);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    QString name;
    bool imagesOnButtons;
    bool colorizeIcons;
    bool useExtraSpacing;
    QColor singleColor;
    QColor textColor;
    /* ... more to come later */
};

#endif // BITCOIN_QT_PLATFORMSTYLE_H
<<<<<<< HEAD

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
