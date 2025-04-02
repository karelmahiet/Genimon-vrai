#include "choixjoueur.h"
#include "ui_choixjoueur.h"
#include "controle.h"
#include <QKeyEvent>
#include <QDebug>

extern Controle *controle;

ChoixJoueur::ChoixJoueur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChoixJoueur)
{
    ui->setupUi(this);

    ui->Continuer->setStyleSheet("background-color: white; color: black; font-size: 14px;");
    ui->Retour->setStyleSheet("background-color: white; color: black; font-size: 14px;");

    initialiserChoixJoueur();
}

ChoixJoueur::~ChoixJoueur()
{
    delete ui;
}

void ChoixJoueur::initialiserChoixJoueur()
{
    etat = 0;
    typeChoisi = "";
    nomJoueur = "";
    nomStarter = "";
    Clavier1 = false;
    Clavier2 = false;
}

void ChoixJoueur::handleKeyPress(int key) {

    if (etat != 0 && etat != 1) {
        if (key == Qt::Key_1) {
            Clavier1 = true;
            qDebug() << "Clavier1 (Oui) détecté";
        } else if (key == Qt::Key_2) {
            Clavier2 = true;
            qDebug() << "Clavier2 (Non) détecté";
        }
    }else{
        Clavier1 = false;
        Clavier2 = false;
    }

    if (etat == 0 && key == Qt::Key_Tab) {
        nomJoueur = ui->NomChoisi->text();
        ui->NomChoisi->clearFocus();
        ui->NomChoisi->clear();
        qDebug() << "Nom validé par Tab :" << nomJoueur;

        etat = 1;
    }
    else if (etat == 1 && key == Qt::Key_Tab)
    {
        nomStarter = ui->NomChoisi->text();
        ui->NomChoisi->clearFocus();
        ui->NomChoisi->clear();
        qDebug() << "Nom validé par Tab :" << nomStarter;

        etat = 2;
    }
    updateQuiz();
}



void ChoixJoueur::updateQuiz() {

    switch (etat) {
    case 0:
        ui->Titre->setText("Votre nom ?");
        ui->NomChoisi->setFocus();
        ui->Nom->setVisible(true);
        ui->NomChoisi->setVisible(true);
        ui->Description->setVisible(false);
        ui->Retour->setVisible(false);
        ui->Continuer->setText("Continuer (Tab)");
        break;
    case 1:
        ui->Titre->setText("Nom de votre premier Genimon?");
        ui->NomChoisi->setFocus();
        ui->Retour->setVisible(false);
        break;
    case 2:
        ui->Titre->setText("Quiz de personnalité");
        ui->Description->setText("Pour déterminer le type de votre premier Genimon, répondez à ce quiz pour qu'il puisse "
                                 "vous représenter. Voulez-vous répondre au quiz? Sinon un type aléatoire sera choisi.");
        ui->Nom->setVisible(false);
        ui->NomChoisi->setVisible(false);
        ui->Description->setVisible(true);
        ui->Retour->setVisible(true);
        ui->Continuer->setText("Oui (1)");
        ui->Retour->setText("Non (2)");

        if (Clavier1) {
            Clavier1 = 0;
            etat = 4;
            updateQuiz();
        }
        else if (Clavier2) {
            Clavier2 = 0;
            etat = 3;
            ui->Description->setText("Quiz non répondu. Un type aléatoire a été choisi.");
            updateQuiz();
        }
        break;

    case 3:
        ui->Continuer->setText("Débuter de la partie (1)");
        ui->Retour->setVisible(false);

        if (Clavier1)
        {
            Clavier1 = 0;
            emit sendNomJoueur(nomJoueur); //Envoyer le nom du joueur a la classe map
            emit requestMenuChange(2); //Passer au menu map
        }
        break;

    case 4:
        ui->Description->setText("Est-ce que 80% est une mauvaise note ?");
        if (Clavier1) {
            Clavier1 =0;
            etat = 5;
            updateQuiz();
        } else if (Clavier2) {
            Clavier2 =0;
            etat = 7;
            updateQuiz();
        }
        break;

    case 5:
        ui->Description->setText("Est-ce que la physique c'est cool ?");
        if (Clavier1) {
            Clavier1 =0;
            ui->Description->setText("Félicitations tu es un génie robotique! Tu as terminé le quiz.");
            typeChoisi = "robotique";
            etat = 3;
            updateQuiz();
        } else if (Clavier2) {
            Clavier2 =0;
            etat = 6;
            updateQuiz();
        }
        break;

    case 6:
        ui->Description->setText("Est-ce que des trucs morts c'est cool ?");
        if (Clavier1) {
            Clavier1 =0;
            ui->Description->setText("Félicitations tu es un génie biotech! Tu as terminé le quiz.");
            typeChoisi = "bioTech";
            etat = 3;
            updateQuiz();
        } else if (Clavier2) {
            Clavier2 =0;
            ui->Description->setText("Félicitations tu es un génie chimique! Tu as terminé le quiz.");
            typeChoisi = "chimique";
            etat = 3;
            updateQuiz();
        }
        break;

    case 7:
        ui->Description->setText("Est-ce que tu penses que les ordinateurs fonctionnent avec de l'essence ?");
        if (Clavier1) {
            Clavier1 =0;
            ui->Description->setText("Hmmm, intéressant... Tu es un génie mécanique. Félicitations ! Tu as terminé le quiz.");
            typeChoisi = "mecanique";
            etat = 3;
            updateQuiz();
        } else if (Clavier2) {
            Clavier2 =0;
            etat = 8;
            updateQuiz();
        }
        break;

    case 8:
        ui->Description->setText("Est-ce que tu sais ce que c'est un Amplis-Op ?");
        if (Clavier1) {
            Clavier1 =0;
            etat = 9;
            updateQuiz();
        } else if (Clavier2) {
            Clavier2 =0;
            etat = 10;
            updateQuiz();
        }
        break;

    case 9:
        ui->Description->setText("Est-ce qu'il te font peur ?");
        if (Clavier1) {
            Clavier1 =0;
            ui->Description->setText("Félicitations tu es un génie informatique! Tu as terminé le quiz.");
            typeChoisi = "informatique";
            etat = 3;
            updateQuiz();
        } else if (Clavier2) {
            Clavier2 =0;
            ui->Description->setText("Félicitations tu es un génie électrique! Tu as terminé le quiz.");
            typeChoisi = "electrique";
            etat = 3;
            updateQuiz();
        }
        break;

    case 10:
        ui->Description->setText("Est-ce que tu es basique ?");
        if (Clavier1) {
            Clavier1 =0;
            ui->Description->setText("Félicitations tu es un génie civil! Tu as terminé le quiz.");
            typeChoisi = "civil";
            etat = 3;
            updateQuiz();
        } else if (Clavier2) {
            Clavier2 =0;
            ui->Description->setText("Félicitations tu es un génie du bâtiment! Tu as terminé le quiz.");
            typeChoisi = "batiment";
            etat = 3;
            updateQuiz();
        }
        break;

    default:
        break;
    }
}
