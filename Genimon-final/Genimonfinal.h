#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Genimonfinal.h"

class Genimonfinal : public QMainWindow
{
    Q_OBJECT

public:
    Genimonfinal(QWidget *parent = nullptr);
    ~Genimonfinal();

private:
    Ui::GenimonfinalClass ui;
};
