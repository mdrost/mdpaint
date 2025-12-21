#ifndef MDP_INTERFACEELLIPSE_H
#define MDP_INTERFACEELLIPSE_H

#include "point.h"

class mdpEllipse
{
public:

    constexpr inline mdpEllipse() noexcept;

    constexpr inline explicit mdpEllipse(int x, int y, int width, int height) noexcept;

    constexpr inline explicit mdpEllipse(const mdpPoint& topLeft, const mdpPoint& bottomRight) noexcept;

    constexpr inline bool isNull() const noexcept;

    constexpr inline bool isValid() const noexcept;

    constexpr inline int x() const noexcept;

    constexpr inline int y() const noexcept;

    constexpr inline int width() const noexcept;

    constexpr inline int height() const noexcept;

    constexpr inline mdpPoint topLeft() const noexcept;

    constexpr inline mdpPoint bottomRight() const noexcept;

private:
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;
};

constexpr inline mdpEllipse::mdpEllipse() noexcept :
    m_x1(0),
    m_y1(0),
    m_x2(-1),
    m_y2(-1)
{
}

constexpr inline mdpEllipse::mdpEllipse(int x, int y, int width, int height) noexcept :
    m_x1(x),
    m_y1(y),
    m_x2(x + width - 1),
    m_y2(y + height - 1)
{
}

constexpr inline mdpEllipse::mdpEllipse(const mdpPoint& topLeft, const mdpPoint& bottomRight) noexcept :
    m_x1(topLeft.x()),
    m_y1(topLeft.y()),
    m_x2(bottomRight.x()),
    m_y2(bottomRight.y())
{
}

constexpr inline bool mdpEllipse::isNull() const noexcept
{
    return m_x1 == (m_x2 - 1) && m_y1 == (m_y2 - 1);
}

constexpr inline bool mdpEllipse::isValid() const noexcept
{
    return m_x2 >= m_x1 && m_y2 >= m_y1;
}

constexpr inline int mdpEllipse::x() const noexcept
{
    return m_x1;
}

constexpr inline int mdpEllipse::y() const noexcept
{
    return m_y1;
}

constexpr inline int mdpEllipse::width() const noexcept
{
    return m_x2 - m_x1 + 1;
}

constexpr inline int mdpEllipse::height() const noexcept
{
    return m_y2 - m_y1 + 1;
}

constexpr inline mdpPoint mdpEllipse::topLeft() const noexcept
{
    return mdpPoint(m_x1, m_y1);
}

constexpr inline mdpPoint mdpEllipse::bottomRight() const noexcept
{
    return mdpPoint(m_x2, m_y2);
}

#endif // MDP_INTERFACEELLIPSE_H
