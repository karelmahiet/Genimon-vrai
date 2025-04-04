#include "controle.h"
#include "./ui_controle.h"
#include <QVBoxLayout>
#include "mainmenu.h"



Controle::Controle(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Controle)
    , stackedWidget(new QStackedWidget(this))
{
    ui->setupUi(this);

    // Créez les différentes pages
    stackedWidget->addWidget(new MainMenu(this)); // Index 0
    stackedWidget->addWidget(new ChoixJoueur(this)); // Index 1
    stackedWidget->addWidget(new Map(this)); // Index 2
    stackedWidget->addWidget(new Capture(this)); // Index 3
    stackedWidget->addWidget(new Combat(this)); // Index 4
    stackedWidget->addWidget(new Genidex(this)); // Index 5
    stackedWidget->addWidget(new HistoRencontre(this)); // Index 6
    stackedWidget->addWidget(new Commande(this)); // Index 7
    stackedWidget->addWidget(new Regle(this)); // Index 8
    stackedWidget->addWidget(new Pause(this)); // Index 9
    stackedWidget->addWidget(new ChoixAction(this)); // Index 10
    setCentralWidget(stackedWidget);

    choixJoueurMenu = qobject_cast<ChoixJoueur*>(stackedWidget->widget(1));
    mapMenu = qobject_cast<Map*>(stackedWidget->widget(2));
    captureMenu = qobject_cast<Capture*>(stackedWidget->widget(3));
    combatMenu = qobject_cast<Combat*>(stackedWidget->widget(4));
    genidexMenu = qobject_cast<Genidex*>(stackedWidget->widget(5));
    histoRencontreMenu = qobject_cast<HistoRencontre*>(stackedWidget->widget(6));
    commandeMenu = qobject_cast<Commande*>(stackedWidget->widget(7));
    regleMenu = qobject_cast<Regle*>(stackedWidget->widget(8));
    pauseMenu = qobject_cast<Pause*>(stackedWidget->widget(9));
    choixActionMenu = qobject_cast<ChoixAction*>(stackedWidget->widget(10));

    //Permet d'envoyer nom joueur de choixJoueur a Map
    connect(choixJoueurMenu, &ChoixJoueur::sendNomJoueur, mapMenu, &Map::setNomJoueur);

}

Controle::~Controle()
{
    delete ui;
}

void Controle::keyPressEvent(QKeyEvent* event) {

    if (stackedWidget->currentIndex() == 0) // Menu Main
    {
        switch (event->key()) {
        case Qt::Key_1:
            changeMenu(1); // Aller à ChoixJoueur
            break;
        case Qt::Key_2:
            changeMenu(7); // Aller à Commande
            break;
        case Qt::Key_3:
            changeMenu(8); // Aller à Regle
            break;
        case Qt::Key_4:
            QApplication::quit(); // Quitter
            break;
        default:
            QMainWindow::keyPressEvent(event);
        }
    }
    else if (stackedWidget->currentIndex() == 1) // Menu ChoixJoueur
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_Tab) {
            emit sendKeyPress(event->key());
        }
        else {
            QMainWindow::keyPressEvent(event); // Comportement par défaut
        }

    }
    else if (stackedWidget->currentIndex() == 2) // Menu Map
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_3 || event->key() == Qt::Key_4
            || event->key() == Qt::Key_W || event->key() == Qt::Key_A || event->key() == Qt::Key_S || event->key() == Qt::Key_D) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 3) // Menu Capture
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2) {
            emit sendKeyPress(event->key());
        }
    }
    else if (stackedWidget->currentIndex() == 4) // Menu Combat
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_3 || event->key() == Qt::Key_4) {
            emit sendKeyPress(event->key());
        }
    }
    else if (stackedWidget->currentIndex() == 5) // Menu Genidex
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_3 || event->key() == Qt::Key_4 || event->key() == Qt::Key_F || event->key() == Qt::Key_A
            || event->key() == Qt::Key_W || event->key() == Qt::Key_D || event->key() == Qt::Key_S) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 6) // Menu HistoRencontre
    {
        if (event->key() == Qt::Key_4) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 7) // Menu Commande
    {
        if (event->key() == Qt::Key_4 || event->key() == Qt::Key_H || event->key() == Qt::Key_A
            || event->key() == Qt::Key_W || event->key() == Qt::Key_D || event->key() == Qt::Key_S) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 8) // Menu Regle
    {
        if (event->key() == Qt::Key_4) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 9) // Menu Pause
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_3 || event->key() == Qt::Key_4) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 10) // Menu ChoixAction
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_3) {
            emit sendKeyPress(event->key());
        }
    }
}

