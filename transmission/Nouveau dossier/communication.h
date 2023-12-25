/*
 * Programme de la classe communication. Cette classe sert a gérer
 * les communications entre le PC et la carte mere.
 * \file communication.h
 * \auteurs équipe 3048
 * \date   13 mars 2023
 * Créé le 1 mars 2023
 */
#pragma once
#include "register.h"

class Communication
{
public:
	static void initialize();

	template<typename T>
	static void transmitUART(T data);

	template<typename T>
	static void transmitUART(T data[]);

	template<typename... T>
	static void transmitUART(T... data);

	static unsigned char receiveUART();
};

#include "communication.tpp"
