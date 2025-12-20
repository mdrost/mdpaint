#include "qtresizescaleskewtool.h"

#include "qthistoryentry.h"
#include "qtmodel.h"

#include <mdpaint/history.h>

#include <QImage>
#include <QPainter>

#include <cmath>
#include <functional>

// public
mdpQtResizeScaleSkewTool::mdpQtResizeScaleSkewTool(mdpQtModel& qtModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) :
    m_qtModel(qtModel),
    m_getResizeScaleSkewData(std::move(getResizeScaleSkewData)),
    m_history(history)
{
}

// public virtual
mdpQtResizeScaleSkewTool::~mdpQtResizeScaleSkewTool() /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::activate() /* override */
{
    mdpResizeScaleSkewData resizeScaleSkewData = m_getResizeScaleSkewData();
    resizeScaleSkew(resizeScaleSkewData);
}

// public virtual
void mdpQtResizeScaleSkewTool::deactivate() /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::mousePressEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::mouseReleaseEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::mouseMoveEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::enterEvent() /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::leaveEvent() /* override */
{
}

// public virtual
void mdpQtResizeScaleSkewTool::resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) /* override */
{
    const QImage* previewImage = m_qtModel.getPreviewImage().get();
    const int imageWidth = previewImage->width();
    const int imageHeight = previewImage->height();
    const double x = resizeScaleSkewData.x;
    const double y = resizeScaleSkewData.y;
    const int width = resizeScaleSkewData.width;
    const int height = resizeScaleSkewData.height;
    const double skewX = resizeScaleSkewData.skewX;
    const double skewY = resizeScaleSkewData.skewY;
    const  double tanSkewX = std::tan(skewX);
    const  double tanSkewY = std::tan(skewY);
    double scaleX;
    double scaleY;
    //double offsetX = -std::min(tanSkewX * height, 0.0);
    //double offsetY = -std::min(tanSkewY * width, 0.0);
    if (resizeScaleSkewData.scale) {
        scaleX = width / (double)imageWidth;
        scaleY = height / (double)imageHeight;
    }
    else {
        scaleX = 1.0;
        scaleY = 1.0;
        //offsetX -= x;
        //offsetY -= y;
    }
    const int newWidth = width + std::abs(tanSkewX) * height;
    const int newHeight = height + std::abs(tanSkewY) * width;
    const double xx = scaleX;
    const double xy = scaleY * tanSkewX;
    const double yx = scaleX * tanSkewY;
    const double yy = scaleY;
    const QTransform matrix(xx, yx, xy, yy, 0.0, 0.0);
    QImage newPreviewImageTmp = previewImage->transformed(matrix, Qt::SmoothTransformation);
    std::shared_ptr<QImage> newPreviewImage = std::make_shared<QImage>(newWidth, newHeight, newPreviewImageTmp.format());
    newPreviewImage->fill(Qt::white);
    std::shared_ptr<QPainter> newPreviewPainter = std::make_shared<QPainter>(newPreviewImage.get());
    newPreviewPainter->drawImage(QPointF(-x, -y), newPreviewImageTmp);
    newPreviewPainter->end();
    m_qtModel.beginDrawing();
    m_qtModel.setPreview(newPreviewImage, newPreviewPainter);
    m_qtModel.endDrawing();
    //m_history.push(new mdpQtHistoryEntry("Resize", m_qtModel, std::move(newPreviewImage), std::move(newPreviewPainter)));
    m_qtModel.submit();
}
