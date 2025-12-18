#include "qtlinetool.h"

#include "qthistoryentry.h"
#include "qtmodel.h"

#include <mdpaint/history.h>

#include <functional>
#include <stdexcept>

// public
mdpQtLineTool::mdpQtLineTool(mdpQtModel& qtModel, mdpHistory& history) :
    m_qtModel(qtModel),
    m_history(history),
    m_previewImage(nullptr),
    m_previewPainter(nullptr),
    m_drawing(false)
{
}

// public
mdpQtLineTool::~mdpQtLineTool()
{
}

// public virtual
void mdpQtLineTool::activate() /* override */
{
    m_previewImage = m_qtModel.getPreviewImage();
    m_previewPainter = m_qtModel.getPreviewPainter();
    onQtModelPreviewResetConnection = m_qtModel.onPreviewReset(std::bind(&mdpQtLineTool::onQtModelPreviewReset, this));
}

// public virtual
void mdpQtLineTool::deactivate() /* override */
{
    onQtModelPreviewResetConnection.disconnect();
    m_previewPainter = nullptr;
    m_previewImage = nullptr;
}

// public virtual
void mdpQtLineTool::mousePressEvent(const int x, const int y) /* override */
{
    m_drawing = true;
    m_qtModel.beginDrawing();
    draw(x, y);
    m_startingX = x;
    m_startingY = y;
    m_qtModel.endDrawing();
}

// public virtual
void mdpQtLineTool::mouseReleaseEvent(const int x, const int y) /* override */
{
    if (m_drawing) {
        //m_history.push(new mdpQtHistoryEntry("Line", m_qtModel, m_previewImage, m_previewPainter));
        m_qtModel.submit();
        m_drawing = false;
    }
}

// public virtual
void mdpQtLineTool::mouseMoveEvent(const int x, const int y) /* override */
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
void mdpQtLineTool::enterEvent() /* override */
{
}

// public virtual
void mdpQtLineTool::leaveEvent() /* override */
{
    m_qtModel.beginDrawing();
    m_qtModel.refresh();
    m_qtModel.endDrawing();
}

// private
void mdpQtLineTool::draw(const int x, const int y)
{
}

// private
void mdpQtLineTool::draw(const int fromX, const int fromY, const int toX, const int toY)
{
}

// private slot
void mdpQtLineTool::onQtModelPreviewReset()
{
    m_previewImage = m_qtModel.getPreviewImage();
    m_previewPainter = m_qtModel.getPreviewPainter();
}
