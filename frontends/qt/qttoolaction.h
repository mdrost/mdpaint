#ifndef MDP_QTTOOLACTION_H
#define MDP_QTTOOLACTION_H

#include <QAction>

class mdpTool;

class mdpQtToolAction final : public QAction
{
    Q_OBJECT

public:

    explicit mdpQtToolAction(QObject* parent = nullptr);

    explicit mdpQtToolAction(const QString& text, QObject* parent = nullptr);

    explicit mdpQtToolAction(const QIcon& icon, const QString& text, QObject* parent = nullptr);

    ~mdpQtToolAction() override;

    void setTool(mdpTool* tool);

    mdpTool* tool() const;

private:
    Q_DISABLE_COPY(mdpQtToolAction)

    mdpTool* m_tool;
};

#endif // MDP_QTTOOLACTION_H
