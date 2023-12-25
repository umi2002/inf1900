#include "button.h"
#include "can.h"
#include "led.h"
#include "memoire_24.h"
#include "sound.h"
#include "svg.h"
#include "timer1.h"
#include "wheels.h"

using u8  = uint8_t;
using u16 = uint16_t;

enum class Distance  //-> enum
{
    INVALID,
    SIDE_LENGTH_INCH_11,
    DIAG_LENGTH_INCH_11,
    SIDE_LENGTH_INCH_22,
    DIAG_LENGTH_INCH_22
};

const u8 validVoltages[4][2] = {
    {80, 255}, //  11 inches side
    {44, 79 }, //  11 inches diag
    {30, 43 }, //  22 inches side
    {21, 29 }, //  22 inches diag
};

const u16 TIME_TO_ARRIVE_AT[] = {
    0,     //invalid distance
    0,     //11 inches side
    1000,  //11 inches diag
    2400,  //22 inches side
    4000,  //22 inches diag
};

u16 target[] = {0,  //voltage (distance)
                0,  //distance
                0,  //angle   (direction)
                0};

const u8 VOLTAGE  = 0;
const u8 DISTANCE = 1;
const u8 ANGLE    = 2;

const u8 NUMBER_OF_ANGLE = 8;

const u16    TIME_TICK_RATE           = 1;
const u16    TIME_TO_TURN_360_DEGREES = 5500;  //4200 //5500
const u16    TWO_SECONDS              = 2000;
volatile u16 time                     = 0;

const u8  NOTES_REPETITION         = 3;
const u8  HIGH_PITCH_NOTE          = 80;
const u16 HIGH_PITCH_NOTE_DURATION = 300;
const u8  LOW_PITCH_NOTE           = 60;
const u16 LOW_PITCH_NOTE_DURATION  = 2000;

const u8 WHEELS_SPEED = 50;
const u8 NULL_SPEED   = 0;

const u8 SIMPLE_SIZE              = 10;
const u8 UNSIGNIFICANT_BITS       = 2;
const u8 NUMBER_OF_VALID_DISTANCE = 4;

volatile bool isInterruptButtonPressed = false;
volatile bool isWhiteButtonPressed     = false;

bool isTargetFound      = true;
bool isPointingToRight  = false;
u8   targetMemoryAdress = 0;

ISR(INT0_vect)
{
    isInterruptButtonPressed = true;

    _delay_ms(delay::DEBOUNCING);

    Register::setBits(&EIFR, INTF0);
}

ISR(INT1_vect)
{
    isWhiteButtonPressed = true;

    _delay_ms(delay::DEBOUNCING);

    Register::setBits(&EIFR, INTF1);
}

ISR(TIMER1_COMPA_vect)
{
    ++time;
}

void enableWhiteButton()
{
    cli();

    Register::setBits(&EIMSK, INT1);
    Register::setBits(&EICRA, ISC10, ISC11);

    sei();
}

void initializeTimer(u16 cycleDurationMs)
{
    cli();

    TCNT1 = 0;
    OCR1A = (float)cycleDurationMs * 7.8125;

    TCCR1A |= (1 << COM1A0);                       //toggle mode
    TCCR1B |=
        (1 << WGM12) | (1 << CS12) | (1 << CS10);  //prescaler = 1024, CTC mode
    TIMSK1 |= (1 << OCIE1A);                       //enable timer interrupt

    TCCR1C = 0;

    sei();
}

void initialize()
{
    Led::initialize(&DDRD, &PORTD, PD4, PD5);

    Button::initialize();
    Button::enableInterrupt();
    enableWhiteButton();

    Wheels::initialize();

    can::initialize();

    Sound::initialize();

    Communication::initialize();

    Memoire24CXXX::initialize();
}

void stopTimer1()
{
    Register::clear(&TCNT1, &TCCR1A, &TCCR1B, &TIMSK1);
}

void waitForSignals(volatile bool& isInterruptButtonPressed,
                    volatile bool& isWhiteButtonPressed)
{
    isInterruptButtonPressed = isWhiteButtonPressed = false;

    while (!isInterruptButtonPressed && !isWhiteButtonPressed)
        ;
}

void setLedAmberUntil(volatile bool& isInterruptButtonPressed,
                      volatile bool& isWhiteButtonPressed)
{
    isInterruptButtonPressed = isWhiteButtonPressed = false;

    while (!isInterruptButtonPressed && !isWhiteButtonPressed)
    {
        Led::setColor(Color::AMBER);
    }
}

