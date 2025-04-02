#include "gestionJeu.h"
#include "joueur.h"

//----------Variables communication----------
#include <iostream>
#include <string>
#include "SerialPort.hpp"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

#define BAUD 115200           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message

bool SendToSerial(SerialPort* arduino, json j_msg);
bool RcvFromSerial(SerialPort* arduino, string& msg);

SerialPort* arduino;

int accX, accY, accZ;
string messageLCD;
int nbSeg;
json j_msg_send;

bool bouton1_On = false;
bool bouton2_On = false;
bool bouton3_On = false;
bool bouton4_On = false;
int numBouton = 0;
bool joystick_On = false;
int posJoystick = 0;
bool accelerometre_On = false;
int posAccelerometre = 0;
//-------------------------------------------
//--------------Variables jeu----------------
enum Etat
{
    Initialise, EnCours, Termine
};

const int maxGenimon = 15;

enum Etat etatJeu = Initialise;
Joueur* joueur;
bool apparitionsPermises = false;
bool disparitionsPermises = false;
bool resfreshPermis = true;
int nbCapsulesGuerisonTerrain = 0;
//-------------------------------------------


bool evenementActif() {
    time_t now = time(nullptr);

    struct tm localTime;

    localtime_s(&localTime, &now);

    if (localTime.tm_hour >= 17 && localTime.tm_hour < 20) {
        return true;
    }
    else {
        return false;
    }
}

void afficherBienvenue()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                            Bienvenue dans Genimon!                                " << endl << endl;
    cout << "          Promenez-vous dans la faculte de genie et rencontrez des                " << endl;
    cout << "          Genimons. Combattez-les pour tentez de les capturer et de les           " << endl;
    cout << "          ajouter a votre Genidex. Une aventure passionnante vous attend.         " << endl << endl;
    cout << "                                Bonne chasse!                                     " << endl << endl << endl;
    cout << "                        Pour demarer le jeu: --1--                                " << endl;
    cout << "                        Pour sortir du jeu: --4--                                 " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void afficherConfirmation()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                  Voulez-vous vraiment mettre fin a la partie?                    " << endl;
    cout << "                  Si vous confirmez, votre progression sera perdu.                " << endl << endl << endl;
    cout << "                               Pour confirmer: --1--                              " << endl;
    cout << "                               Pour annuler: --4--                                " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void afficherPause()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                                   Jeu en pause                                   " << endl << endl;
    cout << "                         Pour sortir du jeu: --1--                                " << endl;
    cout << "                         Pour reinitialiser le jeu: --2--                         " << endl;
    cout << "                         Pour revenir au jeu: --4--                               " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void gererInitialisation()
{
    #ifdef _WIN32
        system("cls");
    #endif
    afficherBienvenue();
    while (!bouton1_On && !bouton4_On);

    if (numBouton == 1)
    {
        #ifdef _WIN32
                system("cls");
        #endif

        joueur = new Joueur;
        cout << "----------------------------------------------------------------------------------" << endl;
        cout << "                                 Setup de la partie                               " << endl;
        cout << "----------------------------------------------------------------------------------" << endl << endl;
        cout << "Entrez votre nom: ";
        //cin >> joueur->nom;
        joueur->choisirStarter();

        etatJeu = EnCours;
    }
    else
    {
        etatJeu = Termine;
    }
}

void gererPause(bool *finPartie)
{
    #ifdef _WIN32
        system("cls");
    #endif
    afficherPause();
    while (!bouton1_On && !bouton2_On && !bouton4_On);

    if (numBouton == 2) {
        gererConfirmation(1, finPartie);
    }
    else if (numBouton == 1) {
        gererConfirmation(2, finPartie);
    }
}

void gererConfirmation(int option, bool* finPartie)
{
    #ifdef _WIN32
        system("cls");
    #endif
    afficherConfirmation();
    while (!bouton1_On && !bouton4_On);

    if (numBouton == 1)
    {
        if (option == 1)
        {
            etatJeu = Initialise;
            apparitionsPermises = false;
            disparitionsPermises = false;
            resfreshPermis = true;
        }
        else
        {
            etatJeu = Termine;
        }
        *finPartie = true;
    }
}

