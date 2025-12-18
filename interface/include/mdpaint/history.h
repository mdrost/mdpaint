#ifndef MDP_INTERFACEHISTORY_H
#define MDP_INTERFACEHISTORY_H

#include "api.h"
#include "historyentry.h"

class MDP_INTERFACE_API mdpHistory final
{
public:

    explicit mdpHistory();

    ~mdpHistory();

    void push(mdpHistoryEntry* historyEntry);
};

#endif // MDP_INTERFACEHISTORY_H
