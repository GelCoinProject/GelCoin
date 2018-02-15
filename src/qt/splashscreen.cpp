<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "splashscreen.h"

<<<<<<< HEAD
#include "guiutil.h"
#include "networkstyle.h"

#include "clientversion.h"
#include "init.h"
#include "util.h"
#include "ui_interface.h"
#include "version.h"
#ifdef ENABLE_WALLET
#include "wallet/wallet.h"
=======
#include "clientversion.h"
#include "init.h"
#include "networkstyle.h"
#include "ui_interface.h"
#include "util.h"
#include "version.h"

#ifdef ENABLE_WALLET
#include "wallet.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif

#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QPainter>

<<<<<<< HEAD
SplashScreen::SplashScreen(Qt::WindowFlags f, const NetworkStyle *networkStyle) :
    QWidget(0, f), curAlignment(0)
{

    // transparent background
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background:transparent;");

    // no window decorations
    setWindowFlags(Qt::FramelessWindowHint);

    // set reference point, paddings
    int paddingLeft             = 14;
    int paddingTop              = 470;
    int titleVersionVSpace      = 17;
    int titleCopyrightVSpace    = 32;

    float fontFactor            = 1.0;

    // define text to place
    QString titleText       = tr("GelCoin");
    QString versionText     = QString(tr("Version %1")).arg(QString::fromStdString(FormatFullVersion()));
    QString copyrightTextBtc   = QChar(0xA9)+QString(" 2009-%1 ").arg(COPYRIGHT_YEAR) + QString(tr("The Bitcoin Core developers"));
    QString copyrightTextGelCoin   = QChar(0xA9)+QString(" 2014-%1 ").arg(COPYRIGHT_YEAR) + QString(tr("The GelCoin developers"));
    QString titleAddText    = networkStyle->getTitleAddText();
    // networkstyle.cpp can't (yet) read themes, so we do it here to get the correct Splash-screen
    QString splashScreenPath = ":/images/" + GUIUtil::getThemeName() + "/splash";
    if(GetBoolArg("-regtest", false))
        splashScreenPath = ":/images/" + GUIUtil::getThemeName() + "/splash_testnet";
    if(GetBoolArg("-testnet", false))
        splashScreenPath = ":/images/" + GUIUtil::getThemeName() + "/splash_testnet";
=======
SplashScreen::SplashScreen(Qt::WindowFlags f, const NetworkStyle* networkStyle) : QWidget(0, f), curAlignment(0)
{
    // set reference point, paddings
    int paddingLeft = 14;
    int paddingTop = 470;
    int titleVersionVSpace = 17;
    int titleCopyrightVSpace = 32;

    float fontFactor = 1.0;

    // define text to place
    QString titleText = tr("LUX Core");
    QString versionText = QString(tr("Version %1")).arg(QString::fromStdString(FormatFullVersion()));
    QString copyrightTextBtc = QChar(0xA9) + QString(" 2009-%1 ").arg(COPYRIGHT_YEAR) + QString(tr("The Bitcoin Core developers"));
    QString copyrightTextDash = QChar(0xA9) + QString(" 2014-%1 ").arg(COPYRIGHT_YEAR) + QString(tr("The Dash Core developers"));
    QString copyrightTextLUX = QChar(0xA9) + QString(" 2015-%1 ").arg(COPYRIGHT_YEAR) + QString(tr("The LUX Core developers"));
    QString titleAddText = networkStyle->getTitleAddText();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    QString font = QApplication::font().toString();

    // load the bitmap for writing some text over it
<<<<<<< HEAD
    pixmap = QPixmap(splashScreenPath);

    QPainter pixPaint(&pixmap);
    pixPaint.setPen(QColor(100,100,100));

    // check font size and drawing with
    pixPaint.setFont(QFont(font, 28*fontFactor));
    QFontMetrics fm = pixPaint.fontMetrics();
    int titleTextWidth  = fm.width(titleText);
    if(titleTextWidth > 160) {
=======
    pixmap = networkStyle->getSplashImage();

    QPainter pixPaint(&pixmap);
    pixPaint.setPen(QColor(100, 100, 100));

    // check font size and drawing with
    pixPaint.setFont(QFont(font, 28 * fontFactor));
    QFontMetrics fm = pixPaint.fontMetrics();
    int titleTextWidth = fm.width(titleText);
    if (titleTextWidth > 160) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // strange font rendering, Arial probably not found
        fontFactor = 0.75;
    }

<<<<<<< HEAD
    pixPaint.setFont(QFont(font, 28*fontFactor));
    fm = pixPaint.fontMetrics();
    titleTextWidth  = fm.width(titleText);
    pixPaint.drawText(paddingLeft,paddingTop,titleText);

    pixPaint.setFont(QFont(font, 15*fontFactor));
    pixPaint.drawText(paddingLeft,paddingTop+titleVersionVSpace,versionText);

    // draw copyright stuff
    pixPaint.setFont(QFont(font, 10*fontFactor));
    pixPaint.drawText(paddingLeft,paddingTop+titleCopyrightVSpace,copyrightTextBtc);
    pixPaint.drawText(paddingLeft,paddingTop+titleCopyrightVSpace+12,copyrightTextGelCoin);

    // draw additional text if special network
    if(!titleAddText.isEmpty()) {
        QFont boldFont = QFont(font, 10*fontFactor);
        boldFont.setWeight(QFont::Bold);
        pixPaint.setFont(boldFont);
        fm = pixPaint.fontMetrics();
        int titleAddTextWidth  = fm.width(titleAddText);
        pixPaint.drawText(pixmap.width()-titleAddTextWidth-10,pixmap.height()-25,titleAddText);
=======
    pixPaint.setFont(QFont(font, 28 * fontFactor));
    fm = pixPaint.fontMetrics();
    //titleTextWidth = fm.width(titleText);
    pixPaint.drawText(paddingLeft, paddingTop, titleText);

    pixPaint.setFont(QFont(font, 15 * fontFactor));
    pixPaint.drawText(paddingLeft, paddingTop + titleVersionVSpace, versionText);

    // draw copyright stuff
    pixPaint.setFont(QFont(font, 10 * fontFactor));
    pixPaint.drawText(paddingLeft, paddingTop + titleCopyrightVSpace, copyrightTextBtc);
    pixPaint.drawText(paddingLeft, paddingTop + titleCopyrightVSpace + 12, copyrightTextDash);
    pixPaint.drawText(paddingLeft, paddingTop + titleCopyrightVSpace + 24, copyrightTextLUX);

    // draw additional text if special network
    if (!titleAddText.isEmpty()) {
        QFont boldFont = QFont(font, 10 * fontFactor);
        boldFont.setWeight(QFont::Bold);
        pixPaint.setFont(boldFont);
        fm = pixPaint.fontMetrics();
        int titleAddTextWidth = fm.width(titleAddText);
        pixPaint.drawText(pixmap.width() - titleAddTextWidth - 10, pixmap.height() - 25, titleAddText);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    pixPaint.end();

<<<<<<< HEAD
=======
    // Set window title
    setWindowTitle(titleText + " " + titleAddText);

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    // Resize window and move to center of desktop, disallow resizing
    QRect r(QPoint(), pixmap.size());
    resize(r.size());
    setFixedSize(r.size());
    move(QApplication::desktop()->screenGeometry().center() - r.center());

    subscribeToCoreSignals();
<<<<<<< HEAD
    installEventFilter(this);
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

SplashScreen::~SplashScreen()
{
    unsubscribeFromCoreSignals();
}

<<<<<<< HEAD
bool SplashScreen::eventFilter(QObject * obj, QEvent * ev) {
    if (ev->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(ev);
        if(keyEvent->text()[0] == 'q' && breakAction != nullptr) {
            breakAction();
        }
    }
    return QObject::eventFilter(obj, ev);
}

void SplashScreen::slotFinish(QWidget *mainWin)
{
    Q_UNUSED(mainWin);

    /* If the window is minimized, hide() will be ignored. */
    /* Make sure we de-minimize the splashscreen window before hiding */
    if (isMinimized())
        showNormal();
    hide();
    deleteLater(); // No more need for this
}

static void InitMessage(SplashScreen *splash, const std::string &message)
=======
void SplashScreen::slotFinish(QWidget* mainWin)
{
    Q_UNUSED(mainWin);
    hide();
}

static void InitMessage(SplashScreen* splash, const std::string& message)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QMetaObject::invokeMethod(splash, "showMessage",
        Qt::QueuedConnection,
        Q_ARG(QString, QString::fromStdString(message)),
<<<<<<< HEAD
        Q_ARG(int, Qt::AlignBottom|Qt::AlignHCenter),
        Q_ARG(QColor, QColor(55,55,55)));
}

static void ShowProgress(SplashScreen *splash, const std::string &title, int nProgress)
=======
        Q_ARG(int, Qt::AlignBottom | Qt::AlignHCenter),
        Q_ARG(QColor, QColor(55, 55, 55)));
}

static void ShowProgress(SplashScreen* splash, const std::string& title, int nProgress)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    InitMessage(splash, title + strprintf("%d", nProgress) + "%");
}

