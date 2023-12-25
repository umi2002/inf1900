#include "point.h"

Point::Point(uint8_t address) : address_(address)
{
    x_ = address % 8;
    y_ = address / 8;
}

void Point::operator=(const Point& other)
{
    address_ = other.address_;
    x_       = other.x_;
    y_       = other.y_;
}

uint8_t Point::address()
{
    return address_;
}

uint8_t Point::x()
{
    return x_;
}

uint8_t Point::y()
{
    return y_;
}
