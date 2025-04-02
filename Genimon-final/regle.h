#ifndef REGLE_H
#define REGLE_H

#include <QWidget>

namespace Ui {
class Regle;
}

class Regle : public QWidget
{
    Q_OBJECT

public:
    explicit Regle(QWidget *parent = nullptr);
    ~Regle();

public slots:
    void handleKeyPress(int key);

private:
    Ui::Regle *ui;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
};

#endif // REGLE_H
