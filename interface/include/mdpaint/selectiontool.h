#ifndef MDP_SELECTIONTOOL_H
#define MDP_SELECTIONTOOL_H

#include "api.h"
#include "signalconnection.h"
#include "tool.h"

#include <functional>
#include <variant>
#include <vector>

class mdpEllipse;
class mdpPoint;
class mdpRectangle;

class MDP_INTERFACE_API mdpSelectionTool : public mdpTool
{
public:

    explicit mdpSelectionTool();

    ~mdpSelectionTool() override;

    [[nodiscard]]
    virtual std::variant<std::monostate, std::vector<mdpPoint>, mdpRectangle, mdpEllipse> selection() const = 0;

    [[nodiscard]]
    virtual mdpRectangle selectionBoundingRectangle() const = 0;

    [[nodiscard]]
    virtual mdpSignalConnection onSelectionChanged(std::function<void ()> slot) const = 0;
};

#endif // MDP_SELECTIONTOOL_H
