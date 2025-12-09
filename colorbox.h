#ifndef MDP_COLORBOX_H
#define MDP_COLORBOX_H

#include <QDockWidget>

class mdpColorBox final : public QDockWidget
{
    Q_OBJECT

public:

    explicit mdpColorBox(QWidget* parent = nullptr);

    ~mdpColorBox() override;

Q_SIGNALS:

private:
    Q_DISABLE_COPY(mdpColorBox)
};

#endif // MDP_COLORBOX_H
