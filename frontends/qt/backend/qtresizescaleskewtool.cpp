#include "qtresizescaleskewtool.h"

#include "qthistoryentry.h"
#include "qtmodel.h"

#include <mdpaint/history.h>

#include <cmath>
#include <functional>
#include <stdexcept>

// public
mdpQtResizeScaleSkewTool::mdpQtResizeScaleSkewTool(mdpQtModel& qtModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) :
    m_qtModel(qtModel),
    m_getResizeScaleSkewData(std::move(getResizeScaleSkewData)),
    m_history(history)
{
}

// public virtual
mdpQtResizeScaleSkewTool::~mdpQtResizeScaleSkewTool() /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::activate() /* override */
{
    mdpResizeScaleSkewData resizeScaleSkewData = m_getResizeScaleSkewData();
    resizeScaleSkew(resizeScaleSkewData);
}

// public virtual
void mdpQtResizeScaleSkewTool::deactivate() /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::mousePressEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::mouseReleaseEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::mouseMoveEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::enterEvent() /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::leaveEvent() /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) /* override */
{
}
