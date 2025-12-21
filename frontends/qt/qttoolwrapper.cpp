#include "qttoolwrapper.h"

// public
mdpQtToolWrapper::mdpQtToolWrapper(std::unique_ptr<mdpTool> tool) :
    m_tool(std::move(tool))
{
}

// public virtual
mdpQtToolWrapper::~mdpQtToolWrapper() /* override */
{
}

// public virtual
void mdpQtToolWrapper::activate() /* override */
{
    m_tool->activate();
    Q_EMIT postActivate();
}

// public virtual
void mdpQtToolWrapper::deactivate() /* override */
{
    Q_EMIT preDeactivate();
    m_tool->deactivate();
}

// public virtual
void mdpQtToolWrapper::mousePressEvent(const int x, const int y) /* override */
{
    m_tool->mousePressEvent(x, y);
}

// public virtual
void mdpQtToolWrapper::mouseReleaseEvent(const int x, const int y) /* override */
{
    m_tool->mouseReleaseEvent(x, y);
}

// public virtual
void mdpQtToolWrapper::mouseMoveEvent(const int x, const int y) /* override */
{
    m_tool->mouseMoveEvent(x, y);
}

// public virtual
void mdpQtToolWrapper::enterEvent() /* override */
{
    m_tool->enterEvent();
}

// public virtual
void mdpQtToolWrapper::leaveEvent() /* override */
{
    m_tool->leaveEvent();
}
