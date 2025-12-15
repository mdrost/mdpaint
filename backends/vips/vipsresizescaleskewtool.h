#ifndef MDP_VIPSRESIZESCALESKEWTOOL_H
#define MDP_VIPSRESIZESCALESKEWTOOL_H

#include <mdpaint/resizescaleskewtool.h>

#include <functional>

class mdpVipsModel;

class mdpHistory;

class mdpVipsResizeScaleSkewTool final : public mdpResizeScaleSkewTool
{
public:

    explicit mdpVipsResizeScaleSkewTool(mdpVipsModel& vipsModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history);

    ~mdpVipsResizeScaleSkewTool() override;

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
    mdpVipsModel& m_vipsModel;
    std::function<mdpResizeScaleSkewData ()> m_getResizeScaleSkewData;
    mdpHistory& m_history;
};

#endif // MDP_VIPSRESIZESCALESKEWTOOL_H
