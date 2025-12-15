#include "vipspentool.h"

#include "vipshistoryentry.h"
#include "vipsmodel.h"
#include "vipssvgtemplates.h"

#include <mdpaint/history.h>

#include <functional>
#include <stdexcept>

// public
mdpVipsPenTool::mdpVipsPenTool(mdpVipsModel& vipsModel, mdpHistory& history) :
    m_vipsModel(vipsModel),
    m_history(history),
    m_previewImage(nullptr),
    m_drawing(false)
{
}

// public virtual
mdpVipsPenTool::~mdpVipsPenTool() /* override */
{
}

// public virtual
void mdpVipsPenTool::activate() /* override */
{
    m_previewImage = m_vipsModel.getPreviewImage();
    onVipsModelPreviewResetConnection = m_vipsModel.onPreviewReset(std::bind(&mdpVipsPenTool::onVipsModelPreviewReset, this));
}

// public virtual
void mdpVipsPenTool::deactivate() /* override */
{
    onVipsModelPreviewResetConnection.disconnect();
    m_previewImage = nullptr;
}

// public virtual
void mdpVipsPenTool::mousePressEvent(const int x, const int y) /* override */
{
    m_drawing = true;
    m_vipsModel.beginDrawing();
    draw(x, y);
    m_lastX = x;
    m_lastY = y;
    m_vipsModel.endDrawing();
}

// public virtual
void mdpVipsPenTool::mouseReleaseEvent(const int x, const int y) /* override */
{
    if (m_drawing) {
        //m_history.push(new mdpVipsHistoryEntry("Pen", m_vipsModel, m_previewImage));
        m_vipsModel.submit();
        m_drawing = false;
    }
}

// public virtual
void mdpVipsPenTool::mouseMoveEvent(const int x, const int y) /* override */
{
    m_vipsModel.beginDrawing();
    if (m_drawing) {
        draw(m_lastX, m_lastY, x, y);
        m_lastX = x;
        m_lastY = y;
    }
    else {
        m_vipsModel.refresh();
        draw(x, y);
    }
    m_vipsModel.endDrawing();
}

// public virtual
void mdpVipsPenTool::enterEvent() /* override */
{
}

// public virtual
void mdpVipsPenTool::leaveEvent() /* override */
{
    m_vipsModel.beginDrawing();
    m_vipsModel.refresh();
    m_vipsModel.endDrawing();
}

// private
void mdpVipsPenTool::draw(const int x, const int y)
{
    VipsImage* const previewImage = m_previewImage;
    const int imageWidth = vips_image_get_width(previewImage);
    const int imageHeight = vips_image_get_height(previewImage);
    const double exactX = x + 0.5;
    const double exactY = y + 0.5;
    char svg[SVG_POINT_SIZE];
    int snprintfResult = std::snprintf(svg, sizeof(svg), svgPointTemplate, imageWidth, imageHeight, exactX, exactY);
    if (snprintfResult < 0 || snprintfResult >= sizeof(svg)) {
        throw std::runtime_error("snprintf");
    }
    VipsImage* svgImage;
    if (vips_svgload_string(svg, &svgImage, nullptr)) {
        throw std::runtime_error(vips_error_buffer());
    }
    VipsImage* newPreviewImage;
    if (vips_composite2(previewImage, svgImage, &newPreviewImage, VIPS_BLEND_MODE_OVER, nullptr)) {
        g_object_unref(svgImage);
        throw std::runtime_error(vips_error_buffer());
    }
    m_vipsModel.setPreview(newPreviewImage); // will set m_previewImage via onVipsModelPreviewReset()
    g_object_unref(newPreviewImage);
    g_object_unref(svgImage);
}

// private
void mdpVipsPenTool::draw(const int fromX, const int fromY, const int toX, const int toY)
{
    VipsImage* const previewImage = m_previewImage;
    const int imageWidth = vips_image_get_width(previewImage);
    const int imageHeight = vips_image_get_height(previewImage);
    const double exactFromX = fromX + 0.5;
    const double exactFromY = fromY + 0.5;
    const double exactToX = toX + 0.5;
    const double exactToY = toY + 0.5;
    char svg[SVG_LINE_SIZE];
    int snprintfResult = std::snprintf(svg, sizeof(svg), svgLineTemplate, imageWidth, imageHeight, exactFromX, exactFromY, exactToX, exactToY);
    if (snprintfResult < 0 || snprintfResult >= sizeof(svg)) {
        throw std::runtime_error("snprintf");
    }
    VipsImage* svgImage;
    if (vips_svgload_string(svg, &svgImage, nullptr)) {
        throw std::runtime_error(vips_error_buffer());
    }
    VipsImage* newPreviewImage;
    if (vips_composite2(previewImage, svgImage, &newPreviewImage, VIPS_BLEND_MODE_OVER, nullptr)) {
        g_object_unref(svgImage);
        throw std::runtime_error(vips_error_buffer());
    }
    m_vipsModel.setPreview(newPreviewImage); // will set m_previewImage via onVipsModelPreviewReset()
    g_object_unref(newPreviewImage);
    g_object_unref(svgImage);
}

// private slot
void mdpVipsPenTool::onVipsModelPreviewReset()
{
    m_previewImage = m_vipsModel.getPreviewImage();
}
