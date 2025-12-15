#include "cairohistoryentry.h"

// public
mdpCairoHistoryEntry::mdpCairoHistoryEntry(std::string description, mdpCairoModel& cairoModel, cairo_surface_t* surface, cairo_t* context) :
    m_description(std::move(description)),
    m_cairoModel(cairoModel),
    m_surface(surface),
    m_context(context)
{
    cairo_surface_reference(surface);
    //if (const cairo_status_t status = cairo_surface_status(surface); status != CAIRO_STATUS_SUCCESS) {
    //    throw std::runtime_error(cairo_status_to_string(status));
    //}
    cairo_reference(context);
    //if (const cairo_status_t status = cairo_status(context); status != CAIRO_STATUS_SUCCESS) {
    //    cairo_surface_destroy(surface);
    //    throw std::runtime_error(cairo_status_to_string(status));
    //}
}

// public virtual
mdpCairoHistoryEntry::~mdpCairoHistoryEntry() /* override */
{
    cairo_destroy(m_context);
    cairo_surface_destroy(m_surface);
}

// public virtual
const char* mdpCairoHistoryEntry::description() /* override */
{
    return m_description.c_str();
}

// public virtual
void mdpCairoHistoryEntry::restore() /* override */
{
    mdpCairoModel& cairoModel = m_cairoModel;
    cairoModel.beginDrawing();
    cairoModel.setPreview(m_surface, m_context);
    cairoModel.endDrawing();
    cairoModel.submit();
}
