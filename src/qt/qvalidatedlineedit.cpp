<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "qvalidatedlineedit.h"

#include "bitcoinaddressvalidator.h"
#include "guiconstants.h"

<<<<<<< HEAD
QValidatedLineEdit::QValidatedLineEdit(QWidget *parent) :
    QLineEdit(parent),
    valid(true),
    checkValidator(0)
=======
QValidatedLineEdit::QValidatedLineEdit(QWidget* parent) : QLineEdit(parent),
                                                          valid(true),
                                                          checkValidator(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    connect(this, SIGNAL(textChanged(QString)), this, SLOT(markValid()));
}

void QValidatedLineEdit::setValid(bool valid)
{
<<<<<<< HEAD
    if(valid == this->valid)
    {
        return;
    }

    if(valid)
    {
        setStyleSheet("");
    }
    else
    {
=======
    if (valid == this->valid) {
        return;
    }

    if (valid) {
        setStyleSheet("");
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        setStyleSheet(STYLE_INVALID);
    }
    this->valid = valid;
}

<<<<<<< HEAD
void QValidatedLineEdit::focusInEvent(QFocusEvent *evt)
=======
void QValidatedLineEdit::focusInEvent(QFocusEvent* evt)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    // Clear invalid flag on focus
    setValid(true);

    QLineEdit::focusInEvent(evt);
}

<<<<<<< HEAD
void QValidatedLineEdit::focusOutEvent(QFocusEvent *evt)
=======
void QValidatedLineEdit::focusOutEvent(QFocusEvent* evt)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    checkValidity();

    QLineEdit::focusOutEvent(evt);
}

void QValidatedLineEdit::markValid()
{
    // As long as a user is typing ensure we display state as valid
    setValid(true);
}

void QValidatedLineEdit::clear()
{
    setValid(true);
    QLineEdit::clear();
}

void QValidatedLineEdit::setEnabled(bool enabled)
{
<<<<<<< HEAD
    if (!enabled)
    {
        // A disabled QValidatedLineEdit should be marked valid
        setValid(true);
    }
    else
    {
=======
    if (!enabled) {
        // A disabled QValidatedLineEdit should be marked valid
        setValid(true);
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Recheck validity when QValidatedLineEdit gets enabled
        checkValidity();
    }

    QLineEdit::setEnabled(enabled);
}

void QValidatedLineEdit::checkValidity()
{
<<<<<<< HEAD
    if (text().isEmpty())
    {
        setValid(true);
    }
    else if (hasAcceptableInput())
    {
        setValid(true);

        // Check contents on focus out
        if (checkValidator)
        {
=======
    if (text().isEmpty()) {
        setValid(true);
    } else if (hasAcceptableInput()) {
        setValid(true);

        // Check contents on focus out
        if (checkValidator) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            QString address = text();
            int pos = 0;
            if (checkValidator->validate(address, pos) == QValidator::Acceptable)
                setValid(true);
            else
                setValid(false);
        }
<<<<<<< HEAD
    }
    else
        setValid(false);

    Q_EMIT validationDidChange(this);
}

void QValidatedLineEdit::setCheckValidator(const QValidator *v)
{
    checkValidator = v;
}

bool QValidatedLineEdit::isValid()
{
    // use checkValidator in case the QValidatedLineEdit is disabled
    if (checkValidator)
    {
        QString address = text();
        int pos = 0;
        if (checkValidator->validate(address, pos) == QValidator::Acceptable)
            return true;
    }

    return valid;
}
=======
    } else
        setValid(false);
}

void QValidatedLineEdit::setCheckValidator(const QValidator* v)
{
    checkValidator = v;
}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
