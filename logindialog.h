#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui {
class LoginDialog;
}
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog() override;

signals: // 自定义信号
    void loginSuccess(QString username);

private slots:
    void on_pushButton_return_clicked();

    // void on_pushButton_to_reg_clicked();

    void on_pushButton_ok_reg_clicked();

    void on_pushButton_ok_log_clicked();

private:
    Ui::LoginDialog *ui;
    QString name = "1";
    QString passwd = "1";


};
#endif // LOGINDIALOG_H
