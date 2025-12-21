#ifndef MDP_QTRESIZESCALESKEWTOOL_H
#define MDP_QTRESIZESCALESKEWTOOL_H

#include <mdpaint/resizescaleskewtool.h>

#include <QObject>

#include <functional>

class mdpQtModel;

class mdpHistory;

class mdpQtResizeScaleSkewTool final : public QObject, public mdpResizeScaleSkewTool
{
    Q_OBJECT

public:

    explicit mdpQtResizeScaleSkewTool(mdpQtModel& qtModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history);

    ~mdpQtResizeScaleSkewTool() override;

    // mdpTool interface:

    void activate() override;

    void deactivate() override;

    void mousePressEvent(int x, int y) override;

    void mouseReleaseEvent(int x, int y) override;

    void mouseMoveEvent(int x, int y) override;

    void enterEvent() override;

    void leaveEvent() override;

    // mdpResizeScaleSkewTool interface:

    void resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) override;

private:
    Q_DISABLE_COPY(mdpQtResizeScaleSkewTool)

    mdpQtModel& m_qtModel;
    std::function<mdpResizeScaleSkewData ()> m_getResizeScaleSkewData;
    mdpHistory& m_history;
};

#endif // MDP_QTRESIZESCALESKEWTOOL_H
