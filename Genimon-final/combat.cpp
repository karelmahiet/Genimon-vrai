#include "combat.h"
#include "ui_combat.h"
#include "genimon.h"

Combat::Combat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Combat)
{
    ui->setupUi(this);
    this->setStyleSheet(":/Decor/Image_Qt/Decor/AreneCombat.png");

}

Combat::~Combat()
{
    delete ui;
}
void Combat::setGenimonAdverse(Genimon* genimon) {
    this->genimon = genimon;

    qDebug() << "Combat lancé contre :" << QString::fromStdString(genimon->getNom());

    QPixmap image(":/Info/Image_Qt/Info/ecran_Albert.png");//devrait etre dynamique
    QLabel* label = new QLabel(this);
    label->setPixmap(image.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    label->move(200, 200);
    label->show();

    QLabel* nom = new QLabel(this);
    nom->setText(QString::fromStdString(genimon->getNom()));
    nom->move(200, 310);
    nom->setStyleSheet("color: white; font-size: 20px;");
    nom->show();
}


void Combat::handleKeyPress(int key) {

}
