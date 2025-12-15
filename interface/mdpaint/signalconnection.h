#ifndef MDP_SIGNALCONNECTION_H
#define MDP_SIGNALCONNECTION_H

#include "api.h"

#include <memory>

class mdpSignalConnectionPrivate;

class MDP_INTERFACE_API [[nodiscard]] mdpSignalConnection final
{
public:

    explicit mdpSignalConnection() noexcept;

    explicit mdpSignalConnection(std::unique_ptr<mdpSignalConnectionPrivate> signalConnection) noexcept;

    mdpSignalConnection(const mdpSignalConnection& other) noexcept = delete;

    mdpSignalConnection(mdpSignalConnection&& other) noexcept;

    mdpSignalConnection& operator=(const mdpSignalConnection& other) noexcept = delete;

    mdpSignalConnection& operator=(mdpSignalConnection&& other) noexcept;

    virtual ~mdpSignalConnection();

    void disconnect();

private:
    std::unique_ptr<mdpSignalConnectionPrivate> m_signalConnection;
};

#endif // MDP_SIGNALCONNECTION_H
