#ifndef MDP_TOOL_H
#define MDP_TOOL_H

class mdpTool
{
public:

    explicit mdpTool();

    virtual ~mdpTool();

    virtual void activate() = 0;

    virtual void deactivate() = 0;

    virtual void mousePressEvent(int x, int y) = 0;

    virtual void mouseReleaseEvent(int x, int y) = 0;

    virtual void mouseMoveEvent(int x, int y) = 0;

    virtual void enterEvent() = 0;

    virtual void leaveEvent() = 0;
};

#endif // MDP_TOOL_H
