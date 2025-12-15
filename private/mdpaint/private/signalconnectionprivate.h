#ifndef MDP_SIGNALCONNECTIONPRIVATE_H
#define MDP_SIGNALCONNECTIONPRIVATE_H

#include "api.h"

class MDP_PRIVATE_API mdpSignalConnectionPrivate
{
public:

    explicit mdpSignalConnectionPrivate();

    virtual ~mdpSignalConnectionPrivate();

    virtual void disconnect() = 0;
};

#endif // MDP_SIGNALCONNECTIONPRIVATE_H
