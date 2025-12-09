#ifndef MDP_RESIZESCALESKEWTOOLWRAPPER_H
#define MDP_RESIZESCALESKEWTOOLWRAPPER_H

#include <mdpaint/resizescaleskewtool.h>

#include <QObject>

class mdpResizeScaleSkewToolWrapper final : public QObject, public mdpResizeScaleSkewTool
{
    Q_OBJECT

public:

    explicit mdpResizeScaleSkewToolWrapper(std::unique_ptr<mdpResizeScaleSkewTool> resizeScaleSkewTool);

    ~mdpResizeScaleSkewToolWrapper() override;

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
    Q_DISABLE_COPY(mdpResizeScaleSkewToolWrapper);

    std::unique_ptr<mdpResizeScaleSkewTool> m_resizeScaleSkewTool;
};

#endif // MDP_RESIZESCALESKEWTOOLWRAPPER_H
