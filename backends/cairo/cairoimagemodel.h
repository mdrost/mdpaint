#ifndef MDP_CAIROIMAGEMODEL_H
#define MDP_CAIROIMAGEMODEL_H

#include "cairomodel.h"

#include <mdpaint/imagemodel.h>
#include <mdpaint/signalconnection.h>

#include <cairo/cairo.h>

#include <boost/signals2/signal.hpp>

class mdpCairoImageModel final : public mdpCairoModel, public mdpImageModel
{
public:

    explicit mdpCairoImageModel(cairo_surface_t* baseSurface, cairo_t* baseContext);

    ~mdpCairoImageModel() override;

    // mdpCairoModel interface:

    [[nodiscard]]
    cairo_surface_t* getBaseSurface() override;

    [[nodiscard]]
    cairo_t* getBaseContext() override;

    [[nodiscard]]
    cairo_surface_t* getPreviewSurface() override;

    [[nodiscard]]
    cairo_t* getPreviewContext() override;

    void beginDrawing() override;

    void endDrawing() override;

    void refresh() override;

    void submit() override;

    void setPreview(cairo_surface_t* newPreviewSurface, cairo_t* newPreviewContext) override;

    [[nodiscard]]
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
    cairo_surface_t* m_baseSurface;
    cairo_t* m_baseContext;
    cairo_surface_t* m_previewSurface;
    cairo_t* m_previewContext;
    mutable boost::signals2::signal<void ()> m_previewResetSignal;
    unsigned char* m_data;
    int m_dataWidth;
    int m_dataHeight;
    int m_dataStride;
    bool m_drawing;
    mutable boost::signals2::signal<void ()> m_dataChangedSignal;
    mutable boost::signals2::signal<void ()> m_dataResetSignal;
};

#endif // MDP_CAIROIMAGEMODEL_H
