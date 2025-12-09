#include "cairo2ellipsetool.h"

#include "cairo2historyentry.h"
#include "cairo2model.h"

#include <mdpaint/history.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

// public
mdpCairo2EllipseTool::mdpCairo2EllipseTool(mdpCairo2Model& cairoModel, mdpHistory& history) :
    m_cairoModel(cairoModel),
    m_history(history),
    m_previewSurface(nullptr),
    m_previewContext(nullptr),
    m_drawing(false)
{
}

// public virtual
mdpCairo2EllipseTool::~mdpCairo2EllipseTool() /* override */
{
}

// public virtual
void mdpCairo2EllipseTool::activate() /* override */
{
    m_previewSurface = m_cairoModel.getPreviewSurface();
    m_previewContext = m_cairoModel.getPreviewContext();
    onCairoModelPreviewResetConnection = m_cairoModel.onPreviewReset(std::bind(&mdpCairo2EllipseTool::onCairoModelPreviewReset, this));
}

// public virtual
void mdpCairo2EllipseTool::deactivate() /* override */
{
    onCairoModelPreviewResetConnection.disconnect();
    m_previewContext = nullptr;
    m_previewSurface = nullptr;
}

// public virtual
void mdpCairo2EllipseTool::mousePressEvent(const int x, const int y) /* override */
{
    m_drawing = true;
    m_cairoModel.beginDrawing();
    draw(x, y);
    m_startingX = x;
    m_startingY = y;
    m_cairoModel.endDrawing();
}

// public virtual
void mdpCairo2EllipseTool::mouseReleaseEvent(const int x, const int y) /* override */
{
    if (m_drawing) {
        m_history.push(new mdpCairo2HistoryEntry("Ellipse", m_cairoModel, m_previewSurface, m_previewContext));
        m_cairoModel.submit();
        m_drawing = false;
    }
}

// public virtual
void mdpCairo2EllipseTool::mouseMoveEvent(const int x, const int y) /* override */
{
    m_cairoModel.beginDrawing();
    m_cairoModel.refresh();
    if (m_drawing) {
        draw(m_startingX, m_startingY, x, y);
    }
    else {
        draw(x, y);
    }
    m_cairoModel.endDrawing();
}

// public virtual
void mdpCairo2EllipseTool::enterEvent() /* override */
{
}

// public virtual
void mdpCairo2EllipseTool::leaveEvent() /* override */
{
    m_cairoModel.beginDrawing();
    m_cairoModel.refresh();
    m_cairoModel.endDrawing();
}

// private
void mdpCairo2EllipseTool::draw(const int x, const int y)
{
    cairo_t* const context = m_previewContext;
    cairo_set_antialias(context, CAIRO_ANTIALIAS_NONE);
    cairo_set_source_rgb(context, 0.0, 0.0, 0.0);
    cairo_set_line_cap(context, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(context, CAIRO_LINE_JOIN_MITER);
    cairo_set_line_width(context, 1);
    const double exactX = x + 0.5;
    const double exactY = y + 0.5;
    cairo_move_to(context, exactX, exactY);
    cairo_close_path(context);
    cairo_stroke(context);
    if (const cairo_status_t status = cairo_status(context); status != CAIRO_STATUS_SUCCESS) {
        throw std::runtime_error(cairo_status_to_string(status));
    }
}

// private
void mdpCairo2EllipseTool::draw(const int fromX, const int fromY, const int toX, const int toY)
{
    cairo_t* const context = m_previewContext;
    cairo_set_antialias(context, CAIRO_ANTIALIAS_NONE);
    cairo_set_source_rgb(context, 0.0, 0.0, 0.0);
    cairo_set_line_cap(context, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(context, CAIRO_LINE_JOIN_MITER);
    cairo_set_line_width(context, 1);
    const double exactX = fromX + 0.5;
    const double exactY = fromY + 0.5;
    const int width = toX - fromX;
    const int height = toY - fromY;
    const double halfWidth = width / 2.0;
    const double halfHeight = height / 2.0;
    if (halfWidth == 0.0 && halfHeight == 0.0) {
        cairo_move_to(context, exactX, exactY);
        cairo_close_path(context);
    }
    else if (halfWidth == 0.0 || halfHeight == 0.0) {
        cairo_move_to(context, exactX, exactY);
        cairo_line_to(context, exactX + width, exactY + height);
    }
    else {
        cairo_save(context);
        cairo_translate(context, exactX + halfWidth, exactY + halfHeight);
        cairo_scale(context, halfWidth, halfHeight);
        cairo_arc(context, 0.0, 0.0, 1.0, 0.0, 2.0 * M_PI);
        cairo_restore(context);
    }
    cairo_stroke(context);
    if (const cairo_status_t status = cairo_status(context); status != CAIRO_STATUS_SUCCESS) {
        throw std::runtime_error(cairo_status_to_string(status));
    }
}

// private slot
void mdpCairo2EllipseTool::onCairoModelPreviewReset()
{
    m_previewSurface = m_cairoModel.getPreviewSurface();
    m_previewContext = m_cairoModel.getPreviewContext();
}
