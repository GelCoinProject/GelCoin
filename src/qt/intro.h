<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_INTRO_H
#define BITCOIN_QT_INTRO_H

#include <QDialog>
#include <QMutex>
#include <QThread>

<<<<<<< HEAD
static const bool DEFAULT_CHOOSE_DATADIR = false;

class FreespaceChecker;

namespace Ui {
    class Intro;
=======
class FreespaceChecker;

namespace Ui
{
class Intro;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

/** Introduction screen (pre-GUI startup).
  Allows the user to choose a data directory,
  in which the wallet and block chain will be stored.
 */
class Intro : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit Intro(QWidget *parent = 0);
    ~Intro();

    QString getDataDirectory();
    void setDataDirectory(const QString &dataDir);
=======
    explicit Intro(QWidget* parent = 0);
    ~Intro();

    QString getDataDirectory();
    void setDataDirectory(const QString& dataDir);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /**
     * Determine data directory. Let the user choose if the current one doesn't exist.
     *
     * @note do NOT call global GetDataDir() before calling this function, this
     * will cause the wrong path to be cached.
     */
    static void pickDataDirectory();

    /**
     * Determine default data directory for operating system.
     */
    static QString getDefaultDataDirectory();

<<<<<<< HEAD
Q_SIGNALS:
    void requestCheck();
    void stopThread();

public Q_SLOTS:
    void setStatus(int status, const QString &message, quint64 bytesAvailable);

private Q_SLOTS:
    void on_dataDirectory_textChanged(const QString &arg1);
=======
signals:
    void requestCheck();
    void stopThread();

public slots:
    void setStatus(int status, const QString& message, quint64 bytesAvailable);

private slots:
    void on_dataDirectory_textChanged(const QString& arg1);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void on_ellipsisButton_clicked();
    void on_dataDirDefault_clicked();
    void on_dataDirCustom_clicked();

private:
<<<<<<< HEAD
    Ui::Intro *ui;
    QThread *thread;
=======
    Ui::Intro* ui;
    QThread* thread;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QMutex mutex;
    bool signalled;
    QString pathToCheck;

    void startThread();
<<<<<<< HEAD
    void checkPath(const QString &dataDir);
=======
    void checkPath(const QString& dataDir);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QString getPathToCheck();

    friend class FreespaceChecker;
};

#endif // BITCOIN_QT_INTRO_H
