#ifndef CSERVER_H
#define CSERVER_H

#include "const.h"

class CServer final: public std::enable_shared_from_this<CServer>
{
public:
    explicit CServer(boost::asio::io_context &ioc, unsigned short &port);
    ~CServer() = default;

    // 服务器启动
    void Start();

private:
    tcp::socket _socket;
    net::io_context &_ioc;
    tcp::acceptor _acceptor;
};

#endif