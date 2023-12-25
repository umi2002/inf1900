#include "vector.h"

#include <cmath>

class Area
{
public:
    Area();
    ~Area();
    double calculateArea(Vector finalPoles);

private:
    const uint8_t inchConversion = 121;
    const double  areaDivisor    = 2.0;
};
