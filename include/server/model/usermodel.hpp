#ifndef USERMODEL_H
#define USEMODEL_H

#include "user.hpp"

// User表的增加方法
class UserModel
{
public:
    bool insert(User& user);

    User query(int id);

    bool updateState(User user);
    // 重置用户的状态消息
    void resetState();
};

#endif