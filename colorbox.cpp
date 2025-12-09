#include "colorbox.h"

// public
mdpColorBox::mdpColorBox(QWidget* parent) :
    QDockWidget(tr("Color Box"), parent)
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);
}

// public
mdpColorBox::~mdpColorBox()
{
}
