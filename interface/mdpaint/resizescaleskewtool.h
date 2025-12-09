#ifndef MDP_RESIZESCALESKEWTOOL_H
#define MDP_RESIZESCALESKEWTOOL_H

#include "tool.h"

struct mdpResizeScaleSkewData
{
    int x;
    int y;
    int width;
    int height;
    bool scale;
    double horizontalSkew;
    double verticalSkew;
};

class mdpResizeScaleSkewTool : public mdpTool
{
public:

    explicit mdpResizeScaleSkewTool();

    ~mdpResizeScaleSkewTool() override;

    virtual void resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) = 0;
};

#endif // MDP_RESIZESCALESKEWTOOL_H
