#ifndef MDP_BACKENDPLUGIN_H
#define MDP_BACKENDPLUGIN_H

#include "api.h"
#include "history.h"
#include "imagemodel.h"
#include "resizescaleskewtool.h"
#include "tool.h"

#include <memory>

class MDP_INTERFACE_API mdpBackendFactory
{
public:

    explicit mdpBackendFactory();

    virtual ~mdpBackendFactory();

    [[nodiscard]]
    virtual std::unique_ptr<mdpImageModel> createImageModel() = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpTool> createPenTool(mdpImageModel& imageModel, mdpHistory& history) = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpTool> createLineTool(mdpImageModel& imageModel, mdpHistory& history) = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpTool> createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpTool> createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpResizeScaleSkewTool> createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) = 0;
};

#endif // MDP_BACKENDPLUGIN_H
