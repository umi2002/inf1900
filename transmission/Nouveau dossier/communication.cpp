#include "communication.h"

void Communication::initialize()
{
	UBRR0L = default_setting::BAUD_RATE;
	Register::setBits(&UCSR0B, RXEN0, TXEN0);
	Register::setBits(&UCSR0C, UCSZ01, UCSZ00);

	//Memoire24CXXX::initialize();
}

//void Communication::writeMemory(const uint16_t memoryAddress, uint8_t* data,
//const uint8_t dataLength)
//{
//    Memoire24CXXX::ecriture(memoryAddress, data, dataLength);
//    _delay_ms(delay::MEMORY_WRITING);
//}

unsigned char Communication::receiveUART()
{
	while (!(Register::areBitsSet(&UCSR0A, RXC0)))
		;

	return UDR0;
}

//void Communication::readMemory(const uint16_t memoryAddress, uint8_t* data,
//const uint8_t dataLength)
//{
//    Memoire24CXXX::lecture(memoryAddress, data, dataLength);
//}
