#ifndef MDP_VIPSIMAGEMODEL_H
#define MDP_VIPSIMAGEMODEL_H

#include "vipsmodel.h"

#include <mdpaint/imagemodel.h>
#include <mdpaint/signalconnection.h>

#include <vips/vips.h>

#include <boost/signals2/signal.hpp>

class mdpVipsImageModel final : public mdpVipsModel, public mdpImageModel
{
public:

    explicit mdpVipsImageModel(VipsImage* baseImage);

    ~mdpVipsImageModel() override;

    // mdpVipsModel interface:

    [[nodiscard]]
    VipsImage* getBaseImage() override;

    [[nodiscard]]
    VipsImage* getPreviewImage() override;

    void beginDrawing() override;

    void endDrawing() override;

    void refresh() override;

    void submit() override;

    void setPreview(VipsImage* newPreviewImage) override;

    mdpSignalConnection onPreviewReset(std::function<void ()> slot) const override;

    // mdpImageModel interface:

    [[nodiscard]]
    const unsigned char* data() const override;

    [[nodiscard]]
    int width() const override;

    [[nodiscard]]
    int height() const override;

    [[nodiscard]]
    int stride() const override;

    [[nodiscard]]
    mdpSignalConnection onDataChanged(std::function<void ()> slot) const override;

    [[nodiscard]]
    mdpSignalConnection onDataReset(std::function<void ()> slot) const override;

private:

    bool endDrawingInternal();

private:
    VipsImage* m_baseImage;
    VipsImage* m_previewImage;
    mutable boost::signals2::signal<void ()> m_previewResetSignal;
    unsigned char* m_data;
    int m_dataWidth;
    int m_dataHeight;
    int m_dataStride;
    bool m_drawing;
    mutable boost::signals2::signal<void ()> m_dataChangedSignal;
    mutable boost::signals2::signal<void ()> m_dataResetSignal;
};

#endif // MDP_VIPSIMAGEMODEL_H
