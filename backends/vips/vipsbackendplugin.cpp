#include "vipsbackendplugin.h"

#include "vipsellipsetool.h"
#include "vipsimagemodel.h"
#include "vipslinetool.h"
#include "vipsmodel.h"
#include "vipspentool.h"
#include "vipsrectangletool.h"
#include "vipsresizescaleskewtool.h"

// public
mdpVipsBackendPlugin::mdpVipsBackendPlugin()
{
}

// public virtual
mdpVipsBackendPlugin::~mdpVipsBackendPlugin() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpVipsBackendPlugin::createImageModel() /* override */
{
    return std::make_unique<mdpVipsImageModel>();
}

// public virtual
std::unique_ptr<mdpTool> mdpVipsBackendPlugin::createPenTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpVipsModel& vipsModel = static_cast<mdpVipsImageModel&>(imageModel);
    return std::make_unique<mdpVipsPenTool>(vipsModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpVipsBackendPlugin::createLineTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpVipsModel& vipsModel = static_cast<mdpVipsImageModel&>(imageModel);
    return std::make_unique<mdpVipsLineTool>(vipsModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpVipsBackendPlugin::createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpVipsModel& vipsModel = static_cast<mdpVipsImageModel&>(imageModel);
    return std::make_unique<mdpVipsRectangleTool>(vipsModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpVipsBackendPlugin::createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpVipsModel& vipsModel = static_cast<mdpVipsImageModel&>(imageModel);
    return std::make_unique<mdpVipsEllipseTool>(vipsModel, history);
}

// public virtual
std::unique_ptr<mdpResizeScaleSkewTool> mdpVipsBackendPlugin::createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) /* override */
{
    mdpVipsModel& vipsModel = static_cast<mdpVipsImageModel&>(imageModel);
    return std::make_unique<mdpVipsResizeScaleSkewTool>(vipsModel, std::move(getResizeScaleSkewData), history);
}
