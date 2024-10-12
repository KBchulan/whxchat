#ifndef LOGIC_SYSTEM_H
#define LOGIC_SYSTEM_H

#include "const.h"

class HttpConnection;

typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;

class LogicSystem final: public Singleton<LogicSystem>
{
    friend class Singleton<LogicSystem>;

public:
    ~LogicSystem() {}

    // 处理get请求
    bool HandleGet(std::string, std::shared_ptr<HttpConnection>);

    // 注册get请求
    void RegGet(std::string, HttpHandler handler);

private:
    LogicSystem();

    std::map<std::string, HttpHandler> _post_handlers;
    std::map<std::string, HttpHandler> _get_handlers;
};



#endif // LOGIC_SYSTEM_H