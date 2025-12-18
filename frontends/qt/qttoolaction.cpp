#include "qttoolaction.h"

#include <mdpaint/tool.h>

// public
mdpQtToolAction::mdpQtToolAction(QObject* parent) :
    QAction(parent),
    m_tool(nullptr)
{
}

// public
mdpQtToolAction::mdpQtToolAction(const QString& text, QObject* parent) :
    QAction(text, parent),
    m_tool(nullptr)
{
}

// public
mdpQtToolAction::mdpQtToolAction(const QIcon& icon, const QString& text, QObject* parent) :
    QAction(icon, text, parent),
    m_tool(nullptr)
{
}

// public
mdpQtToolAction::~mdpQtToolAction()
{
}

// public
void mdpQtToolAction::setTool(mdpTool* tool)
{
    m_tool = tool;
}


// public
mdpTool* mdpQtToolAction::tool() const
{
    return m_tool;
}