void gererGeniedex()
{
    #ifdef _WIN32
        system("cls");
    #endif
    joueur->afficherMenuGeniedex(true);

    bool operationFinie = false;
    while (!operationFinie)
    {
        while (!bouton1_On && !bouton2_On && !bouton3_On && !bouton4_On);

        if (numBouton == 1)
        {
            bool choixFait = false;
            bool refresh = true;
            int indexFleche = 0;
            string optionsType[8] = { "Informatique", "Electrique", "Robotique", "Mecanique", "Civil", "Batiment", "Biotech", "Chimique" };

            while (!choixFait)
            {
                if (refresh)
                {
                    #ifdef _WIN32
                                system("cls");
                    #endif
                    joueur->afficherMenuGeniedex(false);
                    cout << "Choissisez le type de Genimon que vous voulez visualiser (8 choix)" << endl;
                    cout << "Utilisez les touches w et s pour la selection" << endl << endl;

                    for (int i = 0; i < 8; i++)
                    {
                        if (indexFleche == i)
                        {
                            cout << "--> ";
                        }
                        cout << optionsType[i] << endl;
                    }

                    cout << "\nAppuyez sur --1-- pour confirmer le choix" << endl;
                }

                while (!joystick_On && !bouton1_On);

                if (joystick_On)
                {
                    if (posJoystick == 1)
                    {
                        if (indexFleche > 0)
                        {
                            --indexFleche;
                        }
                        refresh = true;
                    }
                    else if (posJoystick == 3)
                    {
                        if (indexFleche < 7)
                        {
                            ++indexFleche;
                        }
                        refresh = true;
                    }
                }
                else
                {
                    choixFait = true;
                }
            }

            joueur->consulterGenidexPartiel(indexFleche);
        }
        else if (numBouton == 2)
        {
            #ifdef _WIN32
                    system("cls");
            #endif
            joueur->afficherMenuGeniedex(false);
            joueur->consulterGenidexComplet();
        }
        else if (numBouton == 3)
        {
            #ifdef _WIN32
                    system("cls");
            #endif
            joueur->afficherMenuGeniedex(false);
            joueur->guerirGenimon();
        }
        else
        {
            operationFinie = true;
        }
    }
}

void gererHistorique()
{
    #ifdef _WIN32
        system("cls");
    #endif
    joueur->consulterHistorique();
    while (!bouton4_On);
}

void gererPartie()
{
    //joueur->afficherPartie();
    bool operationFinie = false;

    while (!operationFinie)
    {
        apparitionsPermises = true;
        disparitionsPermises = true;
        resfreshPermis = true;

        while (!bouton1_On && !bouton2_On && !bouton3_On && !bouton4_On && !joystick_On);

        if (joystick_On)
        {
            if (posJoystick == 4 && joueur->position_x > joueur->borne_x_min) {
                joueur->position_x--;
            }
            else if (posJoystick == 2 && joueur->position_x < joueur->borne_x_max - 1) {
                joueur->position_x++;
            }
            else if (posJoystick == 3 && joueur->position_y < joueur->borne_y_max - 1) {
                joueur->position_y++;
            }
            else if (posJoystick == 1 && joueur->position_y > joueur->borne_y_min) {
                joueur->position_y--;
            }
        }
        else
        {
            if (numBouton == 1) {
                resfreshPermis = false;
                gererGeniedex();
            }
            else if (numBouton == 2) {
                resfreshPermis = false;
                gererHistorique();
            }
            else if (numBouton == 3) {
                apparitionsPermises = false;
                disparitionsPermises = false;
                resfreshPermis = false;
                gererPause(&operationFinie);
            }
        }

        if (joueur->estSurGenimon())
        {
            disparitionsPermises = false;
            resfreshPermis = false;
            joueur->gererGenimon();
        }
        else if (joueur->estSurPorte())
        {
            apparitionsPermises = false;
            disparitionsPermises = false;
            resfreshPermis = false;
            joueur->changerTerrain();
        }
        else
        {
            if (joueur->gererCapsuleVie())
            {
                nbCapsulesGuerisonTerrain--;
            }
        }


        if (etatJeu == EnCours)
        {
            //joueur->afficherPartie();
        }
    }

    apparitionsPermises = false;
    disparitionsPermises = false;
    delete joueur;
}

