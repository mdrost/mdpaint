#include "boostsignals2signalconnectionprivate.h"

// public
mdpBoostSignals2SignalConnectionPrivate::mdpBoostSignals2SignalConnectionPrivate(boost::signals2::connection connection) :
    m_connection(connection)
{
}

// public
mdpBoostSignals2SignalConnectionPrivate::~mdpBoostSignals2SignalConnectionPrivate()
{
}

// public virtual
void mdpBoostSignals2SignalConnectionPrivate::disconnect() /* override */
{
    m_connection.disconnect();
}
