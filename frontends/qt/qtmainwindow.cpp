#include "qtmainwindow.h"

#include "qtcolorbox.h"
#include "qthistoryview.h"
#include "qtimagecontainer.h"
#include "qtresizescaleskewdialog.h"
#include "qtresizescaleskewtoolwrapper.h"
#include "qttoolaction.h"
#include "qttoolbox.h"

#include <mdpaint/backendfactory.h>

#include <QActionGroup>
#include <QApplication>
#include <QGridLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QUndoStack>

#include <functional>

// public
mdpQtMainWindow::mdpQtMainWindow(const std::vector<const mdpBackendFactory*>& backendFactories, QWidget* parent) :
    QMainWindow(parent),
    m_backendFactories(backendFactories)
{
    setWindowTitle(tr("MD Paint"));
    setContextMenuPolicy(Qt::NoContextMenu);
    setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowNestedDocks);

    const mdpBackendFactory* const backendFactory = backendFactories[0];
    m_undoStack = new QUndoStack(this);
    m_imageModel = backendFactory->createImageModel();

    m_penTool = backendFactory->createPenTool(*m_imageModel, m_history);
    m_lineTool = backendFactory->createLineTool(*m_imageModel, m_history);
    m_rectangleTool = backendFactory->createRectangleTool(*m_imageModel, m_history);
    m_ellipseTool = backendFactory->createEllipseTool(*m_imageModel, m_history);
    std::unique_ptr<mdpResizeScaleSkewTool> resizeScaleSkewTool = backendFactory->createResizeScaleSkewTool(*m_imageModel, std::bind(&mdpQtMainWindow::getResizeScaleSkewData, this), m_history);
    m_resizeScaleSkewTool = std::make_unique<mdpQtResizeScaleSkewToolWrapper>(std::move(resizeScaleSkewTool));
    connect(m_resizeScaleSkewTool.get(), &mdpQtResizeScaleSkewToolWrapper::activated, this, &mdpQtMainWindow::onResizeScaleSkewToolActivated);
    m_activeTool = nullptr;

    QMenuBar* menubar = menuBar(); // create menu bar
    menubar->setObjectName(QStringLiteral("menuBar"));
    QMenu* fileMenu = menubar->addMenu(tr("&File"));
    fileMenu->setObjectName(QStringLiteral("fileMenu"));
    QMenu* editMenu = menubar->addMenu(tr("&Edit"));
    editMenu->setObjectName(QStringLiteral("editMenu"));
    QMenu* viewMenu = menubar->addMenu(tr("&View"));
    viewMenu->setObjectName(QStringLiteral("viewMenu"));
    QMenu* helpMenu = menubar->addMenu(tr("&Help"));
    helpMenu->setObjectName(QStringLiteral("helpMenu"));

    QAction* newFileAction = new QAction(tr("&New"), this);
    newFileAction->setObjectName(QStringLiteral("newFileAction"));
    newFileAction->setIcon(QIcon::fromTheme(QStringLiteral("document-new"), QIcon(QStringLiteral(":/icons/document-new.png"))));
#if QT_CONFIG(shortcut)
    newFileAction->setShortcuts(QKeySequence::New);
#endif
    newFileAction->setStatusTip(tr("Create a new file."));
    //connect(newFileAction, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newFileAction);

    fileMenu->addSeparator();

    QAction* exitAction = new QAction(tr("E&xit"), this);
    exitAction->setObjectName(QStringLiteral("exitAction"));
    exitAction->setIcon(QIcon::fromTheme(QStringLiteral("application-exit"), QIcon(QStringLiteral(":/icons/application-exit.png"))));
#if QT_CONFIG(shortcut)
    exitAction->setShortcuts(QKeySequence::Close); // QKeySequence::Quit seems to do nothing