void blinkLedAmberUntil(volatile bool& isButtonInterruptPressed)
{
    isButtonInterruptPressed = false;

    while (!isButtonInterruptPressed)
    {
        for (u8 i = 0; i < 25; ++i)
        {
            Led::setColor(Color::AMBER);
        }

        Led::setColor(Color::OFF);
        _delay_ms(250);
    }
}

void makeHighPitchNoise()
{
    for (u8 i = 0; i < NOTES_REPETITION; ++i)
    {
        Sound::playNote(HIGH_PITCH_NOTE);
        _delay_ms(HIGH_PITCH_NOTE_DURATION);

        Sound::stopSound();
        _delay_ms(HIGH_PITCH_NOTE_DURATION);
    }
}

void makeLowPitchNoise()
{
    Sound::playNote(LOW_PITCH_NOTE);

    _delay_ms(LOW_PITCH_NOTE_DURATION);

    Sound::stopSound();
}

void blinkLedRed()
{
    while (true)
    {
        Led::setColor(Color::RED);
        _delay_ms(250);

        Led::setColor(Color::OFF);
        _delay_ms(250);
    }
}

void startTurning()
{
    Wheels::moveForward(100);
    Wheels::changeDirectionLeft();
    _delay_ms(400);
    Wheels::adjustLeft(WHEELS_SPEED);
    Wheels::adjustRight(WHEELS_SPEED);
}

void stopTurning()
{
    Wheels::moveForward(NULL_SPEED);
}

u8 measureAverageVoltage()
{
    u16 sumVoltage = 0;

    for (u8 i = 0; i < SIMPLE_SIZE; ++i)
    {
        sumVoltage += can::lecture(PA0) >> UNSIGNIFICANT_BITS;
    }

    return sumVoltage / SIMPLE_SIZE;
}

Distance estimateDistance(u8 voltage)
{
    for (u8 i = 0; i < NUMBER_OF_VALID_DISTANCE; ++i)
        if (voltage >= validVoltages[i][0] && voltage <= validVoltages[i][1])
            return static_cast<Distance>(i + 1);

    return Distance::INVALID;
}

// void approachTarget2()
// {
//     if (target[DISTANCE] < 2)
//     {
//         return;
//     }

//     bool isDistanceCorrect = false;

//     while (!isDistanceCorrect)
//     {
//         time = 0;
//         while (time <= 2 * TIME_TO_TURN_360_DEGREES)
//         {
//             Wheels::adjustRight(65);
//             _delay_ms(100);
//             Wheels::adjustRight(NULL_SPEED);
//             u8       voltage  = measureAverageVoltage();
//             Distance distance = estimateDistance(voltage);
//             if ((u16)distance <= target[DISTANCE]
//                 && distance != Distance::INVALID)
//             {
//                 if (voltage >= validVoltages[0][0])
//                 {
//                     isDistanceCorrect = true;
//                 }
//                 break;
//             }
//         }

//         if (time >= 2 * TIME_TO_TURN_360_DEGREES)
//         {
//             isTargetFound = false;
//             break;
//         }

//         time = 0;
//         while (time <= 2 * TIME_TO_TURN_360_DEGREES)
//         {
//             Wheels::adjustLeft(65);
//             _delay_ms(100);
//             Wheels::adjustLeft(NULL_SPEED);
//             u8       voltage  = measureAverageVoltage();
//             Distance distance = estimateDistance(voltage);
//             if ((u16)distance <= target[DISTANCE]
//                 && distance != Distance::INVALID)
//             {
//                 if (voltage >= validVoltages[0][0])
//                 {
//                     isDistanceCorrect = true;
//                 }
//                 break;
//             }
//         }
//         if (time >= 2 * TIME_TO_TURN_360_DEGREES)
//         {
//             isTargetFound = false;
//             break;
//         }
//     }

//     Wheels::adjustLeft(75);
//     _delay_ms(200);
//     Wheels::adjustLeft(NULL_SPEED);
// }

void approachTarget(u8 angle)
{
    u8 voltage = measureAverageVoltage();
    Distance distance = estimateDistance(voltage);

    // tourner selon l'angle
    if (target[ANGLE] >= 4)
    {
        Wheels::adjustLeft(60);
        time = 0;
        while (time < target[3] - 1000);
    }

    while (true)
    {
        // tourner a droite jusqu'a ce que le capteur detecte la cible
        Wheels::adjustLeft(50);

        time = 0;

        while (true)
        {
            voltage  = measureAverageVoltage();
            distance = estimateDistance(voltage);

            if (time >= 5 * TIME_TO_TURN_360_DEGREES)
            {
                isTargetFound = false;
                return;
            }

            if (distance != Distance::INVALID)
            {
                break;
            }
        }

        // avancer
        Wheels::adjustRight(60);
        _delay_ms(500);


        // detecter encore la cible
        voltage = measureAverageVoltage();

        
        // si la cible est detectee, arreter
        if (voltage >= validVoltages[0][0])
        {
            Wheels::adjustRight(0);
            Wheels::adjustLeft(0);
            return;
        }


        // sinon, tourner a gauche et repeter le processus
        Wheels::adjustLeft(0);
        _delay_ms(500);

        Wheels::adjustRight(0);
    }

}

