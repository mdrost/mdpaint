#ifndef MDP_INTERFACEBACKENDFACTORY_H
#define MDP_INTERFACEBACKENDFACTORY_H

#include "api.h"
#include "resizescaleskewtool.h"

#include <functional>
#include <memory>

class mdpHistory;
class mdpImageModel;
//class mdpResizeScaleSkewData;
//class mdpResizeScaleSkewTool;
class mdpSelectionTool;
class mdpTool;

class MDP_INTERFACE_API mdpBackendFactory
{
public:

    explicit mdpBackendFactory();

    virtual ~mdpBackendFactory();

    [[nodiscard]]
    virtual std::unique_ptr<mdpImageModel> createImageModel(int width, int height) const = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpSelectionTool> createFreeFormSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpSelectionTool> createRectangularSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpSelectionTool> createEllipticalSelectionTool(mdpImageModel& imageModel, mdpHistory& history) const = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpTool> createPenTool(mdpImageModel& imageModel, mdpHistory& history) const = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpTool> createLineTool(mdpImageModel& imageModel, mdpHistory& history) const = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpTool> createRectangleTool(mdpImageModel& imageModel, mdpHistory& history) const = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpTool> createEllipseTool(mdpImageModel& imageModel, mdpHistory& history) const = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpResizeScaleSkewTool> createResizeScaleSkewTool(mdpImageModel& imageModel, std::function<mdpResizeScaleSkewData ()> getResizeScaleSkewData, mdpHistory& history) const = 0;
};

#endif // MDP_INTERFACEBACKENDFACTORY_H
