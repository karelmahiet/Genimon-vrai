#include "controle.h"
#include <QApplication>

Controle *controle;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controle = new Controle;
    controle->show();
    return a.exec();
}
