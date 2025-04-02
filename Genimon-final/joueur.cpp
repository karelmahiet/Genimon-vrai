#include "joueur.h"
#include <QDebug>
#include "combat.h"

Joueur::Joueur(int x0, int y0, QWidget* parent)
    :QLabel(parent)
{
    initialiserJoueur(x0, y0);
    creerTerrain();

    imageJoueur.load(":/Decor/Image_Qt/Decor/ChatGPT.png");
    setPixmap(imageJoueur.scaled(120, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setScaledContents(true);
    resize(120, 70);
    move(680,550); // Place l'image sur la map
    show();
}

Joueur::~Joueur()
{
    listeGenimons.vider();
}

void Joueur::initialiserJoueur(int pos_x, int pos_y)
{
    position_x = 50;
    position_y = 45;
    anciennePosition_x = pos_x;
    anciennePosition_y = pos_y;

    borne_x_min = 0;
    borne_y_min = 0;
    borne_x_max = 70;
    borne_y_max = 50;
    estExterieur = true;
    nbGenimonAttrapes = 0;
    nbBalles = 20;
    nbCapsuleGuerison = 0;
}

void Joueur::deplacerJoueur(char direction)
{
    anciennePosition_x = position_x;
    anciennePosition_y = position_y;

    if (direction == 'w' && position_y > 0) position_y--;
    else if (direction == 's' && position_y < 20) position_y++;
    else if (direction == 'a' && position_x > 0) position_x--;
    else if (direction == 'd' && position_x < 36) position_x++;

    move(position_x * 32, position_y * 32); //deplace joueur

    qDebug() << "Joueur : " << position_x << "," << position_y;

    for (int i = 0; i < listeGenimons.Taille(); ++i) {
        Genimon* g = listeGenimons[i];
        qDebug() << "Genimon " << i << ": " << g->position_x << "," << g->position_y;
    }

}

void Joueur::choisirStarter()
{
    extern bool bouton1_On;
    extern bool bouton2_On;
    extern int numBouton;
    int typeChoisi;
    string nomChoisi;

    cout << "\nEntrez le nom de votre premier Genimon:  ";
    cin >> nomChoisi;
    cout << "\nPour determiner son type, repondez a ce petit quiz pour qu'il puisse vous representer." << endl;
    cout << "Vous devez repondre par oui (1) ou par non (2) a chaque question." << endl;
    cout << "Premierement voulez-vous repondre au quiz? Sinon un type aleatoire sera choisi." << endl << endl;

    while (!bouton1_On && !bouton2_On);

    if (numBouton == 1)
    {
        cout << "----Debut du quiz----" << endl;
        cout << "Est ce que 80% est une mauvaise note? " << endl;   
        while (!bouton1_On && !bouton2_On);

        if (numBouton == 1) {
            cout << "Est que la physique c'est cool?" << endl;     
            while (!bouton1_On && !bouton2_On);

            if (numBouton == 1)
            {
                cout << "Tu es un genie robotique" << endl;
                typeChoisi = 2;
            }
            else {
                cout << "Est ce que des trucs morts c'est cool?? " << endl;
                while (!bouton1_On && !bouton2_On);

                if (numBouton == 1)
                {
                    cout << "Tu es un genie biotech" << endl;
                    typeChoisi = 6;
                }
                else {
                    cout << "Tu es un genie chimique" << endl;
                    typeChoisi = 7;
                }
            }
        }
        else {
            cout << "Est ce que tu pense que les ordinateurs fonctionnent avec de l'essence? " << endl;
            while (!bouton1_On && !bouton2_On);

            if (numBouton == 1)
            {
                cout << "Hmmm, interessant... " << endl;
                cout << "Tu es un genie mecanique" << endl;
                typeChoisi = 3;
            }
            else {
                cout << "Est ce que tu sais c'est quoi un Amplis-Op? " << endl;
                while (!bouton1_On && !bouton2_On);

                if (numBouton == 1) {
                    cout << "Est ce qu'il te font peur? " << endl;
                    while (!bouton1_On && !bouton2_On);

                    if (numBouton == 1)
                    {
                        cout << "Tu es un genie informatique" << endl;
                        typeChoisi = 0;
                    }
                    else {
                        cout << "Tu es un genie electrique" << endl;
                        typeChoisi = 1;
                    }
                }
                else {
                    cout << "Est ce qu t'es basic? " << endl;
                    while (!bouton1_On && !bouton2_On);

                    if (numBouton == 1)
                    {
                        cout << "Tu es un genie civil" << endl;
                        typeChoisi = 4;
                    }
                    else {
                        cout << "Tu es un genie du batiment" << endl;
                        typeChoisi = 5;
                    }
                }
            }
        }
    }
    else
    {
        typeChoisi = rand() % 8;
        cout << "Type aleatoire choisi" << endl;
    }

    Genimon* premierGenimon = new Genimon(typeChoisi, nomChoisi);
    genidex[premierGenimon->getTypeNumerique()].listeGenimonAttrapé.push_back(*premierGenimon);
    nbGenimonAttrapes++;

    cout << "\nVotre premier Genimon est " << premierGenimon->getNom() << ", Type: " << premierGenimon->getType();
    cout << ", Rarete: " << premierGenimon->getRarete() << ", PV: " << premierGenimon->getPV();
    cout << ", Degats: " << premierGenimon->getDegats() << endl << endl;

    cout << "Appuyez sur --1-- pour lancer la partie" << endl;

    while (!bouton1_On);
}

void Joueur::changerTerrain()
{
    if (estExterieur)
    {
        borne_x_min = 21;
        borne_y_min = 0;
        borne_x_max = 37;
        borne_y_max = 14;
        estExterieur = false;
        position_x += 2;
    }
    else
    {
        borne_x_min = 0;
        borne_y_min = 0;
        borne_x_max = 21;
        borne_y_max = 21;
        estExterieur = true;
        position_x -= 2;
    }
}

void Joueur::creerTerrain()
{
    for (int y = 0; y < dimensionTerrain_y; y++) {
        for (int x = 0; x < dimensionTerrain_x; x++) {
            terrain[x][y] = '.';
            if ((x == 20 || x == 21) && (y == 11 || y == 10 || y == 9))
            {
                terrain[x][y] = 'X';
            }
        }
    }
    terrain[position_x][position_y] = '1';

    //On crée 6 Genimons au début
    for (int i = 0; i < 6; i++)
    {
        ajouterGenimon(false);
    }
}

bool Joueur::estSurGenimon()
{
    return terrain[position_x][position_y] == '2';
}

bool Joueur::estSurPorte()
{
    return terrain[position_x][position_y] == 'X';
}

bool Joueur::gererCapsuleVie()
{
    if (terrain[position_x][position_y] == 'V' && nbCapsuleGuerison < 9)
    {
        nbCapsuleGuerison++;
        terrain[position_x][position_y] == '.';
        return true;
    }
    else
    {
        return false;
    }
}

int Joueur::getNbCapsuleGuerison()
{
    return nbCapsuleGuerison;
}

void Joueur::ajouterGenimon(bool refresh)
{
    Genimon* nouveauGenimon = new Genimon;
    listeGenimons.ajouterElement(nouveauGenimon);

    int pos_x = rand() % dimensionTerrain_x;
    int pos_y  = rand() % dimensionTerrain_y;

    //Genimon n'apparait pas sur un objet ou hors terrain
    while (terrain[pos_x][pos_y] == '1' || terrain[pos_x][pos_y] == 'X' || terrain[pos_x][pos_y] == '2' || terrain[pos_x][pos_y] == 'V'
        || (pos_x >= 21 && pos_y >= 14))
    {
        pos_x = rand() % dimensionTerrain_x;
        pos_y = rand() % dimensionTerrain_y;
    }
    listeGenimons[listeGenimons.Taille() - 1]->position_x = pos_x;
    listeGenimons[listeGenimons.Taille() - 1]->position_y = pos_y;
    terrain[pos_x][pos_y] = '2';

    if (refresh)
    {
        //afficherPartie();
    }
}

void Joueur::retirerGenimon(bool refresh)
{
    int indexRandom = rand() % listeGenimons.Taille(); //Retire un genimon random
    terrain[listeGenimons[indexRandom]->position_x][listeGenimons[indexRandom]->position_y] = '.';
    listeGenimons.retirerElement(indexRandom);
}

void Joueur::creerCapsuleVie(bool refresh)
{
    int pos_x = rand() % dimensionTerrain_x;
    int pos_y = rand() % dimensionTerrain_y;

    //La capsule de vie n'apparait pas sur un objet ou hors terrain
    while (terrain[pos_x][pos_y] == '1' || terrain[pos_x][pos_y] == 'X' || terrain[pos_x][pos_y] == '2' || terrain[pos_x][pos_y] == 'V'
        || (pos_x >= 21 && pos_y >= 14))
    {
        pos_x = rand() % dimensionTerrain_x;
        pos_y = rand() % dimensionTerrain_y;
    }

    terrain[pos_x][pos_y] = 'V';

    if (refresh)
    {
        //afficherPartie();
    }
}

void Joueur::gererGenimon()
{
    //recherche du genimon
    Genimon* genimon = listeGenimons[0]; //par défaut
    bool genimonTrouve = false;
    int indexGenimon = 0;
    for (int i = 0; i < listeGenimons.Taille(); i++)
    {
        if (listeGenimons[i]->position_x == position_x && listeGenimons[i]->position_y == position_y)
        {
            genimon = listeGenimons[i];
            indexGenimon = i;
            genimonTrouve = true;
        }
    }

    if (genimonTrouve)
    {
        extern bool bouton1_On;
        extern bool bouton2_On;
        extern bool bouton4_On;
        extern int numBouton;
        historique.push_back(*genimon);

        #ifdef _WIN32
                system("cls");
        #endif
        genimon->apparait();

        cout << "\nAppuyer sur --1-- pour l'attraper, sur --2-- pour le combattre ou sur --4-- pour quitter" << endl;
        while (!bouton1_On && !bouton2_On && !bouton4_On);

        if (numBouton == 1)
        {
            if (nbBalles <= 0)
            {
                cout << "Vous n'avez aucune balle, la capture est impossible. Allez combattre des Genimons pour essayer de gagner plus de balles" << endl << endl;
                cout << "Appuyez sur --4-- pour retourner au jeu" << endl;
                
                while(!bouton4_On);
            }
            else
            {
                gererAttrapage(genimon, indexGenimon);
            }
        }
        else if (numBouton == 2)
        {
            if (nbGenimonAttrapes <= 0)
            {
                cout << "Votre Genidex est vide, donc vous ne pouvez pas combattre. Allez capturer des Genimons sur la faculte" << endl << endl;
                cout << "Appuyez sur --4-- pour retourner au jeu" << endl;
                
                while (!bouton4_On);
            }
            else
            {
                gererCombat(genimon);
            }
        }
    }
}

genimonChoisi Joueur::choisirGenimon(Genimon* genimon, int indexFleche)
{
    #ifdef _WIN32
        system("cls");
    #endif
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                               Duel contre un Genimon !                           " << endl << endl;
    cout << "                         Choisissez un Genimon pour le combat                     " << endl << endl << endl;
    cout << "                    Utilisez les touches w et s pour la selection                 " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    genimon->presenter();
    cout << "\nFaites un choix dans l'inventaire:" << endl;

    int compteur = 1;
    genimonChoisi infos;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < genidex[i].listeGenimonAttrapé.size(); j++)
        {
            if (indexFleche == compteur)
            {
                cout << "--> ";
                infos.indexI = i;
                infos.indexJ = j;
            }
            cout << compteur << ") " << "Nom: " << genidex[i].listeGenimonAttrapé[j].getNom() << ", Type: " << genidex[i].listeGenimonAttrapé[j].getType();
            cout << ", Rarete: " << genidex[i].listeGenimonAttrapé[j].getRarete() << ", PV: " << genidex[i].listeGenimonAttrapé[j].getPV();
            cout << ", Degats: " << genidex[i].listeGenimonAttrapé[j].getDegats() << endl;
            compteur++;
        }
    }

    cout << "\nAppuyez sur --1-- pour confirmer le choix ou sur --4-- pour abandonner le combat" << endl << endl;

    return infos;
}

