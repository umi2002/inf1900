#include "svg.h"

int main()
{
    Memoire24CXXX::initialize();
    Communication::initialize();

    for (int i = 0; i < 32; i++)
    {
        Memoire24CXXX::ecriture(i, 0x00);
    }
    Memoire24CXXX::ecriture(18, 0x01);
    Memoire24CXXX::ecriture(15, 0x01);
    Memoire24CXXX::ecriture(5, 0x01);
    Memoire24CXXX::ecriture(8, 0x01);
    Memoire24CXXX::ecriture(20, 0x01);
    Memoire24CXXX::ecriture(6, 0x01);
    Memoire24CXXX::ecriture(24, 0x01);
    Memoire24CXXX::ecriture(13, 0x01);
    Memoire24CXXX::ecriture(28, 0x01);

    SVG::transmitSVG();
    SVG::transmitCrc();

    return 0;
}
