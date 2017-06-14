#include "mainwindow.h"
#include <QApplication>
#include "interface.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface * window = new Interface;
    //QLocale::system().language("English");
    window->show();

    return a.exec();
}
