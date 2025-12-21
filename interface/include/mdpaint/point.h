#ifndef MDP_INTERFACEPOINT_H
#define MDP_INTERFACEPOINT_H

class mdpPoint
{
public:

    constexpr inline explicit mdpPoint(int x, int y) noexcept;

    constexpr inline int x() const noexcept;

    constexpr inline int y() const noexcept;

private:
    int m_x;
    int m_y;
};

constexpr inline mdpPoint::mdpPoint(int x, int y) noexcept :
    m_x(x),
    m_y(y)
{
}

constexpr inline int mdpPoint::x() const noexcept
{
    return m_x;
}

constexpr inline int mdpPoint::y() const noexcept
{
    return m_y;
}

#endif // MDP_INTERFACEPOINT_H
