#include "../include/cserver.h"
#include "../include/http_connection.h"

CServer::CServer(boost::asio::io_context &ioc, unsigned short &port) : _ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(ioc)
{
}

void CServer::Start()
{
    auto self = shared_from_this();
    _acceptor.async_accept(_socket, [self](beast::error_code ec)
    {
        try
        {
            // 出错就放弃此socket连接，继续监听其他链接
            if (ec)
            {
                self->Start();
                return;
            }

            // 创建新链接，同时创建HttpConnection管理这个链接
            std::make_shared<HttpConnection>(std::move(self->_socket))->Start();

            // 继续监听
            self->Start();
        }
        catch (const std::exception &exp)
        {
        } 
    });
}