#include "imagecontainer.h"

#include "imageview.h"
#include "sizegrip.h"
#include "sizeoverlay.h"

#include <QGridLayout>
#include <QSpacerItem>

// public
mdpImageContainer::mdpImageContainer(mdpImageModel& imageModel, QWidget* parent) :
    QScrollArea(parent)
{
    const QSize sizeGripMinimumSize(25, 25);

    QWidget* widget = new QWidget(viewport());
    widget->setObjectName(QStringLiteral("widget"));
    setWidget(widget);

    m_gridLayout = new QGridLayout(widget);
    m_gridLayout->setObjectName(QStringLiteral("gridLayout"));
    m_gridLayout->setSpacing(0);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);

    m_imageView = new mdpImageView(imageModel, widget);
    m_imageView->setObjectName(QStringLiteral("image"));
    m_gridLayout->addWidget(m_imageView, 2, 2, Qt::AlignCenter);

    m_sizeOverlay = new mdpSizeOverlay(widget);
    m_sizeOverlay->setVisible(false);

    m_topLeftSizeGrip = new mdpSizeGrip(mdpSizeGrip::TopLeft, m_sizeOverlay, widget);
    m_topLeftSizeGrip->setObjectName(QStringLiteral("topLeftSizeGrip"));
    m_topLeftSizeGrip->setMinimumSize(sizeGripMinimumSize);
#ifndef QT_NO_CURSOR
    m_topLeftSizeGrip->setCursor(QCursor(Qt::SizeFDiagCursor));
#endif
    m_gridLayout->addWidget(m_topLeftSizeGrip, 1, 1, Qt::AlignRight | Qt::AlignBottom);

    m_bottomRightSizeGrip = new mdpSizeGrip(mdpSizeGrip::BottomRight, m_sizeOverlay, widget);
    m_bottomRightSizeGrip->setObjectName(QStringLiteral("bottomRightSizeGrip"));
    m_bottomRightSizeGrip->setMinimumSize(sizeGripMinimumSize);
#ifndef QT_NO_CURSOR
    m_bottomRightSizeGrip->setCursor(QCursor(Qt::SizeFDiagCursor));
#endif
    m_gridLayout->addWidget(m_bottomRightSizeGrip, 3, 3, Qt::AlignLeft | Qt::AlignTop);

    m_topSizeGrip = new mdpSizeGrip(mdpSizeGrip::Top, m_sizeOverlay, widget);
    m_topSizeGrip->setObjectName(QStringLiteral("topSizeGrip"));
    m_topSizeGrip->setMinimumSize(sizeGripMinimumSize);
#ifndef QT_NO_CURSOR
    m_topSizeGrip->setCursor(QCursor(Qt::SizeVerCursor));
#endif
    m_gridLayout->addWidget(m_topSizeGrip, 1, 2, Qt::AlignHCenter | Qt::AlignBottom);

    m_bottomSizeGrip = new mdpSizeGrip(mdpSizeGrip::Bottom, m_sizeOverlay, widget);
    m_bottomSizeGrip->setObjectName(QStringLiteral("bottomSizeGrip"));
    m_bottomSizeGrip->setMinimumSize(sizeGripMinimumSize);
#ifndef QT_NO_CURSOR
    m_bottomSizeGrip->setCursor(QCursor(Qt::SizeVerCursor));
#endif
    m_gridLayout->addWidget(m_bottomSizeGrip, 3, 2, Qt::AlignHCenter | Qt::AlignTop);

    m_topRightSizeGrip = new mdpSizeGrip(mdpSizeGrip::TopRight, m_sizeOverlay, widget);
    m_topRightSizeGrip->setObjectName(QStringLiteral("topRightSizeGrip"));
    m_topRightSizeGrip->setMinimumSize(sizeGripMinimumSize);
#ifndef QT_NO_CURSOR
    m_topRightSizeGrip->setCursor(QCursor(Qt::SizeBDiagCursor));
#endif
    m_gridLayout->addWidget(m_topRightSizeGrip, 1, 3, Qt::AlignLeft | Qt::AlignBottom);

    m_bottomLeftSizeGrip = new mdpSizeGrip(mdpSizeGrip::BottomLeft, m_sizeOverlay, widget);
    m_bottomLeftSizeGrip->setObjectName(QStringLiteral("bottomLeftSizeGrip"));
    m_bottomLeftSizeGrip->setMinimumSize(sizeGripMinimumSize);
#ifndef QT_NO_CURSOR
    m_bottomLeftSizeGrip->setCursor(QCursor(Qt::SizeBDiagCursor));
#endif
    m_gridLayout->addWidget(m_bottomLeftSizeGrip, 3, 1, Qt::AlignRight | Qt::AlignTop);

    m_leftSizeGrip = new mdpSizeGrip(mdpSizeGrip::Left, m_sizeOverlay, widget);
    m_leftSizeGrip->setObjectName(QStringLiteral("leftSizeGrip"));
    m_leftSizeGrip->setMinimumSize(sizeGripMinimumSize);
#ifndef QT_NO_CURSOR
    m_leftSizeGrip->setCursor(QCursor(Qt::SizeHorCursor));
