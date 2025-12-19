#ifndef MDP_QTMAINWINDOW_H
#define MDP_QTMAINWINDOW_H

#include <mdpaint/history.h>
#include <mdpaint/resizescaleskewtool.h>

#include <QMainWindow>

#include <memory>

class mdpQtColorBox;
class mdpQtHistoryView;
class mdpQtImageContainer;
class mdpQtResizeScaleSkewToolWrapper;
class mdpQtToolBox;

class mdpBackendFactory;
class mdpImageModel;

class QActionGroup;
class QGridLayout;
class QUndoStack;

class mdpQtMainWindow final : public QMainWindow
{
    Q_OBJECT

public:

    explicit mdpQtMainWindow(const std::vector<const mdpBackendFactory*>& backendFactories, QWidget* parent = nullptr);

    ~mdpQtMainWindow() override;

public Q_SLOTS:

    void showToolBox(bool visible = true);

    void showColorBox(bool visible = true);

    void showStatusBar(bool visible = true);

    void showHistoryView(bool visible = true);

    void aboutMdpaint();

private:

    mdpResizeScaleSkewData getResizeScaleSkewData();

private Q_SLOTS:

    void onImageContainerResize(const QRect& newGeometry);

    void onToolActionTriggered(QAction* action);

    void onResizeScaleSkewToolActivated();

private:
    Q_DISABLE_COPY(mdpQtMainWindow)

    const std::vector<const mdpBackendFactory*>& m_backendFactories;
    //
    mdpHistory m_history;
    QUndoStack* m_undoStack;
    std::unique_ptr<mdpImageModel> m_imageModel;
    //
    std::unique_ptr<mdpTool> m_penTool;
    std::unique_ptr<mdpTool> m_lineTool;
    std::unique_ptr<mdpTool> m_rectangleTool;
    std::unique_ptr<mdpTool> m_ellipseTool;
    std::unique_ptr<mdpQtResizeScaleSkewToolWrapper> m_resizeScaleSkewTool;
    mdpTool* m_activeTool;
    //
    mdpQtToolBox* m_toolBox;
    mdpQtColorBox* m_colorBox;
    mdpQtHistoryView* m_historyView;
    QStatusBar* m_statusBar;
    QGridLayout* m_gridLayout;
    mdpQtImageContainer* m_imageContainer;
    //
    QActionGroup* m_toolActionGroup;
    QAction* m_activeToolAction;
    QAction* m_previousActiveToolAction;
};

#endif // MDP_QTMAINWINDOW_H
