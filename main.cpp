
#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;// 实例化主界面对象，默认情况下不显示
    LoginDialog w; // 实例化登录界面对象，默认情况下不显示
    // 连接登录界面的自定义信号与主界面的显示函数
    QObject::connect(&w, SIGNAL(loginSuccess(QString)), &m, SLOT(show()));
    w.show();
    return QApplication::exec();

}
