#include "qtimagereader.h"

#include "backend/qtimagemodel.h"

#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QString>

// public
mdpQtImageReader::mdpQtImageReader()
{
}

// public virtual
mdpQtImageReader::~mdpQtImageReader() /* override */
{
}

// public virtual
std::unique_ptr<mdpImageModel> mdpQtImageReader::read(const std::u8string_view filePath) /* override */
{
    return read(QString::fromUtf8(filePath.data(), filePath.size()));
}

// public
std::unique_ptr<mdpImageModel> mdpQtImageReader::read(const QString& filePath)
{
    std::unique_ptr<QImage> image = std::make_unique<QImage>();
    QImageReader reader(filePath);
    if (!reader.read(image.get())) {
        return nullptr;
    }
    if (image->isNull()) {
        return nullptr;
    }
    std::unique_ptr<QPainter> painter = std::make_unique<QPainter>();
    std::unique_ptr<mdpQtImageModel> imageModel = std::make_unique<mdpQtImageModel>(std::move(image), std::move(painter));
    return imageModel;
}
