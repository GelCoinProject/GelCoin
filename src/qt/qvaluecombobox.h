<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_QVALUECOMBOBOX_H
#define BITCOIN_QT_QVALUECOMBOBOX_H

#include <QComboBox>
#include <QVariant>

/* QComboBox that can be used with QDataWidgetMapper to select ordinal values from a model. */
class QValueComboBox : public QComboBox
{
    Q_OBJECT

    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged USER true)

public:
<<<<<<< HEAD
    explicit QValueComboBox(QWidget *parent = 0);

    QVariant value() const;
    void setValue(const QVariant &value);
=======
    explicit QValueComboBox(QWidget* parent = 0);

    QVariant value() const;
    void setValue(const QVariant& value);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Specify model role to use as ordinal value (defaults to Qt::UserRole) */
    void setRole(int role);

<<<<<<< HEAD
Q_SIGNALS:
=======
signals:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void valueChanged();

private:
    int role;

<<<<<<< HEAD
private Q_SLOTS:
=======
private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void handleSelectionChanged(int idx);
};

#endif // BITCOIN_QT_QVALUECOMBOBOX_H
