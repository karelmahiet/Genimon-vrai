#include "map.h"
#include "ui_map.h"

Map::Map(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Map)
{
    ui->setupUi(this);
    ui->NomPerso->setText(QString("%1").arg(nomJoueur));
    Parent = parent;

    initialiserMap();
}

Map::~Map()
{
    delete ui;
}

void Map::demarrerMenu()
{
    joueur->show();
}

void Map::fermerMenu()
{
    joueur->hide();
}

void Map::initialiserMap()
{
    joueur = new QLabel(Parent);
    joueurX = 680;
    joueurY = 550;
    position_x = 72;
    position_y = 42;
    borne_x_min = 0;
    borne_y_min = 0;
    borne_x_max = 123;
    borne_y_max = 51;

    nbGenimonAttrapes = 0;
    nbBalles = 0;
    nbCapsuleGuerison = 0;
    step = 10;
    estExterieur = true;
    enCombat = false;
    nomJoueur = "default";

    ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-8bit.png"));
    imageJoueur.load(":/Decor/Image_Qt/Decor/ChatGPT.png");
    joueur->setPixmap(imageJoueur.scaled(120, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    joueur->setScaledContents(true);
    joueur->resize(120, 70);
    joueur->move(680, 550);
    joueur->hide();

    //spawnTimer = new QTimer(this);
    //connect(spawnTimer, &QTimer::timeout, this, &Map::spawnRandomGenimon);
    //spawnTimer->start(7000);
}

void Map::handleKeyPress(int key)
{
    if (key == Qt::Key_1) {
        showGenidex();
    }
    else if (key == Qt::Key_2) {
        showHistoRencontre();
    }
    else if (key == Qt::Key_3) {
        showPause();
    }
    else if (key == Qt::Key_W) {
        if (position_y > borne_y_min) {
            joueurY -= step;
            position_y--;
            joueur->move(joueurX, joueurY);
        }
        else if (estExterieur && position_x >= 69 && position_x <= 79 && position_y == 0)
        {
            showIntFaculte();
        }
    }
    else if (key == Qt::Key_A) {
        if (estExterieur)
        {
            if (((position_x > borne_x_min) && (position_x > 21 && position_x <= 105)) || (position_x > borne_x_min && position_y < 10))
            {
                joueurX -= step;
                position_x--;
                joueur->move(joueurX, joueurY);
            }
        }
        else
        {
            if (position_x > borne_x_min)
            {
                joueurX -= step;
                position_x--;
                joueur->move(joueurX, joueurY);
            }
        }
    }
    else if (key == Qt::Key_S) {
        if (estExterieur)
        {
            if (((position_y < borne_y_max) && (position_x >= 21 && position_x <= 105)) || position_y < 9) {
                joueurY += step;
                position_y++;
                joueur->move(joueurX, joueurY);
            }
        }
        else
        {
            if (position_y < borne_y_max - 4) {
                joueurY += step;
                position_y++;
                joueur->move(joueurX, joueurY);
            }
            else if (position_x >= 61 && position_x <= 79 && position_y == borne_y_max - 4)
            {
                showExtFaculte();
            }
        }
    }
    else if (key == Qt::Key_D) {
        if (estExterieur)
        {
            if (((position_x < borne_x_max) && (position_x >= 21 && position_x < 105)) || (position_x < borne_x_max && position_y < 10))
            {
                joueurX += step;
                position_x++;
                joueur->move(joueurX, joueurY);
            }
        }
        else
        {
            if (position_x < borne_x_max)
            {
                joueurX += step;
                position_x++;
                joueur->move(joueurX, joueurY);
            }
        }
    }

    if (!enCombat)
    {
        for (GenimonSprite& g : genimonsSurCarte)
        {
            if (position_x == g.x && position_y == g.y) {
                enCombat = true;
                emit sendGenimonToCombat(g.data);
                emit requestMenuChange(4);
                return;
            }
        }
    }
}

void Map::spawnRandomGenimon() {
    int gx = rand() % 10 + 1;
    int gy = rand() % 8 + 1;

    //pas sur case joueur
    if (gx == position_x && gy == position_y)
        return;

    Genimon* nouveau = new Genimon();
    QLabel* visuel = new QLabel(this);

    visuel->setPixmap(QPixmap(":/Info/Image_Qt/Info/ecran_Albert.png").scaled(50, 50)); //a rendre dynamique
    visuel->setFixedSize(50, 50);
    visuel->move(gx * 50 + 400, gy * 50 + 100);
    visuel->show();

    genimonsSurCarte.append({ nouveau, visuel, gx, gy });
}

void Map::showExtFaculte()
{
    ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-8bit.png"));
    ui->NomPerso->setVisible(true);

    position_x = 74;
    position_y = 0;
    joueurX = 700;
    joueurY = 130;
    joueur->move(joueurX, joueurY);
    estExterieur = true;
}

void Map::showIntFaculte()
{
    ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Cafeteria.jpeg"));
    ui->NomPerso->setVisible(true);

    position_x = 70;
    position_y = borne_y_max - 4;
    joueurX = 660;
    joueurY = 600;
    joueur->move(joueurX, joueurY);
    estExterieur = false;
}

void Map::showCombat()
{
    emit requestMenuChange(4); //Passer au menu combat
    fermerMenu();
}

void Map::showGenidex()
{
    emit requestMenuChange(5); //Passer au menu genidex
    fermerMenu();
}

void Map::showHistoRencontre()
{
    emit requestMenuChange(6); //Passer au menu histoRencontre
    fermerMenu();
}

void Map::showPause()
{
    emit requestMenuChange(9); //Passer au menu pause
    fermerMenu();
}

void Map::setNomJoueur(const QString& nom)
{
    nomJoueur = nom;
    ui->NomPerso->setText(QString("%1").arg(nomJoueur));
}