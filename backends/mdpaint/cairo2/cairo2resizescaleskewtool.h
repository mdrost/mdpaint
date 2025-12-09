#ifndef MDP_CAIRO2RESIZESCALESKEWTOOL_H
#define MDP_CAIRO2RESIZESCALESKEWTOOL_H

#include <mdpaint/resizescaleskewtool.h>

#include <functional>

class mdpCairo2Model;
class mdpHistory;

class mdpCairo2ResizeScaleSkewTool final : public mdpResizeScaleSkewTool
{
public:

    explicit mdpCairo2ResizeScaleSkewTool(mdpCairo2Model& cairoModel, std::function<mdpResizeScaleSkewData()> getResizeScaleSkewData, mdpHistory& history);

    ~mdpCairo2ResizeScaleSkewTool() override;

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
    mdpCairo2Model& m_cairoModel;
    std::function<mdpResizeScaleSkewData()> m_getResizeScaleSkewData;
    mdpHistory& m_history;
};

#endif // MDP_CAIRO3RESIZESCALESKEWTOOL_H
