#include "cairoimagemodel.h"

#include <mdpaint/private/boostsignals2signalconnectionprivate.h>

// public
mdpCairoImageModel::mdpCairoImageModel() :
    m_previewSurface(nullptr),
    m_previewContext(nullptr),
    m_data(nullptr),
    m_dataWidth(0),
    m_dataHeight(0),
    m_dataStride(0),
    m_drawing(false)
{
    m_baseSurface = cairo_image_surface_create_from_png("example.png");
    if (const cairo_status_t status = cairo_surface_status(m_baseSurface); status != CAIRO_STATUS_SUCCESS) {
        throw std::runtime_error(cairo_status_to_string(status));
    }
    m_baseContext = cairo_create(m_baseSurface);
    if (const cairo_status_t status = cairo_status(m_baseContext); status != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy(m_baseSurface);
        throw std::runtime_error(cairo_status_to_string(status));
    }
    try {
        beginDrawing();
        refresh();
        endDrawingInternal();
        m_drawing = false;
    }
    catch (...) {
        cairo_destroy(m_baseContext);
        cairo_surface_destroy(m_baseSurface);
        throw;
    }
}

// public virtual
mdpCairoImageModel::~mdpCairoImageModel() /* override */
{
    ::operator delete[](m_data, std::align_val_t(32)); // TODO: is there prettier syntax?
    cairo_destroy(m_previewContext);
    cairo_surface_destroy(m_previewSurface);
    cairo_destroy(m_baseContext);
    cairo_surface_destroy(m_baseSurface);
}

// public virtual
cairo_surface_t* mdpCairoImageModel::getBaseSurface() /* override */
{
    return m_baseSurface;
}

// public virtual
cairo_t* mdpCairoImageModel::getBaseContext() /* override */
{
    return m_baseContext;
}

// public virtual
cairo_surface_t* mdpCairoImageModel::getPreviewSurface() /* override */
{
    return m_previewSurface;
}

// public virtual
cairo_t* mdpCairoImageModel::getPreviewContext() /* override */
{
    return m_previewContext;
}

// public virtual
void mdpCairoImageModel::beginDrawing() /* override */
{
    assert(!m_drawing);
    m_drawing = true;
}

// public virtual
void mdpCairoImageModel::endDrawing() /* override */
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
void mdpCairoImageModel::refresh() /* override */
{
    assert(m_drawing);
    cairo_surface_t* const baseSurface = m_baseSurface;
    cairo_surface_t* const previewSurface = m_previewSurface;
    cairo_t* const previewContext = m_previewContext;
    const int baseWidth = cairo_image_surface_get_width(baseSurface);
    const int baseHeight = cairo_image_surface_get_height(baseSurface);
    int previewWidth;
    int previewHeight;
    if (previewSurface != nullptr) {
        previewWidth = cairo_image_surface_get_width(previewSurface);
        previewHeight = cairo_image_surface_get_height(previewSurface);
    }
    if (previewSurface == nullptr || previewWidth != baseWidth || previewHeight != baseHeight) {
        cairo_surface_t* const newPreviewSurface = cairo_surface_create_similar_image(
            baseSurface,
            cairo_image_surface_get_format(baseSurface),
            baseWidth,
            baseHeight
        );
        if (const cairo_status_t status = cairo_surface_status(newPreviewSurface); status != CAIRO_STATUS_SUCCESS) {
            throw std::runtime_error(cairo_status_to_string(status));
        }
        cairo_t* newPreviewContext = cairo_create(newPreviewSurface);
        cairo_set_operator(newPreviewContext, CAIRO_OPERATOR_SOURCE);
        cairo_set_source_surface(newPreviewContext, baseSurface, 0.0, 0.0);
        cairo_paint(newPreviewContext);
        if (const cairo_status_t status = cairo_status(newPreviewContext); status != CAIRO_STATUS_SUCCESS) {
            cairo_destroy(newPreviewContext);
            cairo_surface_destroy(newPreviewSurface);
            throw std::runtime_error(cairo_status_to_string(status));
        }
        // XXX: All that referencing inside setPreview() only to be counteracted by unreferencing here later
        // is a little waste of CPU cycles:
        setPreview(newPreviewSurface, newPreviewContext);
        cairo_destroy(newPreviewContext);
        cairo_surface_destroy(newPreviewSurface);
    }
    else {
        cairo_set_operator(previewContext, CAIRO_OPERATOR_SOURCE);
        cairo_set_source_surface(previewContext, baseSurface, 0.0, 0.0);
        cairo_paint(previewContext);
        if (const cairo_status_t status = cairo_status(previewContext); status != CAIRO_STATUS_SUCCESS) {
            throw std::runtime_error(cairo_status_to_string(status));
        }
    }
}

