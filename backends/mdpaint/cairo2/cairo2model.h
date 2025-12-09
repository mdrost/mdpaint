#ifndef MDP_CAIRO2MODEL_H
#define MDP_CAIRO2MODEL_H

#include <mdpaint/signalconnection.h>

#include <cairo/cairo.h>

#include <functional>

class mdpCairo2Model
{
public:

    explicit mdpCairo2Model();

    virtual ~mdpCairo2Model();

    virtual cairo_surface_t* getBaseSurface() = 0;

    virtual cairo_t* getBaseContext() = 0;

    virtual cairo_surface_t* getPreviewSurface() = 0;

    virtual cairo_t* getPreviewContext() = 0;

    virtual void beginDrawing() = 0;

    virtual void endDrawing() = 0;

    virtual void refresh() = 0;

    virtual void submit() = 0;

    virtual void setPreview(cairo_surface_t* newPreviewSurface, cairo_t* newPreviewContext) = 0;

    virtual mdpSignalConnection onPreviewReset(std::function<void ()> slot) = 0;
};

#endif // MDP_CAIRO2MODEL_H
