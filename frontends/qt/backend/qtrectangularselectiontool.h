#ifndef MDP_QTRECTANGULARSELECTIONTOOL_H
#define MDP_QTRECTANGULARSELECTIONTOOL_H

#include <mdpaint/rectangle.h>
#include <mdpaint/selectiontool.h>

#include <QImage>
#include <QObject>

class mdpQtModel;

class mdpHistory;

class mdpQtRectangularSelectionTool final : public QObject, public mdpSelectionTool
{
    Q_OBJECT

public:

    explicit mdpQtRectangularSelectionTool(mdpQtModel& qtModel, mdpHistory& history);

    ~mdpQtRectangularSelectionTool() override;

    // mdpTool interface:

    void activate() override;

    void deactivate() override;

    void mousePressEvent(int x, int y) override;

    void mouseReleaseEvent(int x, int y) override;

    void mouseMoveEvent(int x, int y) override;

    void enterEvent() override;

    void leaveEvent() override;

    // mdpSelectionTool interface:

    [[nodiscard]]
    std::variant<std::monostate, std::vector<mdpPoint>, mdpRectangle, mdpEllipse> selection() const override;

    [[nodiscard]]
    mdpRectangle selectionBoundingRectangle() const override;

    [[nodiscard]]
    mdpSignalConnection onSelectionChanged(std::function<void ()> slot) const override;

Q_SIGNALS:

    void selectionChanged();

private:

    void onQtModelPreviewReset();

private:
    Q_DISABLE_COPY(mdpQtRectangularSelectionTool)

    mdpQtModel& m_qtModel;
    mdpHistory& m_history;
    std::shared_ptr<QImage> m_previewImage;
    std::shared_ptr<QPainter> m_previewPainter;
    mdpSignalConnection onQtModelPreviewResetConnection;
    bool m_selecting;
    mdpRectangle m_selection;
    QImage m_maskImage;
    QImage m_cutoutImage;
    bool m_dragging;
    int m_startingX;
    int m_startingY;
    int m_commitedOffsetX;
    int m_commitedOffsetY;
    int m_offsetX;
    int m_offsetY;
};

#endif // MDP_QTRECTANGULARSELECTIONTOOL_H
