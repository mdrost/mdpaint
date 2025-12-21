#ifndef MDP_QTTOOLBOX_H
#define MDP_QTTOOLBOX_H

#include <QDockWidget>

class QGridLayout;
class QToolButton;

class mdpQtToolBox final : public QDockWidget
{
    Q_OBJECT

public:

    explicit mdpQtToolBox(QWidget* parent = nullptr);

    ~mdpQtToolBox() override;

    void setFreeFormSelectionToolAction(QAction* freeFormSelectionToolAction);

    void setRectangularSelectionToolAction(QAction* rectangularSelectionToolAction);

    void setEllipticalSelectionToolAction(QAction* ellipticalSelectionToolAction);

    void setPenToolAction(QAction* penToolAction);

    void setLineToolAction(QAction* lineToolAction);

    void setRectangleToolAction(QAction* rectangleToolAction);

    void setEllipseToolAction(QAction* ellipseToolAction);

    void setresizeScaleSkewToolAction(QAction* resizeScaleSkewToolAction);

Q_SIGNALS:

private:
    Q_DISABLE_COPY(mdpQtToolBox)

    QGridLayout* m_gridLayout;
    QToolButton* m_freeFormSelectionToolButton;
    QToolButton* m_rectangularSelectionToolButton;
    QToolButton* m_ellipticalSelectionToolButton;
    QToolButton* m_penToolButton;
    QToolButton* m_lineToolButton;
    QToolButton* m_rectangleToolButton;
    QToolButton* m_ellipseToolButton;
    QToolButton* m_resizeScaleSkewToolButton;
};

#endif // MDP_QTTOOLBOX_H
