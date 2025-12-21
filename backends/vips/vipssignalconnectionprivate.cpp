#include "vipssignalconnectionprivate.h"

// public
mdpVipsSignalConnectionPrivate::mdpVipsSignalConnectionPrivate(boost::signals2::connection connection) :
    m_connection(connection)
{
}

// public
mdpVipsSignalConnectionPrivate::~mdpVipsSignalConnectionPrivate()
{
}

// public virtual
void mdpVipsSignalConnectionPrivate::disconnect() /* override */
{
    m_connection.disconnect();
}
