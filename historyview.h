#ifndef MDP_HISTORYVIEW_H
#define MDP_HISTORYVIEW_H

#include <QDockWidget>

class QUndoStack;
class QUndoView;

class mdpHistoryView final : public QDockWidget
{
    Q_OBJECT

public:

    explicit mdpHistoryView(QUndoStack* undoStack, QWidget* parent = nullptr);

    ~mdpHistoryView() override;

Q_SIGNALS:

private:
    Q_DISABLE_COPY(mdpHistoryView)

    QUndoView* m_undoView;
};

#endif // MDP_HISTORYVIEW_H
