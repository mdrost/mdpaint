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

    explicit mdpCairoImageModel();

    ~mdpCairoImageModel() override;

    // mdpCairoModel interface:

    cairo_surface_t* getBaseSurface() override;

    cairo_t* getBaseContext() override;

    cairo_surface_t* getPreviewSurface() override;

    cairo_t* getPreviewContext() override;

    void beginDrawing() override;

    void endDrawing() override;

    void refresh() override;

    void submit() override;

    void setPreview(cairo_surface_t* newPreviewSurface, cairo_t* newPreviewContext) override;

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
    cairo_surface_t* m_baseSurface;
    cairo_t* m_baseContext;
    cairo_surface_t* m_previewSurface;
    cairo_t* m_previewContext;
    boost::signals2::signal<void ()> m_previewResetSignal;
    unsigned char* m_data;
    int m_dataWidth;
    int m_dataHeight;
    int m_dataStride;
    bool m_drawing;
    boost::signals2::signal<void ()> m_dataChangedSignal;
    boost::signals2::signal<void ()> m_dataResetSignal;
};

#endif // MDP_CAIROIMAGEMODEL_H
