#ifndef MDP_CAIRORESIZESCALESKEWTOOL_H
#define MDP_CAIRORESIZESCALESKEWTOOL_H

#include <mdpaint/resizescaleskewtool.h>

#include <functional>

class mdpCairoModel;

class mdpHistory;

class mdpCairoResizeScaleSkewTool final : public mdpResizeScaleSkewTool
{
public:

    explicit mdpCairoResizeScaleSkewTool(mdpCairoModel& cairoModel, std::function<mdpResizeScaleSkewData() > getResizeScaleSkewData, mdpHistory& history);

    ~mdpCairoResizeScaleSkewTool() override;

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
    mdpCairoModel& m_cairoModel;
    std::function<mdpResizeScaleSkewData() > m_getResizeScaleSkewData;
    mdpHistory& m_history;
};

#endif // MDP_CAIRORESIZESCALESKEWTOOL_H
