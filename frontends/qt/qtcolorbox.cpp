#include "qtcolorbox.h"

// public
mdpQtColorBox::mdpQtColorBox(QWidget* parent) :
    QDockWidget(tr("Color Box"), parent)
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);
}

// public
mdpQtColorBox::~mdpQtColorBox()
{
}
