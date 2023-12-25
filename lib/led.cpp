#include "led.h"

void Led::initialize(volatile uint8_t* modePort,
                     volatile uint8_t* port,
                     uint8_t           pinGreen,
                     uint8_t           pinRed)
{
    port_     = port;
    pinGreen_ = pinGreen;
    pinRed_   = pinRed;
    Register::setBits(modePort, pinGreen, pinRed);
}

void Led::setColor(Color color)
{
    switch (color)
    {
        case Color::GREEN :
            Register::setBits(port_, pinGreen_);
            Register::clearBits(port_, pinRed_);
            break;

        case Color::RED :
            Register::setBits(port_, pinRed_);
            Register::clearBits(port_, pinGreen_);
            break;

        case Color::OFF :
            Register::clearBits(port_, pinGreen_, pinRed_);
            break;

        case Color::AMBER :
            setColor(Color::GREEN);
            _delay_ms(delay::GREEN_AMBER);
            setColor(Color::RED);
            _delay_ms(delay::RED_AMBER);
            break;
    }
}

volatile uint8_t* Led::port_;
uint8_t           Led::pinGreen_;
uint8_t           Led::pinRed_;
