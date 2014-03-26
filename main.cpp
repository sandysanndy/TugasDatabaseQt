#include "tampilan.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tampilan w;
    w.show();

    return a.exec();
}
