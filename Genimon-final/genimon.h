#ifndef GENIMON_H
#define GENIMON_H

#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <thread> // Pour sleep_for
#include <chrono> // Pour chrono::milliseconds
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
#include <qlabel.h>
using namespace std;

class Genimon
{
public:
	Genimon();
	Genimon(int typeC, string nomC);
	virtual void apparait();
	void presenter();
	bool capture(int* nbBallesJoueur);
	virtual void setRarete();
	int getTypeNumerique();
	string getType();
	string getTypeSuperieur();
	string getTypeInferieur();
	string getNom();
	string getRarete();
	int getRareteNumerique();
	int getGainBalles();
	int getPV();
	void setPV(int nouveauPV);
	void varierPV(int variation);
	int getDegats();
	int getFacteurDegats();
	int position_x;
	int position_y;
	int pvMax;
protected:
	string nom;
	string rarete;
	string type;
	int typeNumerique;
	int rareteNumerique;
	int facteurChance;
	int gainBalles;

	//variables pour les combats
	string typeSuperieur;
	string typeInferieur;
	int pv;
	int degats;
	int facteurDegats;

	void setNom();
};

#endif
