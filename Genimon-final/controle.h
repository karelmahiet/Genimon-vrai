#ifndef CONTROLE_H
#define CONTROLE_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QKeyEvent>

#include "capture.h"
#include "choixjoueur.h"
#include "combat.h"
#include "commande.h"
#include "genidex.h"
#include "historencontre.h"
#include "map.h"
#include "regle.h"
#include "pause.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Controle;
}
QT_END_NAMESPACE

class Controle : public QMainWindow
{
    Q_OBJECT

public:
    Controle(QWidget *parent = nullptr);
    ~Controle();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::Controle *ui;
    QStackedWidget *stackedWidget;

    ChoixJoueur* choixJoueurMenu;
    Map* mapMenu;
    Capture* captureMenu;
    Combat* combatMenu;
    Genidex* genidexMenu;
    HistoRencontre* histoRencontreMenu;
    Commande* commandeMenu;
    Regle* regleMenu;
    Pause* pauseMenu;

    void changeMenu(int index);

signals:
    void sendKeyPress(int key); // Signal pour envoyer les touches clavier
};
#endif // CONTROLE_H
