#include "communication.h"
#include "led.h"
#include "memoire_24.h"

const uint8_t GREEN_PIN = PA0;
const uint8_t RED_PIN   = PA1;

int main()
{
    Memoire24CXXX::initialize();
    Communication::initialize();
    Register::setBits(&DDRA, GREEN_PIN, RED_PIN);
    Led::initialize(&DDRA, &PORTA, GREEN_PIN, RED_PIN);

    //ordi a carte mere initialise data a la valeur qu'on transmet
    //uint8_t byte = Communication::receiveUART();

    uint16_t initialAddress = 0;
    //Memoire24CXXX::ecriture(initialAddress, byte); //ecrit mem externe

    uint8_t data = '1';

    uint8_t allo;
    //const char allo[] = "allo bonjour";
    ////for (int i = 0; i < 1; i++)
    ////{
    ////uint8_t data = Communication::receiveUART(); //Pc a la carte
    Memoire24CXXX::ecriture(initialAddress, data);  //ecrit dans mem externe
    //Memoire24CXXX::lecture(initialAddress, (uint8_t*)allo);
    Memoire24CXXX::lecture(initialAddress, &allo);  //lit la mem externe
    //for (int i = 0; i < sizeof(allo)-1; i++){
    Communication::transmitUART(allo);  //carte au pc
    //}
    Led::setColor(Color::GREEN);
    //Memoire24CXXX::lecture(initialAddress, &allo);
    ////}

    return 0;
}

//tableau qui prend les points avec 1 s'il y a un point et 0 s'il y en a pas.
//on fait un string de html pour les commandes que python va prendre pour faire
//le svg. meme chose pour le rectangle de la table, les points et tout... avec
//un genre de truc de serie-viaUSB les genre de string vont etre pris par python
//et la il va faire le svg quand il a fini avec tout.
