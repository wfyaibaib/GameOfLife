#include "mainwindow.h"
#include <QApplication>
#include "gamemapmodel.h"
#include "QDebug"
#include "gamemapview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qDebug() << "new Modle!\n";

    GameMapView *view = new GameMapView(60, 30);
    view->show();






    
    return a.exec();
}
