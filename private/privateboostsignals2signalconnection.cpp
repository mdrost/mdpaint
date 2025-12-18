#include "privateboostsignals2signalconnection.h"

// public
mdpPrivateBoostSignals2SignalConnection::mdpPrivateBoostSignals2SignalConnection(boost::signals2::connection connection) :
    m_connection(connection)
{
}

// public
mdpPrivateBoostSignals2SignalConnection::~mdpPrivateBoostSignals2SignalConnection()
{
}

// public virtual
void mdpPrivateBoostSignals2SignalConnection::disconnect() /* override */
{
    m_connection.disconnect();
}
