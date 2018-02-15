<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "bitcoinamountfield.h"

#include "bitcoinunits.h"
#include "guiconstants.h"
#include "qvaluecombobox.h"

<<<<<<< HEAD
#include <QApplication>
#include <QAbstractSpinBox>
=======
#include <QAbstractSpinBox>
#include <QApplication>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLineEdit>

/** QSpinBox that uses fixed-point numbers internally and uses our own
 * formatting/parsing functions.
 */
<<<<<<< HEAD
class AmountSpinBox: public QAbstractSpinBox
=======
class AmountSpinBox : public QAbstractSpinBox
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit AmountSpinBox(QWidget *parent):
        QAbstractSpinBox(parent),
        currentUnit(BitcoinUnits::GEL),
        singleStep(100000) // satoshis
=======
    explicit AmountSpinBox(QWidget* parent) : QAbstractSpinBox(parent),
                                              currentUnit(BitcoinUnits::LUX),
                                              singleStep(100000) // satoshis
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        setAlignment(Qt::AlignRight);

        connect(lineEdit(), SIGNAL(textEdited(QString)), this, SIGNAL(valueChanged()));
    }

<<<<<<< HEAD
    QValidator::State validate(QString &text, int &pos) const
    {
        if(text.isEmpty())
=======
    QValidator::State validate(QString& text, int& pos) const
    {
        if (text.isEmpty())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return QValidator::Intermediate;
        bool valid = false;
        parse(text, &valid);
        /* Make sure we return Intermediate so that fixup() is called on defocus */
        return valid ? QValidator::Intermediate : QValidator::Invalid;
    }

<<<<<<< HEAD
    void fixup(QString &input) const
    {
        bool valid = false;
        CAmount val = parse(input, &valid);
        if(valid)
        {
=======
    void fixup(QString& input) const
    {
        bool valid = false;
        CAmount val = parse(input, &valid);
        if (valid) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            input = BitcoinUnits::format(currentUnit, val, false, BitcoinUnits::separatorAlways);
            lineEdit()->setText(input);
        }
    }

<<<<<<< HEAD
    CAmount value(bool *valid_out=0) const
=======
    CAmount value(bool* valid_out = 0) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        return parse(text(), valid_out);
    }

    void setValue(const CAmount& value)
    {
        lineEdit()->setText(BitcoinUnits::format(currentUnit, value, false, BitcoinUnits::separatorAlways));
<<<<<<< HEAD
        Q_EMIT valueChanged();
=======
        emit valueChanged();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    void stepBy(int steps)
    {
        bool valid = false;
        CAmount val = value(&valid);
        val = val + steps * singleStep;
        val = qMin(qMax(val, CAmount(0)), BitcoinUnits::maxMoney());
        setValue(val);
    }

    void setDisplayUnit(int unit)
    {
        bool valid = false;
        CAmount val = value(&valid);

        currentUnit = unit;

<<<<<<< HEAD
        if(valid)
=======
        if (valid)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            setValue(val);
        else
            clear();
    }

    void setSingleStep(const CAmount& step)
    {
        singleStep = step;
    }

    QSize minimumSizeHint() const
    {
<<<<<<< HEAD
        if(cachedMinimumSizeHint.isEmpty())
        {
=======
        if (cachedMinimumSizeHint.isEmpty()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            ensurePolished();

            const QFontMetrics fm(fontMetrics());
            int h = lineEdit()->minimumSizeHint().height();
<<<<<<< HEAD
            int w = fm.width(BitcoinUnits::format(BitcoinUnits::GEL, BitcoinUnits::maxMoney(), false, BitcoinUnits::separatorAlways));
=======
            int w = fm.width(BitcoinUnits::format(BitcoinUnits::LUX, BitcoinUnits::maxMoney(), false, BitcoinUnits::separatorAlways));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            w += 2; // cursor blinking space

            QStyleOptionSpinBox opt;
            initStyleOption(&opt);
            QSize hint(w, h);
            QSize extra(35, 6);
            opt.rect.setSize(hint + extra);
<<<<<<< HEAD
            extra += hint - style()->subControlRect(QStyle::CC_SpinBox, &opt,
                                                    QStyle::SC_SpinBoxEditField, this).size();
            // get closer to final result by repeating the calculation
            opt.rect.setSize(hint + extra);
            extra += hint - style()->subControlRect(QStyle::CC_SpinBox, &opt,
                                                    QStyle::SC_SpinBoxEditField, this).size();
=======
            extra += hint - style()->subControlRect(QStyle::CC_SpinBox, &opt, QStyle::SC_SpinBoxEditField, this).size();
            // get closer to final result by repeating the calculation
            opt.rect.setSize(hint + extra);
            extra += hint - style()->subControlRect(QStyle::CC_SpinBox, &opt, QStyle::SC_SpinBoxEditField, this).size();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            hint += extra;
            hint.setHeight(h);

            opt.rect = rect();

<<<<<<< HEAD
            cachedMinimumSizeHint = style()->sizeFromContents(QStyle::CT_SpinBox, &opt, hint, this)
                                    .expandedTo(QApplication::globalStrut());
=======
            cachedMinimumSizeHint = style()->sizeFromContents(QStyle::CT_SpinBox, &opt, hint, this).expandedTo(QApplication::globalStrut());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
        return cachedMinimumSizeHint;
    }

private:
    int currentUnit;
    CAmount singleStep;
    mutable QSize cachedMinimumSizeHint;

    /**
     * Parse a string into a number of base monetary units and
     * return validity.
     * @note Must return 0 if !valid.
     */
<<<<<<< HEAD
    CAmount parse(const QString &text, bool *valid_out=0) const
    {
        CAmount val = 0;
        bool valid = BitcoinUnits::parse(currentUnit, text, &val);
        if(valid)
        {
            if(val < 0 || val > BitcoinUnits::maxMoney())
                valid = false;
        }
        if(valid_out)
=======
    CAmount parse(const QString& text, bool* valid_out = 0) const
    {
        CAmount val = 0;
        bool valid = BitcoinUnits::parse(currentUnit, text, &val);
        if (valid) {
            if (val < 0 || val > BitcoinUnits::maxMoney())
                valid = false;
        }
        if (valid_out)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            *valid_out = valid;
        return valid ? val : 0;
    }

protected:
<<<<<<< HEAD
    bool event(QEvent *event)
    {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Comma)
            {
=======
    bool event(QEvent* event)
    {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Comma) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                // Translate a comma into a period
                QKeyEvent periodKeyEvent(event->type(), Qt::Key_Period, keyEvent->modifiers(), ".", keyEvent->isAutoRepeat(), keyEvent->count());
                return QAbstractSpinBox::event(&periodKeyEvent);
            }
        }
        return QAbstractSpinBox::event(event);
    }

    StepEnabled stepEnabled() const
    {
<<<<<<< HEAD
=======
        StepEnabled rv = 0;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (isReadOnly()) // Disable steps when AmountSpinBox is read-only
            return StepNone;
        if (text().isEmpty()) // Allow step-up with empty field
            return StepUpEnabled;
<<<<<<< HEAD

        StepEnabled rv = 0;
        bool valid = false;
        CAmount val = value(&valid);
        if(valid)
        {
            if(val > 0)
                rv |= StepDownEnabled;
            if(val < BitcoinUnits::maxMoney())
=======
        bool valid = false;
        CAmount val = value(&valid);
        if (valid) {
            if (val > 0)
                rv |= StepDownEnabled;
            if (val < BitcoinUnits::maxMoney())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                rv |= StepUpEnabled;
        }
        return rv;
    }

<<<<<<< HEAD
Q_SIGNALS:
=======
signals:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void valueChanged();
};

#include "bitcoinamountfield.moc"

<<<<<<< HEAD
BitcoinAmountField::BitcoinAmountField(QWidget *parent) :
    QWidget(parent),
    amount(0)
=======
BitcoinAmountField::BitcoinAmountField(QWidget* parent) : QWidget(parent),
                                                          amount(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    amount = new AmountSpinBox(this);
    amount->setLocale(QLocale::c());
    amount->installEventFilter(this);
    amount->setMaximumWidth(170);

<<<<<<< HEAD
    QHBoxLayout *layout = new QHBoxLayout(this);
=======
    QHBoxLayout* layout = new QHBoxLayout(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    layout->addWidget(amount);
    unit = new QValueComboBox(this);
    unit->setModel(new BitcoinUnits(this));
    layout->addWidget(unit);
    layout->addStretch(1);
<<<<<<< HEAD
    layout->setContentsMargins(0,0,0,0);
=======
    layout->setContentsMargins(0, 0, 0, 0);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    setLayout(layout);

    setFocusPolicy(Qt::TabFocus);
    setFocusProxy(amount);

    // If one if the widgets changes, the combined content changes as well
    connect(amount, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
    connect(unit, SIGNAL(currentIndexChanged(int)), this, SLOT(unitChanged(int)));

    // Set default based on configuration
    unitChanged(unit->currentIndex());
}

void BitcoinAmountField::clear()
{
    amount->clear();
    unit->setCurrentIndex(0);
}

void BitcoinAmountField::setEnabled(bool fEnabled)
{
    amount->setEnabled(fEnabled);
    unit->setEnabled(fEnabled);
}

bool BitcoinAmountField::validate()
{
    bool valid = false;
    value(&valid);
    setValid(valid);
    return valid;
}

void BitcoinAmountField::setValid(bool valid)
{
    if (valid)
        amount->setStyleSheet("");
    else
        amount->setStyleSheet(STYLE_INVALID);
}

<<<<<<< HEAD
bool BitcoinAmountField::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
    {
=======
bool BitcoinAmountField::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::FocusIn) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Clear invalid flag on focus
        setValid(true);
    }
    return QWidget::eventFilter(object, event);
}

<<<<<<< HEAD
QWidget *BitcoinAmountField::setupTabChain(QWidget *prev)
=======
QWidget* BitcoinAmountField::setupTabChain(QWidget* prev)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QWidget::setTabOrder(prev, amount);
    QWidget::setTabOrder(amount, unit);
    return unit;
}

<<<<<<< HEAD
CAmount BitcoinAmountField::value(bool *valid_out) const
=======
CAmount BitcoinAmountField::value(bool* valid_out) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return amount->value(valid_out);
}

void BitcoinAmountField::setValue(const CAmount& value)
{
    amount->setValue(value);
}

void BitcoinAmountField::setReadOnly(bool fReadOnly)
{
    amount->setReadOnly(fReadOnly);
<<<<<<< HEAD
=======
    unit->setEnabled(!fReadOnly);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void BitcoinAmountField::unitChanged(int idx)
{
    // Use description tooltip for current unit for the combobox
    unit->setToolTip(unit->itemData(idx, Qt::ToolTipRole).toString());

    // Determine new unit ID
    int newUnit = unit->itemData(idx, BitcoinUnits::UnitRole).toInt();

    amount->setDisplayUnit(newUnit);
}

void BitcoinAmountField::setDisplayUnit(int newUnit)
{
    unit->setValue(newUnit);
}

void BitcoinAmountField::setSingleStep(const CAmount& step)
{
    amount->setSingleStep(step);
}
