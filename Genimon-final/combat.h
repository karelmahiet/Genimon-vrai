#ifndef COMBAT_H
#define COMBAT_H

#include <QWidget>
class Genimon;

namespace Ui {
class Combat;
}

class Combat : public QWidget
{
    Q_OBJECT

public:
    explicit Combat(QWidget *parent = nullptr);
    ~Combat();

public slots:
    void handleKeyPress(int key);
    void setGenimonAdverse(Genimon* genimon);

private:
    Ui::Combat *ui;
    Genimon* genimon = nullptr;

signals:
    void requestMenuChange(int index);
};

#endif // COMBAT_H
