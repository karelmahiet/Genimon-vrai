#include "choixaction.h"
#include "ui_choixaction.h"

ChoixAction::ChoixAction(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChoixAction)
{
    ui->setupUi(this);
}

ChoixAction::~ChoixAction()
{
    delete ui;
}



void ChoixAction::handleKeyPress(int key) {
    if (key == Qt::Key_1) {
        emit requestMenuChange(4); //Passer au menu combat
        clearFocus();
    }

    if (key == Qt::Key_2) {
        emit requestMenuChange(3); //Passer au menu capture
        clearFocus();
    }

    if (key == Qt::Key_3) {
        emit requestMenuChange(2); //Passer au menu map
        clearFocus();
    }
}
