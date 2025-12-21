#include "vipsbackendfactory.h"

#include "vipsellipsetool.h"
#include "vipsimagemodel.h"
#include "vipslinetool.h"
#include "vipsmodel.h"
#include "vipspentool.h"
#include "vipsrectangletool.h"
#include "vipsresizescaleskewtool.h"

#include <mdpaint/selectiontool.h>

// public
mdpVipsBackendFactory::mdpVipsBackendFactory()
{
}

// public virtual
mdpVipsBackendFactory::~mdpVipsBackendFactory() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpVipsBackendFactory::createImageModel(int width, int height) const /* override */
{
    VipsImage* baseImage;
    if (vips_black(&baseImage, width, height, "bands", 4, nullptr)) {
        throw std::runtime_error(vips_error_buffer());
    }
    VipsImage* tmpImage;
    double scale[4] = {0, 0, 0, 0};
    double color[4] = {255, 255, 255, 255};
    if (vips_linear(baseImage, &tmpImage, scale, color, 4, "uchar", TRUE, nullptr)) {
        g_object_unref(baseImage);
        throw std::runtime_error(vips_error_buffer());
    }
    g_object_unref(baseImage);
    baseImage = tmpImage;
    if (vips_copy(baseImage, &tmpImage, "interpretation", VIPS_INTERPRETATION_sRGB, nullptr)) {
        g_object_unref(baseImage);
        throw std::runtime_error(vips_error_buffer());
    }
    g_object_unref(baseImage);
    baseImage = tmpImage;
    /*if (vips_premultiply(baseImage, &tmpImage, NULL)) {
        g_object_unref(baseImage);
        throw std::runtime_error(vips_error_buffer());
    }
    g_object_unref(baseImage);
    baseImage = tmpImage;*/
    try {
        std::unique_ptr<mdpImageModel> imageModel = std::make_unique<mdpVipsImageModel>(baseImage);
        g_object_unref(baseImage);
        return imageModel;
    }
    catch (...) {
        g_object_unref(baseImage);
        throw;
    }
}

// public virtual
std::unique_ptr<mdpSelectionTool> mdpVipsBackendFactory::createFreeFormSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    return nullptr;
}

// public virtual
std::unique_ptr<mdpSelectionTool> mdpVipsBackendFactory::createRectangularSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    return nullptr;
}

// public virtual
std::unique_ptr<mdpSelectionTool> mdpVipsBackendFactory::createEllipticalSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const /* override */
{
    return nullptr;
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
