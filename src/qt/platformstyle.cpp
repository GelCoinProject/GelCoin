// Copyright (c) 2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "platformstyle.h"

#include "guiconstants.h"

#include <QApplication>
#include <QColor>
#include <QIcon>
#include <QImage>
#include <QPalette>
#include <QPixmap>

static const struct {
<<<<<<< HEAD
    const char *platformId;
=======
    const char* platformId;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Show images on push buttons */
    const bool imagesOnButtons;
    /** Colorize single-color icons */
    const bool colorizeIcons;
    /** Extra padding/spacing in transactionview */
    const bool useExtraSpacing;
} platform_styles[] = {
    {"macosx", false, false, true},
    {"windows", true, false, false},
    /* Other: linux, unix, ... */
<<<<<<< HEAD
    {"other", true, false, false}
};
static const unsigned platform_styles_count = sizeof(platform_styles)/sizeof(*platform_styles);

namespace {
=======
    {"other", true, false, false}};
static const unsigned platform_styles_count = sizeof(platform_styles) / sizeof(*platform_styles);

namespace
{
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
/* Local functions for colorizing single-color images */

void MakeSingleColorImage(QImage& img, const QColor& colorbase)
{
    img = img.convertToFormat(QImage::Format_ARGB32);
<<<<<<< HEAD
    for (int x = img.width(); x--; )
    {
        for (int y = img.height(); y--; )
        {
=======
    for (int x = img.width(); x--;) {
        for (int y = img.height(); y--;) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            const QRgb rgb = img.pixel(x, y);
            img.setPixel(x, y, qRgba(colorbase.red(), colorbase.green(), colorbase.blue(), qAlpha(rgb)));
        }
    }
}

QIcon ColorizeIcon(const QIcon& ico, const QColor& colorbase)
{
    QIcon new_ico;
    QSize sz;
<<<<<<< HEAD
    Q_FOREACH(sz, ico.availableSizes())
    {
=======
    Q_FOREACH (sz, ico.availableSizes()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        QImage img(ico.pixmap(sz).toImage());
        MakeSingleColorImage(img, colorbase);
        new_ico.addPixmap(QPixmap::fromImage(img));
    }
    return new_ico;
}

QImage ColorizeImage(const QString& filename, const QColor& colorbase)
{
    QImage img(filename);
    MakeSingleColorImage(img, colorbase);
    return img;
}

QIcon ColorizeIcon(const QString& filename, const QColor& colorbase)
{
    return QIcon(QPixmap::fromImage(ColorizeImage(filename, colorbase)));
}
<<<<<<< HEAD

}


PlatformStyle::PlatformStyle(const QString &name, bool imagesOnButtons, bool colorizeIcons, bool useExtraSpacing):
    name(name),
    imagesOnButtons(imagesOnButtons),
    colorizeIcons(colorizeIcons),
    useExtraSpacing(useExtraSpacing),
    singleColor(0,0,0),
    textColor(0,0,0)
=======
}


PlatformStyle::PlatformStyle(const QString& name, bool imagesOnButtons, bool colorizeIcons, bool useExtraSpacing) : name(name),
                                                                                                                    imagesOnButtons(imagesOnButtons),
                                                                                                                    colorizeIcons(colorizeIcons),
                                                                                                                    useExtraSpacing(useExtraSpacing),
                                                                                                                    singleColor(0, 0, 0),
                                                                                                                    textColor(0, 0, 0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    // Determine icon highlighting color
    if (colorizeIcons) {
        const QColor colorHighlightBg(QApplication::palette().color(QPalette::Highlight));
        const QColor colorHighlightFg(QApplication::palette().color(QPalette::HighlightedText));
        const QColor colorText(QApplication::palette().color(QPalette::WindowText));
        const int colorTextLightness = colorText.lightness();
        QColor colorbase;
        if (abs(colorHighlightBg.lightness() - colorTextLightness) < abs(colorHighlightFg.lightness() - colorTextLightness))
            colorbase = colorHighlightBg;
        else
            colorbase = colorHighlightFg;
        singleColor = colorbase;
    }
    // Determine text color
    textColor = QColor(QApplication::palette().color(QPalette::WindowText));
}

QImage PlatformStyle::SingleColorImage(const QString& filename) const
{
    if (!colorizeIcons)
        return QImage(filename);
    return ColorizeImage(filename, SingleColor());
}

QIcon PlatformStyle::SingleColorIcon(const QString& filename) const
{
    if (!colorizeIcons)
        return QIcon(filename);
    return ColorizeIcon(filename, SingleColor());
}

QIcon PlatformStyle::SingleColorIcon(const QIcon& icon) const
{
    if (!colorizeIcons)
        return icon;
    return ColorizeIcon(icon, SingleColor());
}

QIcon PlatformStyle::TextColorIcon(const QString& filename) const
{
    return ColorizeIcon(filename, TextColor());
}

QIcon PlatformStyle::TextColorIcon(const QIcon& icon) const
{
    return ColorizeIcon(icon, TextColor());
}

<<<<<<< HEAD
const PlatformStyle *PlatformStyle::instantiate(const QString &platformId)
{
    for (unsigned x=0; x<platform_styles_count; ++x)
    {
        if (platformId == platform_styles[x].platformId)
        {
            return new PlatformStyle(
                    platform_styles[x].platformId,
                    platform_styles[x].imagesOnButtons,
                    platform_styles[x].colorizeIcons,
                    platform_styles[x].useExtraSpacing);
=======
const PlatformStyle* PlatformStyle::instantiate(const QString& platformId)
{
    for (unsigned x = 0; x < platform_styles_count; ++x) {
        if (platformId == platform_styles[x].platformId) {
            return new PlatformStyle(
                platform_styles[x].platformId,
                platform_styles[x].imagesOnButtons,
                platform_styles[x].colorizeIcons,
                platform_styles[x].useExtraSpacing);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }
    return 0;
}
<<<<<<< HEAD

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
