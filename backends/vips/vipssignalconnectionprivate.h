#ifndef MDP_VIPSSIGNALCONNECTIONPRIVATE_H
#define MDP_VIPSSIGNALCONNECTIONPRIVATE_H

#include <mdpaint/signalconnectionprivate.h>

#include <boost/signals2/connection.hpp>

class mdpVipsSignalConnectionPrivate : public mdpSignalConnectionPrivate
{
public:

    explicit mdpVipsSignalConnectionPrivate(boost::signals2::connection connection);

    ~mdpVipsSignalConnectionPrivate() override;

    void disconnect() override;

private:
    boost::signals2::scoped_connection m_connection;
};

#endif // MDP_VIPSSIGNALCONNECTIONPRIVATE_H
