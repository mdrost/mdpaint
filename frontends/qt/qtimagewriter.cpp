#include "qtimagewriter.h"

#include <QString>
#include <QUtf8StringView>

// public
mdpQtImageWriter::mdpQtImageWriter()
{
}

// public virtual
mdpQtImageWriter::~mdpQtImageWriter() /* override */
{
}

// public virtual
bool mdpQtImageWriter::write(const mdpImageModel& imageModel, const std::u8string_view filePath) /* override */
{
    return write(imageModel, QString::fromUtf8(filePath.data(), filePath.size()));
}

// public
bool mdpQtImageWriter::write(const mdpImageModel& imageModel, const QString& filePath)
{
    return false;
}
