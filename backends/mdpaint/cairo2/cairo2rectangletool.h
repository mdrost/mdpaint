#ifndef MDP_CAIRO2RECTANGLETOOL_H
#define MDP_CAIRO2RECTANGLETOOL_H

#include <mdpaint/signalconnection.h>
#include <mdpaint/tool.h>

#include <cairo/cairo.h>

class mdpCairo2Model;
class mdpHistory;

class mdpCairo2RectangleTool final : public mdpTool
{
public:

    explicit mdpCairo2RectangleTool(mdpCairo2Model& cairoModel, mdpHistory& history);

    ~mdpCairo2RectangleTool() override;

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
    mdpCairo2Model& m_cairoModel;
    mdpHistory& m_history;
    cairo_surface_t* m_previewSurface;
    cairo_t* m_previewContext;
    mdpSignalConnection onCairoModelPreviewResetConnection;
    bool m_drawing;
    int m_startingX;
    int m_startingY;
};

#endif // MDP_CAIRO2RECTANGLETOOL_H
