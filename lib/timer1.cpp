#include "timer1.h"

void Timer1::initialize()
{
    Register::setBits(&DDRD, PD4, PD5);
}

void Timer1::switchToCtc(uint16_t periodA, uint16_t periodB)
{
    cli();

    Register::clear(&TCNT1, &TCCR1A, &TCCR1B, &TIMSK1);

    OCR1A = periodA * conversion::MS_TO_OCR1X + 1;
    Register::setBits(&TCCR1A, COM1A0); // toggle mode
    Register::setBits(&TCCR1B, WGM12, CS10, CS12); // CTC mode, prescaler = 1024
    Register::setBits(&TIMSK1, OCIE1A); // enable interrupt on compare match

    if (periodB != 0)
    {
        OCR1B = periodB * conversion::MS_TO_OCR1X + 1;
        Register::setBits(&TCCR1A, COM1B0); // toggle mode
        Register::setBits(&TIMSK1, OCIE1B); // enable interrupt on compare match
    }
    sei();
}

void Timer1::switchToPwm(float periodA, float periodB)
{
    cli();

    Register::clear(&TCNT1, &TCCR1A, &TCCR1B, &TIMSK1);

    OCR1A = periodA * conversion::MS_TO_OCR1X + 1;
    Register::setBits(&TCCR1A, COM1A1, WGM10); // pwm, phase correct, 8-bit
    Register::setBits(&TCCR1B, CS10, CS12); // prescaler = 256
    Register::setBits(&TIMSK1, OCIE1A); // enable interrupt on compare match

    if (periodB != 0)
    {
        OCR1B = periodB;
        Register::setBits(&TCCR1A, COM1B1); // pwm, phase correct, 8-bit
        Register::setBits(&TIMSK1, OCIE1B); // enable interrupt on compare match
    }
    sei();
}