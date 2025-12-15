#ifndef MDP_RESIZESCALESKEWTOOL_H
#define MDP_RESIZESCALESKEWTOOL_H

#include "api.h"
#include "tool.h"

struct MDP_INTERFACE_API mdpResizeScaleSkewData
{
    int x;
    int y;
    int width; // pre-skew
    int height; // pre-skew
    bool scale;
    double skewX;
    double skewY;
};

class MDP_INTERFACE_API mdpResizeScaleSkewTool : public mdpTool
{
public:

    explicit mdpResizeScaleSkewTool();

    ~mdpResizeScaleSkewTool() override;

    virtual void resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) = 0;
};

#endif // MDP_RESIZESCALESKEWTOOL_H
