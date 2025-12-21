#include "cairobackendfactory.h"

#include "cairoellipsetool.h"
#include "cairoimagemodel.h"
#include "cairolinetool.h"
#include "cairomodel.h"
#include "cairopentool.h"
#include "cairorectangletool.h"
#include "cairoresizescaleskewtool.h"

#include <mdpaint/selectiontool.h> // XXX

#include <cairo/cairo.h>

// public
mdpCairoBackendFactory::mdpCairoBackendFactory()
{
}

// public virtual
mdpCairoBackendFactory::~mdpCairoBackendFactory() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpCairoBackendFactory::createImageModel(const int width, const int height) const /* override */
{
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t* context = cairo_create(surface);
    cairo_set_operator(context, CAIRO_OPERATOR_SOURCE);
    cairo_set_source_rgb(context, 1.0, 1.0, 1.0);
    cairo_paint(context);
    if (const cairo_status_t status = cairo_status(context); status != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy(surface);
        throw std::runtime_error(cairo_status_to_string(status));
    }
    try {
        std::unique_ptr<mdpImageModel> imageModel = std::make_unique<mdpCairoImageModel>(surface, context);
        cairo_destroy(context);
        cairo_surface_destroy(surface);
        return imageModel;
    }
    catch (...) {
        cairo_destroy(context);
        cairo_surface_destroy(surface);
        throw;
    }
}

// public virtual
std::unique_ptr<mdpSelectionTool> mdpCairoBackendFactory::createFreeFormSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    return nullptr;
}

// public virtual
std::unique_ptr<mdpSelectionTool> mdpCairoBackendFactory::createRectangularSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    return nullptr;
}

// public virtual
std::unique_ptr<mdpSelectionTool> mdpCairoBackendFactory::createEllipticalSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    return nullptr;
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendFactory::createPenTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoPenTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendFactory::createLineTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoLineTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendFactory::createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoRectangleTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendFactory::createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoEllipseTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpResizeScaleSkewTool> mdpCairoBackendFactory::createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) const /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoResizeScaleSkewTool>(cairoModel, std::move(getResizeScaleSkewData), history);
}
