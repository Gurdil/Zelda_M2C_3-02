#include <QApplication>
#include <iostream>

#include "controler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOverrideCursor(QCursor(Qt::BlankCursor ));

    //controler *c = new controler();

    ZControler *c = ZControler::getInstance();

    return a.exec();

    std::cout << "Never view" << std::endl;
}
