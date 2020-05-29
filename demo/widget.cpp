#include "widget.h"
#include "ui_widget.h"
#include "windows.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    cpuPercent = 0;

    memoryPercent = 0;
    memoryAll = 0;
    memoryUse = 0;
    labCPUMemory = 0;

    GetCPU();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::GetCPU()
{
#ifdef Q_OS_WIN
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,7))

    static FILETIME preidleTime;
    static FILETIME prekernelTime;
    static FILETIME preuserTime;

    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    quint64 a, b;
    int idle, kernel, user;

    a = (preidleTime.dwHighDateTime << 31) | preidleTime.dwLowDateTime;
    b = (idleTime.dwHighDateTime << 31) | idleTime.dwLowDateTime;
    idle = b -a;

    a = (prekernelTime.dwHighDateTime << 31) | prekernelTime.dwLowDateTime;
    b = (kernelTime.dwHighDateTime << 31) | kernelTime.dwLowDateTime;
    kernel = b -a;

    a = (preuserTime.dwHighDateTime << 31) | preuserTime.dwLowDateTime;
    b = (userTime.dwHighDateTime << 31) | userTime.dwLowDateTime;
    user = b -a;

    cpuPercent = (kernel + user - idle) * 100 / (kernel + user);

    preidleTime = idleTime;
    prekernelTime = kernelTime;
    preuserTime = userTime ;

    QString msg = QString("CPU : %1%  内存 : %2% ( 已用 %3 MB / 共 %4 MB )")
                  .arg(cpuPercent).arg(memoryPercent).arg(memoryUse).arg(memoryAll);
    ui->cpuMemoryLabel->setText(msg);
#endif
#else
    if (process->state() == QProcess::NotRunning) {
        totalNew = idleNew = 0;
        process->start("cat /proc/stat");
    }
#endif
}

