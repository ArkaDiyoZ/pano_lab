#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.jsonParse();
    w.btnsInsertStart();
    w.show();

    return a.exec();
}
