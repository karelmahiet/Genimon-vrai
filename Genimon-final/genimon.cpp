#include "genimon.h"
#include "gestionJeu.h"

Genimon::Genimon()
{
    int random = rand() % 8;
    typeNumerique = random;
    setNom();
    if (random == 0) {
        type = "informatique";
        typeSuperieur = "aucunI";
        typeInferieur = "civil";
    }
    else if (random == 1) {
        type = "electrique";
        typeSuperieur = "aucunE";
        typeInferieur = "batiment";
    }
    else if (random == 2) {
        type = "robotique";
        typeSuperieur = "bioTech";
        typeInferieur = "aucunR";
    }
    else if (random == 3) {
        type = "mecanique";
        typeSuperieur = "civil";
        typeInferieur = "bioTech";
    }
    else if (random == 4) {
        type = "civil";
        typeSuperieur = "informatique";
        typeInferieur = "mecanique";
    }
    else if (random == 5) {
        type = "batiment";
        typeSuperieur = "electrique";
        typeInferieur = "chimique";
    }
    else if (random == 6) {
        type = "bioTech";
        typeSuperieur = "mecanique";
        typeInferieur = "robotique";
    }
    else if (random == 7) {
        type = "chimique";
        typeSuperieur = "batiment";
        typeInferieur = "chimique";
    }

    setRarete();
    facteurDegats = degats/4;
}

Genimon::Genimon(int typeC, string nomC)
{
    if (typeC == 0) {
        type = "informatique";
        typeSuperieur = "aucunI";
        typeInferieur = "civil";
    }
    else if (typeC == 1) {
        type = "electrique";
        typeSuperieur = "aucunE";
        typeInferieur = "batiment";
    }
    else if (typeC == 2) {
        type = "robotique";
        typeSuperieur = "bioTech";
        typeInferieur = "aucunR";
    }
    else if (typeC == 3) {
        type = "mecanique";
        typeSuperieur = "civil";
        typeInferieur = "bioTech";
    }
    else if (typeC == 4) {
        type = "civil";
        typeSuperieur = "informatique";
        typeInferieur = "mecanique";
    }
    else if (typeC == 5) {
        type = "batiment";
        typeSuperieur = "electrique";
        typeInferieur = "chimique";
    }
    else if (typeC == 6) {
        type = "bioTech";
        typeSuperieur = "mecanique";
        typeInferieur = "robotique";

    }
    else if (typeC == 7) {
        type = "chimique";
        typeSuperieur = "batiment";
        typeInferieur = "chimique";
    }

    typeNumerique = typeC;
    nom = nomC;
    rarete = "RARE";
    rareteNumerique = 1;
    facteurChance = 2;
    gainBalles = 15;
    pv = 100 + (rand() % 101); //Entre 100 et 200
    degats = 20 + (rand() % 21); //Entre 20 et 40
    facteurDegats = degats / 4;
    pvMax = pv;
}

