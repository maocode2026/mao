#include "mydatabase.h"
#include <QDebug>
#include <QDateTime>
#include <QThread>

namespace
{
bool isDatabaseBusy(const QSqlError &error)
{
    const QString message = error.text();
    const QString code = error.nativeErrorCode();
    return code == "5" || code == "6"
           || message.contains("database is locked", Qt::CaseInsensitive)
           || message.contains("database is busy", Qt::CaseInsensitive);
}

// SQLite 同一时刻只允许一个写事务。遇到临时写锁时等待后重试，
// 避免数据库管理工具或上次异常退出造成程序直接崩溃。
bool execSqlWithRetry(QSqlQuery &query, const QString &sql, int retryCount = 20)
{
    for (int attempt = 0; attempt <= retryCount; ++attempt)
    {
        if (query.exec(sql))
            return true;
        if (!isDatabaseBusy(query.lastError()) || attempt == retryCount)
            return false;

        query.finish();
        QThread::msleep(250);
    }
    return false;
}
}


MyDatabase::MyDatabase(QObject *parent)
    : QObject{parent}
{

    // 初始化数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/C/qt/demo.db");
    // 驱动层等待锁释放；与下方重试配合，最长约等待 10 秒。
    db.setConnectOptions("QSQLITE_BUSY_TIMEOUT=10000");
    bool ok = db.open();
    if (!ok)
    {
        qCritical() << "数据库打开失败：" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    execSqlWithRetry(query, "pragma busy_timeout=10000;");

    QString sql = "create table if not exists userinfo(id int primary key,name text not null, age int check(age>0)); ";
    bool ok1 = execSqlWithRetry(query, sql);
    if(!ok1)
    {
        qDebug()<<"create table error:"<<query.lastError().text();
        return;
    }
    qDebug() << "userinfo表创建成功/已存在";

    // 保留旧 employees 表，便于兼容此前版本的数据。
    sql = R"(
        create table if not exists employees(
            employee_no text primary key,
            name text not null,
            department text not null,
            position text not null,
            phone text not null,
            face_feature blob not null,
            created_at text not null default (datetime('now', 'localtime'))
        );
    )";
    if (!execSqlWithRetry(query, sql))
    {
        qCritical() << "旧员工表初始化失败：" << query.lastError().text();
    }

    QString accessControlError;
    if (!initializeAccessControlTables(&accessControlError))
        qCritical() << accessControlError;



}
// 获取单例实例
MyDatabase *MyDatabase::instance()
{
    static MyDatabase d;
    return &d;
}
/**
 * @brief 登录校验函数
 * @param name 输入的用户名
 * @param pwd 输入的密码
 * @return 查到匹配用户返回true，否则false
 */

/**
 * @brief 查询全部用户信息
 * @return 返回所有用户信息的列表
 */
QList<UserInfo> MyDatabase::queryUserInfos()
{
    QList<UserInfo> list;

    QString sql = "select id, name, passwd from users;";
    QSqlQuery query;
    bool ok = query.exec(sql);
    if (!ok)
    {
        qDebug() << "select error: " << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString passwd = query.value("passwd").toString();

        list.push_back(UserInfo(id, name, passwd));
    }
    return list;
}

bool MyDatabase::addUser(QString name, QString pwd)//注册插入数据库
{
    //先查询用户名是否存在
    QString sql = "select name from users where name=:name;";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":name",name);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << "查重错误：" << query.lastError().text();
        return false;
    }
    if(query.next())//查到记录，用户名存在
    {

        return false;
    }
    //没查到，用户名不存在
    sql = "insert into users(name,passwd)values(:name,:pwd)";
    query.prepare(sql);
    query.bindValue(":name", name);
    query.bindValue(":pwd", pwd);
    bool ok1 = query.exec();
    if(!ok1)
    {
        qDebug() << "插入失败：" << query.lastError().text();
        return false;
    }
    return true;

}

