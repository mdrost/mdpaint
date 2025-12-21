#include "qtrectangletool.h"

#include "qthistoryentry.h"
#include "qtmodel.h"

#include <mdpaint/history.h>

#include <QPainter>
#include <QPen>

#include <functional>

// public
mdpQtRectangleTool::mdpQtRectangleTool(mdpQtModel& qtModel, mdpHistory& history) :
    m_qtModel(qtModel),
    m_history(history),
    m_previewImage(nullptr),
    m_previewPainter(nullptr),
    m_drawing(false)
{
}

// public virtual
mdpQtRectangleTool::~mdpQtRectangleTool() /* override */
{
}

// public virtual
void mdpQtRectangleTool::activate() /* override */
{
    m_previewImage = m_qtModel.getPreviewImage();
    m_previewPainter = m_qtModel.getPreviewPainter();
    onQtModelPreviewResetConnection = m_qtModel.onPreviewReset(std::bind(&mdpQtRectangleTool::onQtModelPreviewReset, this));
}

// public virtual
void mdpQtRectangleTool::deactivate() /* override */
{
    onQtModelPreviewResetConnection.disconnect();
    m_previewPainter = nullptr;
    m_previewImage = nullptr;
}

// public virtual
void mdpQtRectangleTool::mousePressEvent(const int x, const int y) /* override */
{
    m_drawing = true;
    m_qtModel.beginDrawing();
    draw(x, y);
    m_startingX = x;
    m_startingY = y;
    m_qtModel.endDrawing();
}

// public virtual
void mdpQtRectangleTool::mouseReleaseEvent(const int x, const int y) /* override */
{
    if (m_drawing) {
        //m_history.push(new mdpQtHistoryEntry("Rectangle", m_qtModel, m_previewImage, m_previewPainter));
        m_qtModel.submit();
        m_drawing = false;
    }
}

// public virtual
void mdpQtRectangleTool::mouseMoveEvent(const int x, const int y) /* override */
{
    m_qtModel.beginDrawing();
    m_qtModel.refresh();
    if (m_drawing) {
        draw(m_startingX, m_startingY, x, y);
    }
    else {
        draw(x, y);
    }
    m_qtModel.endDrawing();
}

// public virtual
void mdpQtRectangleTool::enterEvent() /* override */
{
}

// public virtual
void mdpQtRectangleTool::leaveEvent() /* override */
{
    if (m_drawing) {
        return;
    }
    m_qtModel.beginDrawing();
    m_qtModel.refresh();
    m_qtModel.endDrawing();
}

// private
void mdpQtRectangleTool::draw(const int x, const int y)
{
    QPainter* const painter = m_previewPainter.get();
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    const double exactX = x + 0.5;
    const double exactY = y + 0.5;
    painter->drawPoint(QPointF(exactX, exactY));
}

// private
void mdpQtRectangleTool::draw(const int fromX, const int fromY, const int toX, const int toY)
{
    QPainter* const painter = m_previewPainter.get();
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    const double exactFromX = fromX + 0.5;
    const double exactFromY = fromY + 0.5;
    const double exactToX = toX + 0.5;
    const double exactToY = toY + 0.5;
    painter->drawRect(QRectF(QPointF(exactFromX, exactFromY), QPointF(exactToX, exactToY)));
}

// private slot
void mdpQtRectangleTool::onQtModelPreviewReset()
{
    m_previewPainter = m_qtModel.getPreviewPainter();
    m_previewImage = m_qtModel.getPreviewImage();
}
