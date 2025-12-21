#include "qtrectangularselectiontool.h"

#include "qthistoryentry.h"
#include "qtmodel.h"

#include "../qtsignalconnectionprivate.h"

#include <mdpaint/ellipse.h>
#include <mdpaint/history.h>

#include <QPainter>

// public
mdpQtRectangularSelectionTool::mdpQtRectangularSelectionTool(mdpQtModel& qtModel, mdpHistory& history) :
    m_qtModel(qtModel),
    m_history(history),
    m_previewImage(nullptr),
    m_previewPainter(nullptr),
    m_selecting(false),
    m_dragging(false),
    m_commitedOffsetX(0),
    m_commitedOffsetY(0),
    m_offsetX(0),
    m_offsetY(0)
{
}

// public virtual
mdpQtRectangularSelectionTool::~mdpQtRectangularSelectionTool() /* override */
{
}

// public virtual
void mdpQtRectangularSelectionTool::activate() /* override */
{
    m_previewImage = m_qtModel.getPreviewImage();
    m_previewPainter = m_qtModel.getPreviewPainter();
    onQtModelPreviewResetConnection = m_qtModel.onPreviewReset(std::bind(&mdpQtRectangularSelectionTool::onQtModelPreviewReset, this));
}

// public virtual
void mdpQtRectangularSelectionTool::deactivate() /* override */
{
    onQtModelPreviewResetConnection.disconnect();
    m_previewPainter = nullptr;
    m_previewImage = nullptr;
}

// public virtual
void mdpQtRectangularSelectionTool::mousePressEvent(const int x, const int y) /* override */
{
    const mdpRectangle selectionBoundingRect = selectionBoundingRectangle();
    bool insideSelectionBoundingRectangle = x >= selectionBoundingRect.topLeft().x() && y >= selectionBoundingRect.topLeft().y() &&
                                            x <= selectionBoundingRect.bottomRight().x() && y <= selectionBoundingRect.bottomRight().y();
    if (insideSelectionBoundingRectangle) {
        m_dragging = true;
        m_startingX = x;
        m_startingY = y;
    }
    else {
        if (m_selection.isValid()) {
            //m_history.push(new mdpQtHistoryEntry("Rectangular Selection", m_qtModel, m_previewImage, m_previewPainter));
            m_qtModel.submit();
        }
        m_selecting = true;
        m_startingX = x;
        m_startingY = y;
        m_commitedOffsetX = 0;
        m_commitedOffsetY = 0;
        // Don't create any selection yet.
        // 1x1 selection is not very interesting and maybe we are dealing with a click to deselect.
        m_selection = {};
        Q_EMIT selectionChanged();
    }
}

// public virtual
void mdpQtRectangularSelectionTool::mouseReleaseEvent(const int x, const int y) /* override */
{
    if (m_selecting) {
        m_selecting = false;
        QPainter& painter = *m_previewPainter;
        const mdpRectangle selection = m_selection;
        m_maskImage = QImage(selection.width(), selection.height(), QImage::Format_Grayscale8);
        QImage& maskImage = m_maskImage;
        m_cutoutImage = QImage(selection.width(), selection.height(), QImage::Format_ARGB32_Premultiplied);
        m_commitedOffsetX = 0;
        m_commitedOffsetY = 0;
        m_offsetX = 0;
        m_offsetY = 0;

        maskImage.fill(Qt::white);
        painter.begin(&maskImage);
        painter.setPen(Qt::black);
        painter.drawRect(0, 0, selection.width(), selection.height());
        painter.end();

        const QRect roi(selection.x(), selection.y(), selection.width(), selection.height());
        painter.begin(&m_cutoutImage);
        painter.drawImage(QPoint(0, 0), *m_previewImage, roi);
        painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        painter.drawImage(QPoint(0, 0), maskImage);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.end();
    }
    else if (m_dragging) {
        m_commitedOffsetX += m_offsetX;
        m_commitedOffsetY += m_offsetY;
        m_offsetX = 0;
        m_offsetY = 0;
        m_dragging = false;
    }
}

// public virtual
void mdpQtRectangularSelectionTool::mouseMoveEvent(const int x, const int y) /* override */
{
    if (m_selecting) {
        const auto [x1, x2] = std::minmax(m_startingX, x);
        const auto [y1, y2] = std::minmax(m_startingY, y);
        m_selection = mdpRectangle(mdpPoint(x1, y1), mdpPoint(x2, y2));
        Q_EMIT selectionChanged();
    }
    else if (m_dragging) {
        QPainter& painter = *m_previewPainter;
        const mdpRectangle selection = m_selection;
        m_offsetX = x - m_startingX;
        m_offsetY = y - m_startingY;
        m_qtModel.beginDrawing();
        m_qtModel.refresh();
        painter.drawImage(QPoint(selection.x(), selection.y()), m_maskImage);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(QRect(selection.x(), selection.y(), selection.width(), selection.height()), Qt::white);
        painter.drawImage(QPoint(selection.x() + m_commitedOffsetX + m_offsetX, selection.y() + m_commitedOffsetY + m_offsetY), m_cutoutImage);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        m_qtModel.endDrawing();
        Q_EMIT selectionChanged();
    }
}

// public virtual
void mdpQtRectangularSelectionTool::enterEvent() /* override */
{
}

// public virtual
void mdpQtRectangularSelectionTool::leaveEvent() /* override */
{
}

// public virtual
std::variant<std::monostate, std::vector<mdpPoint>, mdpRectangle, mdpEllipse> mdpQtRectangularSelectionTool::selection() const /* override */
{
    if (m_selection.isNull()) {
        return {};
    }
    return mdpRectangle(m_selection.x() + m_commitedOffsetX + m_offsetX,
                        m_selection.y() + m_commitedOffsetY + m_offsetY,
                        m_selection.width(),
                        m_selection.height());
}

// public virtual
mdpRectangle mdpQtRectangularSelectionTool::selectionBoundingRectangle() const /* override */
{
    return mdpRectangle(m_selection.x() + m_commitedOffsetX + m_offsetX,
                        m_selection.y() + m_commitedOffsetY + m_offsetY,
                        m_selection.width(),
                        m_selection.height());
}

// public virtual
mdpSignalConnection mdpQtRectangularSelectionTool::onSelectionChanged(std::function<void ()> slot) const /* override */
{
    return mdpSignalConnection(std::make_unique<mdpQtSignalConnectionPrivate>(connect(this, &mdpQtRectangularSelectionTool::selectionChanged, slot)));
}

// private slot
void mdpQtRectangularSelectionTool::onQtModelPreviewReset()
{
    m_previewPainter = m_qtModel.getPreviewPainter();
    m_previewImage = m_qtModel.getPreviewImage();
}
