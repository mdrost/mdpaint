#ifndef MDP_QTTOOLWRAPPER_H
#define MDP_QTTOOLWRAPPER_H

#include <mdpaint/tool.h>

#include <QObject>

#include <memory>

class mdpQtToolWrapper final : public QObject, public mdpTool
{
    Q_OBJECT

public:

    explicit mdpQtToolWrapper(std::unique_ptr<mdpTool> tool);

    ~mdpQtToolWrapper() override;

    // mdpTool interface:

    void activate() override;

    void deactivate() override;

    void mousePressEvent(int x, int y) override;

    void mouseReleaseEvent(int x, int y) override;

    void mouseMoveEvent(int x, int y) override;

    void enterEvent() override;

    void leaveEvent() override;

Q_SIGNALS:

    void postActivate();

    void preDeactivate();

private:
    Q_DISABLE_COPY(mdpQtToolWrapper);

    std::unique_ptr<mdpTool> m_tool;
};

#endif // MDP_QTTOOLWRAPPER_H
