#ifndef MDP_QTSIZEOVERLAY_H
#define MDP_QTSIZEOVERLAY_H

#include "qtsizegrip.h"

#include <QWidget>

class mdpQtSizeOverlay final : public QWidget
{
    Q_OBJECT

public:

    explicit mdpQtSizeOverlay(QWidget* parent = nullptr);

    ~mdpQtSizeOverlay() override;

    void setType(mdpQtSizeGrip::Type type);

Q_SIGNALS:

protected:

    void paintEvent(QPaintEvent* e) override;

private:
    Q_DISABLE_COPY(mdpQtSizeOverlay)

    mdpQtSizeGrip::Type m_type;
};

#endif // MDP_QTSIZEOVERLAY_H
