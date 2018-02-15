<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_QVALIDATEDLINEEDIT_H
#define BITCOIN_QT_QVALIDATEDLINEEDIT_H

#include <QLineEdit>

/** Line edit that can be marked as "invalid" to show input validation feedback. When marked as invalid,
   it will get a red background until it is focused.
 */
class QValidatedLineEdit : public QLineEdit
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit QValidatedLineEdit(QWidget *parent);
    void clear();
    void setCheckValidator(const QValidator *v);
    bool isValid();

protected:
    void focusInEvent(QFocusEvent *evt);
    void focusOutEvent(QFocusEvent *evt);

private:
    bool valid;
    const QValidator *checkValidator;

public Q_SLOTS:
    void setValid(bool valid);
    void setEnabled(bool enabled);

Q_SIGNALS:
    void validationDidChange(QValidatedLineEdit *validatedLineEdit);
    
private Q_SLOTS:
=======
    explicit QValidatedLineEdit(QWidget* parent);
    void clear();
    void setCheckValidator(const QValidator* v);

protected:
    void focusInEvent(QFocusEvent* evt);
    void focusOutEvent(QFocusEvent* evt);

private:
    bool valid;
    const QValidator* checkValidator;

public slots:
    void setValid(bool valid);
    void setEnabled(bool enabled);

private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void markValid();
    void checkValidity();
};

#endif // BITCOIN_QT_QVALIDATEDLINEEDIT_H
