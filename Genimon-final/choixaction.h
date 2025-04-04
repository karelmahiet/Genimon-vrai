#ifndef CHOIXACTION_H
#define CHOIXACTION_H

#include <QWidget>

namespace Ui {
class ChoixAction;
}

class ChoixAction : public QWidget
{
    Q_OBJECT

public:
    explicit ChoixAction(QWidget *parent = nullptr);
    ~ChoixAction();

public slots:
    void handleKeyPress(int key);

private:
    Ui::ChoixAction *ui;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
};

#endif // CHOIXACTION_H