void Joueur::afficherStatsManche(Genimon* adversaire, Genimon genimonJoueur)
{
    cout << adversaire->getNom() << " a " << adversaire->getPV() << " de PV" << endl;
    cout << genimonJoueur.getNom() << " a " << genimonJoueur.getPV() << " de PV" << endl << endl;
}

bool Joueur::gererCombat(Genimon* genimon)
{
    extern bool bouton1_On;
    extern bool bouton2_On;
    extern bool bouton3_On;
    extern bool bouton4_On;
    extern bool joystick_On;
    extern int numBouton;
    extern int posJoystick;
    bool victoire = false;

    //Partie choix
    bool operationFinie = false;
    bool annulationCombat = false;
    int indexFleche = 1;
    genimonChoisi infos;
    infos = choisirGenimon(genimon, indexFleche);

    while (!operationFinie)
    {
        while (!bouton1_On && !bouton4_On && !joystick_On);

        if (joystick_On)
        {
            if (posJoystick == 1)
            {
                if (indexFleche > 1)
                {
                    --indexFleche;
                }
                infos = choisirGenimon(genimon, indexFleche);
            }
            else if (posJoystick == 3)
            {
                if (indexFleche < nbGenimonAttrapes)
                {
                    ++indexFleche;
                }
                infos = choisirGenimon(genimon, indexFleche);
            }
        }
        else
        {
            if (numBouton == 4)
            {
                annulationCombat = true;
                operationFinie = true;
            }
            else
            {
                if (genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getPV() == 0)
                {
                    cout << "Vous ne pouvez pas utiliser un Genimon KO. Veuillez en choisir un autre ou abandonnez le combat" << endl;
                }
                else if (genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getRareteNumerique() > genimon->getRareteNumerique())
                {
                    cout << "Vous ne pouvez pas utiliser un Genimon de rarete superieure a celle de l'adversaire. Veuillez en choisir un autre ou abandonnez le combat" << endl;
                }
                else
                {
                    operationFinie = true;
                }
            }
        }
    }

    //Partie combat
    if (!annulationCombat)
    {
        Genimon genimonChoisi = genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ];
        int variationDegatsJoueur = 0;
        int variationDegatsAdversaire = 0;
        #ifdef _WIN32
                system("cls");
        #endif
        cout << "----------------------------------------------------------------------------------" << endl;
        cout << "                               Duel contre un Genimon !                           " << endl << endl;
        cout << "                       Battez-le pour recuperer des recompenses                   " << endl << endl;
        cout << "----------------------------------------------------------------------------------" << endl << endl;

        //Set les avantages/désaventages de type
        if (genimon->getTypeSuperieur() == genimonChoisi.getType())
        {
            variationDegatsAdversaire = -genimon->getFacteurDegats();
            cout << "ATTENTION: Par desavantage de type, les degats de l'adversaire sont reduits de " << -1 * variationDegatsAdversaire  << endl << endl;
        }
        else  if (genimon->getTypeInferieur() == genimonChoisi.getType())
        {        
            variationDegatsAdversaire = genimon->getFacteurDegats();
            cout << "ATTENTION: Par avantage de type, les degats de l'adversaire sont augmentes de " << variationDegatsAdversaire << endl << endl;
        }

        if (genimonChoisi.getTypeSuperieur() == genimon->getType())
        {
            variationDegatsJoueur = -genimonChoisi.getFacteurDegats();
            cout << "ATTENTION: Par desavantage de type, les degats du joueur sont reduits de " << -1 * variationDegatsJoueur << endl << endl;
        }
        else  if (genimonChoisi.getTypeInferieur() == genimon->getType())
        {
            variationDegatsJoueur = genimonChoisi.getFacteurDegats();
            cout << "ATTENTION: Par avantage de type, les degats du joueur sont augmentes de " << variationDegatsJoueur << endl << endl;
        }

        //Affiche les opposants
        cout << "Genimon a battre\n" << "Nom: " << genimon->getNom() << ", Type: " << genimon->getType();
        cout << ", Rarete: " << genimon->getRarete() << ", PV: " << genimon->getPV();
        cout << ", Degats: " << genimon->getDegats() + variationDegatsAdversaire;
        if (variationDegatsAdversaire < 0)
        {
            cout << " (-)" << endl << endl;
        }
        else if(variationDegatsAdversaire > 0)
        {
            cout << " (+)" << endl << endl;
        }
        else
        {
            cout << endl << endl;
        }

        cout << "Genimon choisi\n" << "Nom: " << genimonChoisi.getNom() << ", Type: " << genimonChoisi.getType();
        cout << ", Rarete: " << genimonChoisi.getRarete() << ", PV: " << genimonChoisi.getPV();
        cout << ", Degats: " << genimonChoisi.getDegats() + variationDegatsJoueur;
        if (variationDegatsJoueur < 0)
        {
            cout << " (-)" << endl << endl;
        }
        else if (variationDegatsJoueur > 0)
        {
            cout << " (+)" << endl << endl;
        }
        else
        {
            cout << endl << endl;
        }

        int pileOuFace = rand() % 2;
        int numeroManche = 1;
        bool unGenimonMort = false;
        bool tourJoueur = true;
        bool joueurCommence = true;

        int nbAttaquesJoueur = 0;
        int nbAttaquesAdversaire = 0;
        float nbBoucliersJoueur = 0;
        float nbBoucliersAdversaire = 0;
        int nbBonusJoueur = 0;
        int nbBonusAdversaire = 0;
        int nbToursJoueur = 0;
        int nbToursAdversaire = 0;

        cout << "Tirage a pile ou face..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(4));
        if (pileOuFace == 0)
        {
            tourJoueur = true;
            joueurCommence = true;
            nbToursJoueur = -1;
            cout << "Le Joueur commence!" << endl << endl;
        }
        else
        {
            tourJoueur = false;
            joueurCommence = false;
            nbToursAdversaire = -1;
            cout << "L'adversaire commence!" << endl << endl;
        }

        cout << "\n----Manche #" << numeroManche << "----" << endl;

        while (!unGenimonMort)
        {        
            if (tourJoueur)
            {
                nbToursJoueur += 2;
                cout << "Tour Joueur. Nombre de coup: " << nbToursJoueur << endl;
                cout << "Appuyez sur --1-- pour attaquer, sur --2-- pour bloquer, sur --3-- pour accumuler un bonus ou sur --4-- pour quitter le combat" << endl;
                
                while(nbToursJoueur > 0)
                {
                    while (!bouton1_On && !bouton2_On && !bouton3_On && !bouton4_On);

                    if (numBouton == 1)
                    {
                        cout << "*Ajout d'une attaque" << endl;
                        nbAttaquesJoueur++;
                        nbToursJoueur--;
                    }
                    else  if (numBouton == 2)
                    {
                        cout << "*Ajout d'un bouclier" << endl;
                        nbBoucliersJoueur++;
                        nbToursJoueur--;
                    }
                    else  if (numBouton == 3)
                    {
                        if (nbBonusJoueur < 4)
                        {
                            cout << "*Ajout d'un bonus" << endl;
                            nbBonusJoueur++;
                            nbToursJoueur--;
                        }
                        else
                        {
                            cout << "Vous avez atteint le maximum de bonus joueur. Choissisez une autre option" << endl;
                            cout << "Appuyez sur --1-- pour attaquer, sur --2-- pour bloquer, sur --3-- pour accumuler un bonus ou sur --4-- pour quitter le combat" << endl;
                        }
                    }
                    else
                    {
                        cout << "Voulez-vous vraiment quitter le combat? Les PV perdus ne sont pas restaure. (1 pour oui et 2 pour non)" << endl;
                        while (!bouton1_On && !bouton2_On);

                        if (numBouton == 1)
                        {
                            cout << "---Le joueur abandonne le combat---" << endl;
                            unGenimonMort = true;
                            nbToursJoueur = 0;
                            std::this_thread::sleep_for(std::chrono::seconds(2));

                            operationFinie = true;
                        }
                        else
                        {
                            cout << "Appuyez sur --1-- pour attaquer, sur --2-- pour bloquer, sur --3-- pour accumuler un bonus ou sur --4-- pour quitter le combat" << endl;
                            operationFinie = true;
                        }
                    }
                }                                  

                if (!unGenimonMort)
                {           
                    //Actions joueur
                    int nbDegatsPotentiels = 0;
                    if (nbAttaquesJoueur > 0)
                    {                       
                        for (int i = 1; i <= nbAttaquesJoueur; i++)
                        {
                            if (i > nbBoucliersAdversaire)
                            {
                                genimon->varierPV(-(genimonChoisi.getDegats() + variationDegatsJoueur));                             
                            }      
                            nbDegatsPotentiels += genimonChoisi.getDegats() + variationDegatsJoueur;
                        }
                        cout << "Le joueur attaque " << nbAttaquesJoueur << " fois. Nombre de degats infliges : " << nbDegatsPotentiels << endl << endl;
                    }                  
                    else
                    {
                        cout << "Le joueur n'attaque pas" << endl << endl;
                    }

                    if (nbBonusJoueur > 0)
                    {
                        nbToursJoueur += nbBonusJoueur;
                    }

                    //Actions cachées de l'adversaire
                    if (nbBoucliersAdversaire > 0 && nbBonusAdversaire > 0)
                    {
                        cout << "L'adversaire avait accumule " << nbBonusAdversaire << " bonus et avait bloque " << nbBoucliersAdversaire << " fois";
                        if (nbAttaquesJoueur == 0)
                        {
                            cout << ". Bouclier de l'adversaire inutile!";
                        }
                        else if (nbBoucliersAdversaire < nbAttaquesJoueur)
                        {
                            cout << ". Attaque du joueur partiellement bloque";
                        }
                        else if (nbBoucliersAdversaire >= nbAttaquesJoueur)
                        {
                            cout << ". Attaque du joueur completement bloque";
                        }
                        cout << endl;
                    }
                    else if (nbBoucliersAdversaire > 0)
                    {
                        cout << "L'adversaire avait bloque " << nbBoucliersAdversaire << " fois";
                        if (nbAttaquesJoueur == 0)
                        {
                            cout << ". Bouclier de l'adversaire inutile!";
                        }
                        else if (nbBoucliersAdversaire < nbAttaquesJoueur)
                        {
                            cout << ". Attaque du joueur partiellement bloque";
                        }
                        else if (nbBoucliersAdversaire >= nbAttaquesJoueur)
                        {
                            cout << ". Attaque du joueur completement bloque";
                        }
                        cout << endl;
                    }
                    else if(nbBonusAdversaire > 0)
                    {
                        cout << "L'adversaire avait accumule " << nbBonusAdversaire << " bonus" << endl;
                    }                                                     

                    //Vérifications de mort
                    if (genimon->getPV() <= 0)
                    {
                        unGenimonMort = true;
                        victoire = true;
                        genimon->setPV(0); //Minimum de pv à 0

                        afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ]);
                        cout << "Victoire du joueur! " << genimon->getNom() << " est KO" << endl << endl;
                        genimon->setPV(genimon->pvMax); //pv régénéré
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                    }

                    //Fin de tour
                    if (!unGenimonMort)
                    {
                        afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ]);
                        nbAttaquesAdversaire = 0;
                        nbBoucliersAdversaire = 0;
                        nbBonusAdversaire = 0;
                    }

                    //Fin de manche
                    if (!joueurCommence && !unGenimonMort)
                    {                                        
                        ++numeroManche;
                        cout << "\n----Manche #" << numeroManche << "----" << endl;
                    }                
                }

                tourJoueur = false;
            }
            else
            {
                int nbBoucliersMaxAdversaire = 10;
                nbToursAdversaire += 2;
                cout << "Tour Adversaire. Nombre de coup: " << nbToursAdversaire << endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));                           

                //Cas #1: si le joueur fait la première action dans la partie et qu'il n'a pas attaqué
                if (joueurCommence && numeroManche == 1 && nbAttaquesJoueur == 0)
                {
                    int choix;
                    while (nbToursAdversaire > 0)
                    {
                        choix = rand() % 5;
                        if (choix == 0)
                        {
                            nbAttaquesAdversaire++;
                            nbToursAdversaire--;
                        }
                        else if (choix == 1 || choix == 2)
                        {
                            nbBoucliersAdversaire++;
                            nbToursAdversaire--;
                        }
                        else
                        {
                            nbBonusAdversaire++;
                            nbToursAdversaire--;
                        }
                    }                   
                }

                //Cas #2: si l'adversaire peut potentiellement tuer directement le joueur
                if (nbToursAdversaire * (genimon->getDegats() + variationDegatsAdversaire) >= genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getPV())
                {
                    int choix = rand() % 2;
                    if (choix == 0)
                    {
                        nbAttaquesAdversaire = nbToursAdversaire;
                        nbToursAdversaire = 0;
                    }
                }           

                //Cas #3: si la vie de l'adversaire est en-dessous 50%
                if (genimon->getPV() <= genimon->pvMax/2)
                {
                    int choix = rand() % 2;
                    if (choix == 0)
                    {
                        nbBonusAdversaire = nbToursAdversaire / 2;
                        nbBoucliersAdversaire = nbToursAdversaire - nbBonusAdversaire;
                        nbToursAdversaire = 0;
                    }                 
                }

                //Cas #4: si le joueur fait juste attaquer
                if (nbBoucliersJoueur == 0 && nbBonusJoueur == 0)
                {
                    nbBoucliersMaxAdversaire = nbAttaquesAdversaire;
                }

                //Si aucuns des cas spéciaux
                int choix = rand() % 3;
                if (choix == 0 || choix == 1)
                {
                    int choix2;
                    while (nbToursAdversaire > 0)
                    {
                        choix2 = rand() % 3;
                        if (choix2 == 0)
                        {
                            nbAttaquesAdversaire++;
                            nbToursAdversaire--;
                        }
                        else if (choix2 == 1)
                        {
                            if (nbBoucliersAdversaire < nbBoucliersMaxAdversaire)
                            {
                                nbBoucliersAdversaire++;
                                nbToursAdversaire--;
                            }                          
                        }
                        else
                        {
                            if (nbBonusAdversaire < 4)
                            {
                                nbBonusAdversaire++;
                                nbToursAdversaire--;
                            }
                        }
                    }
                }
                else if (nbToursAdversaire > 0)
                {
                    int choix3 = rand() % 5;
                    if (choix3 == 0)
                    {
                        nbAttaquesAdversaire = nbToursAdversaire;
                    }
                    else if (choix3 == 1 && nbToursAdversaire < 5)
                    {
                        nbBonusAdversaire = nbToursAdversaire;
                    }
                    else if (choix3 == 2)
                    {
                        nbAttaquesAdversaire = nbToursAdversaire / 2;
                        nbBonusAdversaire = nbToursAdversaire - nbAttaquesAdversaire;
                    }
                    else if (choix3 == 3)
                    {
                        nbBonusAdversaire = nbToursAdversaire / 2;
                        nbBoucliersAdversaire = nbToursAdversaire - nbBonusAdversaire;
                    }
                    else
                    {
                        nbAttaquesAdversaire = nbToursAdversaire / 2;
                        nbBoucliersAdversaire = nbToursAdversaire - nbAttaquesAdversaire;
                    }
                    nbToursAdversaire = 0;
                }                       
                
                //Actions adversaire
                int nbDegatsPotentiels = 0;
                if (nbAttaquesAdversaire > 0)
                {
                    for (int i = 1; i <= nbAttaquesAdversaire; i++)
                    {
                        if (i > nbBoucliersJoueur)
                        {
                            genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].varierPV(-(genimon->getDegats() + variationDegatsAdversaire));                          
                        }
                        nbDegatsPotentiels += genimon->getDegats() + variationDegatsAdversaire;
                    }
                    cout << "L'adversaire attaque " << nbAttaquesAdversaire << " fois. Nombre de degats infliges: " << nbDegatsPotentiels << endl << endl;
                }       
                else
                {
                    cout << "L'adversaire n'attaque pas" << endl << endl;
                }

                if (nbBonusAdversaire > 0)
                {
                    nbToursAdversaire += nbBonusAdversaire;
                }         

                // Actions cachées du joueur
                if (nbBoucliersJoueur > 0 && nbBonusJoueur > 0)
                {
                    cout << "Le joueur avait accumule " << nbBonusJoueur << " bonus et avait bloque " << nbBoucliersJoueur << " fois";
                    if (nbAttaquesAdversaire == 0)
                    {
                        cout << ". Bouclier du joueur inutile!";
                    }
                    else if (nbBoucliersJoueur < nbAttaquesAdversaire)
                    {
                        cout << ". Attaque de l'adversaire partiellement bloque";
                    }
                    else if (nbBoucliersJoueur >= nbAttaquesAdversaire)
                    {
                        cout << ". Attaque de l'adversaire completement bloque";
                    }
                    cout << endl;
                }
                else if (nbBoucliersJoueur > 0)
                {
                    cout << "Le joueur avait bloque " << nbBoucliersJoueur << " fois";
                    if (nbAttaquesAdversaire == 0)
                    {
                        cout << ". Bouclier du joueur inutile!";
                    }
                    else if (nbBoucliersJoueur < nbAttaquesAdversaire)
                    {
                        cout << ". Attaque de l'adversaire partiellement bloque";
                    }
                    else if (nbBoucliersJoueur >= nbAttaquesAdversaire)
                    {
                        cout << ". Attaque de l'adversaire completement bloque";
                    }
                    cout << endl;
                }
                else if (nbBonusJoueur > 0)
                {
                    cout << "Le joueur avait accumule " << nbBonusJoueur << " bonus" << endl;
                }

                //Vérification de mort
                if (genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getPV() <= 0 && !unGenimonMort)
                {
                    unGenimonMort = true;
                    genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].setPV(0); //Minimum de pv à 0

                    afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ]);
                    cout << "Defaite du joueur! " << genimonChoisi.getNom() << " est KO" << endl << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }       

                //Fin de tour
                if (!unGenimonMort)
                {
                    afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ]);
                    nbAttaquesJoueur = 0;
                    nbBoucliersJoueur = 0;
                    nbBonusJoueur = 0;
                }

                //Fin de manche
                if (joueurCommence && !unGenimonMort)
                {                    
                    ++numeroManche;
                    cout << "\n----Manche #" << numeroManche << "----" << endl;
                }
                
                tourJoueur = true;            
            }
        }

        if (victoire)
        {
            nbBalles += genimon->getGainBalles();
            cout << "Vous avez gagne " << genimon->getGainBalles() << " balles" << endl;
            cout << "Nombre total de balles: " << nbBalles << endl << endl;

            if (genimon->getRareteNumerique() > genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getRareteNumerique())
            {
                cout << "Vous avez battu un Genimon de rarete superieure au votre, bravo!" << endl;
                cout << "Une capsule de guerison vous est donne en recompense" << endl << endl;
                nbCapsuleGuerison++;
            }
        }

        cout << "Appuyez sur --4-- pour quitter le combat" << endl;
        while (!bouton4_On);
    }
    else
    {
        cout << "\n---Combat annule---" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return victoire;
}

