#include <QApplication>
#include "interface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TOffTic d;
    TMainWindow w(&d);
    w.show();

    return a.exec();
}
