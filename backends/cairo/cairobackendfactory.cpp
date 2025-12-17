#include "cairobackendfactory.h"

#include "cairoellipsetool.h"
#include "cairoimagemodel.h"
#include "cairolinetool.h"
#include "cairomodel.h"
#include "cairopentool.h"
#include "cairorectangletool.h"
#include "cairoresizescaleskewtool.h"

// public
mdpCairoBackendFactory::mdpCairoBackendFactory()
{
}

// public virtual
mdpCairoBackendFactory::~mdpCairoBackendFactory() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpCairoBackendFactory::createImageModel() /* override */
{
    return std::make_unique<mdpCairoImageModel>();
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendFactory::createPenTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoPenTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendFactory::createLineTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoLineTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendFactory::createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoRectangleTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairoBackendFactory::createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoEllipseTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpResizeScaleSkewTool> mdpCairoBackendFactory::createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) /* override */
{
    mdpCairoModel& cairoModel = static_cast<mdpCairoImageModel&>(imageModel);
    return std::make_unique<mdpCairoResizeScaleSkewTool>(cairoModel, std::move(getResizeScaleSkewData), history);
}
