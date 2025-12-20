#ifndef MDP_QTMODEL_H
#define MDP_QTMODEL_H

#include <mdpaint/signalconnection.h>

#include <functional>
#include <memory>

class QImage;
class QPainter;

class mdpQtModel
{
public:

    explicit mdpQtModel();

    virtual ~mdpQtModel();

    [[nodiscard]]
    virtual std::shared_ptr<QImage> getBaseImage() = 0;

    [[nodiscard]]
    virtual std::shared_ptr<QPainter> getBasePainter() = 0;

    [[nodiscard]]
    virtual std::shared_ptr<QImage> getPreviewImage() = 0;

    [[nodiscard]]
    virtual std::shared_ptr<QPainter> getPreviewPainter() = 0;

    virtual void beginDrawing() = 0;

    virtual void endDrawing() = 0;

    virtual void refresh() = 0;

    virtual void submit() = 0;

    virtual void setPreview(std::shared_ptr<QImage> newPreviewImage, std::shared_ptr<QPainter> newPreviewPainter) = 0;

    [[nodiscard]]
    virtual mdpSignalConnection onPreviewReset(std::function<void ()> slot) = 0;
};

#endif // MDP_QTMODEL_H
