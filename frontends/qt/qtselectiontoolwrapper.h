#ifndef MDP_QTSELECTIONTOOLWRAPPER_H
#define MDP_QTSELECTIONTOOLWRAPPER_H

#include <mdpaint/selectiontool.h>

#include <QObject>

#include <memory>

class mdpQtSelectionToolWrapper final : public QObject, public mdpSelectionTool
{
    Q_OBJECT

public:

    explicit mdpQtSelectionToolWrapper(std::unique_ptr<mdpSelectionTool> selectionTool);

    ~mdpQtSelectionToolWrapper() override;

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

    void postActivate();

    void preDeactivate();

private:
    Q_DISABLE_COPY(mdpQtSelectionToolWrapper);

    std::unique_ptr<mdpSelectionTool> m_selectionTool;
};

#endif // MDP_QTSELECTIONTOOLWRAPPER_H
