#ifndef MDP_QTHISTORYVIEW_H
#define MDP_QTHISTORYVIEW_H

#include <QDockWidget>

class QUndoStack;
class QUndoView;

class mdpQtHistoryView final : public QDockWidget
{
    Q_OBJECT

public:

    explicit mdpQtHistoryView(QUndoStack* undoStack, QWidget* parent = nullptr);

    ~mdpQtHistoryView() override;

Q_SIGNALS:

private:
    Q_DISABLE_COPY(mdpQtHistoryView)

    QUndoView* m_undoView;
};

#endif // MDP_QTHISTORYVIEW_H
