#include "qtbackendfactory.h"

#include "qtellipsetool.h"
#include "qtimagemodel.h"
#include "qtlinetool.h"
#include "qtmodel.h"
#include "qtpentool.h"
#include "qtrectangletool.h"
#include "qtresizescaleskewtool.h"

// public
mdpQtBackendFactory::mdpQtBackendFactory()
{
}

// public virtual
mdpQtBackendFactory::~mdpQtBackendFactory() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpQtBackendFactory::createImageModel() /* override */
{
    return std::make_unique<mdpQtImageModel>();
}

// public virtual
std::unique_ptr<mdpTool> mdpQtBackendFactory::createPenTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtPenTool>(qtModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpQtBackendFactory::createLineTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtLineTool>(qtModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpQtBackendFactory::createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtRectangleTool>(qtModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpQtBackendFactory::createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtEllipseTool>(qtModel, history);
}

// public virtual
std::unique_ptr<mdpResizeScaleSkewTool> mdpQtBackendFactory::createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtResizeScaleSkewTool>(qtModel, std::move(getResizeScaleSkewData), history);
}
