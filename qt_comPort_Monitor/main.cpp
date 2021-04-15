#include "mainwindow.h"

#include <QApplication>
//#include "./logging/Logger.h"

int main(int argc, char *argv[])
{
//    Logger::init(0);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    bool state = a.exec();

//    Logger::clean();
    return state;
}
