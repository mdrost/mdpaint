#include "cairoellipsetool.h"

#include "cairohistoryentry.h"
#include "cairomodel.h"

#include <mdpaint/history.h>

#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

// public
mdpCairoEllipseTool::mdpCairoEllipseTool(mdpCairoModel& cairoModel, mdpHistory& history) :
    m_cairoModel(cairoModel),
    m_history(history),
    m_previewSurface(nullptr),
    m_previewContext(nullptr),
    m_drawing(false)
{
}

// public virtual
mdpCairoEllipseTool::~mdpCairoEllipseTool() /* override */
{
}

// public virtual
void mdpCairoEllipseTool::activate() /* override */
{
    m_previewSurface = m_cairoModel.getPreviewSurface();
    m_previewContext = m_cairoModel.getPreviewContext();
    onCairoModelPreviewResetConnection = m_cairoModel.onPreviewReset(std::bind(&mdpCairoEllipseTool::onCairoModelPreviewReset, this));
}

// public virtual
void mdpCairoEllipseTool::deactivate() /* override */
{
    onCairoModelPreviewResetConnection.disconnect();
    m_previewContext = nullptr;
    m_previewSurface = nullptr;
}

// public virtual
void mdpCairoEllipseTool::mousePressEvent(const int x, const int y) /* override */
{
    m_drawing = true;
    m_cairoModel.beginDrawing();
    draw(x, y);
    m_startingX = x;
    m_startingY = y;
    m_cairoModel.endDrawing();
}

// public virtual
void mdpCairoEllipseTool::mouseReleaseEvent(const int x, const int y) /* override */
{
    if (m_drawing) {
        //m_history.push(new mdpCairoHistoryEntry("Ellipse", m_cairoModel, m_previewSurface, m_previewContext));
        m_cairoModel.submit();
        m_drawing = false;
    }
}

// public virtual
void mdpCairoEllipseTool::mouseMoveEvent(const int x, const int y) /* override */
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
void mdpCairoEllipseTool::enterEvent() /* override */
{
}

// public virtual
void mdpCairoEllipseTool::leaveEvent() /* override */
{
    m_cairoModel.beginDrawing();
    m_cairoModel.refresh();
    m_cairoModel.endDrawing();
}

// private
void mdpCairoEllipseTool::draw(const int x, const int y)
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
void mdpCairoEllipseTool::draw(const int fromX, const int fromY, const int toX, const int toY)
{
    cairo_t* const context = m_previewContext;
    cairo_set_antialias(context, CAIRO_ANTIALIAS_NONE);
    cairo_set_source_rgb(context, 0.0, 0.0, 0.0);
    cairo_set_line_cap(context, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(context, CAIRO_LINE_JOIN_MITER);
    cairo_set_line_width(context, 1);
    const double exactFromX = fromX + 0.5;
    const double exactFromY = fromY + 0.5;
    const int width = toX - fromX;
    const int height = toY - fromY;
    const double radiusX = width / 2.0;
    const double radiusY = height / 2.0;
    if (radiusX == 0.0 && radiusY == 0.0) {
        cairo_move_to(context, exactFromX, exactFromY);
        cairo_close_path(context);
    }
    else if (radiusX == 0.0 || radiusY == 0.0) {
        cairo_move_to(context, exactFromX, exactFromY);
        cairo_line_to(context, exactFromX + width, exactFromY + height);
    }
    else {
        cairo_save(context);
        cairo_translate(context, exactFromX + radiusX, exactFromY + radiusY);
        cairo_scale(context, radiusX, radiusY);
        cairo_arc(context, 0.0, 0.0, 1.0, 0.0, 2.0 * M_PI);
        cairo_restore(context);
    }
    cairo_stroke(context);
    if (const cairo_status_t status = cairo_status(context); status != CAIRO_STATUS_SUCCESS) {
        throw std::runtime_error(cairo_status_to_string(status));
    }
}

// private slot
void mdpCairoEllipseTool::onCairoModelPreviewReset()
{
    m_previewContext = m_cairoModel.getPreviewContext();
    m_previewSurface = m_cairoModel.getPreviewSurface();
}
