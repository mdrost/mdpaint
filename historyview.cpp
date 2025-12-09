#include "historyview.h"

#include <QUndoView>

// public
mdpHistoryView::mdpHistoryView(QUndoStack* undoStack, QWidget* parent) :
    QDockWidget(tr("History"), parent)
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    m_undoView = new QUndoView(undoStack, this);
    setWidget(m_undoView);
}

// public
mdpHistoryView::~mdpHistoryView()
{
}
