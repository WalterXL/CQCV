#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    //w.setWindowIcon(QPixmap(path_temp.c_str()));
    w.show();
    return a.exec();
}
