#ifndef MDP_CAIRO2HISTORYENTRY_H
#define MDP_CAIRO2HISTORYENTRY_H

#include "cairo2model.h"

#include <mdpaint/historyentry.h>

#include <cairo/cairo.h>

#include <string>

class mdpCairo2HistoryEntry : public mdpHistoryEntry
{
public:

    explicit mdpCairo2HistoryEntry(std::string description, mdpCairo2Model& cairoModel, cairo_surface_t* surface, cairo_t* context);

    ~mdpCairo2HistoryEntry() override;

    const char* description() override;

    void restore() override;

private:
    std::string m_description;
    mdpCairo2Model& m_cairoModel;
    cairo_surface_t* m_surface;
    cairo_t* m_context;
};

#endif // MDP_CAIRO2HISTORYENTRY_H
