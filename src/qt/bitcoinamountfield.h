<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_BITCOINAMOUNTFIELD_H
#define BITCOIN_QT_BITCOINAMOUNTFIELD_H

#include "amount.h"

#include <QWidget>

class AmountSpinBox;

QT_BEGIN_NAMESPACE
class QValueComboBox;
QT_END_NAMESPACE

/** Widget for entering bitcoin amounts.
  */
<<<<<<< HEAD
class BitcoinAmountField: public QWidget
=======
class BitcoinAmountField : public QWidget
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Q_OBJECT

    // ugly hack: for some unknown reason CAmount (instead of qint64) does not work here as expected
    // discussion: https://github.com/bitcoin/bitcoin/pull/5117
    Q_PROPERTY(qint64 value READ value WRITE setValue NOTIFY valueChanged USER true)

public:
<<<<<<< HEAD
    explicit BitcoinAmountField(QWidget *parent = 0);

    CAmount value(bool *value=0) const;
=======
    explicit BitcoinAmountField(QWidget* parent = 0);

    CAmount value(bool* value = 0) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void setValue(const CAmount& value);

    /** Set single step in satoshis **/
    void setSingleStep(const CAmount& step);

    /** Make read-only **/
    void setReadOnly(bool fReadOnly);

    /** Mark current value as invalid in UI. */
    void setValid(bool valid);
    /** Perform input validation, mark field as invalid if entered value is not valid. */
    bool validate();

    /** Change unit used to display amount. */
    void setDisplayUnit(int unit);

    /** Make field empty and ready for new input. */
    void clear();

    /** Enable/Disable. */
    void setEnabled(bool fEnabled);

    /** Qt messes up the tab chain by default in some cases (issue https://bugreports.qt-project.org/browse/QTBUG-10907),
        in these cases we have to set it up manually.
    */
<<<<<<< HEAD
    QWidget *setupTabChain(QWidget *prev);

Q_SIGNALS:
=======
    QWidget* setupTabChain(QWidget* prev);

signals:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void valueChanged();

protected:
    /** Intercept focus-in event and ',' key presses */
<<<<<<< HEAD
    bool eventFilter(QObject *object, QEvent *event);

private:
    AmountSpinBox *amount;
    QValueComboBox *unit;

private Q_SLOTS:
    void unitChanged(int idx);

=======
    bool eventFilter(QObject* object, QEvent* event);

private:
    AmountSpinBox* amount;
    QValueComboBox* unit;

private slots:
    void unitChanged(int idx);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_BITCOINAMOUNTFIELD_H