bool MyDatabase::addUseInfo(const UserInfo &user)//添加用户
{
    QString sql = "insert into users(id,name,passwd) values (:id, :name,:passwd);";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", user.id());
    query.bindValue(":name", user.name());
    query.bindValue(":passwd", user.passwd());
    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << "插入失败：" << query.lastError().text();
        return false;
    }
    return true;
}

bool MyDatabase::updateUserInfo(const UserInfo &user)//修改数据
{
    QString sql = "update users set name=:name, passwd=:passwd where id=:id;";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", user.id());
    query.bindValue(":name", user.name());
    query.bindValue(":passwd", user.passwd());
    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"修改失败："<<query.lastError().text();
        return false;
    }
    return true;

}

bool MyDatabase::deleteUserInfo(int id)//删除
{
    QString sql = "delete from users where id=:id;";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id",id);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"删除失败："<<query.lastError().text();
        return false;
    }
    return true;
}

bool MyDatabase::initializeAccessControlTables(QString *errorMessage)
{
    if (accessControlTablesReady)
        return true;
    if (!db.isOpen())
    {
        if (errorMessage)
            *errorMessage = "数据库没有打开：" + db.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    const QStringList statements = {
        R"(
            create table if not exists staff_face(
                staff_id text primary key,
                name text not null,
                department text not null,
                position text not null,
                phone text not null,
                status text not null default '在职',
                access_areas text not null default '',
                face_feature blob not null,
                created_at text not null default (datetime('now', 'localtime'))
            );
        )",
        R"(
            create table if not exists sys_config(
                config_key text primary key,
                config_value text not null
            );
        )",
        R"(
            create table if not exists access_log(
                id integer primary key autoincrement,
                access_time text not null,
                employee_no text,
                name text,
                department text,
                access_area text not null,
                result text not null
            );
        )",
        "insert or ignore into sys_config(config_key, config_value) values('face_match_threshold', '0.363');"
    };

    for (const QString &sql : statements)
    {
        if (!execSqlWithRetry(query, sql))
        {
            if (errorMessage)
                *errorMessage = "初始化门禁数据库失败：" + query.lastError().text();
            return false;
        }
    }


    // 兼容旧版本 staff_face.employee_no：补充 staff_id 并同步已有工号。
    bool hasStaffId = false;
    staffFaceHasLegacyEmployeeNo = false;
    if (!execSqlWithRetry(query, "pragma table_info(staff_face);"))
    {
        if (errorMessage)
            *errorMessage = "读取员工表结构失败：" + query.lastError().text();
        return false;
    }
    while (query.next())
    {
        const QString columnName = query.value(1).toString();
        hasStaffId = hasStaffId || columnName == "staff_id";
        staffFaceHasLegacyEmployeeNo = staffFaceHasLegacyEmployeeNo || columnName == "employee_no";
    }
    if (!hasStaffId)
    {
        if (!execSqlWithRetry(query, "alter table staff_face add column staff_id text;"))
        {
            if (errorMessage)
                *errorMessage = "升级员工表失败：" + query.lastError().text();
            return false;
        }
    }
    if (staffFaceHasLegacyEmployeeNo
        && !execSqlWithRetry(query, "update staff_face set staff_id=employee_no where staff_id is null or staff_id='';"))
    {
        if (errorMessage)
            *errorMessage = "同步员工工号失败：" + query.lastError().text();
        return false;
    }
    if (!execSqlWithRetry(query, "create unique index if not exists idx_staff_face_staff_id on staff_face(staff_id);"))
    {
        if (errorMessage)
            *errorMessage = "创建工号索引失败：" + query.lastError().text();
        return false;
    }

    // 旧 employees 表数据迁移到 staff_face；分别兼容新旧两种 staff_face 结构。
    const QString migrateSql = staffFaceHasLegacyEmployeeNo
        ? R"(
            insert or ignore into staff_face(
                employee_no, staff_id, name, department, position, phone,
                status, access_areas, face_feature
            )
            select employee_no, employee_no, name, department, position, phone,
                   '在职', '', face_feature from employees;
          )"
        : R"(
            insert or ignore into staff_face(
                staff_id, name, department, position, phone,
                status, access_areas, face_feature
            )
            select employee_no, name, department, position, phone,
                   '在职', '', face_feature from employees;
          )";
    if (!execSqlWithRetry(query, migrateSql))
    {
        if (errorMessage)
            *errorMessage = "迁移旧员工数据失败：" + query.lastError().text();
        return false;
    }
    return true;
}

