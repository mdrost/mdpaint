#ifndef MDP_QTFRONTEND_H
#define MDP_QTFRONTEND_H

#include "qtapi.h"

#include <mdpaint/frontend.h>

class MDP_QT_API mdpQtFrontend : public mdpFrontend
{
public:

    explicit mdpQtFrontend();

    ~mdpQtFrontend() override;

    [[nodiscard]]
    int run(const std::vector<const mdpBackendFactory*>& backendFactories) override;
};

#endif // MDP_QTFRONTEND_H
