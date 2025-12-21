#include "qtsignalconnectionprivate.h"

// public
mdpQtSignalConnectionPrivate::mdpQtSignalConnectionPrivate(QMetaObject::Connection connection) :
    m_connection(connection)
{
}

// public
mdpQtSignalConnectionPrivate::~mdpQtSignalConnectionPrivate()
{
    if (m_connection) {
        QObject::disconnect(m_connection);
    }
}

// public virtual
void mdpQtSignalConnectionPrivate::disconnect() /* override */
{
    QObject::disconnect(m_connection);
}