bool MyDatabase::addEmployee(const EmployeeFaceRecord &employee, QString *errorMessage)
{
    QSqlQuery query(db);
    const QString insertSql = staffFaceHasLegacyEmployeeNo
        ? R"(
            insert into staff_face(employee_no, staff_id, name, department, position, phone,
                                   status, access_areas, face_feature)
            values(:staff_id, :staff_id, :name, :department, :position, :phone,
                   :status, :access_areas, :face_feature);
          )"
        : R"(
            insert into staff_face(staff_id, name, department, position, phone,
                                   status, access_areas, face_feature)
            values(:staff_id, :name, :department, :position, :phone,
                   :status, :access_areas, :face_feature);
          )";
    query.prepare(insertSql);
    query.bindValue(":staff_id", employee.employeeNo);
    query.bindValue(":name", employee.name);
    query.bindValue(":department", employee.department);
    query.bindValue(":position", employee.position);
    query.bindValue(":phone", employee.phone);
    query.bindValue(":status", employee.status.isEmpty() ? "在职" : employee.status);
    query.bindValue(":access_areas", employee.accessAreas.join(','));
    query.bindValue(":face_feature", employee.faceFeature);

    if (!query.exec())
    {
        const QString databaseError = query.lastError().text();
        if (errorMessage)
        {
            if (databaseError.contains("UNIQUE", Qt::CaseInsensitive))
                *errorMessage = "该工号已存在，请更换工号。";
            else
                *errorMessage = "保存员工失败：" + databaseError;
        }
        qDebug() << "insert employee error:" << databaseError;
        return false;
    }
    return true;
}

QList<EmployeeFaceRecord> MyDatabase::queryEmployees(const QString &department,
                                                     const QString &position,
                                                     const QString &status,
                                                     QString *errorMessage)
{
    QList<EmployeeFaceRecord> employees;
    QString sql = R"(
        select staff_id, name, department, position, phone,
               status, access_areas, face_feature
        from staff_face where 1=1
    )";
    if (!department.isEmpty())
        sql += " and department=:department";
    if (!position.isEmpty())
        sql += " and position=:position";
    if (!status.isEmpty())
        sql += " and status=:status";
    sql += " order by staff_id;";

    QSqlQuery query(db);
    query.prepare(sql);
    if (!department.isEmpty())
        query.bindValue(":department", department);
    if (!position.isEmpty())
        query.bindValue(":position", position);
    if (!status.isEmpty())
        query.bindValue(":status", status);
    if (!query.exec())
    {
        if (errorMessage)
            *errorMessage = "查询员工档案失败：" + query.lastError().text();
        return employees;
    }

    while (query.next())
    {
        EmployeeFaceRecord employee;
        employee.employeeNo = query.value(0).toString();
        employee.name = query.value(1).toString();
        employee.department = query.value(2).toString();
        employee.position = query.value(3).toString();
        employee.phone = query.value(4).toString();
        employee.status = query.value(5).toString();
        employee.accessAreas = query.value(6).toString().split(',', Qt::SkipEmptyParts);
        employee.faceFeature = query.value(7).toByteArray();
        employees.append(employee);
    }
    return employees;
}

bool MyDatabase::updateEmployee(const EmployeeFaceRecord &employee,
                                bool updateFaceFeature,
                                QString *errorMessage)
{
    QString sql = R"(
        update staff_face
        set name=:name, department=:department, position=:position,
            phone=:phone, access_areas=:access_areas, status=:status
    )";
    if (updateFaceFeature)
        sql += ", face_feature=:face_feature";
    sql += " where staff_id=:staff_id;";

    QSqlQuery query(db);
    query.prepare(sql);
    query.bindValue(":staff_id", employee.employeeNo);
    query.bindValue(":name", employee.name);
    query.bindValue(":department", employee.department);
    query.bindValue(":position", employee.position);
    query.bindValue(":phone", employee.phone);
    query.bindValue(":access_areas", employee.accessAreas.join(','));
    query.bindValue(":status", employee.status);
    if (updateFaceFeature)
        query.bindValue(":face_feature", employee.faceFeature);

    if (!query.exec() || query.numRowsAffected() != 1)
    {
        if (errorMessage)
            *errorMessage = "更新员工档案失败：" + query.lastError().text();
        return false;
    }
    return true;
}

