#ifndef MDP_VIPSBACKENDPLUGIN_H
#define MDP_VIPSBACKENDPLUGIN_H

#include "api.h"

#include <mdpaint/backendplugin.h>

class MDP_VIPS_API mdpVipsBackendPlugin : public mdpBackendPlugin
{
public:

    explicit mdpVipsBackendPlugin();

    ~mdpVipsBackendPlugin() override;

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

#endif // MDP_VIPSBACKENDPLUGIN_H
