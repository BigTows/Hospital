#include "historywindow.h"
#include <QDebug>

historyWindow::historyWindow(QWidget *parent, std::vector<QString> massive)
{
    QVBoxLayout layout;
    setLayout(&layout);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);


    list = new QListWidget;
    list->clear();
    list->setStyleSheet("background-color: lightblue;"
                        "font: 17px;");
    list->resize(this->width(),this->height());

    for (unsigned int i = 0; i < massive.size(); i++)
    {
        list->addItem(massive[i]);
    }


    layout.addWidget(list);

}
