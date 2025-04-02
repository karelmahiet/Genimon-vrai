#ifndef COMMANDE_H
#define COMMANDE_H

#include <QWidget>

namespace Ui {
class Commande;
}

class Commande : public QWidget
{
    Q_OBJECT

public:
    explicit Commande(QWidget *parent = nullptr);
    ~Commande();

public slots:
    void handleKeyPress(int key);

private:
    Ui::Commande *ui;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
};

#endif // COMMANDE_H
