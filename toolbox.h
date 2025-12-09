#ifndef MDP_TOOLBOX_H
#define MDP_TOOLBOX_H

#include <QDockWidget>

class QGridLayout;
class QToolButton;

class mdpToolBox final : public QDockWidget
{
    Q_OBJECT

public:

    explicit mdpToolBox(QWidget* parent = nullptr);

    ~mdpToolBox() override;

    void setPenToolAction(QAction* penToolAction);

    void setLineToolAction(QAction* lineToolAction);

    void setRectangleToolAction(QAction* rectangleToolAction);

    void setEllipseToolAction(QAction* ellipseToolAction);

    void setresizeScaleSkewToolAction(QAction* resizeScaleSkewToolAction);

Q_SIGNALS:

private:
    Q_DISABLE_COPY(mdpToolBox)

    QWidget* m_widget;
    QGridLayout* m_gridLayout;
    QToolButton* m_penToolButton;
    QToolButton* m_lineToolButton;
    QToolButton* m_rectangleToolButton;
    QToolButton* m_ellipseToolButton;
    QToolButton* m_resizeScaleSkewToolButton;
};

#endif // MDP_TOOLBOX_H
