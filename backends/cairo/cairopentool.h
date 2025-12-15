#ifndef MDP_CAIROPENTOOL_H
#define MDP_CAIROPENTOOL_H

#include <mdpaint/signalconnection.h>
#include <mdpaint/tool.h>

#include <cairo/cairo.h>

class mdpCairoModel;

class mdpHistory;

class mdpCairoPenTool final : public mdpTool
{
public:

    explicit mdpCairoPenTool(mdpCairoModel& cairoModel, mdpHistory& history);

    ~mdpCairoPenTool() override;

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
    int m_lastX;
    int m_lastY;
};

#endif // MDP_CAIROPENTOOL_H
