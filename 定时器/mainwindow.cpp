#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 默认显示
    this->ui->lcdNumber->display("00:00:00:000");
    this->pTimer = new QTimer;
    connect(this->pTimer, &QTimer::timeout, this, &MainWindow::updateDisplay);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDisplay()
{
    QTime currTime = QTime::currentTime();
    int t = this->baseTime.msecsTo(currTime);
    QTime showTime(0,0,0,0);
    showTime = showTime.addMSecs(t);
    this->timeStr = showTime.toString("hh:mm:ss:zzz");
    this->ui->lcdNumber->display(timeStr);
}


void MainWindow::on_startButton_clicked()
{
    // 获取当前时间
    this->baseTime = this->baseTime.currentTime();
    this->pTimer->start(1);

    //
    if (this->ui->stopButton->text() != "停止") {
        this->ui->stopButton->setText("停止");
    }
    if (this->ui->pauseButton->text() != "暂停") {
        this->ui->pauseButton->setText("暂停");
    }
}

void MainWindow::on_stopButton_clicked()
{
    if (this->ui->stopButton->text() == "停止") {
        this->ui->stopButton->setText("清空");
        this->pTimer->stop();
    } else if (this->ui->stopButton->text() == "清空") {
        this->ui->stopButton->setText("停止");
        this->ui->textEdit->clear();
        this->ui->lcdNumber->display("00:00:00:000");
    }
}

void MainWindow::on_pauseButton_clicked()
{
    static QTime pauseTime;
    if (this->ui->pauseButton->text() == "暂停") {
        pauseTime = QTime::currentTime();
        this->ui->pauseButton->setText("继续");
        this->pTimer->stop();
    } else if (this->ui->pauseButton->text() == "继续") {
        // 进行差值计算
        QTime cut = QTime::currentTime();
        int t = pauseTime.msecsTo(cut);
        this->baseTime = this->baseTime.addMSecs(t);
        this->ui->pauseButton->setText("暂停");
        this->pTimer->start();
    }
}

void MainWindow::on_pointButton_clicked()
{
    this->ui->textEdit->append(this->timeStr);
}
