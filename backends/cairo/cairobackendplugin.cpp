#include "cairobackendplugin.h"

#include "cairoellipsetool.h"
#include "cairoimagemodel.h"
#include "cairolinetool.h"
#include "cairomodel.h"
#include "cairopentool.h"
#include "cairorectangletool.h"
#include "cairoresizescaleskewtool.h"

// public
mdpCairoBackendPlugin::mdpCairoBackendPlugin()
{
}

// public virtual
mdpCairoBackendPlugin::~mdpCairoBackendPlugin() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpCairoBackendPlugin::createImageModel() /* override */
{
    return std::make_unique<mdpCairoImageModel>();
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendPlugin::createPenTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoPenTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendPlugin::createLineTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoLineTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendPlugin::createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoRectangleTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendPlugin::createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoEllipseTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpResizeScaleSkewTool> mdpCairoBackendPlugin::createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoResizeScaleSkewTool>(cairoModel, std::move(getResizeScaleSkewData), history);
}
