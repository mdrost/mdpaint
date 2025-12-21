#include "vipsimagemodel.h"

#include "vipssignalconnectionprivate.h"

// public
mdpVipsImageModel::mdpVipsImageModel(VipsImage* baseImage) :
    m_previewImage(nullptr),
    m_data(nullptr),
    m_dataWidth(0),
    m_dataHeight(0),
    m_dataStride(0),
    m_drawing(false)
{
    g_object_ref(baseImage);
    m_baseImage = baseImage;
    try {
        beginDrawing();
        refresh();
        endDrawing();
    }
    catch (...) {
        g_object_unref(m_baseImage);
        throw;
    }
}

// public virtual
mdpVipsImageModel::~mdpVipsImageModel() /* override */
{
    ::operator delete[](m_data, std::align_val_t(32)); // TODO: is there prettier syntax?
    g_object_unref(m_previewImage);
    g_object_unref(m_baseImage);
}

// public virtual
VipsImage* mdpVipsImageModel::getBaseImage() /* override */
{
    return m_baseImage;
}

// public virtual
VipsImage* mdpVipsImageModel::getPreviewImage() /* override */
{
    return m_previewImage;
}

// public virtual
void mdpVipsImageModel::beginDrawing() /* override */
{
    assert(!m_drawing);
    m_drawing = true;
}

// public virtual
void mdpVipsImageModel::endDrawing() /* override */
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
void mdpVipsImageModel::refresh() /* override */
{
    assert(m_drawing);
    VipsImage* const baseImage = m_baseImage;
    VipsImage* const previewImage = m_previewImage;
    const int baseWidth = vips_image_get_width(baseImage);
    const int baseHeight = vips_image_get_height(baseImage);
    int previewWidth;
    int previewHeight;
    if (previewImage != nullptr) {
        previewWidth = vips_image_get_width(previewImage);
        previewHeight = vips_image_get_height(previewImage);
    }
    if (previewImage == nullptr || previewWidth != baseWidth || previewHeight != baseHeight) {
        VipsImage* newPreviewImage;
        if (vips_copy(baseImage, &newPreviewImage, nullptr)) {
            throw std::runtime_error(vips_error_buffer());
        }
        setPreview(newPreviewImage);
    }
    else {
        if (vips_image_write(baseImage, previewImage)) {
            throw std::runtime_error(vips_error_buffer());
        }
    }
}

// public virtual
void mdpVipsImageModel::submit() /* override */
{
    assert(!m_drawing);
    VipsImage* const oldBaseImage = m_baseImage;
    m_baseImage = m_previewImage;
    m_previewImage = nullptr;
    try {
        beginDrawing();
        refresh();
        endDrawingInternal();
        m_drawing = false;
    }
    catch (...) {
        m_previewImage = m_baseImage;
        m_baseImage = oldBaseImage;
        throw;
    }
    g_object_unref(oldBaseImage);
    m_previewResetSignal();
}

// public virtual
void mdpVipsImageModel::setPreview(VipsImage* newPreviewImage) /* override */
{
    assert(m_drawing);
    VipsImage* oldPreviewImage = m_previewImage;
    m_previewImage = vips_image_copy_memory(newPreviewImage);
    if (m_previewImage == nullptr) {
        m_previewImage = oldPreviewImage;
        throw std::runtime_error(vips_error_buffer());
    }
    if (oldPreviewImage != nullptr) {
        g_object_unref(oldPreviewImage);
    }
    m_previewResetSignal();
}

// public virtual
mdpSignalConnection mdpVipsImageModel::onPreviewReset(std::function<void ()> slot) const /* override */
{
    return mdpSignalConnection(std::make_unique<mdpVipsSignalConnectionPrivate>(m_previewResetSignal.connect(slot)));
}

// public virtual
const unsigned char* mdpVipsImageModel::data() const /* override */
{
    return m_data;
}

// public virtual
int mdpVipsImageModel::width() const /* override */
{
    return m_dataWidth;
}

// public virtual
int mdpVipsImageModel::height() const /* override */
{
    return m_dataHeight;
}

// public virtual
int mdpVipsImageModel::stride() const /* override */
{
    return m_dataStride;
}

// public virtual
mdpSignalConnection mdpVipsImageModel::onDataChanged(std::function<void ()> slot) const /* override */
{
    return mdpSignalConnection(std::make_unique<mdpVipsSignalConnectionPrivate>(m_dataChangedSignal.connect(slot)));
}

// public virtual
mdpSignalConnection mdpVipsImageModel::onDataReset(std::function<void ()> slot) const /* override */
{
    return mdpSignalConnection(std::make_unique<mdpVipsSignalConnectionPrivate>(m_dataResetSignal.connect(slot)));
}

bool mdpVipsImageModel::endDrawingInternal()
{
    VipsImage* const image = m_previewImage;
    const int newWidth = vips_image_get_width(image);
    const int newHeight = vips_image_get_height(image);
#if 0
    const int newStride = newWidth;
    const int newDataSize = VIPS_IMAGE_SIZEOF_IMAGE(image);
#else
    const int newStride = VIPS_IMAGE_SIZEOF_LINE(image);
    const int newDataSize = newStride * newHeight;
#endif
    const int dataSize = m_dataStride * m_dataHeight;
    const bool reallocated = newDataSize != dataSize;
    if (reallocated) {
        ::operator delete[](m_data, std::align_val_t(32)); // TODO: is there prettier syntax?
        m_data = static_cast<unsigned char*>(::operator new[](newDataSize, std::align_val_t(32))); // XXX: prettier syntax causes C2956 error on MSVC.
    }
#if 0
    VipsImage* const tmp = vips_image_new_from_memory(m_data, newDataSize, newWidth, newHeight, vips_image_get_bands(image), vips_image_get_format(image));
    if (vips_image_write(image, tmp)) {
        g_object_unref(tmp);
        throw std::runtime_error(vips_error_buffer());
    }
    g_object_unref(tmp);
#else
    VipsRegion *region = vips_region_new(image);
    if (region == nullptr) {
        throw std::runtime_error(vips_error_buffer());
    }
    VipsRect rect = {0, 0, newWidth, newHeight};
    if (vips_region_prepare(region, &rect)) {
        g_object_unref(region);
        throw std::runtime_error(vips_error_buffer());
    }
    unsigned char* data = m_data;
    for (int y = 0; y < newHeight;++ y) {
        void *src = VIPS_REGION_ADDR(region, 0, y);
        void *dst = data + y * newStride;
        std::memcpy(dst, src, newStride);
    }
    g_object_unref(region);
#endif
    const bool reshaped = newWidth != m_dataWidth || newHeight != m_dataHeight;
    m_dataWidth = newWidth;
    m_dataHeight = newHeight;
    m_dataStride = newStride;
    return reallocated || reshaped;
}