void Joueur::gererAttrapage(Genimon* genimon, int indexGenimon)
{
    extern bool bouton4_On;
    #ifdef _WIN32
        system("cls");
    #endif
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                            Face a face avec un Genimon !                         " << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    
    genimon->presenter();

    int typeGenimon = genimon->getTypeNumerique();

    bool captureReussie = genimon->capture(&nbBalles);
    if (captureReussie)
    {
        genidex[typeGenimon].listeGenimonAttrapé.push_back(*genimon);
        nbGenimonAttrapes++;
    }

    listeGenimons.retirerElement(indexGenimon); //Le genimon n'est plus sur le terrain

    cout << "Appuyez sur --4-- pour revenir au jeu" << endl;
    while (!bouton4_On);
}

void Joueur::consulterDétailsType(int typeNumérique, string type)
{
    int tailleListe = genidex[typeNumérique].listeGenimonAttrapé.size();
    cout << "Details pour le type: " << type << endl;

    if (tailleListe == 0)
    {
        cout << "Aucun Genimon pour ce type" << endl;
    }

    for (int i = 0; i < tailleListe; i++)
    {
        cout << i << ") " << "Nom: " << genidex[typeNumérique].listeGenimonAttrapé[i].getNom() << "\n   Type: " << genidex[typeNumérique].listeGenimonAttrapé[i].getType();
        cout << "\n   Rarete: " << genidex[typeNumérique].listeGenimonAttrapé[i].getRarete() << "\n   PV: " << genidex[typeNumérique].listeGenimonAttrapé[i].getPV();
        cout << "\n   Degats: " << genidex[typeNumérique].listeGenimonAttrapé[i].getDegats() << endl;
    }

    cout << endl;
}

