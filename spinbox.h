#ifndef MDP_SPINBOX_H
#define MDP_SPINBOX_H

#include <QSpinBox>

class mdpSpinBox : public QSpinBox
{
    Q_OBJECT

public:

    explicit mdpSpinBox(QWidget* parent = nullptr);

    ~mdpSpinBox() override;

protected:

    void fixup(QString& input) const override;

    QValidator::State validate(QString& input, int& pos) const override;

private:

    QStringView value(const QString& text) const;
};

#endif // MDP_SPINBOX_H
