#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) //几乎不用改
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
