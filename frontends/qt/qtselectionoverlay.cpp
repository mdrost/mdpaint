#include "qtselectionoverlay.h"

#include <mdpaint/selectiontool.h>

#include <QPainter>

// public
mdpQtSelectionOverlay::mdpQtSelectionOverlay(QWidget* parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

// public virtual
mdpQtSelectionOverlay::~mdpQtSelectionOverlay() /* override */
{
}

// public
void mdpQtSelectionOverlay::setSelectionTool(const mdpSelectionTool* selectionTool)
{
    m_selectionTool = selectionTool;
    onSelectionToolSelectionChangedConnection = selectionTool->onSelectionChanged(std::bind(&mdpQtSelectionOverlay::onSelectionToolSelectionChanged, this));
}

// public
void mdpQtSelectionOverlay::clearSelectionTool()
{
    m_selection = {};
    onSelectionToolSelectionChangedConnection.disconnect();
    m_selectionTool = nullptr;
    update();
}

// protected virtual
void mdpQtSelectionOverlay::paintEvent(QPaintEvent* e) /* override */
{
    std::visit([this](auto&& selection) {
        using T = std::decay_t<decltype(selection)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
        }
        else if constexpr (std::is_same_v<T, std::vector<mdpPoint>>) {

        }
        else if constexpr (std::is_same_v<T, mdpRectangle>) {
            QPainter p(this);
            QPen pen(Qt::black, 1, Qt::DotLine);
            p.setPen(pen);
            p.drawRect(selection.x(), selection.y(), selection.width(), selection.height());
        }
        else if constexpr (std::is_same_v<T, mdpEllipse>) {
            QPainter p(this);
            QPen pen(Qt::black, 1, Qt::DotLine);
            p.setPen(pen);
            p.drawEllipse(selection.x(), selection.y(), selection.width(), selection.height());
        }
        else {
            static_assert(false, "non-exhaustive visitor!");
        }
    }, m_selection);
}

// private slot
void mdpQtSelectionOverlay::onSelectionToolSelectionChanged()
{
    m_selection = m_selectionTool->selection();
    update();
}
