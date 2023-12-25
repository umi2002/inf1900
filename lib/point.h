#pragma once

#include "constants.h"

class Point
{
public:
    Point(uint8_t address);
    void    operator=(const Point& other);
    uint8_t address();
    uint8_t x();
    uint8_t y();

private:
    uint8_t address_;
    uint8_t x_;
    uint8_t y_;
};
