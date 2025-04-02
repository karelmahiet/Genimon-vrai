#ifndef GESTIONJEU_H
#define GESTIONJEU_H

#include <ctime>

bool evenementActif();
void afficherBienvenue();
void afficherConfirmation();
void afficherPause();
void gererInitialisation();
void gererPause(bool* finPartie);
void gererConfirmation(int option, bool* finPartie);
void gererGeniedex();
void gererHistorique();
void gererPartie();
void gererThread1();
void gererThread2();
void gererThread3();
void gererThread4();

#endif