//Apparition et disparition des genimons
void gererThread1()
{
    while (true) {
        if (etatJeu == EnCours)
        {
            if (apparitionsPermises && joueur->listeGenimons.Taille() <= maxGenimon)
            {           
                if (joueur->listeGenimons.Taille() <= maxGenimon / 3)
                {
                    joueur->ajouterGenimon(resfreshPermis);
                }
                else
                {
                    if ((rand() % 2) == 1)
                    {
                        joueur->ajouterGenimon(resfreshPermis);
                    }
                }               
            }
            if (disparitionsPermises && joueur->listeGenimons.Taille() >= 10)
            {
                if ((rand() % 5) == 1)
                {
                    joueur->retirerGenimon(resfreshPermis);
                }
            }
        }

        this_thread::sleep_for(chrono::milliseconds(4000));
    }
}

//Capsules de vie
void gererThread2()
{
    while (true) {
        if (etatJeu == EnCours)
        {
            if (apparitionsPermises && nbCapsulesGuerisonTerrain < 1)
            {
                int choix = rand() % 6;
                if (choix == 0)
                {
                    joueur->creerCapsuleVie(resfreshPermis);
                    nbCapsulesGuerisonTerrain++;
                }
            }          
        }

        this_thread::sleep_for(chrono::milliseconds(20000));
    }
}

//Gestion des commandes par clavier
void gererThread3()
{
    char commande = '0';

    while (true)
    {
        bouton1_On = false;
        bouton2_On = false;
        bouton3_On = false;
        bouton4_On = false;
        joystick_On = false;

        commande = _getch();

        if (commande == 'w')
        {
            joystick_On = true;
            posJoystick = 1;
        }
        else if (commande == 'a')
        {
            joystick_On = true;
            posJoystick = 4;
        }
        else if (commande == 's')
        {
            joystick_On = true;
            posJoystick = 3;
        }
        else if (commande == 'd')
        {
            joystick_On = true;
            posJoystick = 2;
        }
        else if (commande == '1')
        {
            bouton1_On = true;
            numBouton = 1;
        }
        else if (commande == '2')
        {
            bouton2_On = true;
            numBouton = 2;
        }
        else if (commande == '3')
        {
            bouton3_On = true;
            numBouton = 3;
        }
        else if (commande == '4')
        {
            bouton4_On = true;
            numBouton = 4;
        }
    }
}

