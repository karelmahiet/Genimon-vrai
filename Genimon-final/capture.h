#ifndef CAPTURE_H
#define CAPTURE_H

#include <QWidget>

namespace Ui {
class Capture;
}

class Capture : public QWidget
{
    Q_OBJECT

public:
    explicit Capture(QWidget *parent = nullptr);
    ~Capture();

public slots:
    void handleKeyPress(int key);

private:
    Ui::Capture *ui;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
};

#endif // CAPTURE_H
