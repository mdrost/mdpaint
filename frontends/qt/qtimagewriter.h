#ifndef MDP_QTIMAGEWRITER_H
#define MDP_QTIMAGEWRITER_H

#include "qtapi.h"

#include <mdpaint/imagewriter.h>

class QString;

class MDP_QT_API mdpQtImageWriter final : public mdpImageWriter
{
public:

    explicit mdpQtImageWriter();

    ~mdpQtImageWriter() override;

    // mdpImageWriter interface:

    [[nodiscard]]
    bool write(const mdpImageModel& imageModel, std::u8string_view filePath) override;

    //

    [[nodiscard]]
    bool write(const mdpImageModel& imageModel, const QString& filePath);
};

#endif // MDP_QTIMAGEWRITER_H
