#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if (QFontDatabase::addApplicationFont(":/fonts/fonts/Bebas.otf") < 0)
        qWarning() << "Bebas cannot be loaded !";

    if (QFontDatabase::addApplicationFont(":/fonts/fonts/FontAwesome.otf") < 0)
        qWarning() << "FontAwesome cannot be loaded !";

    if (QFontDatabase::addApplicationFont(":/fonts/fonts/Rezland.ttf") < 0)
        qWarning() << "Rezland cannot be loaded !";

    return a.exec();
}
