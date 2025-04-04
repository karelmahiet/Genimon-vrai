#include "capture.h"
#include "ui_capture.h"
#include <QEasingCurve>

Capture::Capture(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Capture)
{
    ui->setupUi(this);
    ui->Pokeball->setVisible(false);
}

Capture::~Capture()
{
    delete ui;
}

void Capture::handleKeyPress(int key) {

    if (key == Qt::Key_1) {
        animPokeball();
    }
    else if (key == Qt::Key_2) {
        emit requestMenuChange(2); //Passer au menu map
        clearFocus();
    }
}

void Capture::animPokeball() {

    ui->Pokeball->setVisible(true);

    // Animation de la Pok�ball
    animation = new QPropertyAnimation(ui->Pokeball, "pos", this);
    animation->setDuration(2000); // Dur�e de l'animation
    animation->setStartValue(QPoint(200, 440)); // Position de d�part
    animation->setEndValue(QPoint(800, 170)); // Position d'arriv�e

    // Utiliser un mouvement de courbe parabolique
    animation->setEasingCurve(QEasingCurve::OutQuad); // Courbe d'acc�l�ration de type "rebond"

    animation->start();

    // Timer pour faire dispara�tre la Pok�ball apr�s l'animation
    connect(animation, &QPropertyAnimation::finished, this, [=]() {
        ui->Pokeball->setVisible(false);  // Cacher la Pok�ball apr�s l'animation
        animation->deleteLater();  // Supprimer l'animation apr�s qu'elle soit termin�e
        });

}