void Joueur::demanderInformationsGenimon(int typeNumérique, string type)
{
    extern bool bouton1_On;
    extern bool bouton2_On;
    extern int numBouton;

    cout << "Voulez-vous consulter les informations de chaque Genimon? (1 pour oui et 2 pour non)" << endl;
    while (!bouton1_On && !bouton2_On);

    if (numBouton == 1)
    {
        consulterDétailsType(typeNumérique, type);
    }
    else
    {
        cout << "----Informations non desires----" << endl << endl;
    }
}

void Joueur::guerirGenimon()
{
    extern bool bouton1_On;
    extern bool bouton4_On;
    extern bool joystick_On;
    extern int numBouton;
    extern int posJoystick;

    bool operationFinie = false;
    int indexFleche = 1;
    genimonChoisi infos;

    if (nbCapsuleGuerison > 0 && nbGenimonAttrapes > 0)
    {
        infos = choisirGuerison(indexFleche);
        while (!operationFinie)
        {
            while (!bouton1_On && !bouton4_On && !joystick_On);

            if (joystick_On)
            {
                if (posJoystick == 1)
                {
                    if (indexFleche > 1)
                    {
                        --indexFleche;
                    }
                    infos = choisirGuerison(indexFleche);
                }
                else if (posJoystick == 3)
                {
                    if (indexFleche < nbGenimonAttrapes)
                    {
                        ++indexFleche;
                    }
                    infos = choisirGuerison(indexFleche);
                }
            }
            else
            {
                if (numBouton == 4)
                {
                    #ifdef _WIN32
                             system("cls");
                    #endif
                    afficherMenuGeniedex(true);
                    operationFinie = true;
                }
                else
                {
                    if (genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getPV() == genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].pvMax)
                    {
                        cout << "Le Genimon choisi n'a subi auncun degats. Veuillez en choisir un autre ou annuler la guerison" << endl;
                    }
                    else
                    {
                        genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].setPV(genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].pvMax);
                        nbCapsuleGuerison--;
                        cout << "Guerison effectuee" << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        #ifdef _WIN32
                                   system("cls");
                        #endif
                        afficherMenuGeniedex(true);
                        operationFinie = true;
                    }
                }
            }        
        }
    }
    else
    {
        cout << "Action impossible! Vous n'avez aucune capsule de guerison." << endl;
    }
}

