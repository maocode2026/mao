#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "mydatabase.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);


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

