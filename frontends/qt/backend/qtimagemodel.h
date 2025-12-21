#ifndef MDP_QTIMAGEMODEL_H
#define MDP_QTIMAGEMODEL_H

#include "qtmodel.h"

#include <mdpaint/imagemodel.h>

#include <QObject>

class mdpQtImageModel final : public QObject, public mdpQtModel, public mdpImageModel
{
    Q_OBJECT

public:

    explicit mdpQtImageModel(std::unique_ptr<QImage> baseImage, std::unique_ptr<QPainter> basePainter);

    ~mdpQtImageModel() override;

    // mdpQtModel interface:

    [[nodiscard]]
    std::shared_ptr<QImage> getBaseImage() override;

    [[nodiscard]]
    std::shared_ptr<QPainter> getBasePainter() override;

    [[nodiscard]]
    std::shared_ptr<QImage> getPreviewImage() override;

    [[nodiscard]]
    std::shared_ptr<QPainter> getPreviewPainter() override;

    void beginDrawing() override;

    void endDrawing() override;

    void refresh() override;

    void submit() override;

    void setPreview(std::shared_ptr<QImage> newPreviewImage, std::shared_ptr<QPainter> newPreviewPainter) override;

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

Q_SIGNALS:

    void previewReset();

    void dataChanged();

    void dataReset();

private:
    std::shared_ptr<QImage> m_baseImage;
    std::shared_ptr<QPainter> m_basePainter;
    std::shared_ptr<QImage> m_previewImage;
    std::shared_ptr<QPainter> m_previewPainter;
    unsigned char* m_data;
    int m_dataWidth;
    int m_dataHeight;
    int m_dataStride;
    bool m_drawing;
};

#endif // MDP_QTIMAGEMODEL_H
