#ifndef CHOIXJOUEUR_H
#define CHOIXJOUEUR_H

#include <QWidget>

namespace Ui {
class ChoixJoueur;
}

class ChoixJoueur : public QWidget
{
    Q_OBJECT

public:
    explicit ChoixJoueur(QWidget *parent = nullptr);
    ~ChoixJoueur();

    void updateQuiz();

public slots:
    void handleKeyPress(int key);   // Slot pour gérer les touches 1 et 2
    void initialiserChoixJoueur();

private:
    Ui::ChoixJoueur *ui;

    int etat;
    QString typeChoisi;
    QString nomJoueur;
    QString nomStarter;
    bool Clavier1;
    bool Clavier2;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
    void sendNomJoueur(const QString &nom); // Signal pour envoyer le nom choisi du joueur a map
};

#endif // CHOIXJOUEUR_H
