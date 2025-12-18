#include "qtpentool.h"

#include "qthistoryentry.h"
#include "qtmodel.h"

#include <mdpaint/history.h>

#include <functional>
#include <stdexcept>

// public
mdpQtPenTool::mdpQtPenTool(mdpQtModel& qtModel, mdpHistory& history) :
    m_qtModel(qtModel),
    m_history(history),
    m_previewImage(nullptr),
    m_previewPainter(nullptr),
    m_drawing(false)
{
}

// public virtual
mdpQtPenTool::~mdpQtPenTool() /* override */
{
}

// public virtual
void mdpQtPenTool::activate() /* override */
{
    m_previewImage = m_qtModel.getPreviewImage();
    m_previewPainter = m_qtModel.getPreviewPainter();
    onQtModelPreviewResetConnection = m_qtModel.onPreviewReset(std::bind(&mdpQtPenTool::onQtModelPreviewReset, this));
}

// public virtual
void mdpQtPenTool::deactivate() /* override */
{
    onQtModelPreviewResetConnection.disconnect();
    m_previewPainter = nullptr;
    m_previewImage = nullptr;
}

// public virtual
void mdpQtPenTool::mousePressEvent(const int x, const int y) /* override */
{
    m_drawing = true;
    m_qtModel.beginDrawing();
    draw(x, y);
    m_lastX = x;
    m_lastY = y;
    m_qtModel.endDrawing();
}

// public virtual
void mdpQtPenTool::mouseReleaseEvent(const int x, const int y) /* override */
{
    if (m_drawing) {
        //m_history.push(new mdpQtHistoryEntry("Pen", m_qtModel, m_previewImage, m_previewPainter));
        m_qtModel.submit();
        m_drawing = false;
    }
}

// public virtual
void mdpQtPenTool::mouseMoveEvent(const int x, const int y) /* override */
{
    m_qtModel.beginDrawing();
    if (m_drawing) {
        draw(m_lastX, m_lastY, x, y);
        m_lastX = x;
        m_lastY = y;
    }
    else {
        m_qtModel.refresh();
        draw(x, y);
    }
    m_qtModel.endDrawing();
}

// public virtual
void mdpQtPenTool::enterEvent() /* override */
{
}

// public virtual
void mdpQtPenTool::leaveEvent() /* override */
{
    m_qtModel.beginDrawing();
    m_qtModel.refresh();
    m_qtModel.endDrawing();
}

// private
void mdpQtPenTool::draw(const int x, const int y)
{
}

// private
void mdpQtPenTool::draw(const int fromX, const int fromY, const int toX, const int toY)
{
}

// private slot
void mdpQtPenTool::onQtModelPreviewReset()
{
    m_previewPainter = m_qtModel.getPreviewPainter();
    m_previewImage = m_qtModel.getPreviewImage();
}
