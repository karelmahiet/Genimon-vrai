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

    // Animation de la Pokéball
    animation = new QPropertyAnimation(ui->Pokeball, "pos", this);
    animation->setDuration(2000); // Durée de l'animation
    animation->setStartValue(QPoint(200, 440)); // Position de départ
    animation->setEndValue(QPoint(800, 170)); // Position d'arrivée

    // Utiliser un mouvement de courbe parabolique
    animation->setEasingCurve(QEasingCurve::OutQuad); // Courbe d'accélération de type "rebond"

    animation->start();

    // Timer pour faire disparaître la Pokéball après l'animation
    connect(animation, &QPropertyAnimation::finished, this, [=]() {
        ui->Pokeball->setVisible(false);  // Cacher la Pokéball après l'animation
        animation->deleteLater();  // Supprimer l'animation après qu'elle soit terminée
        });

}