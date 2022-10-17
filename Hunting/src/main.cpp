#include "huntingwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HuntingWidget w;
    w.show();
    return a.exec();
}
