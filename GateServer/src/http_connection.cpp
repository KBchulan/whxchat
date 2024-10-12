#include "../include/logic_system.h"
#include "../include/http_connection.h"

HttpConnection::HttpConnection(tcp::socket socket) : _socket(std::move(socket))
{
}

void HttpConnection::Start()
{
    auto self = shared_from_this();

    http::async_read(_socket, _buffer, _request, [self](boost::beast::error_code ec, std::size_t bytes_transferred)
    {
        try
        {
            if (ec)
            {
                std::cout << "https read error is" << ec.message() << std::endl;
            }
            boost::ignore_unused(bytes_transferred);
            self->HandleReq();
            self->CheckDeadLine();
        }
        catch (std::exception &exp)
        {
            std::cout << "expection is" << exp.what() << std::endl;
        } 
    });
}

void HttpConnection::CheckDeadLine()
{
    auto self = shared_from_this();
    deadline_.async_wait([self](beast::error_code ec){
        if(!ec)
        {
            self->_socket.close(ec);
        }
    });
}

void HttpConnection::WriteResponse()
{
    auto self = shared_from_this();
    _response.content_length(_response.body().size());
    
    http::async_write(_socket, _response, [self](beast::error_code ec, std::size_t bytes_transferred)
    {
        self->_socket.shutdown(tcp::socket::shutdown_send, ec);
        self->deadline_.cancel();
    });
}

void HttpConnection::HandleReq()
{
    // 设置版本
    _response.version(_request.version());
    _response.keep_alive(false);
    if (_request.method() == http::verb::get)
    {
        bool success = LogicSystem::GetInstance()->HandleGet(std::string(_request.target()), shared_from_this());
        if (!success)
        {
            _response.result(http::status::not_found);
            _response.set(http::field::content_type, "text/plain");
            beast::ostream(_response.body()) << "url not found\r\n";
            WriteResponse();
            return;
        }
        _response.result(http::status::ok);
        _response.set(http::field::server, "GateServer");
        WriteResponse();
        return;
    }
}