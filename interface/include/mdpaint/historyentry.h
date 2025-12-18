#ifndef MDP_INTERFACEHISTORYENTRY_H
#define MDP_INTERFACEHISTORYENTRY_H

#include "api.h"

class MDP_INTERFACE_API mdpHistoryEntry
{
public:

    explicit mdpHistoryEntry();

    virtual ~mdpHistoryEntry();

    virtual const char* description() = 0;

    virtual void restore() = 0;
};

#endif // MDP_INTERFACEHISTORYENTRY_H