<<<<<<< HEAD
void SplashScreen::setBreakAction(const std::function<void(void)> &action)
{
    breakAction = action;
}

static void SetProgressBreakAction(SplashScreen *splash, const std::function<void(void)> &action)
{
    QMetaObject::invokeMethod(splash, "setBreakAction",
        Qt::QueuedConnection,
        Q_ARG(std::function<void(void)>, action));
}

#ifdef ENABLE_WALLET
static void ConnectWallet(SplashScreen *splash, CWallet* wallet)
=======
#ifdef ENABLE_WALLET
static void ConnectWallet(SplashScreen* splash, CWallet* wallet)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    wallet->ShowProgress.connect(boost::bind(ShowProgress, splash, _1, _2));
}
#endif

void SplashScreen::subscribeToCoreSignals()
{
    // Connect signals to client
    uiInterface.InitMessage.connect(boost::bind(InitMessage, this, _1));
    uiInterface.ShowProgress.connect(boost::bind(ShowProgress, this, _1, _2));
<<<<<<< HEAD
    uiInterface.SetProgressBreakAction.connect(boost::bind(SetProgressBreakAction, this, _1));
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifdef ENABLE_WALLET
    uiInterface.LoadWallet.connect(boost::bind(ConnectWallet, this, _1));
#endif
}

