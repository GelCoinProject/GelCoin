<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_SPLASHSCREEN_H
#define BITCOIN_QT_SPLASHSCREEN_H

<<<<<<< HEAD
#include <functional>
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <QSplashScreen>

class NetworkStyle;

/** Class for the splashscreen with information of the running client.
 *
 * @note this is intentionally not a QSplashScreen. Bitcoin Core initialization
 * can take a long time, and in that case a progress window that cannot be
 * moved around and minimized has turned out to be frustrating to the user.
 */
class SplashScreen : public QWidget
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit SplashScreen(Qt::WindowFlags f, const NetworkStyle *networkStyle);
    ~SplashScreen();

protected:
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

public Q_SLOTS:
    /** Slot to call finish() method as it's not defined as slot */
    void slotFinish(QWidget *mainWin);

    /** Show message and progress */
    void showMessage(const QString &message, int alignment, const QColor &color);

    /** Sets the break action */
    void setBreakAction(const std::function<void(void)> &action);
protected:
    bool eventFilter(QObject * obj, QEvent * ev);
=======
    explicit SplashScreen(Qt::WindowFlags f, const NetworkStyle* networkStyle);
    ~SplashScreen();

protected:
    void paintEvent(QPaintEvent* event);
    void closeEvent(QCloseEvent* event);

public slots:
    /** Slot to call finish() method as it's not defined as slot */
    void slotFinish(QWidget* mainWin);

    /** Show message and progress */
    void showMessage(const QString& message, int alignment, const QColor& color);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

private:
    /** Connect core signals to splash screen */
    void subscribeToCoreSignals();
    /** Disconnect core signals to splash screen */
    void unsubscribeFromCoreSignals();

    QPixmap pixmap;
    QString curMessage;
    QColor curColor;
    int curAlignment;
<<<<<<< HEAD

    std::function<void(void)> breakAction;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_SPLASHSCREEN_H
