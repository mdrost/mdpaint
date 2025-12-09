#include "imageview.h"

#include <mdpaint/imagemodel.h>
#include <mdpaint/tool.h>

#include <QPainter>
#include <QPaintEvent>

// public
mdpImageView::mdpImageView(mdpImageModel& imageModel, QWidget* parent) :
    QWidget(parent),
    m_imageModel(imageModel),
    m_tool(nullptr)
{
    setMouseTracking(true);
    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    onImageModelDataChangedConnection = imageModel.onDataChanged(std::bind(&mdpImageView::onImageModelDataChanged, this));
    onImageModelDataResetConnection = imageModel.onDataReset(std::bind(&mdpImageView::onImageModelDataReset, this));
    onImageModelDataReset();
}

// public virtual
mdpImageView::~mdpImageView() /* override */
{
}

// public
//QSize mdpImageView::sizeHint() const /* override */
//{
//    return m_image.size();
//}

// public
const mdpTool* mdpImageView::tool() const
{
    return m_tool;
}

// public
void mdpImageView::setTool(mdpTool* tool)
{
    m_tool = tool;
}

// public
void mdpImageView::clearTool()
{
    m_tool = nullptr;
}

//protected virtual
void mdpImageView::mousePressEvent(QMouseEvent* e) /* override */
{
    if (m_tool != nullptr) {
        const QPoint point = e->pos();
        m_tool->mousePressEvent(point.x(), point.y());
    }
    e->accept();
}

//protected virtual
void mdpImageView::mouseReleaseEvent(QMouseEvent* e) /* override */
{
    if (m_tool != nullptr) {
        const QPoint point = e->pos();
        m_tool->mouseReleaseEvent(point.x(), point.y());
    }
    e->accept();
}

//protected virtual
void mdpImageView::mouseMoveEvent(QMouseEvent* e) /* override */
{
    if (m_tool != nullptr) {
        const QPoint point = e->pos();
        m_tool->mouseMoveEvent(point.x(), point.y());
    }
    e->accept();
}

#if QT_CONFIG(wheelevent)
//protected virtual
void mdpImageView::wheelEvent(QWheelEvent* e) /* override */
{
    QWidget::wheelEvent(e);
}
#endif

// protected virtual
void mdpImageView::enterEvent(QEnterEvent *e) /* override */
{
    if (m_tool != nullptr) {
        m_tool->enterEvent();
    }
    e->accept();
}

// protected virtual
void mdpImageView::leaveEvent(QEvent *e) /* override */
{
    if (m_tool != nullptr) {
        m_tool->leaveEvent();
    }
    e->accept();
}

// protected virtual
void mdpImageView::paintEvent(QPaintEvent* e) /* override */
{
    QPainter p(this);
    if (!m_image.isNull()) {
        p.drawImage(e->rect(), m_image, e->rect());
    }
}

// private slot
void mdpImageView::onImageModelDataChanged()
{
    update();
}

// private slot
void mdpImageView::onImageModelDataReset()
{
    int width = m_imageModel.width();
    int height = m_imageModel.height();
    int bytesPerLine = m_imageModel.stride();
    m_image = QImage(m_imageModel.data(), width, height, bytesPerLine, QImage::Format_RGBA8888);
    setFixedSize(width, height);
    update(); // TODO: Is this necessary? Seems to work without it.
}
