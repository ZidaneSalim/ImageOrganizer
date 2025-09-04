#include "imageorganizerwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ImageOrganizerWindow w;
    w.show();
    return a.exec();
}
