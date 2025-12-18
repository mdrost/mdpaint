#ifndef MDP_QTIMAGEMODEL_H
#define MDP_QTIMAGEMODEL_H

#include "qtmodel.h"

#include <mdpaint/imagemodel.h>
#include <mdpaint/signalconnection.h>

#include <boost/signals2/signal.hpp>

class mdpQtImageModel final : public mdpQtModel, public mdpImageModel
{
public:

    explicit mdpQtImageModel();

    ~mdpQtImageModel() override;

    // mdpQtModel interface:

    std::shared_ptr<QImage> getBaseImage() override;

    std::shared_ptr<QPainter> getBasePainter() override;

    std::shared_ptr<QImage> getPreviewImage() override;

    std::shared_ptr<QPainter> getPreviewPainter() override;

    void beginDrawing() override;

    void endDrawing() override;

    void refresh() override;

    void submit() override;

    void setPreview(std::shared_ptr<QImage> newPreviewImage, std::shared_ptr<QPainter> newPreviewPainter) override;

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
    std::shared_ptr<QImage> m_baseImage;
    std::shared_ptr<QPainter> m_basePainter;
    std::shared_ptr<QImage> m_previewImage;
    std::shared_ptr<QPainter> m_previewPainter;
    boost::signals2::signal<void ()> m_previewResetSignal;
    unsigned char* m_data;
    int m_dataWidth;
    int m_dataHeight;
    int m_dataStride;
    bool m_drawing;
    boost::signals2::signal<void ()> m_dataChangedSignal;
    boost::signals2::signal<void ()> m_dataResetSignal;
};

#endif // MDP_QTIMAGEMODEL_H
