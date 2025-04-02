#include "commande.h"
#include "ui_commande.h"

Commande::Commande(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Commande)
{
    ui->setupUi(this);
    ui->ClavierW->setStyleSheet("background-color: red;");
    ui->ClavierA->setStyleSheet("background-color: red;");
    ui->ClavierS->setStyleSheet("background-color: red;");
    ui->ClavierD->setStyleSheet("background-color: red;");
    ui->ClavierH->setStyleSheet("background-color: red;");
}

Commande::~Commande()
{
    delete ui;
}

void Commande::handleKeyPress(int key) {
    if (key == Qt::Key_4) {
        emit requestMenuChange(0); //Passer au menu principal
        clearFocus();
    }

    if (key == Qt::Key_W) {
        ui->ClavierW->setStyleSheet("background-color: green;");
    }else{
        ui->ClavierW->setStyleSheet("background-color: red;");
    }

    if (key == Qt::Key_A) {
        ui->ClavierA->setStyleSheet("background-color: green;");
    }else{
        ui->ClavierA->setStyleSheet("background-color: red;");
    }

    if (key == Qt::Key_D) {
        ui->ClavierD->setStyleSheet("background-color: green;");
    }else{
        ui->ClavierD->setStyleSheet("background-color: red;");
    }

    if (key == Qt::Key_S) {
        ui->ClavierS->setStyleSheet("background-color: green;");
    }else{
        ui->ClavierS->setStyleSheet("background-color: red;");
    }

    if (key == Qt::Key_H) {
        ui->ClavierH->setStyleSheet("background-color: green;");
    }else{
        ui->ClavierH->setStyleSheet("background-color: red;");
    }
}
