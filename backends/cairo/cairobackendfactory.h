#ifndef MDP_CAIROBACKENDFACTORY_H
#define MDP_CAIROBACKENDFACTORY_H

#include "cairoapi.h"

#include <mdpaint/backendfactory.h>

class MDP_CAIRO_API mdpCairoBackendFactory : public mdpBackendFactory
{
public:

    explicit mdpCairoBackendFactory();

    ~mdpCairoBackendFactory() override;

    [[nodiscard]]
    std::unique_ptr<mdpImageModel> createImageModel(int width, int height) const override;

    [[nodiscard]]
    std::unique_ptr<mdpSelectionTool> createFreeFormSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const override;

    [[nodiscard]]
    std::unique_ptr<mdpSelectionTool> createRectangularSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const override;

    [[nodiscard]]
    std::unique_ptr<mdpSelectionTool> createEllipticalSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const override;

    [[nodiscard]]
    std::unique_ptr<mdpTool> createPenTool(mdpImageModel& imageModel, mdpHistory& history) const override;

    [[nodiscard]]
    std::unique_ptr<mdpTool> createLineTool(mdpImageModel& imageModel, mdpHistory& history) const override;

    [[nodiscard]]
    std::unique_ptr<mdpTool> createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) const override;

    [[nodiscard]]
    std::unique_ptr<mdpTool> createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) const override;

    [[nodiscard]]
    std::unique_ptr<mdpResizeScaleSkewTool> createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) const override;
};

#endif // MDP_CAIROBACKENDFACTORY_H
