#ifndef MDP_QTRESIZESCALESKEWDIALOG_H
#define MDP_QTRESIZESCALESKEWDIALOG_H

#include <mdpaint/resizescaleskewtool.h>

#include <QDialog>

class mdpQtResizeScaleSkewDialog : public QDialog
{
    Q_OBJECT

public:

    explicit mdpQtResizeScaleSkewDialog(int currentWidth, int currentHeight);

    ~mdpQtResizeScaleSkewDialog() override;

    mdpResizeScaleSkewData getResizeScaleSkewData() const;

private:
    mdpResizeScaleSkewData m_resizeScaleSkewData;
};

#endif // MDP_QTRESIZESCALESKEWDIALOG_H
