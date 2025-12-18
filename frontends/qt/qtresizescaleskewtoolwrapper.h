#ifndef MDP_QTRESIZESCALESKEWTOOLWRAPPER_H
#define MDP_QTRESIZESCALESKEWTOOLWRAPPER_H

#include <mdpaint/resizescaleskewtool.h>

#include <QObject>

class mdpQtResizeScaleSkewToolWrapper final : public QObject, public mdpResizeScaleSkewTool
{
    Q_OBJECT

public:

    explicit mdpQtResizeScaleSkewToolWrapper(std::unique_ptr<mdpResizeScaleSkewTool> resizeScaleSkewTool);

    ~mdpQtResizeScaleSkewToolWrapper() override;

    void activate() override;

    void deactivate() override;

    void mousePressEvent(int x, int y) override;

    void mouseReleaseEvent(int x, int y) override;

    void mouseMoveEvent(int x, int y) override;

    void enterEvent() override;

    void leaveEvent() override;

    void resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) override;

Q_SIGNALS:

    void activated();

private:
    Q_DISABLE_COPY(mdpQtResizeScaleSkewToolWrapper);

    std::unique_ptr<mdpResizeScaleSkewTool> m_resizeScaleSkewTool;
};

#endif // MDP_QTRESIZESCALESKEWTOOLWRAPPER_H
