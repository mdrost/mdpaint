#ifndef MDP_QTIMAGEREADER_H
#define MDP_QTIMAGEREADER_H

#include "qtapi.h"

#include <mdpaint/imagereader.h>

class QString;

class MDP_QT_API mdpQtImageReader final : public mdpImageReader
{
public:

    explicit mdpQtImageReader();

    ~mdpQtImageReader() override;

    // mdpImageReader interface:

    [[nodiscard]]
    std::unique_ptr<mdpImageModel> read(std::u8string_view filePath) override;

    //

    [[nodiscard]]
    std::unique_ptr<mdpImageModel> read(const QString& filePath);
};

#endif // MDP_QTIMAGEREADER_H
