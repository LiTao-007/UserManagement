#include "mainview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("windows"); //设置界面风格为window风格
    MainView w;
    w.show();

    return a.exec();
}
