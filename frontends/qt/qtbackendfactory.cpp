#include "qtbackendfactory.h"

#include "backend/qtellipsetool.h"
#include "backend/qtimagemodel.h"
#include "backend/qtlinetool.h"
#include "backend/qtmodel.h"
#include "backend/qtpentool.h"
#include "backend/qtrectangletool.h"
#include "backend/qtrectangularselectiontool.h"
#include "backend/qtresizescaleskewtool.h"

#include <QImage>
#include <QPainter>

// public
mdpQtBackendFactory::mdpQtBackendFactory()
{
}

// public virtual
mdpQtBackendFactory::~mdpQtBackendFactory() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpQtBackendFactory::createImageModel(const int width, const int height) const /* override */
{
    std::unique_ptr<QImage> image = std::make_unique<QImage>(width, height, QImage::Format_ARGB32_Premultiplied);
    image->fill(Qt::white);
    std::unique_ptr<QPainter> painter = std::make_unique<QPainter>();
    std::unique_ptr<mdpImageModel> imageModel = std::make_unique<mdpQtImageModel>(std::move(image), std::move(painter));
    return imageModel;
}

// public virtual
std::unique_ptr<mdpSelectionTool> mdpQtBackendFactory::createFreeFormSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    return nullptr;
}

// public virtual
std::unique_ptr<mdpSelectionTool> mdpQtBackendFactory::createRectangularSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    mdpQtModel& qtModel = static_cast<mdpQtImageModel&>(imageModel);
    return std::make_unique<mdpQtRectangularSelectionTool>(qtModel, history);
}

// public virtual
std::unique_ptr<mdpSelectionTool> mdpQtBackendFactory::createEllipticalSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    return nullptr;
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
