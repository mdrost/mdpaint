#ifndef MDP_HISTORY_H
#define MDP_HISTORY_H

#include "api.h"
#include "historyentry.h"

class MDP_INTERFACE_API mdpHistory final
{
public:

    explicit mdpHistory();

    ~mdpHistory();

    void push(mdpHistoryEntry* historyEntry);
};

#endif // MDP_HISTORY_H
