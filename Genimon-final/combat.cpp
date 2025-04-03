#include "combat.h"
#include "ui_combat.h"
#include <QPixmap>

Combat::Combat(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Combat), TransTimer(new QTimer(this))
{
    ui->setupUi(this);
    connect(TransTimer, &QTimer::timeout, this, &Combat::combat);
}

Combat::~Combat()
{
    delete TransTimer;
    delete ui;
}

void Combat::handleKeyPress(int key) {
    if (key == Qt::Key_1 || key == Qt::Key_2 || key == Qt::Key_3 || key == Qt::Key_4) {

    }
}

void Combat::showEvent(QShowEvent* event) {

    //qDebug() << "La fenêtre de combat est maintenant affichée!";
    transition();
    // Démarrer le timer pour exécuter la fonction combat après 3 secondes
    TransTimer->start(3000);  // 3000 millisecondes = 3 secondes

    QWidget::showEvent(event);  // N'oublie pas d'appeler la méthode de base pour conserver le comportement normal
}



void Combat::transition() {

    ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Transition combat.png"));
    ui->Genimon1->move(570, 130);
    ui->Genimon2->move(570, 460);
    ui->Nom1->setVisible(false);
    ui->Nom2->setVisible(false);
    ui->HP1->setVisible(false);
    ui->HP2->setVisible(false);
    ui->Attaque1->setVisible(false);
    ui->Attaque2->setVisible(false);
    ui->Attaque3->setVisible(false);
    ui->Attaque4->setVisible(false);
    ui->HP_V1->setVisible(false);
    ui->HP_V2->setVisible(false);
    ui->TableauInfo->setVisible(false);

}



void Combat::combat() {

    ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/AreneCombat.png"));
    ui->Genimon1->move(280, 280);
    ui->Genimon2->move(900, 140);
    ui->Nom1->setVisible(true);
    ui->Nom2->setVisible(true);
    ui->HP1->setVisible(true);
    ui->HP2->setVisible(true);
    ui->Attaque1->setVisible(true);
    ui->Attaque2->setVisible(true);
    ui->Attaque3->setVisible(true);
    ui->Attaque4->setVisible(true);
    ui->HP_V1->setVisible(true);
    ui->HP_V2->setVisible(true);
    ui->TableauInfo->setVisible(true);

}

void Combat::info() {

    ui->Nom1->setText(QString("Nom: %1").arg("Dylan"));// a remplacer par nom classe genimon
    ui->Nom2->setText(QString("Nom: %1").arg("Moi"));// a remplacer par nom classe genimon
    ui->Attaque1->setText(QString("%1 (1)").arg("Mechant"));// a remplacer par nom classe genimon
    ui->Attaque2->setText(QString("%1 (2)").arg("Manger"));// a remplacer par nom classe genimon
    ui->Attaque3->setText(QString("%1 (3)").arg("WTF"));// a remplacer par nom classe genimon
    ui->Attaque4->setText(QString("%1 (4)").arg("Why not"));// a remplacer par nom classe genimon
    ui->HP_V1->setValue(100);
    ui->HP_V2->setValue(100);

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