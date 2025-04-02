#ifndef HISTORENCONTRE_H
#define HISTORENCONTRE_H

#include <QWidget>

namespace Ui {
class HistoRencontre;
}

class HistoRencontre : public QWidget
{
    Q_OBJECT

public:
    explicit HistoRencontre(QWidget *parent = nullptr);
    ~HistoRencontre();

public slots:
    void handleKeyPress(int key);

private:
    Ui::HistoRencontre *ui;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
};

#endif // HISTORENCONTRE_H
