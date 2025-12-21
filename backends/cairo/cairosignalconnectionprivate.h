#ifndef MDP_CAIROSIGNALCONNECTIONPRIVATE_H
#define MDP_CAIROSIGNALCONNECTIONPRIVATE_H

#include <mdpaint/signalconnectionprivate.h>

#include <boost/signals2/connection.hpp>

class mdpCairoSignalConnectionPrivate : public mdpSignalConnectionPrivate
{
public:

    explicit mdpCairoSignalConnectionPrivate(boost::signals2::connection connection);

    ~mdpCairoSignalConnectionPrivate() override;

    void disconnect() override;

private:
    boost::signals2::scoped_connection m_connection;
};

#endif // MDP_CAIROSIGNALCONNECTIONPRIVATE_H
