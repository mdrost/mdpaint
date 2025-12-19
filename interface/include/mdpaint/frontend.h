#ifndef MDP_INTERFACEFRONTEND_H
#define MDP_INTERFACEFRONTEND_H

#include "api.h"

#include <vector>

class mdpBackendFactory;

class MDP_INTERFACE_API mdpFrontend
{
public:

    explicit mdpFrontend();

    virtual ~mdpFrontend();

    [[nodiscard]]
    virtual int run(const std::vector<const mdpBackendFactory*>& backendFactories) = 0;
};

#endif // MDP_INTERFACEFRONTEND_H
