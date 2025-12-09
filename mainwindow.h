#ifndef MDP_MAINWINDOW_H
#define MDP_MAINWINDOW_H

#include <mdpaint/history.h>
#include <mdpaint/resizescaleskewtool.h>

#include <QMainWindow>

#include <memory>

class mdpColorBox;
class mdpHistoryView;
class mdpImageContainer;
class mdpImageModel;
class mdpResizeScaleSkewToolWrapper;
class mdpToolBox;

class QActionGroup;
class QGridLayout;
class QUndoStack;

class mdpMainWindow final : public QMainWindow
{
    Q_OBJECT

public:

    explicit mdpMainWindow(QWidget* parent = nullptr);

    ~mdpMainWindow() override;

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
    Q_DISABLE_COPY(mdpMainWindow)

    mdpHistory m_history;
    QUndoStack* m_undoStack;
    std::unique_ptr<mdpImageModel> m_imageModel;
    //
    std::unique_ptr<mdpTool> m_penTool;
    std::unique_ptr<mdpTool> m_lineTool;
    std::unique_ptr<mdpTool> m_rectangleTool;
    std::unique_ptr<mdpTool> m_ellipseTool;
    std::unique_ptr<mdpResizeScaleSkewToolWrapper> m_resizeScaleSkewTool;
    mdpTool* m_activeTool;
    //
    mdpToolBox* m_toolBox;
    mdpColorBox* m_colorBox;
    mdpHistoryView* m_historyView;
    QStatusBar* m_statusBar;
    QGridLayout* m_gridLayout;
    mdpImageContainer* m_imageContainer;
    //
    QActionGroup* m_toolActionGroup;
    QAction* m_activeToolAction;
    QAction* m_previousActiveToolAction;
};

#endif // MDP_MAINWINDOW_H
