#include "wheels.h"

void Wheels::initialize()
{
    Register::setBits(&DDRB,
                      directionPinLeft_,
                      directionPinRight_,
                      intensityPinLeft_,
                      intensityPinRight_);

    Register::setBits(&TCCR0A, WGM00);

    Register::setBits(&TCCR0A, COM0A1);
    Register::setBits(&TCCR0A, COM0B1);
    Register::setBits(&TCCR0B, CS01);
}

void Wheels::adjustLeft(uint8_t speed)
{
    OCR0A = speed * max::PWM_VALUE / conversion::TO_PERCENTAGE;
}

void Wheels::adjustRight(uint8_t speed)
{
    OCR0B = speed * max::PWM_VALUE / conversion::TO_PERCENTAGE;
}

void Wheels::moveForward(uint8_t speed)
{
    Register::setBits(outputPort_, directionPinLeft_, directionPinRight_);

    adjustLeft(speed);
    adjustRight(speed);
}

void Wheels::moveBackward(uint8_t speed)
{
    Register::clearBits(outputPort_, directionPinLeft_, directionPinRight_);

    adjustLeft(speed);
    adjustRight(speed);
}

void Wheels::changeDirectionLeft()
{
    Register::toggleBits(outputPort_, directionPinLeft_);
}

void Wheels::changeDirectionRight()
{
    Register::toggleBits(outputPort_, directionPinRight_);
}

void Wheels::rotateRight()
{
    Wheels::moveForward(min::NULL_SPEED);
    _delay_ms(delay::STOP);
    Wheels::moveForward(max::SPEED);
    Wheels::changeDirectionRight();
    _delay_ms(delay::ROTATION);
    Wheels::moveForward(min::NULL_SPEED);
    _delay_ms(delay::STOP);
}

void Wheels::rotateLeft()
{
    Wheels::moveForward(min::NULL_SPEED);
    _delay_ms(delay::STOP);
    Wheels::moveForward(max::SPEED);
    Wheels::changeDirectionLeft();
    _delay_ms(delay::ROTATION);
    Wheels::moveForward(min::NULL_SPEED);
    _delay_ms(delay::STOP);
}

volatile uint8_t* Wheels::outputPort_        = &PORTB;
const uint8_t     Wheels::intensityPinLeft_  = PB3;
const uint8_t     Wheels::intensityPinRight_ = PB4;
const uint8_t     Wheels::directionPinLeft_  = PB5;
const uint8_t     Wheels::directionPinRight_ = PB6;
