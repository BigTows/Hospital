#include "mainwindow.h"
#include <QApplication>
#include "interface.h"
#include <QDebug>
#include <windows.h> //переключение раскладки

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);

    QApplication a(argc, argv);
    Interface * window = new Interface;

    ActivateKeyboardLayout((HKL)1, KLF_REORDER);

    window->setFixedSize(800,600);
    window->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    window->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    window->show();

    return a.exec();
}
