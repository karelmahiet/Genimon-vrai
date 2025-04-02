#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <ctime>
#include "genimon.h"
#include <thread>
#include <vector>
#include "vecteur.h"
#include "gestionJeu.h"
#include <chrono>
#include <conio.h>
#include <cstdlib>
#include <qlabel.h>
using namespace std;

#define dimensionTerrain_x 10
#define dimensionTerrain_y 10

struct caseGenidex
{
	vector<Genimon> listeGenimonAttrapé;
};

struct genimonChoisi
{
	int indexI = 0;
	int indexJ = 0;
};

class Joueur : public QLabel
{
	Q_OBJECT
public:
	explicit Joueur(int x0 = 25, int y0 = 25, QWidget* parent = nullptr);
	~Joueur();

	void afficherMenuPrincipal();
	void afficherMenuGeniedex(bool afficherObjets);
	void creerTerrain();
	void initialiserJoueur(int pos_x, int pos_y);
	void deplacerJoueur(char direction);
	void changerTerrain();
	void consulterGenidexPartiel(int type);
	void consulterGenidexComplet();
	void consulterHistorique();
	void consulterDétailsType(int typeNumérique, string type);
	void demanderInformationsGenimon(int typeNumérique, string type);
	void gererGenimon();
	void ajouterGenimon(bool refresh);
	void retirerGenimon(bool refresh);
	void choisirStarter();
	bool estSurGenimon();
	bool estSurPorte();
	bool gererCapsuleVie();
	void creerCapsuleVie(bool refresh);
	void guerirGenimon();
	int getNbCapsuleGuerison();
	int position_x;
	int position_y;
	int anciennePosition_x;
	int anciennePosition_y;
	Vecteur<Genimon*> listeGenimons;


	//Séparation en entre les deux terrains
	int borne_x_min;
	int borne_y_min;
	int borne_x_max;
	int borne_y_max;
private:
	QPixmap imageJoueur;   //image de joueur
	char terrain[dimensionTerrain_x][dimensionTerrain_y];
	caseGenidex genidex[8];
	vector<Genimon> historique;
	bool estExterieur;
	int nbGenimonAttrapes;
	int nbBalles;
	int nbCapsuleGuerison;

	void gererAttrapage(Genimon* genimon, int indexGenimon);
	genimonChoisi choisirGenimon(Genimon* genimon, int indexFleche);
	bool gererCombat(Genimon* genimon);
	void afficherStatsManche(Genimon* adversaire, Genimon genimonJoueur);
	genimonChoisi choisirGuerison(int indexFleche);
};

#endif
