#include "vipsresizescaleskewtool.h"

#include "vipshistoryentry.h"
#include "vipsmodel.h"

#include <mdpaint/history.h>

#include <cmath>
#include <functional>
#include <stdexcept>

// public
mdpVipsResizeScaleSkewTool::mdpVipsResizeScaleSkewTool(mdpVipsModel& vipsModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) :
    m_vipsModel(vipsModel),
    m_getResizeScaleSkewData(std::move(getResizeScaleSkewData)),
    m_history(history)
{
}

// public virtual
mdpVipsResizeScaleSkewTool::~mdpVipsResizeScaleSkewTool() /* override */
{
}

// public virtual
void mdpVipsResizeScaleSkewTool::activate() /* override */
{
    mdpResizeScaleSkewData resizeScaleSkewData = m_getResizeScaleSkewData();
    resizeScaleSkew(resizeScaleSkewData);
}

// public virtual
void mdpVipsResizeScaleSkewTool::deactivate() /* override */
{
}

// public virtual
void mdpVipsResizeScaleSkewTool::mousePressEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpVipsResizeScaleSkewTool::mouseReleaseEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpVipsResizeScaleSkewTool::mouseMoveEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpVipsResizeScaleSkewTool::enterEvent() /* override */
{
}

// public virtual
void mdpVipsResizeScaleSkewTool::leaveEvent() /* override */
{
}

// public virtual
void mdpVipsResizeScaleSkewTool::resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) /* override */
{
    VipsImage* const previewImage = m_vipsModel.getPreviewImage();
    const int imageWidth = vips_image_get_width(previewImage);
    const int imageHeight = vips_image_get_height(previewImage);
    const int x = resizeScaleSkewData.x;
    const int y = resizeScaleSkewData.y;
    const int width = resizeScaleSkewData.width;
    const int height = resizeScaleSkewData.height;
    const double skewX = resizeScaleSkewData.skewX;
    const double skewY = resizeScaleSkewData.skewY;
    const  double tanSkewX = std::tan(skewX);
    const  double tanSkewY = std::tan(skewY);
    double scaleX;
    double scaleY;
    gdouble offsetX = -std::min(tanSkewY * width, 0.0);
    gdouble offsetY = -std::min(tanSkewX * height, 0.0);
    if (resizeScaleSkewData.scale) {
        scaleX = width / (double)imageWidth;
        scaleY = height / (double)imageHeight;
        offsetX += x;
        offsetY += y;
    }
    else {
        scaleX = 1.0;
        scaleY = 1.0;
    }
    const int newWidth = width + std::abs(tanSkewY) * height;
    const int newHeight = height + std::abs(tanSkewX) * width;
    VipsImage* newPreviewImage;
    double xx = scaleX;
    double xy = scaleX * tanSkewY;
    double yx = scaleY * tanSkewX;
    double yy = scaleY;
    const VipsArrayInt* const area = vips_array_int_newv(4, x, y, newWidth, newHeight);
    const VipsArrayDouble* const background = vips_array_double_newv(4, 255.0, 255.0, 255.0, 255.0 );
    if (vips_affine(
            previewImage, &newPreviewImage,
            xx, xy,
            yx, yy,
            "oarea", area,
            "odx", offsetX,
            "ody", offsetY,
            "background", background,
            nullptr)) {
        vips_area_unref(VIPS_AREA(background));
        vips_area_unref(VIPS_AREA(area));
        throw std::runtime_error(vips_error_buffer());
    }
    vips_area_unref(VIPS_AREA(background));
    vips_area_unref(VIPS_AREA(area));
    try {
        m_vipsModel.beginDrawing();
        m_vipsModel.setPreview(newPreviewImage);
        m_vipsModel.endDrawing();
        //m_history.push(new mdpVipsHistoryEntry("Resize", m_vipsModel, newPreviewImage));
        m_vipsModel.submit();
        g_object_unref(newPreviewImage);
    }
    catch (...) {
        g_object_unref(newPreviewImage);
        throw;
    }
}
