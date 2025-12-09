#ifndef MDP_HISTORYENTRY_H
#define MDP_HISTORYENTRY_H

class mdpHistoryEntry
{
public:

    explicit mdpHistoryEntry();

    virtual ~mdpHistoryEntry();

    virtual const char* description() = 0;

    virtual void restore() = 0;
};

#endif // MDP_HISTORYENTRY_H