void Genimon::setNom()
{
    if (typeNumerique == 0) { // informatique
        int random = rand() % 4;
        if (random == 0)
            nom = "Jeremie";
        else if (random == 1)
            nom = "Alexis";
        else if (random == 2)
            nom = "Karel";
        else if (random == 3)
            nom = "Raphael";
    }
    else if (typeNumerique == 1) { // electrique
        int random = rand() % 4;
        if (random == 0)
            nom = "Florian";
        else if (random == 1)
            nom = "Dylan";
        else if (random == 2)
            nom = "Marek";
        else if (random == 3)
            nom = "Vincent";
    }
    else if (typeNumerique == 2) { // robotique
        int random = rand() % 4;
        if (random == 0)
            nom = "Zack";
        else if (random == 1)
            nom = "Melianne";
        else if (random == 2)
            nom = "Joe";
        else if (random == 3)
            nom = "Ethan";
    }
    else if (typeNumerique == 3) { // mecanique
        int random = rand() % 4;
        if (random == 0)
            nom = "Eric";
        else if (random == 1)
            nom = "Robert";
        else if (random == 2)
            nom = "Olivier";
        else if (random == 3)
            nom = "Isabelle";
    }
    else if (typeNumerique == 4) { // civil
        int random = rand() % 4;
        if (random == 0)
            nom = "Sammuel";
        else if (random == 1)
            nom = "Jeff";
        else if (random == 2)
            nom = "Francois";
        else if (random == 3)
            nom = "Laurianne";

    }
    else if (typeNumerique == 5) { // batiment
        int random = rand() % 4;
        if (random == 0)
            nom = "Steve";
        else if (random == 1)
            nom = "Tony";
        else if (random == 2)
            nom = "Marianne";
        else if (random == 3)
            nom = "Angelie";
    }
    else if (typeNumerique == 6) { // bioTech
        int random = rand() % 4;
        if (random == 0)
            nom = "Philippe";
        else if (random == 1)
            nom = "Lilianne";
        else if (random == 2)
            nom = "Antoine";
        else if (random == 3)
            nom = "Mikael";
    }
    else if (typeNumerique == 7) { // chimique
        int random = rand() % 4;
        if (random == 0)
            nom = "Darnley";
        else if (random == 1)
            nom = "Elon";
        else if (random == 2)
            nom = "Donald";
        else if (random == 3)
            nom = "Justin";
    }
}

void Genimon::setRarete()
{
    bool evenement = evenementActif();
    int random = rand() % 100;

    if (evenement)  //5@8
    {
        if (random < 30)
        {
            rarete = "COMMUN";
            rareteNumerique = 0;
            facteurChance = 4;
            gainBalles = 10;

            pv = 50 + (rand() % 51); //Entre 50 et 100
            degats = 10 + (rand() % 11); //Entre 10 et 20
        }
        else if (random < 60)
        {
            rarete = "RARE";
            rareteNumerique = 1;
            facteurChance = 2;
            gainBalles = 15;

            pv = 100 + (rand() % 101); //Entre 100 et 200
            degats = 20 + (rand() % 21); //Entre 20 et 40
        }
        else if (random < 80)
        {
            rarete = "EPIQUE";
            rareteNumerique = 2;
            facteurChance = 1;
            gainBalles = 20;

            pv = 200 + (rand() % 101); //Entre 200 et 300
            degats = 40 + (rand() % 21); //Entre 40 et 60
        }
        else if (random < 99)
        {
            rarete = "!! LEGENDAIRE !!";
            rareteNumerique = 3;
            facteurChance = 0;
            gainBalles = 25;

            pv = 300 + (rand() % 201); //Entre 300 et 500
            degats = 60 + (rand() % 31); //Entre 60 et 90
        }
        else
        {
            rarete = "*** SECRET ***";
            rareteNumerique = 4;
            facteurChance = 0;
            gainBalles = 30;

            pv = 500 + (rand() % 201); //Entre 500 et 700
            degats = 90 + (rand() % 31); //Entre 90 et 120
        }
    }
    else
    {
        if (random < 50)
        {
            rarete = "COMMUN";
            rareteNumerique = 0;
            facteurChance = 4;
            gainBalles = 10;

            pv = 50 + (rand() % 51); //Entre 50 et 100
            degats = 10 + (rand() % 11); //Entre 10 et 20
        }
        else if (random < 80)
        {
            rarete = "RARE";
            rareteNumerique = 1;
            facteurChance = 2;
            gainBalles = 15;

            pv = 100 + (rand() % 101); //Entre 100 et 200
            degats = 20 + (rand() % 21); //Entre 20 et 40
        }
        else if (random < 95)
        {
            rarete = "EPIQUE";
            rareteNumerique = 2;
            facteurChance = 1;
            gainBalles = 20;

            pv = 200 + (rand() % 101); //Entre 200 et 300
            degats = 40 + (rand() % 21); //Entre 40 et 60
        }
        else if (random < 99)
        {
            rarete = "!! LEGENDAIRE !!";
            rareteNumerique = 3;
            facteurChance = 0;
            gainBalles = 25;

            pv = 300 + (rand() % 201); //Entre 300 et 500
            degats = 60 + (rand() % 31); //Entre 60 et 90
        }
        else
        {
            rarete = "*** SECRET ***";
            rareteNumerique = 4;
            facteurChance = 0;
            gainBalles = 30;

            pv = 500 + (rand() % 201); //Entre 500 et 700
            degats = 90 + (rand() % 31); //Entre 90 et 120
        }

        pvMax = pv;
    }
}

