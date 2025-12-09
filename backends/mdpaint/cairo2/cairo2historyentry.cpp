#include "cairo2historyentry.h"

// public
mdpCairo2HistoryEntry::mdpCairo2HistoryEntry(std::string description, mdpCairo2Model& cairoModel, cairo_surface_t* surface, cairo_t* context) :
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
mdpCairo2HistoryEntry::~mdpCairo2HistoryEntry() /* override */
{
    cairo_destroy(m_context);
    cairo_surface_destroy(m_surface);
}

// public virtual
const char* mdpCairo2HistoryEntry::description() /* override */
{
    return m_description.c_str();
}

// public virtual
void mdpCairo2HistoryEntry::restore() /* override */
{
    mdpCairo2Model& cairoModel = m_cairoModel;
    cairoModel.beginDrawing();
    cairoModel.setPreview(m_surface, m_context);
    cairoModel.endDrawing();
    cairoModel.submit();
}
