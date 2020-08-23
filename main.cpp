#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QVector<QString> fonts = {
        "Bebas.otf",
        "FontAwesome.otf",
        "Rezland.ttf",
        "Arial.ttf"
    };

    for (QVector<QString>::const_iterator it = fonts.begin(); it != fonts.end(); it++)
    {
        if (QFontDatabase::addApplicationFont(":/fonts/fonts/" + *it) < 0)
        {
            qWarning() << "The font, " << *it << ", could not be loaded!";
        }
    }

    return a.exec();
}
