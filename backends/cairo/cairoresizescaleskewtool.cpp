#include "cairoresizescaleskewtool.h"

#include "cairohistoryentry.h"
#include "cairomodel.h"

#include <mdpaint/history.h>

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
    const double x = -resizeScaleSkewData.x;
    const double y = -resizeScaleSkewData.y;
    const int newWidth = resizeScaleSkewData.width;
    const int newHeight = resizeScaleSkewData.height;
    cairo_surface_t* previewSurface = m_cairoModel.getPreviewSurface();
    cairo_surface_t* newPreviewSurface = cairo_surface_create_similar_image(
        previewSurface,
        cairo_image_surface_get_format(previewSurface),
        newWidth,
        newHeight
    );
    if (const cairo_status_t status = cairo_surface_status(newPreviewSurface); status != CAIRO_STATUS_SUCCESS) {
        throw std::runtime_error(cairo_status_to_string(status));
    }
    cairo_t* newPreviewContext = cairo_create(newPreviewSurface);
    if (resizeScaleSkewData.scale) {
        const int width = cairo_image_surface_get_width(previewSurface);
        const int height = cairo_image_surface_get_height(previewSurface);
        const double xScale = newWidth / (double)width;
        const double yScale = newHeight / (double)height;
        cairo_save(newPreviewContext);
        cairo_scale(newPreviewContext, xScale, yScale);
        cairo_set_operator(newPreviewContext, CAIRO_OPERATOR_SOURCE);
        cairo_set_source_surface(newPreviewContext, previewSurface, 0.0, 0.0);
        cairo_pattern_t* pattern = cairo_get_source(newPreviewContext);
        cairo_pattern_set_filter(pattern, CAIRO_FILTER_BEST);
        cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
        if (const cairo_status_t status = cairo_pattern_status(pattern); status != CAIRO_STATUS_SUCCESS) {
            throw std::runtime_error(cairo_status_to_string(status));
        }
        cairo_paint(newPreviewContext);
        cairo_restore(newPreviewContext);
    }
    else {
        cairo_set_operator(newPreviewContext, CAIRO_OPERATOR_SOURCE);
        cairo_set_source_rgb(newPreviewContext, 1.0, 1.0, 1.0);
        cairo_paint(newPreviewContext);
        cairo_set_operator(newPreviewContext, CAIRO_OPERATOR_OVER);
        cairo_set_source_surface(newPreviewContext, previewSurface, x, y);
        cairo_paint(newPreviewContext);
    }
    if (const cairo_status_t status = cairo_status(newPreviewContext); status != CAIRO_STATUS_SUCCESS) {
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
