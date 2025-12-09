#ifndef MDP_SIZEGRIP_H
#define MDP_SIZEGRIP_H

#include <QWidget>

class mdpSizeGrip final : public QWidget
{
    Q_OBJECT

public:
    enum Type // TODO: find better name?
    {
        //None,
        TopLeft,
        BottomRight,
        Top,
        Bottom,
        TopRight,
        BottomLeft,
        Left,
        Right,
    };

public:

    explicit mdpSizeGrip(Type type, QWidget* resizable, QWidget* parent = nullptr);

    ~mdpSizeGrip() override;

    Type type() const;

    QSize sizeHint() const override;

Q_SIGNALS:

    void resizeAboutToStart();

    void resizeFinished();

protected:

    void mousePressEvent(QMouseEvent* e) override;

    void mouseReleaseEvent(QMouseEvent* e) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void paintEvent(QPaintEvent* e) override;

private:
    Q_DISABLE_COPY(mdpSizeGrip)

    Type m_type;
    QWidget* m_resizable;
    bool m_resizing;
    QRect m_startResizableGeometry;
    QPointF m_startMousePosition;
};

#endif // MDP_SIZEGRIP_H
