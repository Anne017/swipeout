#include "block.h"

Block::Block(const int &id, const int &x, const int &y, const int &height, const int &width, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_startX(x),
    m_x(x),
    m_startY(y),
    m_y(y),
    m_height(height),
    m_width(width)
{

}

int Block::id() const
{
    return m_id;
}

void Block::setId(const int &id)
{
    m_id = id;
}

int Block::startX() const
{
    return m_startX;
}

int Block::x() const
{
    return m_x;
}

void Block::setX(const int &x)
{
    m_x = x;
    emit xChanged();
}

int Block::startY() const
{
    return m_startY;
}

int Block::y() const
{
    return m_y;
}

void Block::setY(const int &y)
{
    m_y = y;
    emit yChanged();
}

int Block::width() const
{
    return m_width;
}

void Block::setWidth(const int &width)
{
    m_width = width;
}

int Block::height() const
{
    return m_height;
}

void Block::setHeight(const int &height)
{
    m_height = height;
}

void Block::resetPosition()
{
    setX(m_startX);
    setY(m_startY);
    emit positionResetted();
}