bool MyDatabase::disableEmployee(const QString &staffId, QString *errorMessage)
{
    QSqlQuery query(db);
    query.prepare("update staff_face set status='离职' where staff_id=:staff_id;");
    query.bindValue(":staff_id", staffId);
    if (!query.exec() || query.numRowsAffected() != 1)
    {
        if (errorMessage)
            *errorMessage = "禁用员工失败：" + query.lastError().text();
        return false;
    }
    accessControlTablesReady = true;
    return true;
}

bool MyDatabase::deleteEmployee(const QString &staffId, QString *errorMessage)
{
    QSqlQuery query(db);
    query.prepare("delete from staff_face where staff_id=:staff_id;");
    query.bindValue(":staff_id", staffId);
    if (!query.exec() || query.numRowsAffected() != 1)
    {
        if (errorMessage)
            *errorMessage = "删除员工失败：" + query.lastError().text();
        return false;
    }
    // 通行日志作为历史审计记录保留，不随员工档案一起删除。
    return true;
}

QList<EmployeeFaceRecord> MyDatabase::queryEmployeeFaces(QString *errorMessage)
{
    QList<EmployeeFaceRecord> employees;
    QSqlQuery query(db);
    if (!query.exec(R"(
        select staff_id, name, department, position, phone,
               status, access_areas, face_feature
        from staff_face
        where status = '在职';
    )"))
    {
        const QString databaseError = query.lastError().text();
        if (errorMessage)
            *errorMessage = "读取员工人脸数据失败：" + databaseError;
        qDebug() << "select employee error:" << databaseError;
        return employees;
    }

    while (query.next())
    {
        EmployeeFaceRecord employee;
        employee.employeeNo = query.value(0).toString();
        employee.name = query.value(1).toString();
        employee.department = query.value(2).toString();
        employee.position = query.value(3).toString();
        employee.phone = query.value(4).toString();
        employee.status = query.value(5).toString();
        employee.accessAreas = query.value(6).toString().split(',', Qt::SkipEmptyParts);
        employee.faceFeature = query.value(7).toByteArray();
        employees.append(employee);
    }
    return employees;
}

double MyDatabase::faceMatchThreshold(QString *errorMessage)
{
    QSqlQuery query(db);
    query.prepare("select config_value from sys_config where config_key=:key;");
    query.bindValue(":key", "face_match_threshold");
    if (!query.exec())
    {
        if (errorMessage)
            *errorMessage = "读取人脸匹配阈值失败：" + query.lastError().text();
        return 0.363;
    }

    if (query.next())
    {
        bool ok = false;
        const double value = query.value(0).toDouble(&ok);
        if (ok && value >= 0.0 && value <= 1.0)
            return value;
    }
    return 0.363;
}

bool MyDatabase::addAccessLog(const AccessLogRecord &record, QString *errorMessage)
{
    QSqlQuery query(db);
    query.prepare(R"(
        insert into access_log(access_time, employee_no, name, department,
                               access_area, result)
        values(:access_time, :employee_no, :name, :department,
               :access_area, :result);
    )");
    query.bindValue(":access_time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"));
    query.bindValue(":employee_no", record.employeeNo);
    query.bindValue(":name", record.name);
    query.bindValue(":department", record.department);
    query.bindValue(":access_area", record.accessArea);
    query.bindValue(":result", record.result);

    if (!query.exec())
    {
        if (errorMessage)
            *errorMessage = "写入通行日志失败：" + query.lastError().text();
        qDebug() << "insert access log error:" << query.lastError().text();
        return false;
    }
    return true;
}





