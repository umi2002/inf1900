#include "vector.h"

class Shape
{
public:
    Shape();
    ~Shape();

    void convexForm(Vector vectorPole);

private:
    int  distSq(uint8_t p1, uint8_t p2);
    int  orientation(uint8_t p1, uint8_t p2, uint8_t p3);
    void switchPoints(Vector& vectorPole, uint8_t adr1, uint8_t adr2);
    int  compare(uint8_t p1, uint8_t p2, uint8_t p3);
    void getPoleCoordinates();

    Vector poleCoordinates_;
};
