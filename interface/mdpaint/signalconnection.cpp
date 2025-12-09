#include "signalconnection.h"

#include <mdpaint/private/signalconnectionprivate.h>

// public
mdpSignalConnection::mdpSignalConnection() noexcept
{
}

// public
mdpSignalConnection::mdpSignalConnection(std::unique_ptr<mdpSignalConnectionPrivate> signalConnection) noexcept :
    m_signalConnection(std::move(signalConnection))
{
}

// public
mdpSignalConnection::mdpSignalConnection(mdpSignalConnection&& other) noexcept :
    m_signalConnection(std::move(other.m_signalConnection))
{
}

// public
mdpSignalConnection& mdpSignalConnection::operator=(mdpSignalConnection&& other) noexcept
{
    m_signalConnection = std::move(other.m_signalConnection);
    return *this;
}

// public
mdpSignalConnection::~mdpSignalConnection()
{
}

// public
void mdpSignalConnection::disconnect()
{
    m_signalConnection->disconnect();
}
