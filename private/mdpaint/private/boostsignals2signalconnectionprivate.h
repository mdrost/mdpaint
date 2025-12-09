#ifndef MDP_BOOSTSIGNALS2SIGNALCONNECTION_H
#define MDP_BOOSTSIGNALS2SIGNALCONNECTION_H

#include "signalconnectionprivate.h"

#include <boost/signals2/connection.hpp>

class mdpBoostSignals2SignalConnectionPrivate : public mdpSignalConnectionPrivate
{
public:

    explicit mdpBoostSignals2SignalConnectionPrivate(boost::signals2::connection connection);

    ~mdpBoostSignals2SignalConnectionPrivate() override;

    void disconnect() override;

private:
    boost::signals2::scoped_connection m_connection;
};

#endif // MDP_BOOSTSIGNALS2SIGNALCONNECTION_H
