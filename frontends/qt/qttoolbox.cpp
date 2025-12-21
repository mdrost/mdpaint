#include "qttoolbox.h"

#include <QGridLayout>
#include <QToolButton>

// public
mdpQtToolBox::mdpQtToolBox(QWidget* parent) :
    QDockWidget(tr("Tool Box"), parent),
    m_freeFormSelectionToolButton(nullptr),
    m_rectangularSelectionToolButton(nullptr),
    m_ellipticalSelectionToolButton(nullptr),
    m_penToolButton(nullptr),
    m_lineToolButton(nullptr),
    m_rectangleToolButton(nullptr),
    m_ellipseToolButton(nullptr),
    m_resizeScaleSkewToolButton(nullptr)
{
    QWidget* widget = new QWidget(this);
    widget->setObjectName(QStringLiteral("widget"));
    setWidget(widget);

    m_gridLayout = new QGridLayout(widget);
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
void mdpQtToolBox::setFreeFormSelectionToolAction(QAction* const freeFormSelectionToolAction)
{
    delete m_freeFormSelectionToolButton;
    m_freeFormSelectionToolButton = new QToolButton(this);
    m_freeFormSelectionToolButton->setDefaultAction(freeFormSelectionToolAction);
    m_gridLayout->addWidget(m_freeFormSelectionToolButton, 0, 0);
}

// public
void mdpQtToolBox::setRectangularSelectionToolAction(QAction* const rectangularSelectionToolAction)
{
    delete m_rectangularSelectionToolButton;
    m_rectangularSelectionToolButton = new QToolButton(this);
    m_rectangularSelectionToolButton->setDefaultAction(rectangularSelectionToolAction);
    m_gridLayout->addWidget(m_rectangularSelectionToolButton, 0, 1);
}

// public
void mdpQtToolBox::setEllipticalSelectionToolAction(QAction* const ellipticalSelectionToolAction)
{
    delete m_ellipticalSelectionToolButton;
    m_ellipticalSelectionToolButton = new QToolButton(this);
    m_ellipticalSelectionToolButton->setDefaultAction(ellipticalSelectionToolAction);
    m_gridLayout->addWidget(m_ellipticalSelectionToolButton, 1, 0);
}

// public
void mdpQtToolBox::setPenToolAction(QAction* const penToolAction)
{
    delete m_penToolButton;
    m_penToolButton = new QToolButton(this);
    m_penToolButton->setDefaultAction(penToolAction);
    m_gridLayout->addWidget(m_penToolButton, 2, 0);
}

// public
void mdpQtToolBox::setLineToolAction(QAction* const lineToolAction)
{
    delete m_lineToolButton;
    m_lineToolButton = new QToolButton(this);
    m_lineToolButton->setDefaultAction(lineToolAction);
    m_gridLayout->addWidget(m_lineToolButton, 2, 1);
}

// public
void mdpQtToolBox::setRectangleToolAction(QAction* const rectangleToolAction)
{
    delete m_rectangleToolButton;
    m_rectangleToolButton = new QToolButton(this);
    m_rectangleToolButton->setDefaultAction(rectangleToolAction);
    m_gridLayout->addWidget(m_rectangleToolButton, 3, 0);
}

// public
void mdpQtToolBox::setEllipseToolAction(QAction* const ellipseToolAction)
{
    delete m_ellipseToolButton;
    m_ellipseToolButton = new QToolButton(this);
    m_ellipseToolButton->setDefaultAction(ellipseToolAction);
    m_gridLayout->addWidget(m_ellipseToolButton, 3, 1);
}

// public
void mdpQtToolBox::setresizeScaleSkewToolAction(QAction* const resizeScaleSkewToolAction)
{
    delete m_resizeScaleSkewToolButton;
    m_resizeScaleSkewToolButton = new QToolButton(this);
    m_resizeScaleSkewToolButton->setDefaultAction(resizeScaleSkewToolAction);
    m_gridLayout->addWidget(m_resizeScaleSkewToolButton, 4, 0);
}