#endif
    exitAction->setStatusTip(tr("Exit the application."));
    connect(exitAction, &QAction::triggered, this, &mdpQtMainWindow::close);
    fileMenu->addAction(exitAction);

    QAction* undoAction = m_undoStack->createUndoAction(this);
    undoAction->setObjectName(QStringLiteral("undoAction"));
    undoAction->setText(tr("Undo"));
    undoAction->setIcon(QIcon::fromTheme(QStringLiteral("edit-undo"), QIcon(QStringLiteral(":/icons/edit-undo.png"))));
#if QT_CONFIG(shortcut)
    undoAction->setShortcuts(QKeySequence::Undo);
#endif
    undoAction->setStatusTip(tr("Undo the last action."));
    editMenu->addAction(undoAction);

    QAction* redoAction = m_undoStack->createRedoAction(this);
    redoAction->setObjectName(QStringLiteral("redoAction"));
    redoAction->setText(tr("Redo"));
    redoAction->setIcon(QIcon::fromTheme(QStringLiteral("edit-redo"), QIcon(QStringLiteral(":/icons/edit-redo.png"))));
#if QT_CONFIG(shortcut)
    redoAction->setShortcuts(QKeySequence::Redo);
#endif
    redoAction->setStatusTip(tr("Redo the previously undone action."));
    editMenu->addAction(redoAction);

    QAction* showToolBoxAction = new QAction(tr("Tool Box"), this);
    showToolBoxAction->setObjectName(QStringLiteral("showToolBoxAction"));
    showToolBoxAction->setCheckable(true);
    showToolBoxAction->setChecked(true);
    showToolBoxAction->setStatusTip(tr("Show or hide the tool box."));
    connect(showToolBoxAction, &QAction::triggered, this, &mdpQtMainWindow::showToolBox);
    viewMenu->addAction(showToolBoxAction);

    QAction* showColorBoxAction = new QAction(tr("Color Box"), this);
    showColorBoxAction->setObjectName(QStringLiteral("showColorBoxAction"));
    showColorBoxAction->setCheckable(true);
    showColorBoxAction->setChecked(true);
    showColorBoxAction->setStatusTip(tr("Show or hide the color box."));
    connect(showColorBoxAction, &QAction::triggered, this, &mdpQtMainWindow::showColorBox);
    viewMenu->addAction(showColorBoxAction);

    QAction* showHistoryViewAction = new QAction(tr("History"), this);
    showHistoryViewAction->setObjectName(QStringLiteral("showHistoryViewAction"));
    showHistoryViewAction->setCheckable(true);
    showHistoryViewAction->setChecked(false);
    showHistoryViewAction->setStatusTip(tr("Show or hide the history."));
    connect(showHistoryViewAction, &QAction::triggered, this, &mdpQtMainWindow::showHistoryView);
    viewMenu->addAction(showHistoryViewAction);

    QAction* showStatusBarAction = new QAction(tr("Status Bar"), this);
    showStatusBarAction->setObjectName(QStringLiteral("showStatusBarAction"));
    showStatusBarAction->setCheckable(true);
    showStatusBarAction->setChecked(true);
    showStatusBarAction->setStatusTip(tr("Show or hide the status bar."));
    connect(showStatusBarAction, &QAction::triggered, this, &mdpQtMainWindow::showStatusBar);
    viewMenu->addAction(showStatusBarAction);

    QAction* aboutMdpaintAction = helpMenu->addAction(tr("About &MD Paint"), this, &mdpQtMainWindow::aboutMdpaint);
    aboutMdpaintAction->setObjectName(QStringLiteral("aboutMdpaintAction"));
    aboutMdpaintAction->setIcon(QIcon(QStringLiteral(":/icons/mdpaint.png")));
    aboutMdpaintAction->setStatusTip(tr("Show the MD Paint's About box."));

    QAction* aboutQtAction = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAction->setObjectName(QStringLiteral("aboutQtAction"));
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box."));

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    setCentralWidget(centralWidget);

    m_toolBox = new mdpQtToolBox(this);
    m_toolBox->setObjectName(QStringLiteral("toolBox"));
    m_toolBox->setVisible(showToolBoxAction->isChecked());
    addDockWidget(Qt::LeftDockWidgetArea, m_toolBox);

    m_colorBox = new mdpQtColorBox(this);
    m_colorBox->setObjectName(QStringLiteral("colorBox"));
    m_colorBox->setVisible(showColorBoxAction->isChecked());
    addDockWidget(Qt::BottomDockWidgetArea, m_colorBox);

    m_historyView = new mdpQtHistoryView(m_undoStack, this);
    m_historyView->setObjectName(QStringLiteral("historyView"));
    m_historyView->setVisible(showHistoryViewAction->isChecked());
    addDockWidget(Qt::RightDockWidgetArea, m_historyView);

    m_statusBar = statusBar(); // create status bar
    m_statusBar->setObjectName(QStringLiteral("statusBar"));
    m_statusBar->setVisible(showStatusBarAction->isChecked());

    m_gridLayout = new QGridLayout(centralWidget);
    m_gridLayout->setObjectName(QStringLiteral("gridLayout"));
    m_gridLayout->setSpacing(0);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);

    m_imageContainer = new mdpQtImageContainer(*m_imageModel, centralWidget);
    m_imageContainer->setObjectName(QStringLiteral("imageContainer"));
    m_imageContainer->setWidgetResizable(true);
    //m_imageContainer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //m_imageContainer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_gridLayout->addWidget(m_imageContainer, 0, 0, 1, 1);
    connect(m_imageContainer, &mdpQtImageContainer::resize, this, &mdpQtMainWindow::onImageContainerResize);

    m_toolActionGroup = new QActionGroup(this);
    m_toolActionGroup->setObjectName(QStringLiteral("toolActionGroup"));
    m_toolActionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::Exclusive);
    connect(m_toolActionGroup, &QActionGroup::triggered, this, &mdpQtMainWindow::onToolActionTriggered);

    mdpQtToolAction* penToolAction = new mdpQtToolAction(tr("Pen"), this);
    penToolAction->setObjectName(QStringLiteral("penToolAction"));
    penToolAction->setTool(m_penTool.get());
    penToolAction->setCheckable(true);
    penToolAction->setIcon(QIcon(QStringLiteral(":/icons/tool-pen.png")));
    penToolAction->setStatusTip(tr("Draw a free-form line."));
    m_toolBox->setPenToolAction(penToolAction);
    m_toolActionGroup->addAction(penToolAction);

    mdpQtToolAction* lineToolAction = new mdpQtToolAction(tr("Line"), this);
    lineToolAction->setObjectName(QStringLiteral("lineToolAction"));
    lineToolAction->setTool(m_lineTool.get());
    lineToolAction->setCheckable(true);
    lineToolAction->setIcon(QIcon(QStringLiteral(":/icons/tool-line.png")));
    lineToolAction->setStatusTip(tr("Draw a straight line."));
    m_toolBox->setLineToolAction(lineToolAction);
    m_toolActionGroup->addAction(lineToolAction);

    mdpQtToolAction* rectangleToolAction = new mdpQtToolAction(tr("Rectangle"), this);
    rectangleToolAction->setObjectName(QStringLiteral("rectangleToolAction"));
    rectangleToolAction->setTool(m_rectangleTool.get());
    rectangleToolAction->setCheckable(true);
    rectangleToolAction->setIcon(QIcon(QStringLiteral(":/icons/tool-rectangle.png")));
    rectangleToolAction->setStatusTip(tr("Draw a rectangle."));
    m_toolBox->setRectangleToolAction(rectangleToolAction);
    m_toolActionGroup->addAction(rectangleToolAction);

    mdpQtToolAction* ellipseToolAction = new mdpQtToolAction(tr("Ellipse"), this);
    ellipseToolAction->setObjectName(QStringLiteral("ellipseToolAction"));
    ellipseToolAction->setTool(m_ellipseTool.get());
    ellipseToolAction->setCheckable(true);
    ellipseToolAction->setIcon(QIcon(QStringLiteral(":/icons/tool-ellipse.png")));
    ellipseToolAction->setStatusTip(tr("Draw an ellipse."));
    m_toolBox->setEllipseToolAction(ellipseToolAction);
    m_toolActionGroup->addAction(ellipseToolAction);

    mdpQtToolAction* resizeScaleSkewToolAction = new mdpQtToolAction(tr("Resize/Scale/Skew"), this);
    resizeScaleSkewToolAction->setObjectName(QStringLiteral("resizeScaleSkewToolAction"));
    resizeScaleSkewToolAction->setTool(m_resizeScaleSkewTool.get());
    resizeScaleSkewToolAction->setCheckable(true);
    resizeScaleSkewToolAction->setIcon(QIcon(QStringLiteral(":/icons/tool-resizescaleskew.png")));
    resizeScaleSkewToolAction->setStatusTip(tr("Resize, scale and skew the image."));
    m_toolBox->setresizeScaleSkewToolAction(resizeScaleSkewToolAction);
    m_toolActionGroup->addAction(resizeScaleSkewToolAction);

    m_activeToolAction = nullptr;
    m_previousActiveToolAction = nullptr;

    //penToolAction->trigger();
}

