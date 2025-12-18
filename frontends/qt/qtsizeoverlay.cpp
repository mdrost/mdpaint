#include "qtsizeoverlay.h"

#include <QPainter>

// public
mdpQtSizeOverlay::mdpQtSizeOverlay(QWidget* parent) :
    QWidget(parent),
    m_type(mdpQtSizeGrip::TopLeft)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

// public virtual
mdpQtSizeOverlay::~mdpQtSizeOverlay() /* override */
{
}

// public
void mdpQtSizeOverlay::setType(mdpQtSizeGrip::Type type)
{
    m_type = type;
}

// protected virtual
void mdpQtSizeOverlay::paintEvent(QPaintEvent* e) /* override */
{
    QPainter p(this);
    QPen pen(Qt::black, 4, Qt::DotLine);
    p.setPen(pen);
    int w = width();
    int h = height();
    switch (m_type) {
    case mdpQtSizeGrip::TopLeft: {
        p.drawLine(0, h, 0, 0);
        p.drawLine(w, 0, 0, 0);
        p.drawLine(w, h, 0, h);
        p.drawLine(w, h, w, 0);
    } break;
    case mdpQtSizeGrip::BottomRight: {
        p.drawLine(0, 0, 0, h);
        p.drawLine(0, 0, w, 0);
        p.drawLine(0, h, w, h);
        p.drawLine(w, 0, w, h);
    } break;
    case mdpQtSizeGrip::Top: {
        p.drawLine(0, h, 0, 0);
        p.drawLine(0, 0, w, 0); // direction doesn't matter
        p.drawLine(0, h, w, h); // direction doesn't matter
        p.drawLine(w, h, w, 0);
    } break;
    case mdpQtSizeGrip::Bottom: {
        p.drawLine(0, 0, 0, h);
        p.drawLine(0, 0, w, 0); // direction doesn't matter
        p.drawLine(0, h, w, h); // direction doesn't matter
        p.drawLine(w, 0, w, h);
    } break;
    case mdpQtSizeGrip::TopRight: {
        p.drawLine(0, h, 0, 0);
        p.drawLine(0, 0, w, 0);
        p.drawLine(0, h, w, h);
        p.drawLine(w, h, w, 0);
    } break;
    case mdpQtSizeGrip::BottomLeft: {
        p.drawLine(0, 0, 0, h);
        p.drawLine(w, 0, 0, 0);
        p.drawLine(w, h, 0, h);
        p.drawLine(w, 0, w, h);
    } break;
    case mdpQtSizeGrip::Left: {
        p.drawLine(0, 0, 0, h); // direction doesn't matter
        p.drawLine(w, 0, 0, 0);
        p.drawLine(w, h, 0, h);
        p.drawLine(w, 0, w, h); // direction doesn't matter
    } break;
    case mdpQtSizeGrip::Right: {
        p.drawLine(0, 0, 0, h); // direction doesn't matter
        p.drawLine(0, 0, w, 0);
        p.drawLine(0, h, w, h);
        p.drawLine(w, 0, w, h); // direction doesn't matter
    } break;
    }
}
