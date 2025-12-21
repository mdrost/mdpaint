#include "qtimageview.h"

#include <mdpaint/imagemodel.h>
#include <mdpaint/tool.h>

#include <QPainter>
#include <QPaintEvent>

#include <functional>

// public
mdpQtImageView::mdpQtImageView(mdpImageModel& imageModel, QWidget* parent) :
    QWidget(parent),
    m_imageModel(imageModel),
    m_tool(nullptr)
{
    setMouseTracking(true);
    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    onImageModelDataChangedConnection = imageModel.onDataChanged(std::bind(&mdpQtImageView::onImageModelDataChanged, this));
    onImageModelDataResetConnection = imageModel.onDataReset(std::bind(&mdpQtImageView::onImageModelDataReset, this));
    onImageModelDataReset();
}

// public virtual
mdpQtImageView::~mdpQtImageView() /* override */
{
}

// public
QSize mdpQtImageView::sizeHint() const /* override */
{
    return m_image.size();
}

// public
//const mdpTool* mdpQtImageView::tool() const
//{
//    return m_tool;
//}

// public
void mdpQtImageView::setTool(mdpTool* tool)
{
    m_tool = tool;
}

// public
void mdpQtImageView::clearTool()
{
    m_tool = nullptr;
}

//protected virtual
void mdpQtImageView::mousePressEvent(QMouseEvent* e) /* override */
{
    if (m_tool != nullptr) {
        const QPoint point = e->pos();
        m_tool->mousePressEvent(point.x(), point.y());
    }
    e->accept();
}

//protected virtual
void mdpQtImageView::mouseReleaseEvent(QMouseEvent* e) /* override */
{
    if (m_tool != nullptr) {
        const QPoint point = e->pos();
        m_tool->mouseReleaseEvent(point.x(), point.y());
    }
    e->accept();
}

//protected virtual
void mdpQtImageView::mouseMoveEvent(QMouseEvent* e) /* override */
{
    if (m_tool != nullptr) {
        const QPoint point = e->pos();
        m_tool->mouseMoveEvent(point.x(), point.y());
    }
    e->accept();
}

#if QT_CONFIG(wheelevent)
//protected virtual
void mdpQtImageView::wheelEvent(QWheelEvent* e) /* override */
{
    QWidget::wheelEvent(e);
}
#endif

// protected virtual
void mdpQtImageView::enterEvent(QEnterEvent *e) /* override */
{
    if (m_tool != nullptr) {
        m_tool->enterEvent();
    }
    e->accept();
}

// protected virtual
void mdpQtImageView::leaveEvent(QEvent *e) /* override */
{
    if (m_tool != nullptr) {
        m_tool->leaveEvent();
    }
    e->accept();
}

// protected virtual
void mdpQtImageView::paintEvent(QPaintEvent* e) /* override */
{
    QPainter p(this);
    if (!m_image.isNull()) {
        p.drawImage(e->rect(), m_image, e->rect());
    }
}

// private slot
void mdpQtImageView::onImageModelDataChanged()
{
    update();
}

// private slot
void mdpQtImageView::onImageModelDataReset()
{
    int width = m_imageModel.width();
    int height = m_imageModel.height();
    int bytesPerLine = m_imageModel.stride();
    m_image = QImage(m_imageModel.data(), width, height, bytesPerLine, QImage::Format_ARGB32_Premultiplied);
    setFixedSize(width, height);
    update(); // TODO: Is this necessary? Seems to work without it.
}
