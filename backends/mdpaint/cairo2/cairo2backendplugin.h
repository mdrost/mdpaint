#ifndef MDP_CAIRO2BACKENDPLUGIN_H
#define MDP_CAIRO2BACKENDPLUGIN_H

#include <mdpaint/backendplugin.h>

class mdpCairo2BackendPlugin : public mdpBackendPlugin
{
public:

    explicit mdpCairo2BackendPlugin();

    ~mdpCairo2BackendPlugin() override;

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
    std::unique_ptr<mdpResizeScaleSkewTool> createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData()> getResizeScaleSkewData, mdpHistory& history) override;
};

#endif // MDP_CAIRO2BACKENDPLUGIN_H
