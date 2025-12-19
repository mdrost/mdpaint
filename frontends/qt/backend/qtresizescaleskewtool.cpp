#include "qtresizescaleskewtool.h"

#include "qthistoryentry.h"
#include "qtmodel.h"

#include <mdpaint/history.h>

#include <QImage>
#include <QPainter>
#include <QDebug>

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
    double offsetX = -std::min(tanSkewY * height, 0.0);
    double offsetY = -std::min(tanSkewX * width, 0.0);
    if (resizeScaleSkewData.scale) {
        scaleX = width / (double)imageWidth;
        scaleY = height / (double)imageHeight;
    }
    else {
        scaleX = 1.0;
        scaleY = 1.0;
        offsetX -= x;
        offsetY -= y;
    }
    const int newWidth = width + std::abs(tanSkewY) * height;
    const int newHeight = height + std::abs(tanSkewX) * width;
    double xx = scaleX;
    double xy = scaleX * tanSkewX;
    double yx = scaleY * tanSkewY;
    double yy = scaleY;
    /*double xx = 1.0;
    double xy = tanSkewY;
    double yx = tanSkewX;
    double yy = 1.0;*/
    QTransform matrix(xx, xy, yx, yy, 0.0, 0.0);
    std::shared_ptr<QImage> newPreviewImage = std::make_shared<QImage>(previewImage->transformed(matrix));
    std::shared_ptr<QPainter> newPreviewPainter = std::make_shared<QPainter>();
    qDebug() << *newPreviewImage;
    m_qtModel.beginDrawing();
    m_qtModel.setPreview(newPreviewImage, newPreviewPainter);
    m_qtModel.endDrawing();
    //m_history.push(new mdpQtHistoryEntry("Resize", m_qtModel, std::move(newPreviewImage), std::move(newPreviewPainter)));
    m_qtModel.submit();
}
