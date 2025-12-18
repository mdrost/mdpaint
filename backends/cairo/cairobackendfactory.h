#ifndef MDP_CAIROBACKENDFACTORY_H
#define MDP_CAIROBACKENDFACTORY_H

#include <mdpaint/backendfactory.h>

class mdpCairoBackendFactory : public mdpBackendFactory
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

#endif // MDP_CAIROBACKENDFACTORY_H
