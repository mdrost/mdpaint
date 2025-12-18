#ifndef MDP_QTRECTANGLETOOL_H
#define MDP_QTRECTANGLETOOL_H

#include <mdpaint/signalconnection.h>
#include <mdpaint/tool.h>

#include <memory>

class mdpQtModel;

class mdpHistory;

class QImage;
class QPainter;

class mdpQtRectangleTool final : public mdpTool
{
public:

    explicit mdpQtRectangleTool(mdpQtModel& qtModel, mdpHistory& history);

    ~mdpQtRectangleTool() override;

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

    void onQtModelPreviewReset();

private:
    mdpQtModel& m_qtModel;
    mdpHistory& m_history;
    std::shared_ptr<QImage> m_previewImage;
    std::shared_ptr<QPainter> m_previewPainter;
    mdpSignalConnection onQtModelPreviewResetConnection;
    bool m_drawing;
    int m_startingX;
    int m_startingY;
};

#endif // MDP_QTRECTANGLETOOL_H
