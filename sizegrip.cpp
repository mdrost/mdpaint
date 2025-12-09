#include "sizegrip.h"

#include <QPainter>
#include <QPaintEvent>

// public
mdpSizeGrip::mdpSizeGrip(Type type, QWidget* resizable, QWidget* parent) :
    QWidget(parent),
    m_type(type),
    m_resizable(resizable),
    m_resizing(false)
{
    /*
    switch (type) {
    case TopLeft: {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    } break;
    case BottomRight: {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    } break;
    case Top: {
        setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    } break;
    case Bottom: {
        setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    } break;
    case TopRight: {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    } break;
    case BottomLeft: {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    } break;
    case Left: {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    } break;
    case Right: {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    } break;
    }
    */
}

// public virtual
mdpSizeGrip::~mdpSizeGrip() /* override */
{
}

// public
mdpSizeGrip::Type mdpSizeGrip::type() const
{
    return m_type;
}

// public virtual
QSize mdpSizeGrip::sizeHint() const /* override */
{
    return QSize(5, 5);
}

// protected virtual
void mdpSizeGrip::mousePressEvent(QMouseEvent* e) /* override */
{
    if (e->button() == Qt::LeftButton && !m_resizing) { // TODO: is checking m_resizing necessary?
        Q_EMIT resizeAboutToStart();
        m_resizing = true;
        m_startResizableGeometry = m_resizable->geometry();
        m_startMousePosition = e->position();
    }
    else if (e->button() == Qt::RightButton && m_resizing) {
        // TODO: handle cancelling
    }
}

// protected virtual
void mdpSizeGrip::mouseReleaseEvent(QMouseEvent* e) /* override */
{
    if (e->button() == Qt::LeftButton && m_resizing) { // TODO: is checking m_resizing necessary?
        m_resizing = false;
        Q_EMIT resizeFinished();
    }
}

// protected virtual
void mdpSizeGrip::mouseMoveEvent(QMouseEvent* e) /* override */
{
    if (m_resizing) {
        const QPoint diff = (e->position() - m_startMousePosition).toPoint();
        QRect newGeometry = m_startResizableGeometry;
        // TODO: get rid of constants.
        switch (m_type) {
        case TopLeft: {
            newGeometry.setTopLeft(m_startResizableGeometry.topLeft() + diff);
            newGeometry.setTop(std::min(newGeometry.top(), newGeometry.bottom() - 4));
            newGeometry.setLeft(std::min(newGeometry.left(), newGeometry.right() - 4));
        } break;
        case BottomRight: {
            newGeometry.setBottomRight(m_startResizableGeometry.bottomRight() + diff);
            newGeometry.setBottom(std::max(newGeometry.bottom(), newGeometry.top() + 4));
            newGeometry.setRight(std::max(newGeometry.right(), newGeometry.left() + 4));
        } break;
        case Top: {
            newGeometry.setTop(m_startResizableGeometry.top() + diff.y());
            newGeometry.setTop(std::min(newGeometry.top(), newGeometry.bottom() - 4));
        } break;
        case Bottom: {
            newGeometry.setBottom(m_startResizableGeometry.bottom() + diff.y());
            newGeometry.setBottom(std::max(newGeometry.bottom(), newGeometry.top() + 4));
        } break;
        case TopRight: {
            newGeometry.setTopRight(m_startResizableGeometry.topRight() + diff);
            newGeometry.setTop(std::min(newGeometry.top(), newGeometry.bottom() - 4));
            newGeometry.setRight(std::max(newGeometry.right(), newGeometry.left() + 4));
        } break;
        case BottomLeft: {
            newGeometry.setBottomLeft(m_startResizableGeometry.bottomLeft() + diff);
            newGeometry.setBottom(std::max(newGeometry.bottom(), newGeometry.top() + 4));
            newGeometry.setLeft(std::min(newGeometry.left(), newGeometry.right() - 4));
        } break;
        case Left: {
            newGeometry.setLeft(m_startResizableGeometry.left() + diff.x());
            newGeometry.setLeft(std::min(newGeometry.left(), newGeometry.right() - 4));
        } break;
        case Right: {
            newGeometry.setRight(m_startResizableGeometry.right() + diff.x());
            newGeometry.setRight(std::max(newGeometry.right(), newGeometry.left() + 4));
        } break;
        }
        m_resizable->setGeometry(newGeometry);
    }
}

// protected virtual
void mdpSizeGrip::paintEvent(QPaintEvent* e) /* override */
{
    const int gripSize = 5;
    QPainter p(this);
    QPen pen(Qt::black, 1);
    p.setPen(pen);
    switch (m_type) {
    case TopLeft: {
        p.drawRect(
            width() - gripSize, height() - gripSize,
            gripSize - 1, gripSize - 1
        );
    } break;
    case BottomRight: {
        p.drawRect(
            0, 0,
            gripSize - 1, gripSize - 1
        );
    } break;
    case Top: {
        p.drawRect(
            (width() - gripSize) / 2, height() - gripSize,
            gripSize - 1, gripSize - 1
        );
    } break;
    case Bottom: {
        p.drawRect(
            (width() - gripSize) / 2, 0,
            gripSize - 1, gripSize - 1
        );
    } break;
    case TopRight: {
        p.drawRect(
            0, height() - gripSize,
            gripSize - 1, gripSize - 1
        );
    } break;
    case BottomLeft: {
        p.drawRect(QRect(
            width() - gripSize, 0,
            gripSize - 1, gripSize - 1
        ));
    } break;
    case Left: {
        p.drawRect(
            width() - gripSize, (height() - gripSize) / 2,
            gripSize - 1, gripSize - 1
        );
    } break;
    case Right: {
        p.drawRect(
            0, (height() - gripSize) / 2,
            gripSize - 1, gripSize - 1
        );
    } break;
    }
}
