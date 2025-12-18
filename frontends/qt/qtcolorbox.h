#ifndef MDP_QTCOLORBOX_H
#define MDP_QTCOLORBOX_H

#include <QDockWidget>

class mdpQtColorBox final : public QDockWidget
{
    Q_OBJECT

public:

    explicit mdpQtColorBox(QWidget* parent = nullptr);

    ~mdpQtColorBox() override;

Q_SIGNALS:

private:
    Q_DISABLE_COPY(mdpQtColorBox)
};

#endif // MDP_QTCOLORBOX_H
