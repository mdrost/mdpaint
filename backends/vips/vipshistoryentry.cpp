#include "vipshistoryentry.h"

// public
mdpVipsHistoryEntry::mdpVipsHistoryEntry(std::string description, mdpVipsModel& vipsModel, VipsImage* image) :
    m_description(std::move(description)),
    m_vipsModel(vipsModel),
    m_image(image)
{
    g_object_ref(image);
}

// public virtual
mdpVipsHistoryEntry::~mdpVipsHistoryEntry() /* override */
{
    g_object_unref(m_image);
}

// public virtual
const char* mdpVipsHistoryEntry::description() /* override */
{
    return m_description.c_str();
}

// public virtual
void mdpVipsHistoryEntry::restore() /* override */
{
    mdpVipsModel& vipsModel = m_vipsModel;
    vipsModel.beginDrawing();
    vipsModel.setPreview(m_image);
    vipsModel.endDrawing();
    vipsModel.submit();
}