#endif
    m_gridLayout->addWidget(m_leftSizeGrip, 2, 1, Qt::AlignRight | Qt::AlignVCenter);

    m_rightSizeGrip = new mdpSizeGrip(mdpSizeGrip::Right, m_sizeOverlay, widget);
    m_rightSizeGrip->setObjectName(QStringLiteral("rightSizeGrip"));
    m_rightSizeGrip->setMinimumSize(sizeGripMinimumSize);
#ifndef QT_NO_CURSOR
    m_rightSizeGrip->setCursor(QCursor(Qt::SizeHorCursor));
#endif
    m_gridLayout->addWidget(m_rightSizeGrip, 2, 3, Qt::AlignLeft | Qt::AlignVCenter);

    m_spacer0 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_gridLayout->addItem(m_spacer0, 0, 2);
    m_spacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_gridLayout->addItem(m_spacer1, 2, 0);
    m_spacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_gridLayout->addItem(m_spacer2, 2, 4);
    m_spacer3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_gridLayout->addItem(m_spacer3, 4, 2);

    // TODO: maybe instead of passing SizeGrip we should use QObject::sender()?
    connect(m_topLeftSizeGrip, &mdpSizeGrip::resizeAboutToStart, this, [=, this]() {
        onResizeAboutToStart(m_topLeftSizeGrip);
    });
    connect(m_bottomRightSizeGrip, &mdpSizeGrip::resizeAboutToStart, this, [=, this]() {
        onResizeAboutToStart(m_bottomRightSizeGrip);
    });
    connect(m_topSizeGrip, &mdpSizeGrip::resizeAboutToStart, this, [=, this]() {
        onResizeAboutToStart(m_topSizeGrip);
    });
    connect(m_bottomSizeGrip, &mdpSizeGrip::resizeAboutToStart, this, [=, this]() {
        onResizeAboutToStart(m_bottomSizeGrip);
    });
    connect(m_topRightSizeGrip, &mdpSizeGrip::resizeAboutToStart, this, [=, this]() {
        onResizeAboutToStart(m_topRightSizeGrip);
    });
    connect(m_bottomLeftSizeGrip, &mdpSizeGrip::resizeAboutToStart, this, [=, this]() {
        onResizeAboutToStart(m_bottomLeftSizeGrip);
    });
    connect(m_leftSizeGrip, &mdpSizeGrip::resizeAboutToStart, this, [=, this]() {
        onResizeAboutToStart(m_leftSizeGrip);
    });
    connect(m_rightSizeGrip, &mdpSizeGrip::resizeAboutToStart, this, [=, this]() {
        onResizeAboutToStart(m_rightSizeGrip);
    });

    connect(m_topLeftSizeGrip, &mdpSizeGrip::resizeFinished, this, &mdpImageContainer::onResizeFinished);
    connect(m_bottomRightSizeGrip, &mdpSizeGrip::resizeFinished, this, &mdpImageContainer::onResizeFinished);
    connect(m_topSizeGrip, &mdpSizeGrip::resizeFinished, this, &mdpImageContainer::onResizeFinished);
    connect(m_bottomSizeGrip, &mdpSizeGrip::resizeFinished, this, &mdpImageContainer::onResizeFinished);
    connect(m_topRightSizeGrip, &mdpSizeGrip::resizeFinished, this, &mdpImageContainer::onResizeFinished);
    connect(m_bottomLeftSizeGrip, &mdpSizeGrip::resizeFinished, this, &mdpImageContainer::onResizeFinished);
    connect(m_leftSizeGrip, &mdpSizeGrip::resizeFinished, this, &mdpImageContainer::onResizeFinished);
    connect(m_rightSizeGrip, &mdpSizeGrip::resizeFinished, this, &mdpImageContainer::onResizeFinished);
}

// public virtual
mdpImageContainer::~mdpImageContainer() /* override */
{
}

// public
const mdpTool* mdpImageContainer::tool() const
{
    return m_imageView->tool();
}

// public
void mdpImageContainer::setTool(mdpTool* tool)
{
    m_imageView->setTool(tool);
}

// public
void mdpImageContainer::clearTool()
{
    m_imageView->clearTool();
}

// private slot
void mdpImageContainer::onResizeAboutToStart(const mdpSizeGrip* sizeGrip)
{
    m_sizeOverlay->setType(sizeGrip->type());
    QRect newGeo = m_imageView->geometry();
    newGeo.setTopLeft(newGeo.topLeft() - QPoint(2, 2));
    newGeo.setBottomRight(newGeo.bottomRight() + QPoint(2, 2));
    m_sizeOverlay->setGeometry(newGeo);
    m_sizeOverlay->setVisible(true);
}

// private slot
void mdpImageContainer::onResizeFinished()
{
    m_sizeOverlay->setVisible(false);
    QRect newGeo = m_sizeOverlay->geometry();
    // TODO: can this geometry rearrangment be prettier?
    const QPoint topLeft = m_imageView->geometry().topLeft();
    newGeo.setTopLeft(newGeo.topLeft() + QPoint(2, 2) - topLeft);
    newGeo.setBottomRight(newGeo.bottomRight() - QPoint(2, 2) - topLeft);
    Q_EMIT resize(newGeo);
}
