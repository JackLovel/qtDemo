#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_pauseButton_clicked();

    void on_pointButton_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *pTimer;
    QTime baseTime;

    // 显示时间
    QString timeStr;

    void updateDisplay();

};
#endif // MAINWINDOW_H
