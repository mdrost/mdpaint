#ifndef MDP_QTIMAGECONTAINER_H
#define MDP_QTIMAGECONTAINER_H

#include <QScrollArea>

class mdpImageModel;
class mdpQtImageView;
class mdpQtSizeGrip;
class mdpQtSizeOverlay;
class mdpTool;

class QGridLayout;
class QSpacerItem;

class mdpQtImageContainer final : public QScrollArea
{
    Q_OBJECT

public:

    explicit mdpQtImageContainer(mdpImageModel& imageModel, QWidget* parent = nullptr);

    ~mdpQtImageContainer();

    const mdpTool* tool() const;

    void setTool(mdpTool* tool);

    void clearTool();

Q_SIGNALS:

    void resize(const QRect& newGeometry);

private Q_SLOTS:

    void onResizeAboutToStart(const mdpQtSizeGrip* sizeGrip);

    void onResizeFinished();

private:
    Q_DISABLE_COPY(mdpQtImageContainer)

    QGridLayout* m_gridLayout;
    mdpQtImageView* m_imageView;
    mdpQtSizeOverlay* m_sizeOverlay;
    mdpQtSizeGrip* m_topLeftSizeGrip;
    mdpQtSizeGrip* m_bottomRightSizeGrip;
    mdpQtSizeGrip* m_topSizeGrip;
    mdpQtSizeGrip* m_bottomSizeGrip;
    mdpQtSizeGrip* m_topRightSizeGrip;
    mdpQtSizeGrip* m_bottomLeftSizeGrip;
    mdpQtSizeGrip* m_leftSizeGrip;
    mdpQtSizeGrip* m_rightSizeGrip;
    QSpacerItem* m_spacer0;
    QSpacerItem* m_spacer1;
    QSpacerItem* m_spacer2;
    QSpacerItem* m_spacer3;
};

#endif // MDP_QTIMAGECONTAINER_H
