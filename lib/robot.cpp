#include "robot.h"

void Robot::initialize()
{
    Led::initialize(&DDRA, &PORTA, PA0, PA1);
    Wheels::initialize();
    Memoire24CXXX::initialize();
    Sound::initialize();
}

uint16_t Robot::getTotalAdrresses()
{
    uint8_t lowByte  = 0;
    uint8_t highByte = 0;
    Memoire24CXXX::lecture(address_++, &highByte);
    Memoire24CXXX::lecture(address_--, &lowByte);

    return ((highByte << BYTE_LENGTH) | lowByte) - COMMANDS_START_ADDRESS;
}

void Robot::loadListCommands(uint8_t listCommands[], const uint16_t nBytes)
{
    listCommands_ = listCommands;

    for (uint16_t i = COMMANDS_START_ADDRESS; i < nBytes; i++)
        Memoire24CXXX::lecture(i, &listCommands_[i]);
}

void Robot::loadCommand()
{
    instruction_ = listCommands_[address_++];
    operand_     = listCommands_[address_++];
}

void Robot::execCommand()
{
    static uint8_t  loopIterations   = 0;
    static uint16_t loopBeginAdrress = 0;

    if (instruction_ == 0x01)
        isStarted_ = true;

    if (!isStarted_)
        return;

    switch (instruction_)
    {
        case 0x01 :
            break;
        case 0x02 :
            for (uint16_t i = 0; i < operand_ * conversion::OPERAND_TO_MS; i++)
                _delay_ms(delay::MS);

            break;
        case 0x44 :
            switch (operand_)
            {
                case 0x01 :
                    Led::setColor(Color::GREEN);
                    break;
                case 0x02 :
                    Led::setColor(Color::RED);
                    break;
            }
            break;
        case 0x45 :
            Led::setColor(Color::OFF);
            break;
        case 0x48 :
            Sound::playNote(operand_);
            break;
        case 0x09 :
            Sound::stopSound();
            break;
        case 0x60 :
            Wheels::moveForward(min::NULL_SPEED);
            break;
        case 0x61 :
            Wheels::moveForward(min::NULL_SPEED);
            break;
        case 0x62 :
            Wheels::moveForward(operand_ * conversion::TO_PERCENTAGE
                                / max::PWM_VALUE);
            break;
        case 0x63 :
            Wheels::moveBackward(operand_ * conversion::TO_PERCENTAGE
                                 / max::PWM_VALUE);
            break;
        case 0x64 :
            Wheels::rotateLeft();
            break;
        case 0x65 :
            Wheels::rotateRight();
            break;
        case 0xC0 :
            loopIterations   = operand_;
            loopBeginAdrress = address_;
            break;
        case 0xC1 :
            if (loopIterations <= 0)
                break;
            loopIterations--;
            address_ = loopBeginAdrress;
            loadCommand();
            execCommand();
            break;
        case 0xFF :
            isStarted_ = false;
            break;
    }
}

uint8_t* Robot::listCommands_;
uint16_t Robot::address_;
uint8_t  Robot::instruction_;
uint8_t  Robot::operand_;
bool     Robot::isStarted_;