void Genimon::apparait() {
    cout << endl << "    -----Un Genimon sauvage " << rarete << " de type " << type << " apparait!-----" << endl;
    cout << "                   -----Il s'agit de " << nom << "-----                       " << endl;
    cout << "-----Il possede " << pv << " points de vie et il attaque avec " << degats << " de degats.-----" << endl << endl;
}

void Genimon::presenter() {
    cout << "\nInteraction avec " << nom << ", Type: " << type;
    cout << ", Rarete: " << rarete << ", PV: " << pv;
    cout << ", Degats: " << degats << endl << endl;
}

int Genimon::getTypeNumerique() {
    return typeNumerique;
}

string Genimon::getType() {
    return type;
}

string Genimon::getTypeSuperieur()
{
    return typeSuperieur;
}

string Genimon::getTypeInferieur()
{
    return typeInferieur;
}

string Genimon::getRarete() {
    return rarete;
}

int Genimon::getRareteNumerique() {
    return rareteNumerique;
}

string Genimon::getNom() {
    return nom;
}

int Genimon::getPV() {
    return pv;
}

void Genimon::setPV(int nouveauPV)
{
    pv = nouveauPV;
}

void Genimon::varierPV(int variation)
{
    pv += variation;
}

int Genimon::getDegats() {
    return degats;
}

int Genimon::getFacteurDegats()
{
    return facteurDegats;
}

int Genimon::getGainBalles()
{
    return gainBalles;
}

bool Genimon::capture(int* nbBallesJoueur)
{
    extern bool bouton1_On;
    extern bool bouton2_On;
    extern int numBouton;
    bool captureReussie = false;
    bool captureFinie = false;

    while (!captureFinie)
    {      
        if (*nbBallesJoueur <= 0)
        {
            cout << "Nombre de balles insuffisantes" << endl;
            cout << nom << " s'est echappe..." << endl;
            cout << endl << "-----Fin du face a face-----" << endl << endl;
            captureFinie = true;
        }
        else
        {
            cout << "Nombre de balles restantes: " << *nbBallesJoueur << endl;
            cout << "Voulez-vous le capturer? (1 pour oui et 2 pour non)" << endl;
            while (!bouton1_On && !bouton2_On);

            bool estCapturé = false;
            if (numBouton == 1) {
                cout << "Balle lancee!" << endl;
                (*nbBallesJoueur)--;
                int random = rand() % 20;
                if (random >= 0 && random < (8 + facteurChance)) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "--1--" << endl;
                    random = rand() % 20;
                    if (random >= 0 && random < (10 + facteurChance)) {
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        cout << "--2--" << endl;
                        random = rand() % 20;
                        if (random >= 0 && random < (12 + facteurChance)) {
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            cout << nom << " capture! Bravo" << endl;
                            estCapturé = true;
                            captureReussie = true;
                            captureFinie = true;
                            cout << endl << "-----Fin du face a face-----" << endl << endl;
                        }
                    }
                }
                if (!estCapturé) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << nom << " s'est echappe de la balle..." << endl << endl;
                }
            }
            else {
                cout << nom << " s'est enfuit..." << endl;
                cout << endl << "-----Fin du face a face-----" << endl << endl;
                captureFinie = true;
            }
        }
    }

    return captureReussie;
}