//Gestion des commandes par manette
void gererThread4()
{
    while (true)
    {
        Sleep(100);

        json j_msg_rcv; // effacer le message precedent
        string raw_msg;

        // Reception message Arduino
        if (!RcvFromSerial(arduino, raw_msg)) {
            //cerr << "Erreur lors de la reception du message. " << endl;
        }

        //       std::cout << "Chaine non-modifiee : " << endl << raw_msg << std::endl;

        size_t pos1 = raw_msg.find('{');
        size_t pos2 = raw_msg.find('}', pos1);
        if (pos2 != std::string::npos && pos1 != std::string::npos) {
            raw_msg = raw_msg.substr(pos1, pos2 + 1);
        }
        else {
            raw_msg = "";
        }
        //        std::cout << "Chaine modifiee : " << endl << raw_msg << std::endl;


                // Affichage du message reçu de l'Arduino
        if (raw_msg.size() > 0) {
            // Transfert du message en JSON

            try {
                j_msg_rcv = json::parse(raw_msg);        //ERREUR PROVIENT D'ICI
            }
            catch (const json::parse_error& e) {
                //std::cerr << "Erreur de parsing : " << e.what() << std::endl;
                //std::cout << "Json mauvais:    " << endl << raw_msg << endl;
            }

            //std::cout << "Message de l'Arduino: " << j_msg_rcv << endl;

            if (j_msg_rcv.contains("boutton")) {
                numBouton = j_msg_rcv["boutton"];
                if (numBouton == 1)
                {
                    bouton1_On = true;
                }
                else if (numBouton == 2)
                {
                    bouton2_On = true;
                }
                else if (numBouton == 3)
                {
                    bouton3_On = true;
                }
                else if (numBouton == 4)
                {
                    bouton4_On = true;
                }
            }
            if (j_msg_rcv.contains("JoyPosition")) {
                posJoystick = j_msg_rcv["JoyPosition"];
                if (posJoystick != 0)
                {
                    joystick_On = true;
                }
            }

            if (j_msg_rcv.contains("AccX")) {
                accX = j_msg_rcv["AccX"];
            }
            if (j_msg_rcv.contains("AccY")) {
                accY = j_msg_rcv["AccY"];
            }
            if (j_msg_rcv.contains("AccZ")) {
                accZ = j_msg_rcv["AccZ"];
            }

            bouton1_On = false;
            bouton2_On = false;
            bouton3_On = false;
            bouton4_On = false;
            joystick_On = false;

            Sleep(100);

            /*system("cls");
            cout << "bouton: " << numBouton << endl;
            cout << "joystick: " << posJoystick << endl << endl;

            if (numBouton == 1) nbSeg = 1;
            if (numBouton == 2) nbSeg = 2;
            if (numBouton == 3) nbSeg = 3;
            if (numBouton == 4) nbSeg = 4;
            if (numBouton == 0) nbSeg = 0;*/

            //Affichage sur le 7-segments
            if (etatJeu == EnCours)
            {
                nbSeg = joueur->getNbCapsuleGuerison();
            }
            else
            {
                nbSeg = 0;
            }

            // Envoie message Arduino
            j_msg_send["messageLCD"] = messageLCD;
            j_msg_send["nbSeg"] = nbSeg;

            if (!SendToSerial(arduino, j_msg_send)) {          //ENVOI DE DONNEES
                //cerr << "Erreur lors de l'envoie du message. " << endl;
            }
        }
    }
}

int execution()
{
    //--------Initialisation du port de communication----------
    string com = "\\\\.\\COM3";
    arduino = new SerialPort(com.c_str(), BAUD);

    if (!arduino->isConnected()) {
        cerr << "Impossible de se connecter au port " << string(com) << ". Fermeture du programme!" << endl;
        exit(1);
    }

    accX = 0, accY = 0, accZ = 0;
    messageLCD = "CA FONCTIONNE";  // Message à afficher sur le LCD
    nbSeg = 5;  // Nombre à afficher sur le 7 segments
    //-----------------------------------------------------------

    srand(time(0));
    thread t(gererThread1);
    t.detach();
    thread t2(gererThread2);
    t2.detach();
    //thread t3(gererThread3);
    //t3.detach();
    thread t4(gererThread4);
    t4.detach();

    while (true)
    {
        switch (etatJeu)
        {
        case Initialise:
            gererInitialisation();
            break;
        case EnCours:
            gererPartie();
            break;
        case Termine:
            cout << "----------------------------------------------------------------------------------" << endl;
            cout << "                               ...Fin du jeu...                             " << endl;
            exit(0);
            break;
        default:
            break;
        }
    }

    return 0;
}

//Fonctions de communcation
bool SendToSerial(SerialPort* arduino, json j_msg) {
    // Return 0 if error
    string msg = j_msg.dump();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}

bool RcvFromSerial(SerialPort* arduino, string& msg) {
    // Return 0 if error
    // Message output in msg
    string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;

    msg.clear(); // clear string

    // Version fonctionnelle dans VScode et Visual Studio
    buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    str_buffer.assign(char_buffer, buffer_size);
    msg.append(str_buffer);

    return true;
}

