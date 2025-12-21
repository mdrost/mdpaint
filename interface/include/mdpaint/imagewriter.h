#ifndef MDP_INTERFACEIMAGEWRITER_H
#define MDP_INTERFACEIMAGEWRITER_H

#include "api.h"

#include <string_view>
class mdpImageModel;

class MDP_INTERFACE_API mdpImageWriter
{
public:

    explicit mdpImageWriter();

    virtual ~mdpImageWriter();

    [[nodiscard]]
    virtual bool write(const mdpImageModel& imageModel, std::u8string_view filePath) = 0;
};

#endif // MDP_INTERFACEIMAGEWRITER_H
