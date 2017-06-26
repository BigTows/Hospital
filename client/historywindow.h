#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QListWidget>
#include <QDialog>
#include <QVBoxLayout>

class historyWindow:  public QDialog
{
public:
    historyWindow(QWidget * parent = 0, std::vector<QString> massive = std::vector<QString>());

    QListWidget * list;
};

#endif // HISTORYWINDOW_H
