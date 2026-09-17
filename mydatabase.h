#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QByteArray>
#include <QList>
#include <QStringList>

#include "userinfo.h"

struct EmployeeFaceRecord
{
    QString employeeNo;
    QString name;
    QString department;
    QString position;
    QString phone;
    QString status;
    QStringList accessAreas;
    QByteArray faceFeature;
};

struct AccessLogRecord
{
    QString employeeNo;
    QString name;
    QString department;
    QString accessArea;
    QString result;
};

// 封装数据库相关的操作，单例类型
class MyDatabase : public QObject
{
    Q_OBJECT
public:
    static MyDatabase* instance();
    // 登录校验
    bool myLogin(QString name, QString pwd)
    {
        QString sql = "select name, passwd from users where name=:name and passwd=:passwd;";
        QSqlQuery query;
        query.prepare(sql);
        query.bindValue(":name", name);
        query.bindValue(":passwd", pwd);
        bool ok = query.exec();
        if (!ok)
        {
            qDebug() << "select error: " << query.lastError().text();
            return false;
        }

        if (query.next())
            return true;

        return false;
    }
    // 查询全部用户
    QList<UserInfo> queryUserInfos();
    // 注册用户（注册）
    bool addUser(QString name, QString pwd);
    //添加用户（界面进入后）
    bool addUseInfo(const UserInfo & user);
    //更新用户
    bool updateUserInfo(const UserInfo & user);
    //删除数据
    bool deleteUserInfo(int id);

    // 员工信息与登录用户使用两张相互独立的表。
    bool addEmployee(const EmployeeFaceRecord &employee, QString *errorMessage = nullptr);
    QList<EmployeeFaceRecord> queryEmployees(const QString &department,
                                             const QString &position,
                                             const QString &status,
                                             QString *errorMessage = nullptr);
    bool updateEmployee(const EmployeeFaceRecord &employee,
                        bool updateFaceFeature,
                        QString *errorMessage = nullptr);
    bool disableEmployee(const QString &staffId, QString *errorMessage = nullptr);
    // 只返回“在职”员工，离职和休假员工不会进入人脸比对集合。
    QList<EmployeeFaceRecord> queryEmployeeFaces(QString *errorMessage = nullptr);
    double faceMatchThreshold(QString *errorMessage = nullptr);
    bool addAccessLog(const AccessLogRecord &record, QString *errorMessage = nullptr);
private:
    bool initializeAccessControlTables(QString *errorMessage = nullptr);
    explicit MyDatabase(QObject *parent = nullptr);
    MyDatabase(const MyDatabase&) = delete;
    MyDatabase& operator=(const MyDatabase&) = delete;

    QSqlDatabase db;
    bool staffFaceHasLegacyEmployeeNo = false;
};

#endif // MYDATABASE_H
