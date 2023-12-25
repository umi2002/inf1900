#include "svg.h"

void SVG::transmitString(const char string[], uint32_t size)
{
    Communication::transmitUART(string);
    calculateCrc32(string, size);
}

void SVG::calculateCrc32(const char* s, uint32_t n)
{
    crc_ = ~crc_;

    for (uint32_t i = 0; i < n; i++)
    {
        char ch = s[i];
        for (uint32_t j = 0; j < 8; j++)
        {
            uint32_t b   = (ch ^ crc_) & 1;
            crc_       >>= 1;
            if (b)
                crc_ = crc_ ^ 0xEDB88320;
            ch >>= 1;
        }
    }
    crc_ = ~crc_;
}

void SVG::transmitSVG()
{
    Shape shape;
    shape.getPoleCoordinates();
    Vector   finalPoles = shape.convexForm();
    uint16_t area       = Area::calculateArea(finalPoles);

    Communication::transmitUART(0x02);

    transmitString(
        "<svg width=\"100%\" height=\"100%\" "
        "xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1152 "
        "576\">\n\t<rect "
        "x=\"50\" y=\"50\" width=\"960\" height=\"480\" stroke=\"black\" "
        "stroke-width=\"1\" fill=\"white\"/>\n\t<text x=\"50\" y=\"45\" "
        "font-family=\"arial\" font-size=\"20\" fill=\"blue\">Section 02 -- "
        "equipe 3048 -- EMBOT</text>\n\t<text x=\"50\" y=\"550\" "
        "font-family=\"arial\" font-size=\"20\" fill=\"blue\">Aire: ",
        stringSizes_[0]);

    uint8_t nDigits = 0;
    for (uint16_t i = area; i > 0; i /= 10)
    {
        nDigits++;
    }
    char areaString[nDigits];
    itoa(area, areaString, 10);
    transmitString(areaString, nDigits);

    transmitString(" pouces carres</text>\n", stringSizes_[1]);

    transmitString("\t<polygon points=\"", stringSizes_[2]);

    for (uint8_t i = 0; i < finalPoles.getSize(); i++)
    {
        uint8_t  address = finalPoles.getData(i);
        uint16_t x       = 145 + 110 * (address % 8);
        uint16_t y       = 455 - 110 * (address / 8);

        nDigits = 0;
        for (uint16_t k = x; k > 0; k /= 10)
        {
            nDigits++;
        }
        char xString[nDigits];
        itoa(x, xString, 10);
        transmitString(xString, nDigits);

        transmitString(",", stringSizes_[3]);

        nDigits = 0;
        for (uint16_t k = y; k > 0; k /= 10)
        {
            nDigits++;
        }
        char yString[nDigits];
        itoa(y, yString, 10);
        transmitString(yString, nDigits);

        transmitString(" ", stringSizes_[4]);
    }

    transmitString("\" stroke=\"black\" stroke-width=\"1\" fill=\""
                   "green\"/>\n",
                   stringSizes_[5]);

    for (uint8_t i = 0; i < 32; i++)
    {
        uint16_t x = 145 + 110 * (i % 8);
        uint16_t y = 455 - 110 * (i / 8);
        uint8_t  val;
        Memoire24CXXX::lecture(i, &val);

        if (val != 0)
        {
            transmitString("\t<circle cx=\"", stringSizes_[6]);

            nDigits = 0;
            for (uint16_t k = x; k > 0; k /= 10)
            {
                nDigits++;
            }
            char xString[nDigits];
            itoa(x, xString, 10);
            transmitString(xString, nDigits);

            transmitString("\" cy=\"", stringSizes_[7]);

            nDigits = 0;
            for (uint16_t k = y; k > 0; k /= 10)
            {
                nDigits++;
            }
            char yString[nDigits];
            itoa(y, yString, 10);
            transmitString(yString, nDigits);

            transmitString("\" r=\"10\" stroke=\"gray\" "
                           "stroke-width=\"1\" fill=\"gray\"/>\n",
                           stringSizes_[8]);
        }
        else
        {
            transmitString("\t<rect x=\"", stringSizes_[9]);

            nDigits = 0;
            for (uint16_t k = x; k > 0; k /= 10)
            {
                nDigits++;
            }
            char xString[nDigits];
            itoa(x, xString, 10);
            transmitString(xString, nDigits);

            transmitString("\" y=\"", stringSizes_[10]);

            nDigits = 0;
            for (uint16_t k = y; k > 0; k /= 10)
            {
                nDigits++;
            }
            char yString[nDigits];
            itoa(y, yString, 10);
            transmitString(yString, nDigits);

            transmitString("\" width=\"5\" height=\"5\" "
                           "stroke=\"black\" stroke-width=\"1\" "
                           "fill=\"black\"/>\n",
                           stringSizes_[11]);
        }
    }

    transmitString("</svg>\n", stringSizes_[12]);

    Communication::transmitUART(0x03);
}

void SVG::transmitCrc()
{
    char crcString[9];
    convertToHex(crc_, crcString);
    Communication::transmitUART(crcString);
    
    Communication::transmitUART(0x04);
}

void SVG::convertToHex(uint32_t value, char buffer[9])
{
    for (uint8_t i = 0; i < 8; i++)
    {
        buffer[i] = hexDigits_[value % 16];
        value /= 16;
    }

    buffer[8] = '\0';

    uint8_t i = 8;
    uint8_t j = 0;
    while (j < i - 1)
    {
        char temp       = buffer[j];
        buffer[j]  = buffer[i - 1];
        buffer[i - 1] = temp;
        j++;
        i--;
    }
}

uint32_t       SVG::crc_        = 0;
const uint32_t SVG::stringSizes_[13] = {
    369, 22, 18, 1, 1, 49, 13, 6, 54, 10, 5, 70, 7};
const char SVG::hexDigits_[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                   '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
