#include "timer.h"

void Timer::initialize()
{
    Register::setBits(&DDRD, PD6, PD7);
}

void Timer::switchToCtc(uint8_t outputCompareValueA,
                        uint8_t outputCompareValueB)
{
    cli();

    Register::clear(&TCNT2, &TCCR2A, &TCCR2B, &TIMSK2);

    OCR2A = outputCompareValueA;
    Register::setBits(&TCCR2A, COM2A0, WGM21);  //toggle mode
    Register::setBits(&TCCR2B, CS21, CS22);     //CTC mode, prescaler = ??

    if (outputCompareValueB != 0)
    {
        OCR2B = outputCompareValueB;
        Register::setBits(&TCCR2A, COM2B0);  //toggle mode
        Register::setBits(&TIMSK2, OCIE2B);  //enable interrupt on compare match
    }
    sei();
}

void Timer::switchToPwm(uint8_t outputCompareValueA,
                        uint8_t outputCompareValueB)
{
    cli();

    Register::clear(&TCNT2, &TCCR2A, &TCCR2B, &TIMSK2);

    OCR2A = outputCompareValueA;
    Register::setBits(&TCCR2A, COM2A1, WGM20);  //pwm, phase correct, 8-bit
    Register::setBits(&TCCR2B, CS22);           //prescaler = 256
    Register::setBits(&TIMSK2, OCIE2A);  //enable interrupt on compare match

    if (outputCompareValueB != 0)
    {
        OCR2B = outputCompareValueB;
        Register::setBits(&TCCR2A, COM2B1);  //pwm, phase correct, 8-bit
        Register::setBits(&TIMSK2, OCIE2B);  //enable interrupt on compare match
    }
    sei();
}
