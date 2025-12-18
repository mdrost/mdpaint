#include "qtspinbox.h"

// public
mdpQtSpinBox::mdpQtSpinBox(QWidget* parent)
    : QSpinBox(parent)
{
}

// public virtual
mdpQtSpinBox::~mdpQtSpinBox() /* override */
{
}

// protected virtual
void mdpQtSpinBox::fixup(QString& input) const /* override */
{
    QStringView v = value(input);
    bool ok;
    int num;
    if (displayIntegerBase() == 10) {
        num = QLocale().toInt(v, &ok);
    }
    else {
        num = v.toInt(&ok);
    }
    QLocale().toInt(v, &ok);
    if (ok) {
        if (num < minimum()) {
            num = minimum();
        }
        else if (num > maximum()) {
            num = maximum();
        }
        input = QString::number(num, displayIntegerBase());
        input = prefix() + input + suffix();
    }
    else {
        QSpinBox::fixup(input);
    }
}

// protected virtual
QValidator::State mdpQtSpinBox::validate(QString& input, int& pos) const /* override */
{
    QStringView v = value(input);
    if (v.isEmpty()) {
        return QValidator::Intermediate;
    }
    bool ok;
    int num;
    if (displayIntegerBase() == 10) {
        num = QLocale().toInt(v, &ok);
    }
    else {
        num = v.toInt(&ok);
    }
    if (ok) {
        if (num >= minimum() && num <= maximum()) {
            return QValidator::Acceptable;
        }
        else {
            return QValidator::Intermediate;
        }
    }
    else {
        return QSpinBox::validate(input, pos);
    }
}

QStringView mdpQtSpinBox::value(const QString& text) const
{
    QStringView result(text);
    QString p = prefix();
    if (result.startsWith(p)) {
        result.chop(p.length());
    }
    QString s = suffix();
    if (result.endsWith(s)) {
        result = QStringView(result.data(), result.size() - s.size());
    }
    return result;
}
