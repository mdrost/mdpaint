#ifndef MDP_VIPSLINETOOL_H
#define MDP_VIPSLINETOOL_H

#include <mdpaint/signalconnection.h>
#include <mdpaint/tool.h>

#include <vips/vips.h>

class mdpVipsModel;

class mdpHistory;

class mdpVipsLineTool final : public mdpTool
{
public:

    explicit mdpVipsLineTool(mdpVipsModel& vipsModel, mdpHistory& history);

    ~mdpVipsLineTool() override;

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

#endif // MDP_VIPSLINETOOL_H
