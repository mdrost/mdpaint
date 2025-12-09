#include "cairo2backendplugin.h"

#include "cairo2ellipsetool.h"
#include "cairo2imagemodel.h"
#include "cairo2linetool.h"
#include "cairo2model.h"
#include "cairo2pentool.h"
#include "cairo2rectangletool.h"
#include "cairo2resizescaleskewtool.h"

// public
mdpCairo2BackendPlugin::mdpCairo2BackendPlugin()
{
}

// public virtual
mdpCairo2BackendPlugin::~mdpCairo2BackendPlugin() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpCairo2BackendPlugin::createImageModel() /* override */
{
    return std::make_unique<mdpCairo2ImageModel>();
}

// public virtual
std::unique_ptr<mdpTool> mdpCairo2BackendPlugin::createPenTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairo2Model& cairoModel = static_cast<mdpCairo2ImageModel&>(imageModel);
    return std::make_unique<mdpCairo2PenTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairo2BackendPlugin::createLineTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairo2Model& cairoModel = static_cast<mdpCairo2ImageModel&>(imageModel);
    return std::make_unique<mdpCairo2LineTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairo2BackendPlugin::createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairo2Model& cairoModel = static_cast<mdpCairo2ImageModel&>(imageModel);
    return std::make_unique<mdpCairo2RectangleTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpCairo2BackendPlugin::createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpCairo2Model& cairoModel = static_cast<mdpCairo2ImageModel&>(imageModel);
    return std::make_unique<mdpCairo2EllipseTool>(cairoModel, history);
}

// public virtual
std::unique_ptr<mdpResizeScaleSkewTool> mdpCairo2BackendPlugin::createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData()> getResizeScaleSkewData, mdpHistory& history) /* override */
{
    mdpCairo2Model& cairoModel = static_cast<mdpCairo2ImageModel&>(imageModel);
    return std::make_unique<mdpCairo2ResizeScaleSkewTool>(cairoModel, std::move(getResizeScaleSkewData), history);
}
