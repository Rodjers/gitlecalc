#include "gitlecalculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GitleCalculator w;
    w.show();
    return a.exec();
}
