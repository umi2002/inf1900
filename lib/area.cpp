#include "area.h"

#include "debug.h"
#include "point.h"

Area::Area() { }

Area::~Area() { }

uint16_t Area::calculateArea(Vector finalPoles)
{
    uint8_t n = finalPoles.getSize();

    int area = 0;
    for (int i = 0; i < n; i++)
    {  //n ou n+1
        uint8_t j          = (i + 1) % n;
        Point   firstPole  = Point(finalPoles.getData(i));
        uint8_t x1         = firstPole.x();
        uint8_t y1         = firstPole.y();
        Point   secondPole = Point(finalPoles.getData(j));
        uint8_t x2         = secondPole.x();
        uint8_t y2         = secondPole.y();

        area += x1 * y2;
        area -= y1 * x2;
    }
    area = fabs(area) / areaDivisor * inchConversion;
    return area;
}
