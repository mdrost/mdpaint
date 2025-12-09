#include "graphicsmagickimagemodel.h"

#include <QRect>

#include <cstdlib>

// public
mdpGraphicsMagickImageModel::mdpGraphicsMagickImageModel(QObject* parent) :
    mdpImageModel(parent)
{
    GetExceptionInfo(&m_exception);
    m_imageInfo = CloneImageInfo(nullptr);
    strncpy_s(m_imageInfo->filename, "C:\\git\\mdpaint\\example2.png", MaxTextExtent);
    m_image = ReadImage(m_imageInfo, &m_exception);
    if (m_image == nullptr) {
        CatchException(&m_exception);
        exit(EXIT_FAILURE);
    }
    const size_t columns = m_image->columns;
    const size_t rows = m_image->rows;
    m_pixels = static_cast<uchar*>(::operator new[](columns * rows * 4, std::align_val_t(32))); // TODO: is there prettier syntax?
    MagickPassFail exportResult = ExportImagePixelArea(m_image, RGBAQuantum, 8, m_pixels, nullptr, nullptr);
    if (exportResult == MagickFail) {
        exit(EXIT_FAILURE);
    }
}

// public
mdpGraphicsMagickImageModel::~mdpGraphicsMagickImageModel()
{
    ::operator delete[](m_pixels, std::align_val_t(32));
    DestroyImage(m_image);
    DestroyImageInfo(m_imageInfo);
    DestroyExceptionInfo(&m_exception);
}

// public
Image* mdpGraphicsMagickImageModel::image()
{
    return m_image;
}

// public
void mdpGraphicsMagickImageModel::syncPixels()
{
    MagickPassFail exportResult = ExportImagePixelArea(m_image, RGBAQuantum, 8, m_pixels, nullptr, nullptr);
    if (exportResult == MagickFail) {
        exit(EXIT_FAILURE);
    }
    Q_EMIT contentChanged();
}

// public
const uchar* mdpGraphicsMagickImageModel::pixels() const /* override */
{
    return m_pixels;
}

// public
int mdpGraphicsMagickImageModel::width() const /* override */
{
    return m_image->columns;
}

// public
int mdpGraphicsMagickImageModel::height() const /* override */
{
    return m_image->rows;
}

// public
void mdpGraphicsMagickImageModel::resize(const QRect& newGeometry) /* override */
{
    RectangleInfo rectangleInfo;
    rectangleInfo.width = newGeometry.width();
    rectangleInfo.height = newGeometry.height();
    rectangleInfo.x = newGeometry.x();
    rectangleInfo.y = newGeometry.y();
    Image* oldImage = m_image;
    m_image = ExtentImage(oldImage, &rectangleInfo, &m_exception);
    if (m_image == nullptr) {
        CatchException(&m_exception);
        exit(EXIT_FAILURE);
    }
    const size_t columns = m_image->columns;
    const size_t rows = m_image->rows;
    const bool pixelsReallocated = columns != oldImage->columns || rows != oldImage->rows;
    DestroyImage(oldImage);
    if (pixelsReallocated) {
        ::operator delete[](m_pixels, std::align_val_t(32));
        m_pixels = nullptr;
        m_pixels = static_cast<uchar*>(::operator new[](columns * rows * 4, std::align_val_t(32))); // TODO: is there prettier syntax?
    }
    MagickPassFail exportResult = ExportImagePixelArea(m_image, RGBAQuantum, 8, m_pixels, nullptr, nullptr);
    if (exportResult == MagickFail) {
        exit(EXIT_FAILURE);
    }
    if (pixelsReallocated) {
        Q_EMIT contentAndSizeChanged();
    }
    else {
        Q_EMIT contentChanged();
    }
}
