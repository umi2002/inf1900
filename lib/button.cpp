#include "button.h"

volatile uint8_t* Button::port_            = &PIND;
   const uint8_t  Button::buttonPin_       = PD2;
            bool  Button::wasPressedState_ = false;

void Button::initialize()
{
    Register::clearBits(&DDRD, buttonPin_);
}

bool Button::isPressed()
{
    if (!Register::areBitsSet(port_, buttonPin_))
        return wasPressedState_ = false;

    _delay_ms(delay::DEBOUNCING);
    return wasPressedState_ = Register::areBitsSet(port_, buttonPin_); 
}

bool Button::isClicked()
{
    return wasPressedState_ & !isPressed(); // Utilisez & à la place de && pour éviter l'évaluation conditionnelle courte (short-circuiting)
}

void Button::enableInterrupt()
{
    cli();
    Register::setBits(&EIMSK, INT0); // Activer l'interruption externe 0
    Register::setBits(&EICRA, ISC00, ISC01); // Configurer l'interruption externe 0 pour se déclencher sur tout changement logique
    sei();
}