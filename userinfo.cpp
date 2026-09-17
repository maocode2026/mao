#include "userinfo.h"

UserInfo::UserInfo(int id, QString name, QString passwd) : _id(id), _name(name), _passwd(passwd){}

int UserInfo::id() const
{
    return _id;
}

QString UserInfo::name() const
{
    return _name;
}

QString UserInfo::passwd() const
{
    return _passwd;
}
