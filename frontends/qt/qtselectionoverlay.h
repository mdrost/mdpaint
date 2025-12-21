#ifndef MDP_QTSELECTIONOVERLAY_H
#define MDP_QTSELECTIONOVERLAY_H

#include <mdpaint/ellipse.h>
#include <mdpaint/point.h>
#include <mdpaint/rectangle.h>
#include <mdpaint/signalconnection.h>

#include <QWidget>

#include <variant>
#include <vector>

class mdpSelectionTool;

class mdpQtSelectionOverlay final : public QWidget
{
    Q_OBJECT

public:

    explicit mdpQtSelectionOverlay(QWidget* parent = nullptr);

    ~mdpQtSelectionOverlay() override;

    void setSelectionTool(const mdpSelectionTool* selectionTool);

    void clearSelectionTool();

Q_SIGNALS:

protected:

    void paintEvent(QPaintEvent* e) override;

private Q_SLOTS:

    void onSelectionToolSelectionChanged();

private:
    Q_DISABLE_COPY(mdpQtSelectionOverlay)

    const mdpSelectionTool* m_selectionTool;
    mdpSignalConnection onSelectionToolSelectionChangedConnection;
    std::variant<std::monostate, std::vector<mdpPoint>, mdpRectangle, mdpEllipse> m_selection;

};

#endif // MDP_QTSELECTIONOVERLAY_H