genimonChoisi Joueur::choisirGuerison(int indexFleche)
{
    #ifdef _WIN32
        system("cls");
    #endif
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                           Choisissez un Genimon a soigner                        " << endl << endl;
    cout << "                    Utilisez les touches w et s pour la selection                 " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "\nFaites un choix dans l'inventaire:" << endl;

    int compteur = 1;
    genimonChoisi infos;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < genidex[i].listeGenimonAttrapé.size(); j++)
        {
            if (indexFleche == compteur)
            {
                cout << "--> ";
                infos.indexI = i;
                infos.indexJ = j;
            }
            cout << compteur << ") " << "Nom: " << genidex[i].listeGenimonAttrapé[j].getNom() << ", Type: " << genidex[i].listeGenimonAttrapé[j].getType();
            cout << ", Rarete: " << genidex[i].listeGenimonAttrapé[j].getRarete() << ", PV: " << genidex[i].listeGenimonAttrapé[j].getPV();
            cout << ", PV max: " << genidex[i].listeGenimonAttrapé[j].pvMax << ", Degats: " << genidex[i].listeGenimonAttrapé[j].getDegats() << endl;
            compteur++;
        }
    }

    cout << "\nAppuyez sur --1-- pour confirmer le choix ou sur --4-- pour annuler la guerison" << endl << endl;

    return infos;
}

