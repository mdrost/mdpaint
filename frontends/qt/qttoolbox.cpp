#include "qttoolbox.h"

#include <QGridLayout>
#include <QToolButton>

// public
mdpQtToolBox::mdpQtToolBox(QWidget* parent) :
    QDockWidget(tr("Tool Box"), parent),
    m_penToolButton(nullptr),
    m_lineToolButton(nullptr),
    m_rectangleToolButton(nullptr),
    m_ellipseToolButton(nullptr),
    m_resizeScaleSkewToolButton(nullptr)
{
    m_widget = new QWidget(this);
    m_widget->setObjectName(QStringLiteral("widget"));
    setWidget(m_widget);

    m_gridLayout = new QGridLayout(m_widget);
    m_gridLayout->setObjectName(QStringLiteral("gridLayout"));
    //m_gridLayout->setSpacing(0);
    //m_gridLayout->setContentsMargins(0, 0, 0, 0);
    m_gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    setFeatures(QDockWidget::NoDockWidgetFeatures);
}

// public
mdpQtToolBox::~mdpQtToolBox()
{
}

// public
void mdpQtToolBox::setPenToolAction(QAction* penToolAction)
{
    delete m_penToolButton;
    m_penToolButton = new QToolButton(this);
    m_penToolButton->setDefaultAction(penToolAction);
    m_gridLayout->addWidget(m_penToolButton, 2, 0);
}

// public
void mdpQtToolBox::setLineToolAction(QAction* lineToolAction)
{
    delete m_lineToolButton;
    m_lineToolButton = new QToolButton(this);
    m_lineToolButton->setDefaultAction(lineToolAction);
    m_gridLayout->addWidget(m_lineToolButton, 2, 1);
}

// public
void mdpQtToolBox::setRectangleToolAction(QAction* rectangleToolAction)
{
    delete m_rectangleToolButton;
    m_rectangleToolButton = new QToolButton(this);
    m_rectangleToolButton->setDefaultAction(rectangleToolAction);
    m_gridLayout->addWidget(m_rectangleToolButton, 3, 0);
}

// public
void mdpQtToolBox::setEllipseToolAction(QAction* ellipseToolAction)
{
    delete m_ellipseToolButton;
    m_ellipseToolButton = new QToolButton(this);
    m_ellipseToolButton->setDefaultAction(ellipseToolAction);
    m_gridLayout->addWidget(m_ellipseToolButton, 3, 1);
}

// public
void mdpQtToolBox::setresizeScaleSkewToolAction(QAction* resizeScaleSkewToolAction)
{
    delete m_resizeScaleSkewToolButton;
    m_resizeScaleSkewToolButton = new QToolButton(this);
    m_resizeScaleSkewToolButton->setDefaultAction(resizeScaleSkewToolAction);
    m_gridLayout->addWidget(m_resizeScaleSkewToolButton, 4, 0);
}
