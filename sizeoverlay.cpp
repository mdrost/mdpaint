#include "sizeoverlay.h"

#include <QPainter>

// public
mdpSizeOverlay::mdpSizeOverlay(QWidget* parent) :
    QWidget(parent),
    m_type(mdpSizeGrip::TopLeft)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

// public virtual
mdpSizeOverlay::~mdpSizeOverlay() /* override */
{
}

// public
void mdpSizeOverlay::setType(mdpSizeGrip::Type type)
{
    m_type = type;
}

// protected virtual
void mdpSizeOverlay::paintEvent(QPaintEvent* e) /* override */
{
    QPainter p(this);
    QPen pen(Qt::black, 4, Qt::DotLine);
    p.setPen(pen);
    int w = width();
    int h = height();
    switch (m_type) {
    case mdpSizeGrip::TopLeft: {
        p.drawLine(0, h, 0, 0);
        p.drawLine(w, 0, 0, 0);
        p.drawLine(w, h, 0, h);
        p.drawLine(w, h, w, 0);
    } break;
    case mdpSizeGrip::BottomRight: {
        p.drawLine(0, 0, 0, h);
        p.drawLine(0, 0, w, 0);
        p.drawLine(0, h, w, h);
        p.drawLine(w, 0, w, h);
    } break;
    case mdpSizeGrip::Top: {
        p.drawLine(0, h, 0, 0);
        p.drawLine(0, 0, w, 0); // direction doesn't matter
        p.drawLine(0, h, w, h); // direction doesn't matter
        p.drawLine(w, h, w, 0);
    } break;
    case mdpSizeGrip::Bottom: {
        p.drawLine(0, 0, 0, h);
        p.drawLine(0, 0, w, 0); // direction doesn't matter
        p.drawLine(0, h, w, h); // direction doesn't matter
        p.drawLine(w, 0, w, h);
    } break;
    case mdpSizeGrip::TopRight: {
        p.drawLine(0, h, 0, 0);
        p.drawLine(0, 0, w, 0);
        p.drawLine(0, h, w, h);
        p.drawLine(w, h, w, 0);
    } break;
    case mdpSizeGrip::BottomLeft: {
        p.drawLine(0, 0, 0, h);
        p.drawLine(w, 0, 0, 0);
        p.drawLine(w, h, 0, h);
        p.drawLine(w, 0, w, h);
    } break;
    case mdpSizeGrip::Left: {
        p.drawLine(0, 0, 0, h); // direction doesn't matter
        p.drawLine(w, 0, 0, 0);
        p.drawLine(w, h, 0, h);
        p.drawLine(w, 0, w, h); // direction doesn't matter
    } break;
    case mdpSizeGrip::Right: {
        p.drawLine(0, 0, 0, h); // direction doesn't matter
        p.drawLine(0, 0, w, 0);
        p.drawLine(0, h, w, h);
        p.drawLine(w, 0, w, h); // direction doesn't matter
    } break;
    }
}
