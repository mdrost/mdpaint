#ifndef MDP_PRIVATEBOOSTSIGNALS2SIGNALCONNECTION_H
#define MDP_PRIVATEBOOSTSIGNALS2SIGNALCONNECTION_H

#include "privateapi.h"
#include "privatesignalconnection.h"

#include <boost/signals2/connection.hpp>

class MDP_PRIVATE_API mdpPrivateBoostSignals2SignalConnection : public mdpPrivateSignalConnection
{
public:

    explicit mdpPrivateBoostSignals2SignalConnection(boost::signals2::connection connection);

    ~mdpPrivateBoostSignals2SignalConnection() override;

    void disconnect() override;

private:
    boost::signals2::scoped_connection m_connection;
};

#endif // MDP_PRIVATEBOOSTSIGNALS2SIGNALCONNECTION_H
