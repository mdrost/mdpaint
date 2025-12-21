#ifndef MDP_QTIMAGEVIEW_H
#define MDP_QTIMAGEVIEW_H

#include <mdpaint/signalconnection.h>

#include <QImage>
#include <QWidget>

class mdpImageModel;
class mdpTool;

class mdpQtImageView final : public QWidget
{
    Q_OBJECT

public:

    explicit mdpQtImageView(mdpImageModel& imageModel, QWidget* parent = nullptr);

    ~mdpQtImageView();

    QSize sizeHint() const override;

    //const mdpTool* tool() const;

    void setTool(mdpTool* tool);

    void clearTool();

Q_SIGNALS:

protected:

    void mousePressEvent(QMouseEvent* e) override;

    void mouseReleaseEvent(QMouseEvent* e) override;

    void mouseMoveEvent(QMouseEvent* e) override;

#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent* e) override;
#endif

    void enterEvent(QEnterEvent *e) override;

    void leaveEvent(QEvent *e) override;

    void paintEvent(QPaintEvent* e) override;

private Q_SLOTS:

    void onImageModelDataChanged();

    void onImageModelDataReset();

private:
    Q_DISABLE_COPY(mdpQtImageView)

    mdpImageModel& m_imageModel;
    QImage m_image;
    mdpTool* m_tool;
    mdpSignalConnection onImageModelDataChangedConnection;
    mdpSignalConnection onImageModelDataResetConnection;
};

#endif // MDP_QTIMAGEVIEW_H
