#include "svg.h"
#include "button.h"
#include "led.h"
#include "timer1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint16_t DELAY = 2000;
const uint8_t LED_GREEN = (1 << PA0);
const uint8_t LED_OFF = 0;
const uint8_t GREEN_PIN = PA0;
const uint8_t RED_PIN = PA1;
const uint16_t PERIOD = 0.1;

volatile bool gButtonIsPressed = false;
volatile bool gTimerIsExpired = false;

void initInterrupt(void);
uint32_t crc32(const char* s, uint32_t n, uint32_t crc);



int main(){

    Memoire24CXXX::initialize();
    Communication::initialize();
    Timer1::initialize();
    Button::initialize();

    for (int i = 0; i < 32; i++)
    {
        Memoire24CXXX::ecriture(i, 0x00);
    }
    Memoire24CXXX::ecriture(0, 0x01);
    Memoire24CXXX::ecriture(9, 0x01);
    Memoire24CXXX::ecriture(18, 0x01);
    Memoire24CXXX::ecriture(15, 0x01);
    Memoire24CXXX::ecriture(5, 0x01);
    Memoire24CXXX::ecriture(8, 0x01);
    Memoire24CXXX::ecriture(20, 0x01);
    Memoire24CXXX::ecriture(31, 0x01);
    Memoire24CXXX::ecriture(11, 0x01);
    Memoire24CXXX::ecriture(25, 0x01);
    Memoire24CXXX::ecriture(6, 0x01);

    initInterrupt();

    while (true){
    //while(!gButtonIsPressed);
    cli();
    Shape shape;
    if (Button::isClicked()){
    //if(gButtonIsPressed){
        Led::setColor(Color::GREEN);
        _delay_ms(DELAY);
        Led::setColor(Color::OFF);
        Timer1::switchToPwm(PERIOD);
        //shape.getPoleCoordinates(); //Memoire24CXXX::lecture(i, &data);
        SVG::transmitSVG();
        SVG::transmitCrc();
        Timer1::switchToPwm(0);
        Led::setColor(Color::OFF);
        break;
    }
    }

    return 0;
}