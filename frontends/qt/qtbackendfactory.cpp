#include "qtbackendfactory.h"

#include "backend/qtellipsetool.h"
#include "backend/qtimagemodel.h"
#include "backend/qtlinetool.h"
#include "backend/qtmodel.h"
#include "backend/qtpentool.h"
#include "backend/qtrectangletool.h"
#include "backend/qtresizescaleskewtool.h"

// public
mdpQtBackendFactory::mdpQtBackendFactory()
{
}

// public virtual
mdpQtBackendFactory::~mdpQtBackendFactory() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpQtBackendFactory::createImageModel() const /* override */
{
    return std::make_unique<mdpQtImageModel>();
}

// public virtual
std::unique_ptr<mdpTool> mdpQtBackendFactory::createPenTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtPenTool>(qtModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpQtBackendFactory::createLineTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtLineTool>(qtModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpQtBackendFactory::createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtRectangleTool>(qtModel, history);
}

// public virtual
std::unique_ptr<mdpTool> mdpQtBackendFactory::createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtEllipseTool>(qtModel, history);
}

// public virtual
std::unique_ptr<mdpResizeScaleSkewTool> mdpQtBackendFactory::createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) const /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtResizeScaleSkewTool>(qtModel, std::move(getResizeScaleSkewData), history);
}
