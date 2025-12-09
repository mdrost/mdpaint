#include "toolaction.h"

#include <mdpaint/tool.h>

// public
mdpToolAction::mdpToolAction(QObject* parent) :
    QAction(parent),
    m_tool(nullptr)
{
}

// public
mdpToolAction::mdpToolAction(const QString& text, QObject* parent) :
    QAction(text, parent),
    m_tool(nullptr)
{
}

// public
mdpToolAction::mdpToolAction(const QIcon& icon, const QString& text, QObject* parent) :
    QAction(icon, text, parent),
    m_tool(nullptr)
{
}

// public
mdpToolAction::~mdpToolAction()
{
}

// public
void mdpToolAction::setTool(mdpTool* tool)
{
    m_tool = tool;
}


// public
mdpTool* mdpToolAction::tool() const
{
    return m_tool;
}
