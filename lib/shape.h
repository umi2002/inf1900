#include "point.h"
#include "vector.h"

class Shape
{
public:
    Shape();
    ~Shape();

    void   convexForm(Vector vectorPole);
    void   getPoleCoordinates();
    Vector convexForm();

private:
    uint8_t nextToTop(Vector V);
    int     distSq(Point p1, Point p2);
    int     orientation(Point p1, Point p2, Point p3);
    void    switchPoints(uint8_t adr1, uint8_t adr2);
    int     compare(Point p1, Point p2);
    void    sort();

    Vector poleCoordinates_ = Vector(140);
    Point  p0_              = Point(0);
};
