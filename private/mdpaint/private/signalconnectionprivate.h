#ifndef MDP_SIGNALCONNECTIONPRIVATE_H
#define MDP_SIGNALCONNECTIONPRIVATE_H

class mdpSignalConnectionPrivate
{
public:

    explicit mdpSignalConnectionPrivate();

    virtual ~mdpSignalConnectionPrivate();

    virtual void disconnect() = 0;
};

#endif // MDP_SIGNALCONNECTIONPRIVATE_H
