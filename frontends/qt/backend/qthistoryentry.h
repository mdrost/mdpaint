#ifndef MDP_QTHISTORYENTRY_H
#define MDP_QTHISTORYENTRY_H

#include "qtmodel.h"

#include <mdpaint/historyentry.h>

#include <string>

class mdpQtHistoryEntry : public mdpHistoryEntry
{
public:

    explicit mdpQtHistoryEntry(std::string description, mdpQtModel& qtModel, std::shared_ptr<QImage> image, std::shared_ptr<QPainter> painter);

    ~mdpQtHistoryEntry() override;

    const char* description() override;

    void restore() override;

private:
    std::string m_description;
    mdpQtModel& m_qtModel;
    std::shared_ptr<QImage> m_image;
    std::shared_ptr<QPainter> m_painter;
};

#endif // MDP_QTHISTORYENTRY_H
