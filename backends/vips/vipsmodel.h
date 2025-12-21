#ifndef MDP_VIPSMODEL_H
#define MDP_VIPSMODEL_H

#include <mdpaint/signalconnection.h>

#include <vips/vips.h>

#include <functional>

class mdpVipsModel
{
public:

    explicit mdpVipsModel();

    virtual ~mdpVipsModel();

    [[nodiscard]]
    virtual VipsImage* getBaseImage() = 0;

    [[nodiscard]]
    virtual VipsImage* getPreviewImage() = 0;

    virtual void beginDrawing() = 0;

    virtual void endDrawing() = 0;

    virtual void refresh() = 0;

    virtual void submit() = 0;

    virtual void setPreview(VipsImage* newPreviewImage) = 0;

    [[nodiscard]]
    virtual mdpSignalConnection onPreviewReset(std::function<void ()> slot) const = 0;
};

#endif // MDP_VIPSMODEL_H