// public virtual
mdpQtMainWindow::~mdpQtMainWindow() /* override */
{
}

// public slot
void mdpQtMainWindow::showToolBox(bool visible)
{
    m_toolBox->setVisible(visible);
}

// public slot
void mdpQtMainWindow::showColorBox(bool visible)
{
    m_colorBox->setVisible(visible);
}

// public slot
void mdpQtMainWindow::showHistoryView(bool visible)
{
    m_historyView->setVisible(visible);
}

// public slot
void mdpQtMainWindow::showStatusBar(bool visible)
{
    m_statusBar->setVisible(visible);
}

// public slot
void mdpQtMainWindow::aboutMdpaint()
{
}

// private
mdpResizeScaleSkewData mdpQtMainWindow::getResizeScaleSkewData()
{
    mdpQtResizeScaleSkewDialog dialog(m_imageModel->width(), m_imageModel->height());
    dialog.exec();
    return dialog.getResizeScaleSkewData();
}

// private slot
void mdpQtMainWindow::onImageContainerResize(const QRect& newGeometry)
{
    mdpResizeScaleSkewData resizeScaleSkewData = {
        //.x = newGeometry.x(),
        //.y = newGeometry.y(),
        //.width = newGeometry.width(),
        //.height = newGeometry.height(),
        //.scale = false,
        //.skewX = 0.0,
        //.skewY = 0.0
        .x = 32,
        .y = 16,
        .width = 192,
        .height = 64,
        .scale = true,
        //.skewX = 0 * M_PI / 180.0,
        //.skewY = 26.565 * M_PI / 180.0
        .skewX = -45 * M_PI / 180.0,
        .skewY = -0 * M_PI / 180.0
        //.skewX = 0 * M_PI / 180.0,
        //.skewY = 60 * M_PI / 180.0
    };
    m_resizeScaleSkewTool->resizeScaleSkew(resizeScaleSkewData);
}

// private slot
void mdpQtMainWindow::onToolActionTriggered(QAction* action)
{
    if (m_activeTool != nullptr) {
        m_activeTool->deactivate();
    }
    mdpQtToolAction* toolAction = qobject_cast<mdpQtToolAction*>(action);
    mdpTool* tool = nullptr;
    if (toolAction != nullptr) {
        tool = toolAction->tool();
    }
    m_activeTool = tool;
    m_previousActiveToolAction = m_activeToolAction;
    m_activeToolAction = action;
    if (tool != nullptr) {
        m_imageContainer->setTool(tool);
        tool->activate();
    }
    else {
        m_imageContainer->clearTool();
    }
}

void mdpQtMainWindow::onResizeScaleSkewToolActivated()
{
    if (m_previousActiveToolAction != nullptr && m_previousActiveToolAction != m_activeToolAction) {
        m_previousActiveToolAction->trigger();
    }
}