void Joueur::consulterGenidexPartiel(int type)
{
    if (type == 0)
    {
        cout << "Nombre de Genimon de type informatique captures: " << genidex[0].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(0, "informatique");
    }
    else if (type == 1)
    {
        cout << "Nombre de Genimon de type electrique captures: " << genidex[1].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(1, "electrique");
    }
    else if (type == 2)
    {
        cout << "Nombre de Genimon de type robotique captures: " << genidex[2].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(2, "robotique");
    }
    else if (type == 3)
    {
        cout << "Nombre de Genimon de type mecanique captures: " << genidex[3].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(3, "mecanique");
    }
    else if (type == 4)
    {
        cout << "Nombre de Genimon de type civil captures: " << genidex[4].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(4, "civil");
    }
    else if (type == 5)
    {
        cout << "Nombre de Genimon de type batiment captures: " << genidex[5].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(5, "batiment");
    }
    else if (type == 6)
    {
        cout << "Nombre de Genimon de type bioTech captures: " << genidex[6].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(6, "bioTech");
    }
    else if (type == 7)
    {
        cout << "Nombre de Genimon de type chimique captures: " << genidex[7].listeGenimonAttrapé.size() << endl;;
        demanderInformationsGenimon(7, "chimique");
    }

    cout << "Choisissez une option du menu pour lancer une autre recherche ou pour fermer le Genidex" << endl;
}