void sendDataToComputer()
{
    Led::setColor(Color::GREEN);
    _delay_ms(2000);

    initializeTimer(50);

    SVG::transmitSVG();
    SVG::transmitCrc();

    Register::clear(&TCNT1, &TCCR1A, &TCCR1B, &TIMSK1);
    PORTD &= ~(1 << PD5);
    PORTD &= ~(1 << PD4);
    // uint8_t data;
    // for (uint8_t i = 0; i < 32; i++)
    // {
    //     Memoire24CXXX::lecture(i, &data);
    //     Communication::transmitUART(data);
    // }
}

u8 determineAngle(volatile u16 time)
{
    return (NUMBER_OF_ANGLE * time / TIME_TO_TURN_360_DEGREES)
         % NUMBER_OF_ANGLE;
}

bool failFilterTest(u8 voltage, Distance distance, u8 angle)
{
    return (voltage <= target[VOLTAGE]);
}

void scan360Degrees()
{
    u8       adcVoltage = 0;
    Distance distance   = Distance::INVALID;
    u8       angle      = 0;

    time = 0;

    Wheels::adjustLeft(60);

    while (time < TIME_TO_TURN_360_DEGREES)
    {
        adcVoltage = measureAverageVoltage();
        distance   = estimateDistance(adcVoltage);
        angle      = determineAngle(time);

        if (failFilterTest(adcVoltage, distance, angle))
        {
            continue;
        }

        target[VOLTAGE]  = adcVoltage;
        target[DISTANCE] = static_cast<u8>(distance);
        target[ANGLE]    = angle;
        target[3]        = time;
    }

    Wheels::adjustLeft(NULL_SPEED);
}

void writePositionInMemory()
{
    const int8_t TABLE[] = {8, 9, 1, -7, -8, -9, -1, 7, 8, 9};

    auto scalarProduct = [TABLE](u8 norm, u8 angle)
    {
        return TABLE[target[ANGLE] + (isPointingToRight ? 2 : 0)]
             * (norm < 3 ? 1 : 2);
    };

    targetMemoryAdress += scalarProduct(target[DISTANCE], target[ANGLE]);

    Memoire24CXXX::ecriture(targetMemoryAdress, 0x01);
}

int main()
{
    initialize();

    waitForSignals(isInterruptButtonPressed, isWhiteButtonPressed);

    if (isWhiteButtonPressed)
    {
        sendDataToComputer();

        return 0;
    }

    for (u8 i = 0; i < 32; i++)
    {
        Memoire24CXXX::ecriture(i, 0x00);
    }

    setLedAmberUntil(isInterruptButtonPressed, isWhiteButtonPressed);

    Led::setColor((isPointingToRight = isWhiteButtonPressed) ? Color::RED
                                                             : Color::GREEN);

    _delay_ms(TWO_SECONDS);

    while (true)
    {
        DDRD &= ~(1 << PD4);
        DDRD &= ~(1 << PD5);
        initializeTimer(TIME_TICK_RATE);
        scan360Degrees();

        if (!(isTargetFound = target[DISTANCE]))
        {
            break;
        }
        _delay_ms(2000);
        approachTarget(target[DISTANCE]);
        if (!(isTargetFound))
        {
            break;
        }

        writePositionInMemory();
        isPointingToRight = false;
        target[VOLTAGE]  = 0;
        target[DISTANCE] = 0;
        target[ANGLE]    = 0;

        Register::clear(&TCNT1, &TCCR1A, &TCCR1B, &TIMSK1);
        makeHighPitchNoise();

        DDRD |= (1 << PD4);
        DDRD |= (1 << PD5);
        blinkLedAmberUntil(isInterruptButtonPressed);
    }

    makeLowPitchNoise();

    Register::clear(&TCNT1, &TCCR1A, &TCCR1B, &TIMSK1);
    DDRD |= (1 << PD4);
    DDRD |= (1 << PD5);
    blinkLedRed();

    return 0;
}
