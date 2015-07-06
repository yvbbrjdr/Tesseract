#include "tesseractwidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    alutInit(&argc,argv);
    TesseractWidget w;
    w.show();
    return a.exec();
}