void Joueur::consulterGenidexComplet()
{
    cout << "Nombre de Genimon de type informatique captures: " << genidex[0].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(0, "informatique");
   
    cout << "Nombre de Genimon de type electrique captures: " << genidex[1].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(1, "electrique");
    
    cout << "Nombre de Genimon de type robotique captures: " << genidex[2].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(2, "robotique");
    
    cout << "Nombre de Genimon de type mecanique captures: " << genidex[3].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(3, "mecanique");
    
    cout << "Nombre de Genimon de type civil captures: " << genidex[4].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(4, "civil");
    
    cout << "Nombre de Genimon de type batiment captures: " << genidex[5].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(5, "batiment");
   
    cout << "Nombre de Genimon de type bioTech captures: " << genidex[6].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(6, "bioTech");
    
    cout << "Nombre de Genimon de type chimique captures: " << genidex[7].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(7, "chimique");

    cout << "Choisissez une option du menu pour lancer une autre recherche ou pour fermer le Genidex" << endl;
}

void Joueur::consulterHistorique()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                             Historique des rencontres                            " << endl;
    cout << "----------------------------------------------------------------------------------" << endl << endl;

    if (historique.size() == 0)
    {
        cout << "Aucun Genimon rencontre" << endl;
    }

    for (int i = 0; i < historique.size(); i++)
    {
        cout << i << ") " << "Nom: " << historique[i].getNom() << ", Type: " << historique[i].getType();
        cout << ", Rarete: " << historique[i].getRarete() << ", PV: " << historique[i].getPV();
        cout << ", Degats: " << historique[i].getDegats() << endl;
    }

    cout << "\nAppuyez sur --4-- pour fermer l'historique" << endl;
}

void Joueur::afficherMenuPrincipal()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                                 Menu Principal                                   " << endl << endl;
    cout << "                        Pour ouvrir le Genidex: --1--                             " << endl;
    cout << "                        Pour voir l'historique des rencontres: --2--              " << endl;
    cout << "                        Pour mettre le jeu en pause: --3--                        " << endl << endl << endl;
    cout << "                 Utilisez les touches w,a,s,d pour vous deplacer                  " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void Joueur::afficherMenuGeniedex(bool afficherObjets)
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                                  Menu Genidex                                    " << endl << endl;
    cout << "                      Pour visualiser une categorie du Genidex: --1--             " << endl;
    cout << "                      Pour visualiser l'ensemble du Genidex: --2--                " << endl;
    cout << "                      Pour guerir un Genimon: --3--                               " << endl;
    cout << "                      Pour fermer le Genidex: --4--                               " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    if (afficherObjets)
    {
        cout << "\nNombre total de balles: " << nbBalles;
        cout << "\nNombre total de capsules de guerison: " << nbCapsuleGuerison << endl;
    }
}