#include "qtimagemodel.h"

#include <mdpaint/private/privateboostsignals2signalconnection.h>

#include <QImage>
#include <QPainter>
#include <QDebug>

// public
mdpQtImageModel::mdpQtImageModel() :
    m_data(nullptr),
    m_dataWidth(0),
    m_dataHeight(0),
    m_dataStride(0),
    m_drawing(false)
{
    m_baseImage = std::make_shared<QImage>("example.png");
    if (m_baseImage->isNull()) {
        throw std::runtime_error("QImage");
    }
    m_basePainter = std::make_shared<QPainter>();
    beginDrawing();
    refresh();
    endDrawing();
}

// public virtual
mdpQtImageModel::~mdpQtImageModel() /* override */
{
}

// public virtual
std::shared_ptr<QImage> mdpQtImageModel::getBaseImage() /* override */
{
    return m_baseImage;
}

// public virtual
std::shared_ptr<QPainter> mdpQtImageModel::getBasePainter() /* override */
{
    return m_basePainter;
}

// public virtual
std::shared_ptr<QImage> mdpQtImageModel::getPreviewImage() /* override */
{
    return m_previewImage;
}

// public virtual
std::shared_ptr<QPainter> mdpQtImageModel::getPreviewPainter() /* override */
{
    return m_previewPainter;
}

// public virtual
void mdpQtImageModel::beginDrawing() /* override */
{
    assert(!m_drawing);
    m_drawing = true;
    if (m_previewImage) {
        m_previewPainter->begin(m_previewImage.get());
    }
}

// public virtual
void mdpQtImageModel::endDrawing() /* override */
{
    assert(m_drawing);
    const bool reallocatedOrReshaped = endDrawingInternal();
    if (reallocatedOrReshaped) {
        m_dataResetSignal();
    }
    else {
        m_dataChangedSignal();
    }
    m_drawing = false;
}

// public virtual
void mdpQtImageModel::refresh() /* override */
{
    assert(m_drawing);
    QImage* const baseImage = m_baseImage.get();
    QImage* const previewImage = m_previewImage.get();
    QPainter* const previewPainter = m_previewPainter.get();
#if 0
    const int baseWidth = baseImage->width();
    const int baseHeight = baseImage->height();
    int previewWidth;
    int previewHeight;
    if (previewImage != nullptr) {
        previewWidth = previewImage->width();
        previewHeight = previewImage->height();
    }
#endif
    if (previewImage == nullptr) {
        std::shared_ptr<QImage> newPreviewImage = std::make_shared<QImage>(*baseImage);
        if (newPreviewImage->isNull()) {
            throw std::runtime_error("QImage");
        }
        std::shared_ptr<QPainter> newPreviewPainter = std::make_shared<QPainter>();
        setPreview(std::move(newPreviewImage), std::move(newPreviewPainter));
    }
#if 0
    else if (previewWidth != baseWidth || previewHeight != baseHeight) {
        *m_previewImage = *baseImage;
    }
    else {
        previewPainter->drawImage(QPointF(0.0, 0.0), *baseImage);
    }
#else
    else {
        previewPainter->end();
        *m_previewImage = *baseImage;
        previewPainter->begin(m_previewImage.get());
    }
#endif
}

// public virtual
void mdpQtImageModel::submit() /* override */
{
    assert(!m_drawing);
    const std::shared_ptr<QImage> oldBaseImage = m_baseImage;
    const std::shared_ptr<QPainter> oldBasePainter = m_basePainter;
    m_baseImage = m_previewImage;
    m_basePainter = m_previewPainter;
    m_previewImage = nullptr;
    m_previewPainter = nullptr;
    try {
        beginDrawing();
        refresh();
        endDrawingInternal();
        m_drawing = false;
    }
    catch (...) {
        m_previewImage = m_baseImage;
        m_previewPainter = m_basePainter;
        m_baseImage = oldBaseImage;
        m_basePainter = oldBasePainter;
        throw;
    }
    m_previewResetSignal();
}

// public virtual
void mdpQtImageModel::setPreview(std::shared_ptr<QImage> newPreviewImage, std::shared_ptr<QPainter> newPreviewPainter) /* override */
{
    assert(m_drawing);
    m_previewPainter = newPreviewPainter;
    m_previewImage = newPreviewImage;
    newPreviewPainter->begin(newPreviewImage.get());
    m_previewResetSignal();
}

// public virtual
mdpSignalConnection mdpQtImageModel::onPreviewReset(std::function<void ()> slot) /* override */
{
    return mdpSignalConnection(std::unique_ptr<mdpPrivateSignalConnection>(new mdpPrivateBoostSignals2SignalConnection(m_previewResetSignal.connect(slot))));
}

// public virtual
const unsigned char* mdpQtImageModel::data() const /* override */
{
    return m_previewImage->bits();
}

// public virtual
int mdpQtImageModel::width() const /* override */
{
    return m_previewImage->width();
}

// public virtual
int mdpQtImageModel::height() const /* override */
{
    return m_previewImage->height();
}

// public virtual
int mdpQtImageModel::stride() const /* override */
{
    return m_previewImage->bytesPerLine();
}

// public virtual
mdpSignalConnection mdpQtImageModel::onDataChanged(std::function<void ()> slot) /* override */
{
    return mdpSignalConnection(std::unique_ptr<mdpPrivateSignalConnection>(new mdpPrivateBoostSignals2SignalConnection(m_dataChangedSignal.connect(slot))));
}

// public virtual
mdpSignalConnection mdpQtImageModel::onDataReset(std::function<void ()> slot) /* override */
{
    return mdpSignalConnection(std::unique_ptr<mdpPrivateSignalConnection>(new mdpPrivateBoostSignals2SignalConnection(m_dataResetSignal.connect(slot))));
}

bool mdpQtImageModel::endDrawingInternal()
{
    m_previewPainter->end();
    return true;
}
