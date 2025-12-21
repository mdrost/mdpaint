#ifndef MDP_INTERFACEIMAGEREADER_H
#define MDP_INTERFACEIMAGEREADER_H

#include "api.h"

#include <memory>
#include <string_view>

class mdpImageModel;

class MDP_INTERFACE_API mdpImageReader
{
public:

    explicit mdpImageReader();

    virtual ~mdpImageReader();

    [[nodiscard]]
    virtual std::unique_ptr<mdpImageModel> read(std::u8string_view filePath) = 0;
};

#endif // MDP_INTERFACEIMAGEREADER_H
