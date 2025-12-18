#include "qthistoryentry.h"

// public
mdpQtHistoryEntry::mdpQtHistoryEntry(std::string description, mdpQtModel& qtModel, std::shared_ptr<QImage> image, std::shared_ptr<QPainter> painter) :
    m_description(std::move(description)),
    m_qtModel(qtModel),
    m_image(std::move(image)),
    m_painter(std::move(painter))
{
}

// public virtual
mdpQtHistoryEntry::~mdpQtHistoryEntry() /* override */
{
}

// public virtual
const char* mdpQtHistoryEntry::description() /* override */
{
    return m_description.c_str();
}

// public virtual
void mdpQtHistoryEntry::restore() /* override */
{
    mdpQtModel& qtModel = m_qtModel;
    qtModel.beginDrawing();
    qtModel.setPreview(m_image, m_painter);
    qtModel.endDrawing();
    qtModel.submit();
}
