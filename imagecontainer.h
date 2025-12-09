#ifndef MDP_IMAGECONTAINER_H
#define MDP_IMAGECONTAINER_H

#include <QScrollArea>

class mdpImageModel;
class mdpImageView;
class mdpSizeGrip;
class mdpSizeOverlay;
class mdpTool;

class QGridLayout;
class QSpacerItem;

class mdpImageContainer final : public QScrollArea
{
    Q_OBJECT

public:

    explicit mdpImageContainer(mdpImageModel& imageModel, QWidget* parent = nullptr);

    ~mdpImageContainer();

    const mdpTool* tool() const;

    void setTool(mdpTool* tool);

    void clearTool();

Q_SIGNALS:

    void resize(const QRect& newGeometry);

private Q_SLOTS:

    void onResizeAboutToStart(const mdpSizeGrip* sizeGrip);

    void onResizeFinished();

private:
    Q_DISABLE_COPY(mdpImageContainer)

    QGridLayout* m_gridLayout;
    mdpImageView* m_imageView;
    mdpSizeOverlay* m_sizeOverlay;
    mdpSizeGrip* m_topLeftSizeGrip;
    mdpSizeGrip* m_bottomRightSizeGrip;
    mdpSizeGrip* m_topSizeGrip;
    mdpSizeGrip* m_bottomSizeGrip;
    mdpSizeGrip* m_topRightSizeGrip;
    mdpSizeGrip* m_bottomLeftSizeGrip;
    mdpSizeGrip* m_leftSizeGrip;
    mdpSizeGrip* m_rightSizeGrip;
    QSpacerItem* m_spacer0;
    QSpacerItem* m_spacer1;
    QSpacerItem* m_spacer2;
    QSpacerItem* m_spacer3;
};

#endif // MDP_IMAGECONTAINER_H
