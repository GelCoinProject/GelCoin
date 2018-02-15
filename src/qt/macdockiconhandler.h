<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_MACDOCKICONHANDLER_H
#define BITCOIN_QT_MACDOCKICONHANDLER_H

#include <QMainWindow>
#include <QObject>

QT_BEGIN_NAMESPACE
class QIcon;
class QMenu;
class QWidget;
QT_END_NAMESPACE

/** Macintosh-specific dock icon handler.
 */
class MacDockIconHandler : public QObject
{
    Q_OBJECT

public:
    ~MacDockIconHandler();

<<<<<<< HEAD
    QMenu *dockMenu();
    void setIcon(const QIcon &icon);
    void setMainWindow(QMainWindow *window);
    static MacDockIconHandler *instance();
    static void cleanup();
    void handleDockIconClickEvent();

Q_SIGNALS:
=======
    QMenu* dockMenu();
    void setIcon(const QIcon& icon);
    void setMainWindow(QMainWindow* window);
    static MacDockIconHandler* instance();
    static void cleanup();
    void handleDockIconClickEvent();

signals:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void dockIconClicked();

private:
    MacDockIconHandler();

<<<<<<< HEAD
    QWidget *m_dummyWidget;
    QMenu *m_dockMenu;
    QMainWindow *mainWindow;
=======
    QWidget* m_dummyWidget;
    QMenu* m_dockMenu;
    QMainWindow* mainWindow;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_MACDOCKICONHANDLER_H
