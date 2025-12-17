#ifndef MDP_CAIROBACKENDPLUGIN_H
#define MDP_CAIROBACKENDPLUGIN_H

#include "api.h"

#include <mdpaint/backendfactory.h>

class MDP_CAIRO_API mdpCairoBackendFactory : public mdpBackendFactory
{
public:

    explicit mdpCairoBackendFactory();

    ~mdpCairoBackendFactory() override;

    [[nodiscard]]
    std::unique_ptr<mdpImageModel> createImageModel() override;

    [[nodiscard]]
    std::unique_ptr<mdpTool> createPenTool(mdpImageModel& imageModel, mdpHistory& history) override;

    [[nodiscard]]
    std::unique_ptr<mdpTool> createLineTool(mdpImageModel& imageModel, mdpHistory& history) override;

    [[nodiscard]]
    std::unique_ptr<mdpTool> createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) override;

    [[nodiscard]]
    std::unique_ptr<mdpTool> createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) override;

    [[nodiscard]]
    std::unique_ptr<mdpResizeScaleSkewTool> createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) override;
};

#endif // MDP_CAIROBACKENDPLUGIN_H
