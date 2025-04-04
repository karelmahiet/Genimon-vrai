#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <vector>
#include <QVector>
#include "genimon.h"
#include "combat.h"

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

    void showCombat();
    void demarrerMenu();
    void fermerMenu();

public slots:
    void handleKeyPress(int key);
    void setNomJoueur(const QString& nom);
    void initialiserMap();
    void gererMode5a8();

private:
    Ui::Map* ui;
    QWidget* Parent;
    QTimer* spawnTimer;
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

    //caseGenidex genidex[8];
    vector<Genimon> historique;
    QVector<Genimon*> listeGenimons;
    int nbGenimonAttrapes;
    int nbBalles;
    int nbCapsuleGuerison;

    int step;
    bool estExterieur;
    QString nomJoueur;
    bool mode5a8Actif;
    bool estSurMap;

    void gererGenimonMap();
    void showExtFaculte();
    void showIntFaculte();
    void showGenidex();
    void showHistoRencontre();
    void showPause();
    void ajouterGenimon();
    void retirerGenimon();

signals:
    void requestMenuChange(int index);
    void sendGenimonToCombat(Genimon* genimon);
    void sendHistorique(vector<Genimon> historique);
};

#endif // MAP_H
