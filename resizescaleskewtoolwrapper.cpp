#include "resizescaleskewtoolwrapper.h"

// public
mdpResizeScaleSkewToolWrapper::mdpResizeScaleSkewToolWrapper(std::unique_ptr<mdpResizeScaleSkewTool> resizeScaleSkewTool) :
    m_resizeScaleSkewTool(std::move(resizeScaleSkewTool))
{
}

// public virtual
mdpResizeScaleSkewToolWrapper::~mdpResizeScaleSkewToolWrapper() /* override */
{
}

// public virtual
void mdpResizeScaleSkewToolWrapper::activate() /* override */
{
    m_resizeScaleSkewTool->activate();
    Q_EMIT activated();
}

// public virtual
void mdpResizeScaleSkewToolWrapper::deactivate() /* override */
{
    m_resizeScaleSkewTool->deactivate();
}

// public virtual
void mdpResizeScaleSkewToolWrapper::mousePressEvent(const int x, const int y) /* override */
{
    m_resizeScaleSkewTool->mousePressEvent(x, y);
}

// public virtual
void mdpResizeScaleSkewToolWrapper::mouseReleaseEvent(const int x, const int y) /* override */
{
    m_resizeScaleSkewTool->mouseReleaseEvent(x, y);
}

// public virtual
void mdpResizeScaleSkewToolWrapper::mouseMoveEvent(const int x, const int y) /* override */
{
    m_resizeScaleSkewTool->mouseMoveEvent(x, y);
}

// public virtual
void mdpResizeScaleSkewToolWrapper::enterEvent() /* override */
{
    m_resizeScaleSkewTool->enterEvent();
}

// public virtual
void mdpResizeScaleSkewToolWrapper::leaveEvent() /* override */
{
    m_resizeScaleSkewTool->leaveEvent();
}

// public virtual
void mdpResizeScaleSkewToolWrapper::resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) /* override */
{
    m_resizeScaleSkewTool->resizeScaleSkew(resizeScaleSkewData);
}
