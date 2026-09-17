#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class UserInfo
{
public:
    UserInfo(int id, QString name, QString passwd);

    int id() const;
    QString name() const;
    QString passwd() const;
private:
    int _id;
    QString _name;
    QString _passwd;
};

#endif // USERINFO_H
