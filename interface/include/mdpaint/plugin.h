#ifndef MDP_INTERFACEPLUGIN_H
#define MDP_INTERFACEPLUGIN_H

#include "api.h"
#include "backendfactory.h"
#include "frontend.h"

#include <memory>

class MDP_INTERFACE_API mdpPlugin
{
public:

    explicit mdpPlugin();

    virtual ~mdpPlugin();

    virtual void initialize() = 0;

    virtual void terminate() = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpFrontend> createFrontend() = 0;

    [[nodiscard]]
    virtual std::unique_ptr<mdpBackendFactory> createBackendFactory() = 0;
};

using mdpCreatePluginFunction = std::unique_ptr<mdpPlugin>(*)(int& argc, char** argv);

#endif // MDP_INTERFACEPLUGIN_H
