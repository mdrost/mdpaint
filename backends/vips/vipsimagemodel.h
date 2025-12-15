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

    explicit mdpVipsImageModel();

    ~mdpVipsImageModel() override;

    // mdpVipsModel interface:

    VipsImage* getBaseImage() override;

    VipsImage* getPreviewImage() override;

    void beginDrawing() override;

    void endDrawing() override;

    void refresh() override;

    void submit() override;

    void setPreview(VipsImage* newPreviewImage) override;

    mdpSignalConnection onPreviewReset(std::function<void ()> slot) override;

    // mdpImageModel interface:

    const unsigned char* data() const override;

    int width() const override;

    int height() const override;

    int stride() const override;

    mdpSignalConnection onDataChanged(std::function<void ()> slot) override;

    mdpSignalConnection onDataReset(std::function<void ()> slot) override;

private:

    bool endDrawingInternal();

private:
    VipsImage* m_baseImage;
    VipsImage* m_previewImage;
    boost::signals2::signal<void ()> m_previewResetSignal;
    unsigned char* m_data;
    int m_dataWidth;
    int m_dataHeight;
    int m_dataStride;
    bool m_drawing;
    boost::signals2::signal<void ()> m_dataChangedSignal;
    boost::signals2::signal<void ()> m_dataResetSignal;
};

#endif // MDP_VIPSIMAGEMODEL_H
