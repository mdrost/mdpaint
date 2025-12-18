#include "qtresizescaleskewdialog.h"

#include "qtspinbox.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

// public
mdpQtResizeScaleSkewDialog::mdpQtResizeScaleSkewDialog(int currentWidth, int currentHeight) :
    m_resizeScaleSkewData({0, 0, currentWidth, currentHeight, true, 0.0, 0.0})
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setObjectName(QStringLiteral("layout"));
    QLabel* titleLabel = new QLabel(tr("Resize, Scale and Skew"), this);
    titleLabel->setObjectName(QStringLiteral("titleLabel"));
    titleLabel->setStyleSheet("font-weight: bold; font-size: 12pt");
    layout->addWidget(titleLabel);
    QLabel* resizeScaleLabel = new QLabel(tr("Resize"), this);
    resizeScaleLabel->setObjectName(QStringLiteral("resizeScaleLabel"));
    resizeScaleLabel->setStyleSheet("font-weight: bold");
    layout->addWidget(resizeScaleLabel);
    QGridLayout* resizeScaleLayout = new QGridLayout();
    layout->addLayout(resizeScaleLayout);
    QLabel* resizeScaleHorizontalLabel = new QLabel(tr("Horizontal"), this);
    resizeScaleHorizontalLabel->setObjectName(QStringLiteral("resizeScaleHorizontalLabel"));
    resizeScaleLayout->addWidget(resizeScaleHorizontalLabel, 0, 0);
    QLabel* resizeScaleVerticalLabel = new QLabel(tr("Vertical"), this);
    resizeScaleVerticalLabel->setObjectName(QStringLiteral("resizeScaleVerticalLabel"));
    resizeScaleLayout->addWidget(resizeScaleVerticalLabel, 0, 2);
    QSpinBox* resizeScaleHorizontalSpinBox = new QSpinBox(this);
    resizeScaleHorizontalSpinBox->setObjectName(QStringLiteral("resizeScaleHorizontalSpinBox"));
    resizeScaleHorizontalSpinBox->setRange(1, std::numeric_limits<int>::max());
    resizeScaleHorizontalSpinBox->setValue(m_resizeScaleSkewData.width);
    resizeScaleLayout->addWidget(resizeScaleHorizontalSpinBox, 1, 0);
    QSpinBox* resizeScaleVerticalSpinBox = new QSpinBox(this);
    resizeScaleVerticalSpinBox->setObjectName(QStringLiteral("resizeScaleVerticalSpinBox"));
    resizeScaleVerticalSpinBox->setRange(1, std::numeric_limits<int>::max());
    resizeScaleVerticalSpinBox->setValue(m_resizeScaleSkewData.height);
    resizeScaleLayout->addWidget(resizeScaleVerticalSpinBox, 1, 2);
    QLabel* skewLabel = new QLabel(tr("Skew"), this);
    skewLabel->setObjectName(QStringLiteral("skewLabel"));
    skewLabel->setStyleSheet("font-weight: bold");
    layout->addWidget(skewLabel);
    QGridLayout* skewLayout = new QGridLayout();
    skewLayout->setObjectName(QStringLiteral("skewLayout"));
    layout->addLayout(skewLayout);
    QLabel* skewHorizontalLabel = new QLabel(tr("Horizontal"), this);
    skewHorizontalLabel->setObjectName(QStringLiteral("skewHorizontalLabel"));
    skewLayout->addWidget(skewHorizontalLabel, 0, 0);
    QLabel* skewVerticalLabel = new QLabel(tr("Vertical"), this);
    skewVerticalLabel->setObjectName(QStringLiteral("skewVerticalLabel"));
    skewLayout->addWidget(skewVerticalLabel, 0, 1);
    QSpinBox* skewHorizontalSpinBox = new mdpQtSpinBox(this);
    skewHorizontalSpinBox->setObjectName(QStringLiteral("skewHorizontalSpinBox"));
    skewHorizontalSpinBox->setRange(-89, 89);
    skewHorizontalSpinBox->setSuffix(QStringLiteral("°"));
    skewHorizontalSpinBox->setValue(m_resizeScaleSkewData.skewX);
    skewLayout->addWidget(skewHorizontalSpinBox, 1, 0);
    QSpinBox* skewVerticalSpinBox = new mdpQtSpinBox(this);
    skewVerticalSpinBox->setObjectName(QStringLiteral("skewVerticalSpinBox"));
    skewVerticalSpinBox->setRange(-89, 89);
    skewVerticalSpinBox->setSuffix(QStringLiteral("°"));
    skewVerticalSpinBox->setValue(m_resizeScaleSkewData.skewY);
    skewLayout->addWidget(skewVerticalSpinBox, 1, 1);
}

// public virtual
mdpQtResizeScaleSkewDialog::~mdpQtResizeScaleSkewDialog() /* override */
{
}

// public
mdpResizeScaleSkewData mdpQtResizeScaleSkewDialog::getResizeScaleSkewData() const
{
    return m_resizeScaleSkewData;
}
