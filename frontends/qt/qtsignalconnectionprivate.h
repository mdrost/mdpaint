#ifndef MDP_QTSIGNALCONNECTIONPRIVATE_H
#define MDP_QTSIGNALCONNECTIONPRIVATE_H

#include <mdpaint/signalconnectionprivate.h>

#include <QObject>

class mdpQtSignalConnectionPrivate : public mdpSignalConnectionPrivate
{
public:

    explicit mdpQtSignalConnectionPrivate(QMetaObject::Connection connection);

    ~mdpQtSignalConnectionPrivate() override;

    void disconnect() override;

private:
    QMetaObject::Connection m_connection;
};

#endif // MDP_QTSIGNALCONNECTIONPRIVATE_H
