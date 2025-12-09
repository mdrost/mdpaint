#ifndef MDP_TOOLACTION_H
#define MDP_TOOLACTION_H

#include <QAction>

class mdpTool;

class mdpToolAction final : public QAction
{
    Q_OBJECT

public:

    explicit mdpToolAction(QObject* parent = nullptr);

    explicit mdpToolAction(const QString& text, QObject* parent = nullptr);

    explicit mdpToolAction(const QIcon& icon, const QString& text, QObject* parent = nullptr);

    ~mdpToolAction() override;

    void setTool(mdpTool* tool);

    mdpTool* tool() const;

private:
    Q_DISABLE_COPY(mdpToolAction)

    mdpTool* m_tool;
};

#endif // MDP_TOOLACTION_H
