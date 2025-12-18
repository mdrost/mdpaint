#ifndef MDP_QTSPINBOX_H
#define MDP_QTSPINBOX_H

#include <QSpinBox>

class mdpQtSpinBox : public QSpinBox
{
    Q_OBJECT

public:

    explicit mdpQtSpinBox(QWidget* parent = nullptr);

    ~mdpQtSpinBox() override;

protected:

    void fixup(QString& input) const override;

    QValidator::State validate(QString& input, int& pos) const override;

private:

    QStringView value(const QString& text) const;
};

#endif // MDP_QTSPINBOX_H
