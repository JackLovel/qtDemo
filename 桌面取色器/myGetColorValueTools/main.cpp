#include <QApplication>
#include "frmmain.h"

#include <QTextCodec>
#include <QDesktopWidget>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec=QTextCodec::codecForLocale();
    QTextCodec::setCodecForLocale(codec);

    QDesktopWidget *desktop = QApplication::desktop();
    int width=desktop->width();
    int height=desktop->height();

    frmMain w;
    w.setWindowFlags(Qt::WindowMinimizeButtonHint);
    w.setWindowFlags(Qt::WindowStaysOnTopHint);
    w.move((width-w.width())/2,(height-w.height())/2);
    w.setFixedSize(w.width(),w.height());
    w.show();
    QApplication::setStyle(QStyleFactory::create("Plastique"));

    return a.exec();
}
