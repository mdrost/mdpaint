#ifndef MDP_CAIROHISTORYENTRY_H
#define MDP_CAIROHISTORYENTRY_H

#include "cairomodel.h"

#include <mdpaint/historyentry.h>

#include <cairo/cairo.h>

#include <string>

class mdpCairoHistoryEntry : public mdpHistoryEntry
{
public:

    explicit mdpCairoHistoryEntry(std::string description, mdpCairoModel& cairoModel, cairo_surface_t* surface, cairo_t* context);

    ~mdpCairoHistoryEntry() override;

    const char* description() override;

    void restore() override;

private:
    std::string m_description;
    mdpCairoModel& m_cairoModel;
    cairo_surface_t* m_surface;
    cairo_t* m_context;
};

#endif // MDP_CAIROHISTORYENTRY_H
