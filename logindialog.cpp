#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "mydatabase.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setWindowTitle("医院门禁系统登录");
    setStyleSheet(R"(
        QDialog, QWidget { background: #f5f7fa; color: #263238; font-size: 14px; }
        QLabel { color: #37474f; }
        QLineEdit { background: white; border: 1px solid #cfd8dc; border-radius: 6px;
                    padding: 7px 10px; }
        QLineEdit:focus { border: 1px solid #1976d2; }
        QPushButton { background: #1976d2; color: white; border: none; border-radius: 6px;
                      padding: 8px 20px; min-height: 24px; }
        QPushButton:hover { background: #1565c0; }
        QPushButton:pressed { background: #0d47a1; }
    )");


    ui->stackedWidget->setCurrentWidget(ui->page_login);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_return_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_login);
}

// void LoginDialog::on_pushButton_to_reg_clicked()
// {
//     ui->stackedWidget->setCurrentWidget(ui->page_register);
// }

// 注册页面的 确定 按钮
void LoginDialog::on_pushButton_ok_reg_clicked()
{
    // 获取用户输入的数据
    QString name = ui->lineEdit_name_reg->text();
    QString pwd = ui->lineEdit_passwd_reg->text();
    QString pwd2 = ui->lineEdit_passwd2_reg->text();

    // 判断, 并给出提示
    if (name.isEmpty() || pwd.isEmpty() || pwd2.isEmpty())
    {
        QMessageBox::warning(this, "警告", "用户名或密码不能为空！");
        return;
    }
    if (pwd != pwd2)
    {
        QMessageBox::critical(this, "错误", "两次密码不一致！");
        return;
    }

    // 把数据写入数据库
    bool ret = MyDatabase::instance()->addUser(name,pwd);
    if(ret)
    {
        QMessageBox::information(this, "提示", "注册成功！");
    }
    else
    {
        QMessageBox::warning(this, "警告", "用户名已经存在，注册失败！");
    }
}

// 登录界面中的 确定 按钮
void LoginDialog::on_pushButton_ok_log_clicked()
{
    QString name = ui->lineEdit_name_log->text();
    QString pwd = ui->lineEdit_passwd_log->text();

    if (name.isEmpty() || pwd.isEmpty())
    {
        QMessageBox::warning(this, "警告", "用户名或密码不能为空！");
        return;
    }
    qDebug() << name << ", " << pwd;

    bool ok = MyDatabase::instance()->myLogin(name, pwd);
    if (ok)
    {
        QMessageBox::information(this, "提示", "登录成功！");
        emit loginSuccess(name);
        this->hide();
    }
    else
    {
        QMessageBox::critical(this, "错误", "用户名或密码错误！");
        return;
    }
}

