#include "frmmain.h"
#include "ui_frmmain.h"

#include <QTimer>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QScreen>
#include <QDebug>

frmMain::frmMain(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::frmMain)
{
    ui->setupUi(this);
    ShowColorValue();
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::ShowColorValue()
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();

    ui->txtXY->setText(tr("X:%1  Y:%2").arg(x).arg(y));
    QString strDecimalValue, strHex;

//    https://blog.csdn.net/hpu11/article/details/72859154
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0, x, y, 2, 2);
    if (!pixmap.isNull())
    {
        QImage image = pixmap.toImage();
        if (!image.isNull())
        {
            if (image.valid(0, 0))
            {
                QColor color = image.pixel(0, 0);
                int red=color.red();
                int green=color.green();
                int blue=color.blue();
                qDebug() << "rgb" << red << green << blue;

                QString strRed=QString("%1").arg(red&0xFF,2,16,QLatin1Char('0'));
                QString strGreen=QString("%1").arg(green&0xFF,2,16,QLatin1Char('0'));
                QString strBlue=QString("%1").arg(blue&0xFF,2,16,QLatin1Char('0'));

                strDecimalValue = tr("%1, %2, %3").arg(red).arg(green).arg(blue);
                strHex=tr("#%1%2%3").arg(strRed.toUpper()).arg(strGreen.toUpper()).arg(strBlue.toUpper());
            }
        }
    }

    QString str=tr("background-color: rgb(%1);").arg(strDecimalValue);
    ui->labColor->setStyleSheet(str);
    ui->txtRgb->setText(strDecimalValue);
    ui->txtWeb->setText(strHex);
    // 每隔 10 毫秒, 调用一次 ShowColorValue() 函数
    QTimer::singleShot(100, this, SLOT(ShowColorValue()));
}
