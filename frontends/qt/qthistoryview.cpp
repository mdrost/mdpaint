#include "qthistoryview.h"

#include <QUndoView>

// public
mdpQtHistoryView::mdpQtHistoryView(QUndoStack* undoStack, QWidget* parent) :
    QDockWidget(tr("History"), parent)
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    m_undoView = new QUndoView(undoStack, this);
    setWidget(m_undoView);
}

// public
mdpQtHistoryView::~mdpQtHistoryView()
{
}
