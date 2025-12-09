#ifndef MDP_MAGICKIMAGEMODEL_H
#define MDP_MAGICKIMAGEMODEL_H

#include "imagemodel.h"

#include <magick/api.h>

class mdpGraphicsMagickImageModel final : public mdpImageModel
{
    Q_OBJECT

public:

    explicit mdpGraphicsMagickImageModel(QObject* parent = nullptr);

    ~mdpGraphicsMagickImageModel();

    Image* image();

    void syncPixels();

    const uchar* data() const override;

    int width() const override;

    int height() const override;

    void resize(const QRect& newGeometry) override;

private:
    Q_DISABLE_COPY(mdpGraphicsMagickImageModel)

    ExceptionInfo m_exception;
    ImageInfo* m_imageInfo;
    Image* m_image;
    uchar* m_pixels;
};

#endif // MDP_MAGICKIMAGEMODEL_H
