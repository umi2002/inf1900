#include "shape.h"
using namespace std;

uint8_t maxColumns = 8;

Shape::Shape() { }

Shape::~Shape() { }

uint8_t Shape::nextToTop(Vector< uint8_t > V)
{
    uint8_t p = V.top();
    V.pop();
    uint8_t res = V.top();
    V.push(p);
    return res;
}

//ici on devrait avoir un tableau qui indique si on a un poteau ou non (a faire
//dans lecture de la memoire externe) ecrire les coordonnees (x,y) pour chaque
//poteau
// struct PoleType{
//     int x;
//     int y;
// };

//int calculateCoordinates(){
//    PoleType *pole;
//    vector<PoleType> poleTable;

////poleTable = [];
//int x = 0;
//int y = 0;

void Shape::getPoleCoordinates()
{
    uint8_t data;

    for (int i = 0; i < 32; i++)
    {
        Memoire24CXXX::lecture(i, &data);
        poleCoordinates_.push_back(data);
    }
}

//for (int i = 0; i < tab.size(); i++){
//    if (tab[i] == 1){
//        if (i >= 0 & i<= 7){
//            y = 0;
//        }
//        elif (i >= 8 & i<= 15){
//            y = 1;
//        }
//        elif (i>= 16 & i <= 23){
//            y = 2;
//        }
//        elif (i>= 24 & i <= 31){
//            y = 3;
//        }
//        x = i - y * 8;
//        poleTable.push_back((x,y));
//    }

//else{
//    rien
//}
//}
//};

//Algorithm Graham

int Shape::distSq(uint8_t p1, uint8_t p2)
{
    //---- get les coordonnees x et y -----------------
    uint8_t pole1 = vectorPole.getData(p1);
    uint8_t p1x   = pole1 % 8;
    uint8_t p1y   = pole1 / 8;
    uint8_t pole2 = vectorPole.getData(p2);
    uint8_t p2x   = pole2 % 8;
    uint8_t p2y   = pole2 / 8;
    return (p1x - p2x) * (p1x - p2x) + (p1y - p2y) * (p1y - p2y);
}

int Shape::orientation(uint8_t p1, uint8_t p2, uint8_t p3)
{
    //return ((P3.x-P1.x) * (P2.y-P1.y) - (P3.y-P1.y) * (P2.x-P1.x)) > 0;

    //---- get les coordonnees x et y -----------------
    uint8_t pole1 = vectorPole.getData(p1);
    uint8_t p1x   = pole1 % 8;
    uint8_t p1y   = pole1 / 8;
    uint8_t pole2 = vectorPole.getData(p2);
    uint8_t p2x   = pole2 % 8;
    uint8_t p2y   = pole2 / 8;
    uint8_t pole3 = vectorPole.getData(p3);
    uint8_t p3x   = pole3 % 8;
    uint8_t p3y   = pole3 / 8;

    int value = (p2y - p1y) * (p3x - p2x) - (p2x - p1x) * (p3y - p2y);
    if (value == 0)
    {
        return 0;
    }
    return (value > 0) ? 1 : 2;
};

void Shape::switchPoints(Vector& vectorPole, uint16_t adr1, uint16_t adr2)
{  //fonction qui switch les poteaux
    uint8_t p1 = vectorPole.getData(adr1);
    uint8_t p2 = vectorPole.getData(adr2);
    vectorPole.writeData(adr1, p2);
    vectorPole.wrtieData(adr2, p1);
};

int Shape::compare(uint8_t p1, uint8_t p2, uint8_t p3)
{
    //uint8_t p1 = (uint8_t*)vp1;
    //uint8_t p2 = (uint8_t*)vp2;
    //// PoleType *p1 = (PoleType *)vp1;
    //// PoleType *p2 = (PoleType *)vp2;

    int o = orientation(p1, p2, p3);
    if (o == 0)
    {
        return (distSq(p0, p2) >= distSq(p0, p1)) ? -1 : 1;
    }
    return (o == 2) ? -1 : 1;
    //et si o == 1 ?
}

void Shape::convexForm(Vector vectorPole)
{
    //------------ trouver les cooredonnees du point de depart -----------------

    PoleType pole0;
    uint16_t n         = vectorPole.getSize();
    uint8_t  poleIndex = vectorPole.getData(0);
    uint8_t  ymin      = poleIndex / 8;
    uint8_t  min       = 0;

    //------------- Trouver le poteau le plus bas ------------------------------
    for (int i = 1; i < n; i++)
    {
        int y = poleTable[i].y;  //y = au y a l indice i dans le tableau

        if ((y < ymin) || (ymin == y && poleTable[i].x < poleTable[min].x))
        {
            ymin = poleTable[i].y, min = i;
        }
    }
    //------------- Switch pour mettre le plus bas a l<indice 0
    //------------------
    switchPoints(40, 40 + min);

    uint8_t pole0 = vectorPole.getData(0);
    //pole0 = poleTable[0];
    uint8_t pole1 = vectorPole.getData(1);
    qsort(&pole1, n - 1, n, compare);  //A VOIR SI OK OU NON + COMPARE

    //qsort(&poleTable[1], n-1, sizeof(poleTable), compare); //faire la methode
    //compare!!
    int m = 1;
    poleM = vectorPole.getData(m);
    for (int i = 1; i < n; i++)
    {
        pole     = vectorPole.getData(i);
        nextPole = vectorPole.getData(i + 1);
        while (i < n - 1 && orientation(p0, ))
            while (i < n - 1 && orientation(p0, pole, nextPole) == 0)
                i++;
        poleM = pole;
        m++;
    }
    if (m < 3)
    {
        return;
    }
    uint8_t         p0 = vectorPole.getData(0);
    uint8_t         p1 = vectorPole.getData(1);
    uint8_t         p2 = vectorPole.getData(2);
    stack< Vector > V;
    V.push_back(p0);
    V.push_back(p1);
    V.push_back(p2);

    for (int i = 3; i < m; i++)
    {
        while (V.getSize() > 1 && orientation(nextToTop(V), V.top(), pole) != 2)
            V.pop();
        V.push(pole);
    }

    while (!V.empty())
    {
        uint8_t val = V.top();
        V.pop();
    }
}
