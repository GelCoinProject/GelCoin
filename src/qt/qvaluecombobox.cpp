<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "qvaluecombobox.h"

<<<<<<< HEAD
QValueComboBox::QValueComboBox(QWidget *parent) :
        QComboBox(parent), role(Qt::UserRole)
=======
QValueComboBox::QValueComboBox(QWidget* parent) : QComboBox(parent), role(Qt::UserRole)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSelectionChanged(int)));
}

QVariant QValueComboBox::value() const
{
    return itemData(currentIndex(), role);
}

<<<<<<< HEAD
void QValueComboBox::setValue(const QVariant &value)
=======
void QValueComboBox::setValue(const QVariant& value)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    setCurrentIndex(findData(value, role));
}

void QValueComboBox::setRole(int role)
{
    this->role = role;
}

void QValueComboBox::handleSelectionChanged(int idx)
{
<<<<<<< HEAD
    Q_EMIT valueChanged();
=======
    emit valueChanged();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