void SplashScreen::unsubscribeFromCoreSignals()
{
    // Disconnect signals from client
    uiInterface.InitMessage.disconnect(boost::bind(InitMessage, this, _1));
    uiInterface.ShowProgress.disconnect(boost::bind(ShowProgress, this, _1, _2));
#ifdef ENABLE_WALLET
<<<<<<< HEAD
    if(pwalletMain)
=======
    if (pwalletMain)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        pwalletMain->ShowProgress.disconnect(boost::bind(ShowProgress, this, _1, _2));
#endif
}

<<<<<<< HEAD
void SplashScreen::showMessage(const QString &message, int alignment, const QColor &color)
=======
void SplashScreen::showMessage(const QString& message, int alignment, const QColor& color)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    curMessage = message;
    curAlignment = alignment;
    curColor = color;
    update();
}

<<<<<<< HEAD
void SplashScreen::paintEvent(QPaintEvent *event)
=======
void SplashScreen::paintEvent(QPaintEvent* event)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
    QRect r = rect().adjusted(5, 5, -5, -5);
    painter.setPen(curColor);
    painter.drawText(r, curAlignment, curMessage);
}

<<<<<<< HEAD
void SplashScreen::closeEvent(QCloseEvent *event)
=======
void SplashScreen::closeEvent(QCloseEvent* event)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    StartShutdown(); // allows an "emergency" shutdown during startup
    event->ignore();
}
