#include "src/mainwindow/mainwindow.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QPushButton b("hello world");
    b.show();
    b.setToolTip("hello");
    return a.exec();
}
