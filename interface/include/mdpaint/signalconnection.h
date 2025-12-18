#ifndef MDP_INTERFACESIGNALCONNECTION_H
#define MDP_INTERFACESIGNALCONNECTION_H

#include "api.h"

#include <memory>

class mdpPrivateSignalConnection;

class MDP_INTERFACE_API [[nodiscard]] mdpSignalConnection final
{
public:

    explicit mdpSignalConnection() noexcept;

    explicit mdpSignalConnection(std::unique_ptr<mdpPrivateSignalConnection> signalConnection) noexcept;

    mdpSignalConnection(const mdpSignalConnection& other) noexcept = delete;

    mdpSignalConnection(mdpSignalConnection&& other) noexcept;

    mdpSignalConnection& operator=(const mdpSignalConnection& other) noexcept = delete;

    mdpSignalConnection& operator=(mdpSignalConnection&& other) noexcept;

    virtual ~mdpSignalConnection();

    void disconnect();

private:
    std::unique_ptr<mdpPrivateSignalConnection> m_signalConnection;
};

#endif // MDP_INTERFACESIGNALCONNECTION_H
