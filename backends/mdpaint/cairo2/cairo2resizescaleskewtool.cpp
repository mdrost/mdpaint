#include "cairo2resizescaleskewtool.h"

#include "cairo2historyentry.h"
#include "cairo2model.h"

#include <mdpaint/history.h>

#include <functional>
#include <stdexcept>

// public
mdpCairo2ResizeScaleSkewTool::mdpCairo2ResizeScaleSkewTool(mdpCairo2Model& cairoModel, std::function<mdpResizeScaleSkewData()> getResizeScaleData, mdpHistory& history) :
    m_cairoModel(cairoModel),
    m_getResizeScaleSkewData(std::move(getResizeScaleData)),
    m_history(history)
{
}

// public virtual
mdpCairo2ResizeScaleSkewTool::~mdpCairo2ResizeScaleSkewTool() /* override */
{
}

// public virtual
void mdpCairo2ResizeScaleSkewTool::activate() /* override */
{
    mdpResizeScaleSkewData resizeScaleData = m_getResizeScaleSkewData();
    resizeScaleSkew(resizeScaleData);
}

// public virtual
void mdpCairo2ResizeScaleSkewTool::deactivate() /* override */
{
}

// public virtual
void mdpCairo2ResizeScaleSkewTool::mousePressEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpCairo2ResizeScaleSkewTool::mouseReleaseEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpCairo2ResizeScaleSkewTool::mouseMoveEvent(const int x, const int y) /* override */
{
}

// public virtual
void mdpCairo2ResizeScaleSkewTool::enterEvent() /* override */
{
}

// public virtual
void mdpCairo2ResizeScaleSkewTool::leaveEvent() /* override */
{
}

// public virtual
void mdpCairo2ResizeScaleSkewTool::resizeScaleSkew(const mdpResizeScaleSkewData& resizeScaleData) /* override */
{
    const double x = -resizeScaleData.x;
    const double y = -resizeScaleData.y;
    const int newWidth = resizeScaleData.width;
    const int newHeight = resizeScaleData.height;
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
    if (resizeScaleData.scale) {
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
    m_cairoModel.beginDrawing();
    m_cairoModel.setPreview(newPreviewSurface, newPreviewContext);
    m_cairoModel.endDrawing();
    m_history.push(new mdpCairo2HistoryEntry("Resize", m_cairoModel, newPreviewSurface, newPreviewContext));
    m_cairoModel.submit();
    cairo_destroy(newPreviewContext);
    cairo_surface_destroy(newPreviewSurface);
}
