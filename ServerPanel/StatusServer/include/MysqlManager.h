#ifndef MYSQLMANAGER_H
#define MYSQLMANAGER_H

#include "const.h"
#include "MysqlDao.h"

class MysqlDao;
class MysqlManager final : public Singleton<MysqlManager>
{
    friend class Singleton<MysqlManager>;

public:
    ~MysqlManager();

    // 注册新用户
    int RegUser(const std::string &name, const std::string &email, const std::string &pwd);
    
    // 检查邮箱是否已被注册
    bool CheckEmail(const std::string &name, const std::string &email);
    
    // 更新用户密码
    bool UpdatePwd(const std::string &name, const std::string &newpassword);
    
    // 验证用户密码是否正确,并返回用户信息
    bool CheckPwd(const std::string &email, const std::string &pwd, UserInfo &userInfo);
    
    // 测试存储过程
    // bool TestProcedure(const std::string &email, int &uid, std::string &name);

private:
    MysqlManager();

private:
    MysqlDao _dao;
};

#endif // !MYSQLMANAGER_H