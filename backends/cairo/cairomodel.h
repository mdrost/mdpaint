#ifndef MDP_CAIROMODEL_H
#define MDP_CAIROMODEL_H

#include <mdpaint/signalconnection.h>

#include <cairo/cairo.h>

#include <functional>

class mdpCairoModel
{
public:

    explicit mdpCairoModel();

    virtual ~mdpCairoModel();

    [[nodiscard]]
    virtual cairo_surface_t* getBaseSurface() = 0;

    [[nodiscard]]
    virtual cairo_t* getBaseContext() = 0;

    [[nodiscard]]
    virtual cairo_surface_t* getPreviewSurface() = 0;

    [[nodiscard]]
    virtual cairo_t* getPreviewContext() = 0;

    virtual void beginDrawing() = 0;

    virtual void endDrawing() = 0;

    virtual void refresh() = 0;

    virtual void submit() = 0;

    virtual void setPreview(cairo_surface_t* newPreviewSurface, cairo_t* newPreviewContext) = 0;

    [[nodiscard]]
    virtual mdpSignalConnection onPreviewReset(std::function<void ()> slot) const = 0;
};

#endif // MDP_CAIROMODEL_H
