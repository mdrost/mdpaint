#ifndef MDP_INTERFACEIMAGEMODEL_H
#define MDP_INTERFACEIMAGEMODEL_H

#include "api.h"

#include "signalconnection.h"

#include <functional>

class MDP_INTERFACE_API mdpImageModel
{
public:

    explicit mdpImageModel();

    virtual ~mdpImageModel();

    // must be 32-bit aligned
    virtual const unsigned char* data() const = 0;

    virtual int width() const = 0;

    virtual int height() const = 0;

    virtual int stride() const = 0;

    virtual mdpSignalConnection onDataChanged(std::function<void ()> slot) = 0;

    virtual mdpSignalConnection onDataReset(std::function<void ()> slot) = 0;
};

#endif // MDP_INTERFACEIMAGEMODEL_H
