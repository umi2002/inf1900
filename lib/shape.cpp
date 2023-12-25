#include "shape.h"

#include "debug.h"
#include "memoire_24.h"
#include "vector.h"

uint8_t maxColumns = 8;

Shape::Shape() { }

Shape::~Shape() { }

uint8_t Shape::nextToTop(Vector V)
{
    uint8_t nextToTopIndex = V.getSize() - 2;
    uint8_t res            = V.getData(nextToTopIndex);

    return res;
}

void Shape::getPoleCoordinates()
{
    uint8_t data;

    for (int i = 0; i < 32; i++)
    {
        Memoire24CXXX::lecture(i, &data);
        if (data == 0x01)
        {
            poleCoordinates_.push_back(i);
        }
    }
}

//Algorithm Graham
//https://www.geeksforgeeks.org/convex-hull-using-graham-scan/

int Shape::distSq(Point p1, Point p2)
{
    //---- get les coordonnees x et y -----------------
    uint8_t x1 = p1.x();
    uint8_t y1 = p1.y();
    uint8_t x2 = p2.x();
    uint8_t y2 = p2.y();

    return square(x1 - x2) + square(y1 - y2);
}

int Shape::orientation(Point p1, Point p2, Point p3)
{

    //---- get les coordonnees x et y -----------------
    uint8_t x1 = p1.x();
    uint8_t y1 = p1.y();
    uint8_t x2 = p2.x();
    uint8_t y2 = p2.y();
    uint8_t x3 = p3.x();
    uint8_t y3 = p3.y();

    int value = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);
    if (value == 0)
    {
        return 0;
    }

    return (value > 0) ? 1 : 2;
};

void Shape::switchPoints(uint8_t adr1, uint8_t adr2)
{  //fonction qui switch les poteaux
    uint8_t p1 = poleCoordinates_.getData(adr1);
    uint8_t p2 = poleCoordinates_.getData(adr2);

    poleCoordinates_.writeData(adr1, p2);
    poleCoordinates_.writeData(adr2, p1);
};

int Shape::compare(Point p1, Point p2)
{
    int o = orientation(p0_, p1, p2);
    if (o == 0)
    {
        return (distSq(p0_, p2) >= distSq(p0_, p1)) ? -1 : 1;
    }

    return (o == 2) ? -1 : 1;
}

void Shape::sort()
{
    uint8_t n = poleCoordinates_.getSize();

    for (uint8_t i = 1; i < n; i++)
    {
        uint8_t j = i;

        Point p1 = Point(poleCoordinates_.getData(j - 1));
        Point p2 = Point(poleCoordinates_.getData(j));

        bool comparison = compare(p1, p2) == 1;
        while (j > 0 && comparison)
        {
            switchPoints(j - 1, j);
            j--;
            p1         = Point(poleCoordinates_.getData(j - 1));
            p2         = Point(poleCoordinates_.getData(j));
            comparison = compare(p1, p2) == 1;
        }
    }
}

Vector Shape::convexForm()
{
    //------------ trouver les cooredonnees du point de depart -----------------

    uint8_t n = poleCoordinates_.getSize();
    p0_       = Point(poleCoordinates_.getData(0));
    sort();

    uint8_t m = 1;

    for (int i = m; i < n; i++)
    {
        Point pole     = Point(poleCoordinates_.getData(i));
        Point nextPole = Point(poleCoordinates_.getData(i + 1));
        while (i < n - 1 && orientation(p0_, pole, nextPole) == 0)
        {
            i++;
            pole     = Point(poleCoordinates_.getData(i));
            nextPole = Point(poleCoordinates_.getData(i + 1));
        }

        pole = Point(poleCoordinates_.getData(i));
        poleCoordinates_.writeData(m, pole.address());
        m++;
    }

    uint8_t p0 = poleCoordinates_.getData(0);
    uint8_t p1 = poleCoordinates_.getData(1);
    uint8_t p2 = poleCoordinates_.getData(2);
    Vector  V  = Vector(200);
    V.push_back(p0);
    V.push_back(p1);
    V.push_back(p2);

    for (int i = 3; i < m; i++)
    {
        Point p1 = Point(nextToTop(V));
        Point p2 = Point(V.getData(V.getSize() - 1));
        Point p3 = Point(poleCoordinates_.getData(i));

        while (V.getSize() > 1 && orientation(p1, p2, p3) != 2)
        {
            V.pop_back();
            p1 = Point(nextToTop(V));
            p2 = Point(V.getData(V.getSize() - 1));
        }
        V.push_back(p3.address());
    }

    return V;
}
