#include "map.h"
#include "ui_map.h"

const int maxGenimon = 15;
const int position_x_ref = 72;
const int position_y_ref = 42;
const int image_x_ref = 680;
const int image_y_ref = 550;

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
    spawnTimer->start(4000);

    for (int i = 0; i < listeGenimons.count(); i++)
    {
        listeGenimons[i]->show();
    }
}

void Map::fermerMenu()
{
    joueur->hide();
    spawnTimer->stop();

    for (int i = 0; i < listeGenimons.count(); i++)
    {
        listeGenimons[i]->hide();
    }
}

void Map::initialiserMap()
{
    joueur = new QLabel(Parent);
    joueurX = image_x_ref;
    joueurY = image_y_ref;
    position_x = position_x_ref;
    position_y = position_y_ref;
    borne_x_min = 0;
    borne_y_min = 0;
    borne_x_max = 123;
    borne_y_max = 53;

    nbGenimonAttrapes = 0;
    nbBalles = 0;
    nbCapsuleGuerison = 0;
    step = 10;
    estExterieur = true;
    nomJoueur = "default";
    mode5a8Actif = false;

    ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-8bit.png"));
    imageJoueur.load(":/Decor/Image_Qt/Decor/ChatGPT.png");
    joueur->setPixmap(imageJoueur.scaled(120, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    joueur->setScaledContents(true);
    joueur->resize(120, 70);
    joueur->move(680, 550);
    joueur->hide();

    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &Map::gererGenimonMap);
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
            if (position_y < borne_y_max - 6) {
                joueurY += step;
                position_y++;
                joueur->move(joueurX, joueurY);
            }
            else if (position_x >= 61 && position_x <= 79 && position_y == borne_y_max - 6)
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

    //Détection collisions
    for (int i = 0; i < listeGenimons.count(); i++)
    {
        if (listeGenimons[i]->position_x - 4 == position_x && listeGenimons[i]->position_y - 1 == position_y)
        {
            emit sendGenimonToCombat(listeGenimons[i]);
            showCombat();
            return;
        }
    }
}

void Map::gererGenimonMap()
{
    //Ajouter un genimon
    if (listeGenimons.count() < maxGenimon)
    {
        if (listeGenimons.count() <= maxGenimon / 3)
        {
            ajouterGenimon();
        }
        else
        {
            if ((rand() % 2) == 1)
            {
                ajouterGenimon();
            }
        }
    }

    //Retirer un genimon
    if (listeGenimons.count() >= 10)
    {
        if ((rand() % 5) == 1)
        {
            retirerGenimon();
        }
    }
}

void Map::ajouterGenimon()
{
    Genimon* nouveauGenimon = new Genimon(Parent);
    listeGenimons.append(nouveauGenimon);
    if(estExterieur)
    {
        nouveauGenimon->position_x = 21 + rand() % 84;
        nouveauGenimon->position_y = rand() % borne_y_max;
    }
    else
    {
        nouveauGenimon->position_x = rand() % borne_x_max;
        nouveauGenimon->position_y = rand() % borne_y_max - 6;
    }

    while (nouveauGenimon->position_x == position_x && nouveauGenimon->position_y == position_y)
    {
        if (estExterieur)
        {
            nouveauGenimon->position_x = 21 + rand() % 84;
            nouveauGenimon->position_y = rand() % borne_y_max;
        }
        else
        {
            nouveauGenimon->position_x = rand() % borne_x_max;
            nouveauGenimon->position_y = rand() % borne_y_max - 6;
        }
    }

    //Position x
    if (nouveauGenimon->position_x == position_x_ref)
    {
        nouveauGenimon->genimonX = image_x_ref;
    }
    else if (nouveauGenimon->position_x < position_x_ref)
    {
        int difference = position_x_ref - nouveauGenimon->position_x;
        nouveauGenimon->genimonX = image_x_ref - (difference * step);
    }
    else if (nouveauGenimon->position_x > position_x_ref)
    {
        int difference = nouveauGenimon->position_x - position_x_ref;
        nouveauGenimon->genimonX = image_x_ref + (difference * step);
    }

    //Position y
    if (nouveauGenimon->position_y == position_y_ref)
    {
        nouveauGenimon->genimonY = image_y_ref;
    }
    else if (nouveauGenimon->position_y < position_y_ref)
    {
        int difference = position_y_ref - nouveauGenimon->position_y;
        nouveauGenimon->genimonY = image_y_ref - (difference * step);
    }
    else if (nouveauGenimon->position_y > position_y_ref)
    {
        int difference = nouveauGenimon->position_y - position_y_ref;
        nouveauGenimon->genimonY = image_y_ref + (difference * step);
    }

    nouveauGenimon->move(nouveauGenimon->genimonX, nouveauGenimon->genimonY);

    if (estExterieur && nouveauGenimon->estExterieur)
    {
        nouveauGenimon->show();
    }
    else if (!estExterieur && !nouveauGenimon->estExterieur)
    {
        nouveauGenimon->show();
    }
}

void Map::retirerGenimon()
{
    int indexRandom = rand() % listeGenimons.count(); //Retire un genimon random
    listeGenimons[indexRandom]->hide();
    listeGenimons.remove(indexRandom);
}

void Map::gererMode5a8()
{
    if (mode5a8Actif)
    {
        mode5a8Actif = false;
        if (estExterieur)
        {
            ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-8bit.png"));
        }
        else
        {
            ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Cafeteria.jpeg"));
        }
    }
    else
    {
        mode5a8Actif = true;
        if (estExterieur)
        {
            ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-8bit_5a8.png"));
        }
        else
        {
            ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Cafeteria_5a8.jpeg"));
        }
    }
}

void Map::showExtFaculte()
{
    if (mode5a8Actif)
    {
        ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-8bit_5a8.png"));
    }
    else
    {
        ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-8bit.png"));
    }
    ui->NomPerso->setVisible(true);

    position_x = 74;
    position_y = 0;
    joueurX = 700;
    joueurY = 130;
    joueur->move(joueurX, joueurY);
    estExterieur = true;

    for (int i = 0; i < listeGenimons.count(); i++)
    {
        if (listeGenimons[i]->estExterieur)
        {
            listeGenimons[i]->show();
        }
        else
        {
            listeGenimons[i]->hide();
        }
    }
}

void Map::showIntFaculte()
{
    if (mode5a8Actif)
    {
        ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Cafeteria_5a8.jpeg"));
    }
    else
    {
        ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Cafeteria.jpeg"));
    }
    ui->NomPerso->setVisible(true);

    position_x = 70;
    position_y = borne_y_max - 6;
    joueurX = 660;
    joueurY = 600;
    joueur->move(joueurX, joueurY);
    estExterieur = false;

    for (int i = 0; i < listeGenimons.count(); i++)
    {
        if (listeGenimons[i]->estExterieur)
        {
            listeGenimons[i]->hide();
        }
        else
        {
            listeGenimons[i]->show();
        }
    }
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