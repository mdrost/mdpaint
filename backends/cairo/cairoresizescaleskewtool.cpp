#include "cairoresizescaleskewtool.h"

#include "cairohistoryentry.h"
#include "cairomodel.h"

#include <mdpaint/history.h>

#include <cmath>
#include <functional>
#include <stdexcept>

// public
mdpCairoResizeScaleSkewTool::mdpCairoResizeScaleSkewTool(mdpCairoModel& cairoModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) :
    m_cairoModel(cairoModel),
    m_getResizeScaleSkewData(std::move(getResizeScaleSkewData)),
    m_history(history)
{
}

// public virtual
mdpCairoResizeScaleSkewTool::~mdpCairoResizeScaleSkewTool() /* override */
{
}

// public virtual
void mdpCairoResizeScaleSkewTool::activate() /* override */
{
    mdpResizeScaleSkewData resizeScaleSkewData = m_getResizeScaleSkewData();
    resizeScaleSkew(resizeScaleSkewData);
}

// public virtual
void mdpCairoResizeScaleSkewTool::deactivate() /* override */
{
}

// public virtual
void mdpCairoResizeScaleSkewTool::mousePressEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpCairoResizeScaleSkewTool::mouseReleaseEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpCairoResizeScaleSkewTool::mouseMoveEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpCairoResizeScaleSkewTool::enterEvent() /* override */
{
}

// public virtual
void mdpCairoResizeScaleSkewTool::leaveEvent() /* override */
{
}

// public virtual
void mdpCairoResizeScaleSkewTool::resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleSkewData) /* override */
{
    cairo_surface_t* previewSurface = m_cairoModel.getPreviewSurface();
    const int imageWidth = cairo_image_surface_get_width(previewSurface);
    const int imageHeight = cairo_image_surface_get_height(previewSurface);
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
    double offsetX = -std::min(tanSkewY * width, 0.0);
    double offsetY = -std::min(tanSkewX * height, 0.0);
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
    const int newWidth = width + std::abs(tanSkewY) * width;
    const int newHeight = height + std::abs(tanSkewX) * height;
    cairo_surface_t* newPreviewSurface = cairo_surface_create_similar_image(
        previewSurface,
        cairo_image_surface_get_format(previewSurface),
        newWidth,
        newHeight
    );
    cairo_t* newPreviewContext = cairo_create(newPreviewSurface);
    cairo_save(newPreviewContext);
    cairo_set_operator(newPreviewContext, CAIRO_OPERATOR_SOURCE);
    cairo_set_source_surface(newPreviewContext, previewSurface, 0.0, 0.0);
    cairo_pattern_t* pattern = cairo_get_source(newPreviewContext);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_BEST);
    cairo_matrix_t matrix;
    double xx = scaleX;
    double xy = scaleX * tanSkewY;
    double yx = scaleY * tanSkewX;
    double yy = scaleY;
    cairo_matrix_init(&matrix, xx, yx, xy, yy, offsetX, offsetY);
    if (const cairo_status_t status = cairo_matrix_invert(&matrix); status != CAIRO_STATUS_SUCCESS) {
        cairo_destroy(newPreviewContext);
        cairo_surface_destroy(newPreviewSurface);
        throw std::runtime_error(cairo_status_to_string(status));
    }
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_set_source(newPreviewContext, pattern);
    cairo_paint(newPreviewContext);
    cairo_restore(newPreviewContext);
    if (const cairo_status_t status = cairo_status(newPreviewContext); status != CAIRO_STATUS_SUCCESS) {
        cairo_destroy(newPreviewContext);
        cairo_surface_destroy(newPreviewSurface);
        throw std::runtime_error(cairo_status_to_string(status));
    }
    try {
        m_cairoModel.beginDrawing();
        m_cairoModel.setPreview(newPreviewSurface, newPreviewContext);
        m_cairoModel.endDrawing();
        //m_history.push(new mdpCairoHistoryEntry("Resize", m_cairoModel, newPreviewSurface, newPreviewContext));
        m_cairoModel.submit();
        cairo_destroy(newPreviewContext);
        cairo_surface_destroy(newPreviewSurface);
    }
    catch (...) {
        cairo_destroy(newPreviewContext);
        cairo_surface_destroy(newPreviewSurface);
        throw;
    }
}
