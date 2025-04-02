#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <vector>
#include "genimon.h"

namespace Ui {
    class Map;
}

//struct caseGenidex
//{
//    vector<Genimon> listeGenimonAttrapé;
//};
//
//struct genimonChoisi
//{
//    int indexI = 0;
//    int indexJ = 0;
//};

// Structure utilisée pour afficher les Genimons sur la map
struct GenimonSprite {
    Genimon* data;
    QLabel* label;
    int x;
    int y;
};

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget* parent = nullptr);
    ~Map();

    void demarrerMenu();
    void fermerMenu();
    void initialiserMap();

public slots:
    void handleKeyPress(int key);
    void setNomJoueur(const QString& nom);

private:
    Ui::Map* ui;
    QWidget* Parent;

    QLabel* joueur;
    QPixmap imageJoueur;
    int joueurX;
    int joueurY;
    int position_x;
    int position_y;
    int borne_x_min;
    int borne_y_min;
    int borne_x_max;
    int borne_y_max;

    /*caseGenidex genidex[8];
    vector<Genimon> historique;
    Vecteur<Genimon*> listeGenimons;*/
    int nbGenimonAttrapes;
    int nbBalles;
    int nbCapsuleGuerison;

    int step;
    bool estExterieur;
    bool enCombat;
    QString nomJoueur;

    QVector<GenimonSprite> genimonsSurCarte;
    QTimer* spawnTimer;

    void spawnRandomGenimon();
    void showExtFaculte();
    void showIntFaculte();
    void showCombat();
    void showGenidex();
    void showHistoRencontre();
    void showPause();

signals:
    void requestMenuChange(int index);
    void sendGenimonToCombat(Genimon* genimon);
};

#endif // MAP_H
