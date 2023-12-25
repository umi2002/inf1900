#include "aire.h"

Area::Area() { }

Area::~Area() { }

double Area::calculateArea(Vector finalPoles)
{
    uint8_t initialPole = finalePoles.getData(0);
    finalPoles.push_back(initialPole);  //mettre le premier pole aussi a la fin
                                        //(pour fermer la forme)
    uint8_t n = finalPoles.getSize();

    double area = 0.0;
    for (int i = 0; i < n; i++)
    {  //n ou n+1
        uint8_t j          = (i + 1) % n;
        uint8_t firstPole  = finalPoles.getData(i);
        uint8_t secondPole = finalPoles.getData(j);

        area += (firstPole % 8) * (secondPole / 8);
        area -= (firstPole / 8) * (secondPole % 8);
    }
    return abs(area) / areaDivisor * inchConversion;
}
