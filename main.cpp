#include "mainwindow.h"

#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // qss樣式
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly))
    {
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("open failed");
    }

    // 主窗口
    MainWindow w;
    w.show();

    return a.exec();
}
