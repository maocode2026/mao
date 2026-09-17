/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_login;
    QLabel *label_5;
    QLineEdit *lineEdit_name_log;
    QLineEdit *lineEdit_passwd_log;
    QPushButton *pushButton_ok_log;
    QLabel *label_6;
    QLabel *label_7;
    QWidget *page_register;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_name_reg;
    QLineEdit *lineEdit_passwd_reg;
    QLineEdit *lineEdit_passwd2_reg;
    QPushButton *pushButton_ok_reg;
    QPushButton *pushButton_return;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->setEnabled(true);
        LoginDialog->resize(478, 373);
        verticalLayout = new QVBoxLayout(LoginDialog);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(LoginDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setEnabled(true);
        page_login = new QWidget();
        page_login->setObjectName("page_login");
        label_5 = new QLabel(page_login);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(90, 150, 81, 31));
        lineEdit_name_log = new QLineEdit(page_login);
        lineEdit_name_log->setObjectName("lineEdit_name_log");
        lineEdit_name_log->setGeometry(QRect(180, 90, 211, 31));
        lineEdit_passwd_log = new QLineEdit(page_login);
        lineEdit_passwd_log->setObjectName("lineEdit_passwd_log");
        lineEdit_passwd_log->setEnabled(true);
        lineEdit_passwd_log->setGeometry(QRect(180, 150, 211, 31));
        lineEdit_passwd_log->setEchoMode(QLineEdit::EchoMode::Password);
        pushButton_ok_log = new QPushButton(page_login);
        pushButton_ok_log->setObjectName("pushButton_ok_log");
        pushButton_ok_log->setGeometry(QRect(210, 240, 93, 40));
        label_6 = new QLabel(page_login);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(90, 90, 81, 31));
        label_7 = new QLabel(page_login);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(130, 10, 201, 41));
        QFont font;
        font.setPointSize(20);
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stackedWidget->addWidget(page_login);
        page_register = new QWidget();
        page_register->setObjectName("page_register");
        label = new QLabel(page_register);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 10, 201, 41));
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(page_register);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 80, 81, 31));
        label_3 = new QLabel(page_register);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(70, 130, 81, 31));
        label_4 = new QLabel(page_register);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 180, 81, 31));
        lineEdit_name_reg = new QLineEdit(page_register);
        lineEdit_name_reg->setObjectName("lineEdit_name_reg");
        lineEdit_name_reg->setGeometry(QRect(180, 80, 211, 31));
        lineEdit_passwd_reg = new QLineEdit(page_register);
        lineEdit_passwd_reg->setObjectName("lineEdit_passwd_reg");
        lineEdit_passwd_reg->setGeometry(QRect(180, 130, 211, 31));
        lineEdit_passwd_reg->setEchoMode(QLineEdit::EchoMode::Password);
        lineEdit_passwd2_reg = new QLineEdit(page_register);
        lineEdit_passwd2_reg->setObjectName("lineEdit_passwd2_reg");
        lineEdit_passwd2_reg->setGeometry(QRect(180, 180, 211, 31));
        lineEdit_passwd2_reg->setEchoMode(QLineEdit::EchoMode::Password);
        pushButton_ok_reg = new QPushButton(page_register);
        pushButton_ok_reg->setObjectName("pushButton_ok_reg");
        pushButton_ok_reg->setGeometry(QRect(140, 250, 93, 40));
        pushButton_return = new QPushButton(page_register);
        pushButton_return->setObjectName("pushButton_return");
        pushButton_return->setGeometry(QRect(300, 250, 93, 40));
        stackedWidget->addWidget(page_register);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(LoginDialog);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "LoginDialog", nullptr));
        label_5->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        pushButton_ok_log->setText(QCoreApplication::translate("LoginDialog", "\347\241\256\345\256\232", nullptr));
        label_6->setText(QCoreApplication::translate("LoginDialog", "\347\224\250\346\210\267", nullptr));
        label_7->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225\351\241\265\351\235\242", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "\346\263\250\345\206\214\351\241\265\351\235\242", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "\347\224\250\346\210\267", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("LoginDialog", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        pushButton_ok_reg->setText(QCoreApplication::translate("LoginDialog", "\347\241\256\345\256\232", nullptr));
        pushButton_return->setText(QCoreApplication::translate("LoginDialog", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
