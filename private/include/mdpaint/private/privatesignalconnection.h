#ifndef MDP_PRIVATESIGNALCONNECTIONPRIVATE_H
#define MDP_PRIVATESIGNALCONNECTIONPRIVATE_H

#include "privateapi.h"

class MDP_PRIVATE_API mdpPrivateSignalConnection
{
public:

    explicit mdpPrivateSignalConnection();

    virtual ~mdpPrivateSignalConnection();

    virtual void disconnect() = 0;
};

#endif // MDP_PRIVATESIGNALCONNECTIONPRIVATE_H
