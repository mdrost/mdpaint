#ifndef MDP_CAIRORECTANGLETOOL_H
#define MDP_CAIRORECTANGLETOOL_H

#include <mdpaint/signalconnection.h>
#include <mdpaint/tool.h>

#include <cairo/cairo.h>

class mdpCairoModel;

class mdpHistory;

class mdpCairoRectangleTool final : public mdpTool
{
public:

    explicit mdpCairoRectangleTool(mdpCairoModel& cairoModel, mdpHistory& history);

    ~mdpCairoRectangleTool() override;

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

    void onCairoModelPreviewReset();

private:
    mdpCairoModel& m_cairoModel;
    mdpHistory& m_history;
    cairo_surface_t* m_previewSurface;
    cairo_t* m_previewContext;
    mdpSignalConnection onCairoModelPreviewResetConnection;
    bool m_drawing;
    int m_startingX;
    int m_startingY;
};

#endif // MDP_CAIRORECTANGLETOOL_H
