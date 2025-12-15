#ifndef MDP_VIPSELLIPSETOOL_H
#define MDP_VIPSELLIPSETOOL_H

#include <mdpaint/signalconnection.h>
#include <mdpaint/tool.h>

#include <vips/vips.h>

class mdpVipsModel;

class mdpHistory;

class mdpVipsEllipseTool final : public mdpTool
{
public:

    explicit mdpVipsEllipseTool(mdpVipsModel& vipsModel, mdpHistory& history);

    ~mdpVipsEllipseTool() override;

    // mdpTool interface:

    void activate() override;

    void deactivate() override;

    void mousePressEvent(int x, int y) override;

    void mouseReleaseEvent(int x, int y) override;

    void mouseMoveEvent(int x, int y) override;

    void enterEvent() override;

    void leaveEvent() override;

private:

    void draw(int x, int y);

    void draw(int fromX, int fromY, int toX, int toY);

    void onVipsModelPreviewReset();

private:
    mdpVipsModel& m_vipsModel;
    mdpHistory& m_history;
    VipsImage* m_previewImage;
    mdpSignalConnection onVipsModelPreviewResetConnection;
    bool m_drawing;
    int m_startingX;
    int m_startingY;
};

#endif // MDP_VIPSELLIPSETOOL_H
