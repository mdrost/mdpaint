#ifndef MDP_SIZEOVERLAY_H
#define MDP_SIZEOVERLAY_H

#include "sizegrip.h"

#include <QWidget>

class mdpSizeOverlay final : public QWidget
{
    Q_OBJECT

public:

    explicit mdpSizeOverlay(QWidget* parent = nullptr);

    ~mdpSizeOverlay() override;

    void setType(mdpSizeGrip::Type type);

Q_SIGNALS:

protected:

    void paintEvent(QPaintEvent* e) override;

private:
    Q_DISABLE_COPY(mdpSizeOverlay)

    mdpSizeGrip::Type m_type;
};

#endif // MDP_SIZEOVERLAY_H
