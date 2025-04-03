#include "pause.h"
#include "ui_pause.h"

Pause::Pause(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Pause)
{
    ui->setupUi(this);
}

Pause::~Pause()
{
    delete ui;
}

void Pause::handleKeyPress(int key) {
    if (key == Qt::Key_1) {
        QApplication::quit(); // Quitter
    }
    else if (key == Qt::Key_2) {
        emit requestMenuChange(0); //Passer au menu main
        emit reinitialiserJeu();
    }
    else if (key == Qt::Key_3) {
        emit mode5a8();
    }
    else if (key == Qt::Key_4) {
        emit requestMenuChange(2); //Passer au menu map
    }
}
