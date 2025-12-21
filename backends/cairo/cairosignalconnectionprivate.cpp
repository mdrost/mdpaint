#include "cairosignalconnectionprivate.h"

// public
mdpCairoSignalConnectionPrivate::mdpCairoSignalConnectionPrivate(boost::signals2::connection connection) :
    m_connection(connection)
{
}

// public
mdpCairoSignalConnectionPrivate::~mdpCairoSignalConnectionPrivate()
{
}

// public virtual
void mdpCairoSignalConnectionPrivate::disconnect() /* override */
{
    m_connection.disconnect();
}
