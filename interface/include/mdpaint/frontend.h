#ifndef MDP_INTERFACEFRONTEND_H
#define MDP_INTERFACEFRONTEND_H

#include "api.h"

class MDP_INTERFACE_API mdpFrontend
{
public:

    explicit mdpFrontend();

    virtual ~mdpFrontend();

    [[nodiscard]]
    virtual int run() = 0;
};

#endif // MDP_INTERFACEFRONTEND_H
