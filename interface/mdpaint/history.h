#ifndef MDP_HISTORY_H
#define MDP_HISTORY_H

#include "historyentry.h"

class mdpHistory final
{
public:

    explicit mdpHistory();

    ~mdpHistory();

    void push(mdpHistoryEntry* historyEntry);
};

#endif // MDP_HISTORY_H
