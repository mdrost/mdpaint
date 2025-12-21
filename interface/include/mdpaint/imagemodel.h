#ifndef MDP_INTERFACEIMAGEMODEL_H
#define MDP_INTERFACEIMAGEMODEL_H

#include "api.h"

#include <functional>

class mdpSignalConnection;

class MDP_INTERFACE_API mdpImageModel
{
public:

    explicit mdpImageModel();

    virtual ~mdpImageModel();

    // must be 32-bit aligned
    [[nodiscard]]
    virtual const unsigned char* data() const = 0;

    [[nodiscard]]
    virtual int width() const = 0;

    [[nodiscard]]
    virtual int height() const = 0;

    [[nodiscard]]
    virtual int stride() const = 0;

    [[nodiscard]]
    virtual mdpSignalConnection onDataChanged(std::function<void ()> slot) const = 0;

    [[nodiscard]]
    virtual mdpSignalConnection onDataReset(std::function<void ()> slot) const = 0;
};

#endif // MDP_INTERFACEIMAGEMODEL_H
