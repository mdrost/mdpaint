#ifndef MDP_RESIZESCALESKEWDIALOG_H
#define MDP_RESIZESCALESKEWDIALOG_H

#include <mdpaint/resizescaleskewtool.h>

#include <QDialog>

class mdpResizeScaleSkewDialog : public QDialog
{
    Q_OBJECT

public:

    explicit mdpResizeScaleSkewDialog(int currentWidth, int currentHeight);

    ~mdpResizeScaleSkewDialog() override;

    mdpResizeScaleSkewData getResizeScaleSkewData() const;

private:
    mdpResizeScaleSkewData m_resizeScaleSkewData;
};

#endif // MDP_RESIZESCALESKEWDIALOG_H
