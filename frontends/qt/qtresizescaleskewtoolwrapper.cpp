#include "qtresizescaleskewtoolwrapper.h"

// public
mdpQtResizeScaleSkewToolWrapper::mdpQtResizeScaleSkewToolWrapper(std::unique_ptr<mdpResizeScaleSkewTool> resizeScaleSkewTool) :
    m_resizeScaleSkewTool(std::move(resizeScaleSkewTool))
{
}

// public virtual
mdpQtResizeScaleSkewToolWrapper::~mdpQtResizeScaleSkewToolWrapper() /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewToolWrapper::activate() /* override */
{
    m_resizeScaleSkewTool->activate();
    Q_EMIT postActivate();
}

// public virtual
void mdpQtResizeScaleSkewToolWrapper::deactivate() /* override */
{
    Q_EMIT preDeactivate();
    m_resizeScaleSkewTool->deactivate();
}

// public virtual
void mdpQtResizeScaleSkewToolWrapper::mousePressEvent(const int x, const int y) /* override */
{
    m_resizeScaleSkewTool->mousePressEvent(x, y);
}

// public virtual
void mdpQtResizeScaleSkewToolWrapper::mouseReleaseEvent(const int x, const int y) /* override */
{
    m_resizeScaleSkewTool->mouseReleaseEvent(x, y);
}

// public virtual
void mdpQtResizeScaleSkewToolWrapper::mouseMoveEvent(const int x, const int y) /* override */
{
    m_resizeScaleSkewTool->mouseMoveEvent(x, y);
}

// public virtual
void mdpQtResizeScaleSkewToolWrapper::enterEvent() /* override */
{
    m_resizeScaleSkewTool->enterEvent();
}

// public virtual
void mdpQtResizeScaleSkewToolWrapper::leaveEvent() /* override */
{
    m_resizeScaleSkewTool->leaveEvent();
}

// public virtual
void mdpQtResizeScaleSkewToolWrapper::resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) /* override */
{
    m_resizeScaleSkewTool->resizeScaleSkew(resizeScaleSkewData);
}
