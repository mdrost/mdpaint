#include "qtselectiontoolwrapper.h"

#include <mdpaint/ellipse.h>
#include <mdpaint/point.h>
#include <mdpaint/rectangle.h>

// public
mdpQtSelectionToolWrapper::mdpQtSelectionToolWrapper(std::unique_ptr<mdpSelectionTool> selectionTool) :
    m_selectionTool(std::move(selectionTool))
{
}

// public virtual
mdpQtSelectionToolWrapper::~mdpQtSelectionToolWrapper() /* override */
{
}

// public virtual
void mdpQtSelectionToolWrapper::activate() /* override */
{
    m_selectionTool->activate();
    Q_EMIT postActivate();
}

// public virtual
void mdpQtSelectionToolWrapper::deactivate() /* override */
{
    Q_EMIT preDeactivate();
    m_selectionTool->deactivate();
}

// public virtual
void mdpQtSelectionToolWrapper::mousePressEvent(const int x, const int y) /* override */
{
    m_selectionTool->mousePressEvent(x, y);
}

// public virtual
void mdpQtSelectionToolWrapper::mouseReleaseEvent(const int x, const int y) /* override */
{
    m_selectionTool->mouseReleaseEvent(x, y);
}

// public virtual
void mdpQtSelectionToolWrapper::mouseMoveEvent(const int x, const int y) /* override */
{
    m_selectionTool->mouseMoveEvent(x, y);
}

// public virtual
void mdpQtSelectionToolWrapper::enterEvent() /* override */
{
    m_selectionTool->enterEvent();
}

// public virtual
void mdpQtSelectionToolWrapper::leaveEvent() /* override */
{
    m_selectionTool->leaveEvent();
}

// public virtual
std::variant<std::monostate, std::vector<mdpPoint>, mdpRectangle, mdpEllipse> mdpQtSelectionToolWrapper::selection() const /* override */
{
    return m_selectionTool->selection();
}

// public virtual
mdpRectangle mdpQtSelectionToolWrapper::selectionBoundingRectangle() const /* override */
{
    return m_selectionTool->selectionBoundingRectangle();
}

// public virtual
mdpSignalConnection mdpQtSelectionToolWrapper::onSelectionChanged(std::function<void ()> slot) const /* override */
{
    return m_selectionTool->onSelectionChanged(std::move(slot));
}
