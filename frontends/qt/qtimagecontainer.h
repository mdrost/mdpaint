#ifndef MDP_QTIMAGECONTAINER_H
#define MDP_QTIMAGECONTAINER_H

#include <QScrollArea>

class mdpQtImageView;
class mdpQtSelectionOverlay;
class mdpQtSizeGrip;
class mdpQtSizeOverlay;

class mdpImageModel;
class mdpSelectionTool;
class mdpTool;

class mdpQtImageContainer final : public QScrollArea
{
    Q_OBJECT

public:

    explicit mdpQtImageContainer(mdpImageModel& imageModel, QWidget* parent = nullptr);

    ~mdpQtImageContainer();

    void setTool(mdpTool* tool);

    void clearTool();

    void setSelectionTool(mdpSelectionTool* selectionTool);

    void clearSelectionTool();

Q_SIGNALS:

    void resize(const QRect& newGeometry);

private Q_SLOTS:

    void onResizeAboutToStart(const mdpQtSizeGrip* sizeGrip);

    void onResizeFinished();

private:
    Q_DISABLE_COPY(mdpQtImageContainer)

    mdpQtImageView* m_imageView;
    mdpQtSelectionOverlay* m_selectionOverlay;
    mdpQtSizeOverlay* m_sizeOverlay;
    mdpQtSizeGrip* m_topLeftSizeGrip;
    mdpQtSizeGrip* m_bottomRightSizeGrip;
    mdpQtSizeGrip* m_topSizeGrip;
    mdpQtSizeGrip* m_bottomSizeGrip;
    mdpQtSizeGrip* m_topRightSizeGrip;
    mdpQtSizeGrip* m_bottomLeftSizeGrip;
    mdpQtSizeGrip* m_leftSizeGrip;
    mdpQtSizeGrip* m_rightSizeGrip;
};

#endif // MDP_QTIMAGECONTAINER_H
