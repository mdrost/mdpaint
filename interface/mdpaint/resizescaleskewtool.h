#ifndef MDP_RESIZESCALESKEWTOOL_H
#define MDP_RESIZESCALESKEWTOOL_H

#include "tool.h"

struct mdpResizeScaleSkewData
{
    int x;
    int y;
    int width; // pre-skew
    int height; // pre-skew
    bool scale;
    double skewX;
    double skewY;
};

class mdpResizeScaleSkewTool : public mdpTool
{
public:

    explicit mdpResizeScaleSkewTool();

    ~mdpResizeScaleSkewTool() override;

    virtual void resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) = 0;
};

#endif // MDP_RESIZESCALESKEWTOOL_H
