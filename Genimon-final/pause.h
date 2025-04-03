#ifndef PAUSE_H
#define PAUSE_H

#include <QWidget>

namespace Ui {
    class Pause;
}

class Pause : public QWidget
{
    Q_OBJECT

public:
    explicit Pause(QWidget* parent = nullptr);
    ~Pause();

public slots:
    void handleKeyPress(int key);

private:
    Ui::Pause* ui;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
    void reinitialiserJeu();
    void mode5a8();
};

#endif // PAUSE_H
