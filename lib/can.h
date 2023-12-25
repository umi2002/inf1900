/**
 * Programme qui encapsule les opérations permettant
 * de convertir valeurs analogiques en valeurs numériques.
 * \file can.h
 * Output: Aucune.
 * Input: Valeurs analogiques transmises par les pins A0 et A1.
 */

#pragma once
#include "constants.h"

/*
 * Classe can:
 *   Le constructeur initialise le convertisseur.
 *   Une lecture enclanche une conversion et le resultat
 *   est retourne sur 16 bits.
 *
 */

class can
{
public:
    static void initialize();

    //retourne la valeur numerique correspondant a la valeur
    //analogique sur le port A.  pos doit etre entre 0 et 7
    //inclusivement.  Seulement les 10 bits de poids faible
    //sont significatifs.
    static uint16_t lecture(uint8_t pos);

private:
    //Donnees membres - aucun
};