// public virtual
void mdpCairoImageModel::submit() /* override */
{
    cairo_surface_t* const oldBaseSurface = m_baseSurface;
    cairo_t* const oldBaseContext = m_baseContext;
    m_baseSurface = m_previewSurface;
    m_baseContext = m_previewContext;
    m_previewSurface = nullptr;
    m_previewContext = nullptr;
    try {
        beginDrawing();
        refresh();
        endDrawingInternal();
        m_drawing = false;
    }
    catch (...) {
        m_previewSurface = m_baseSurface;
        m_previewContext = m_baseContext;
        m_baseSurface = oldBaseSurface;
        m_baseContext = oldBaseContext;
        throw;
    }
    cairo_destroy(oldBaseContext);
    cairo_surface_destroy(oldBaseSurface);
    m_previewResetSignal();
}

// public virtual
void mdpCairoImageModel::setPreview(cairo_surface_t* newPreviewSurface, cairo_t* newPreviewContext) /* override */
{
    assert(m_drawing);
    cairo_surface_reference(newPreviewSurface);
    //if (const cairo_status_t status = cairo_surface_status(newPreviewSurface); status != CAIRO_STATUS_SUCCESS) {
    //    throw std::runtime_error(cairo_status_to_string(status));
    //}
    cairo_reference(newPreviewContext);
    //if (const cairo_status_t status = cairo_status(newPreviewContext); status != CAIRO_STATUS_SUCCESS) {
    //    cairo_surface_destroy(newPreviewSurface);
    //    throw std::runtime_error(cairo_status_to_string(status));
    //}
    cairo_destroy(m_previewContext);
    cairo_surface_destroy(m_previewSurface);
    m_previewSurface = newPreviewSurface;
    m_previewContext = newPreviewContext;
    m_previewResetSignal();
}

// public virtual
mdpSignalConnection mdpCairoImageModel::onPreviewReset(std::function<void ()> slot) /* override */
{
    return mdpSignalConnection(std::unique_ptr<mdpSignalConnectionPrivate>(new mdpBoostSignals2SignalConnectionPrivate(m_previewResetSignal.connect(slot))));
}

// public virtual
const unsigned char* mdpCairoImageModel::data() const /* override */
{
    return m_data;
}

// public virtual
int mdpCairoImageModel::width() const /* override */
{
    return m_dataWidth;
}

// public virtual
int mdpCairoImageModel::height() const /* override */
{
    return m_dataHeight;
}

// public virtual
int mdpCairoImageModel::stride() const /* override */
{
    return m_dataStride;
}

// public virtual
mdpSignalConnection mdpCairoImageModel::onDataChanged(std::function<void ()> slot) /* override */
{
    return mdpSignalConnection(std::unique_ptr<mdpSignalConnectionPrivate>(new mdpBoostSignals2SignalConnectionPrivate(m_dataChangedSignal.connect(slot))));
}

// public virtual
mdpSignalConnection mdpCairoImageModel::onDataReset(std::function<void ()> slot) /* override */
{
    return mdpSignalConnection(std::unique_ptr<mdpSignalConnectionPrivate>(new mdpBoostSignals2SignalConnectionPrivate(m_dataResetSignal.connect(slot))));
}

bool mdpCairoImageModel::endDrawingInternal()
{
    cairo_surface_t* const surface = m_previewSurface;
    unsigned char* data = cairo_image_surface_get_data(surface);
    if (data == nullptr) {
        throw std::runtime_error(cairo_status_to_string(CAIRO_STATUS_NULL_POINTER));
    }
    cairo_surface_flush(surface);
    if (const cairo_status_t status = cairo_surface_status(surface); status != CAIRO_STATUS_SUCCESS) {
        throw std::runtime_error(cairo_status_to_string(status));
    }
    const int newWidth = cairo_image_surface_get_width(surface);
    const int newHeight = cairo_image_surface_get_height(surface);
    const int newStride = cairo_image_surface_get_stride(surface);
    const int newDataSize = newStride * newHeight;
    const int dataSize = m_dataStride * m_dataHeight;
    const bool reallocated = newDataSize != dataSize;
    if (reallocated) {
        ::operator delete[](m_data, std::align_val_t(32)); // TODO: is there prettier syntax?
        m_data = static_cast<unsigned char*>(::operator new[](newDataSize, std::align_val_t(32))); // XXX: prettier syntax causes C2956 error on MSVC.
    }
    unsigned char* newData = cairo_image_surface_get_data(surface);
    if (newData == nullptr) {
        throw std::runtime_error(cairo_status_to_string(CAIRO_STATUS_NULL_POINTER));
    }
    cairo_surface_flush(surface);
    if (const cairo_status_t status = cairo_surface_status(surface); status != CAIRO_STATUS_SUCCESS) {
        throw std::runtime_error(cairo_status_to_string(status));
    }
    std::memcpy(m_data, newData, newDataSize);
    const bool reshaped = newWidth != m_dataWidth || newHeight != m_dataHeight;
    m_dataWidth = newWidth;
    m_dataHeight = newHeight;
    m_dataStride = newStride;
    return reallocated || reshaped;
}
