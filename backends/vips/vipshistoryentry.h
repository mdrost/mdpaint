#ifndef MDP_VIPSHISTORYENTRY_H
#define MDP_VIPSHISTORYENTRY_H

#include "vipsmodel.h"

#include <mdpaint/historyentry.h>

#include <vips/vips.h>

#include <string>

class mdpVipsHistoryEntry : public mdpHistoryEntry
{
public:

    explicit mdpVipsHistoryEntry(std::string description, mdpVipsModel& vipsModel, VipsImage* image);

    ~mdpVipsHistoryEntry() override;

    const char* description() override;

    void restore() override;

private:
    std::string m_description;
    mdpVipsModel& m_vipsModel;
    VipsImage* m_image;
};

#endif // MDP_CAIROHISTORYENTRY_H
