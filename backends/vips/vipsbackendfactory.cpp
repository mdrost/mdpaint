#include "vipsbackendfactory.h"

#include "vipsellipsetool.h"
#include "vipsimagemodel.h"
#include "vipslinetool.h"
#include "vipsmodel.h"
#include "vipspentool.h"
#include "vipsrectangletool.h"
#include "vipsresizescaleskewtool.h"

// public
mdpVipsBackendFactory::mdpVipsBackendFactory()
{
}

// public virtual
mdpVipsBackendFactory::~mdpVipsBackendFactory() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpVipsBackendFactory::createImageModel() const /* override */
{
    return std::make_unique<mdpVipsImageModel>();
}

// public virtual
std::unique_ptr<mdpTool> mdpVipsBackendFactory::createPenTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpVipsModel& vipsModel = static_cast<mdpVipsImageModel&>(imageModel);
    return std::make_unique<mdpVipsPenTool>(vipsModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpVipsBackendFactory::createLineTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpVipsModel& vipsModel = static_cast<mdpVipsImageModel&>(imageModel);
    return std::make_unique<mdpVipsLineTool>(vipsModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpVipsBackendFactory::createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpVipsModel& vipsModel = static_cast<mdpVipsImageModel&>(imageModel);
    return std::make_unique<mdpVipsRectangleTool>(vipsModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpVipsBackendFactory::createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpVipsModel& vipsModel = static_cast<mdpVipsImageModel&>(imageModel);
    return std::make_unique<mdpVipsEllipseTool>(vipsModel, history);
}

// public virtual
std::unique_ptr<mdpResizeScaleSkewTool> mdpVipsBackendFactory::createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) const /* override */
{
    mdpVipsModel& vipsModel = static_cast<mdpVipsImageModel&>(imageModel);
    return std::make_unique<mdpVipsResizeScaleSkewTool>(vipsModel, std::move(getResizeScaleSkewData), history);
}
