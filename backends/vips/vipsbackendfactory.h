#ifndef MDP_VIPSBACKENDFACTORY_H
#define MDP_VIPSBACKENDFACTORY_H

#include <mdpaint/backendfactory.h>

class mdpVipsBackendFactory : public mdpBackendFactory
{
public:

    explicit mdpVipsBackendFactory();

    ~mdpVipsBackendFactory() override;

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

#endif // MDP_VIPSBACKENDFACTORY_H
