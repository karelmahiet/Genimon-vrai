#include "historencontre.h"
#include "ui_historencontre.h"
#include <string>

HistoRencontre::HistoRencontre(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoRencontre)
{
    ui->setupUi(this);
}

HistoRencontre::~HistoRencontre()
{
    delete ui;
}

void HistoRencontre::handleKeyPress(int key) {
    if (key == Qt::Key_4) {
        emit requestMenuChange(2); //Passer au menu map
    }
}

void HistoRencontre::ecrireHistorique(vector<Genimon> historique)
{
    QString texte = "";
    for (int i = 0; i < historique.size(); i++)
    {
        texte.append(to_string(i) + ") Nom: " + historique[i].getNom() + ", Type: " + historique[i].getType() + ", Rarete: " + historique[i].getRarete()
                     + ", PV: " + to_string(historique[i].getPV()) + ", Degats: " + to_string(historique[i].getDegats()) + "\n");
    }
    if (historique.size() == 0)
    {
        texte = "Aucun genimon rencontre";
    }
    ui->Affichage1->setText(texte);
}