void Controle::changeMenu(int index) {
    if (index >= 0 && index < stackedWidget->count()) {
        stackedWidget->setCurrentIndex(index);
    }

    // Deconnecter les liens entres menu avant d'en faire d'autres
    disconnect(this, &Controle::sendKeyPress, choixJoueurMenu, &ChoixJoueur::handleKeyPress);
    disconnect(choixJoueurMenu, &ChoixJoueur::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, mapMenu, &Map::handleKeyPress);
    disconnect(mapMenu, &Map::requestMenuChange, this, &Controle::changeMenu);
    disconnect(mapMenu, &Map::sendGenimonToCombat, combatMenu, &Combat::setGenimonAdverse);
    disconnect(this, &Controle::sendKeyPress, captureMenu, &Capture::handleKeyPress);
    disconnect(captureMenu, &Capture::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, combatMenu, &Combat::handleKeyPress);
    disconnect(combatMenu, &Combat::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, genidexMenu, &Genidex::handleKeyPress);
    disconnect(genidexMenu, &Genidex::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, histoRencontreMenu, &HistoRencontre::handleKeyPress);
    disconnect(histoRencontreMenu, &HistoRencontre::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, commandeMenu, &Commande::handleKeyPress);
    disconnect(commandeMenu, &Commande::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, regleMenu, &Regle::handleKeyPress);
    disconnect(regleMenu, &Regle::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, pauseMenu, &Pause::handleKeyPress);
    disconnect(pauseMenu, &Pause::requestMenuChange, this, &Controle::changeMenu);
    disconnect(pauseMenu, &Pause::mode5a8, mapMenu, &Map::gererMode5a8);
    disconnect(this, &Controle::sendKeyPress, choixActionMenu, &ChoixAction::handleKeyPress);
    disconnect(choixActionMenu, &ChoixAction::requestMenuChange, this, &Controle::changeMenu);


    // Relier commande clavier et de changement de menu aux autres menus.
    if (index == 1) {
        choixJoueurMenu->updateQuiz();
        connect(this, &Controle::sendKeyPress, choixJoueurMenu, &ChoixJoueur::handleKeyPress);
        connect(choixJoueurMenu, &ChoixJoueur::requestMenuChange, this, &Controle::changeMenu);
    }
    else if (index == 2) {
        mapMenu->demarrerMenu();
        connect(this, &Controle::sendKeyPress, mapMenu, &Map::handleKeyPress);
        connect(mapMenu, &Map::requestMenuChange, this, &Controle::changeMenu);
        connect(mapMenu, &Map::sendGenimonToCombat, combatMenu, &Combat::setGenimonAdverse);
    }
    else if (index == 3) {
        connect(this, &Controle::sendKeyPress, captureMenu, &Capture::handleKeyPress);
        connect(captureMenu, &Capture::requestMenuChange, this, &Controle::changeMenu);
    }
    else if (index == 4) {
        connect(this, &Controle::sendKeyPress, combatMenu, &Combat::handleKeyPress);
        connect(combatMenu, &Combat::requestMenuChange, this, &Controle::changeMenu);
    }
    else if (index == 5) {
        connect(this, &Controle::sendKeyPress, genidexMenu, &Genidex::handleKeyPress);
        connect(genidexMenu, &Genidex::requestMenuChange, this, &Controle::changeMenu);
    }
    else if (index == 6) {
        connect(this, &Controle::sendKeyPress, histoRencontreMenu, &HistoRencontre::handleKeyPress);
        connect(histoRencontreMenu, &HistoRencontre::requestMenuChange, this, &Controle::changeMenu);
    }
    else if (index == 7) {
        connect(this, &Controle::sendKeyPress, commandeMenu, &Commande::handleKeyPress);
        connect(commandeMenu, &Commande::requestMenuChange, this, &Controle::changeMenu);
    }
    else if (index == 8) {
        connect(this, &Controle::sendKeyPress, regleMenu, &Regle::handleKeyPress);
        connect(regleMenu, &Regle::requestMenuChange, this, &Controle::changeMenu);
    }
    else if (index == 9) {
        connect(this, &Controle::sendKeyPress, pauseMenu, &Pause::handleKeyPress);
        connect(pauseMenu, &Pause::requestMenuChange, this, &Controle::changeMenu);
        connect(pauseMenu, &Pause::reinitialiserJeu, choixJoueurMenu, &ChoixJoueur::initialiserChoixJoueur);
        connect(pauseMenu, &Pause::reinitialiserJeu, mapMenu, &Map::initialiserMap);
        connect(pauseMenu, &Pause::mode5a8, mapMenu, &Map::gererMode5a8);
    }
    else if (index == 10) {
        connect(this, &Controle::sendKeyPress, choixActionMenu, &ChoixAction::handleKeyPress);
        connect(choixActionMenu, &ChoixAction::requestMenuChange, this, &Controle::changeMenu);
    }
}