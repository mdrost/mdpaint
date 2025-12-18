#include "qtellipsetool.h"

#include "qthistoryentry.h"
#include "qtmodel.h"

#include <mdpaint/history.h>

#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

// public
mdpQtEllipseTool::mdpQtEllipseTool(mdpQtModel& qtModel, mdpHistory& history) :
    m_qtModel(qtModel),
    m_history(history),
    m_previewImage(nullptr),
    m_previewPainter(nullptr),
    m_drawing(false)
{
}

// public virtual
mdpQtEllipseTool::~mdpQtEllipseTool() /* override */
{
}

// public virtual
void mdpQtEllipseTool::activate() /* override */
{
    m_previewImage = m_qtModel.getPreviewImage();
    m_previewPainter = m_qtModel.getPreviewPainter();
    onQtModelPreviewResetConnection = m_qtModel.onPreviewReset(std::bind(&mdpQtEllipseTool::onQtModelPreviewReset, this));
}

// public virtual
void mdpQtEllipseTool::deactivate() /* override */
{
    onQtModelPreviewResetConnection.disconnect();
    m_previewImage = nullptr;
}

// public virtual
void mdpQtEllipseTool::mousePressEvent(const int x, const int y) /* override */
{
    m_drawing = true;
    m_qtModel.beginDrawing();
    draw(x, y);
    m_startingX = x;
    m_startingY = y;
    m_qtModel.endDrawing();
}

// public virtual
void mdpQtEllipseTool::mouseReleaseEvent(const int x, const int y) /* override */
{
    if (m_drawing) {
        //m_history.push(new mdpQtHistoryEntry("Ellipse", m_qtModel, m_previewImage, m_previewPainter));
        m_qtModel.submit();
        m_drawing = false;
    }
}

// public virtual
void mdpQtEllipseTool::mouseMoveEvent(const int x, const int y) /* override */
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
void mdpQtEllipseTool::enterEvent() /* override */
{
}

// public virtual
void mdpQtEllipseTool::leaveEvent() /* override */
{
    m_qtModel.beginDrawing();
    m_qtModel.refresh();
    m_qtModel.endDrawing();
}

// private
void mdpQtEllipseTool::draw(const int x, const int y)
{
}

// private
void mdpQtEllipseTool::draw(const int fromX, const int fromY, const int toX, const int toY)
{
}

// private slot
void mdpQtEllipseTool::onQtModelPreviewReset()
{
    m_previewImage = m_qtModel.getPreviewImage();
    m_previewPainter = m_qtModel.getPreviewPainter();
}
