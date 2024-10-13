#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H

#include "const.h"

class HttpConnection final : public std::enable_shared_from_this<HttpConnection>
{
    friend class LogicSystem;

public:
    explicit HttpConnection(tcp::socket socket);
    ~HttpConnection() = default;

    // 启动服务用于监听读写事件
    void Start();

private:
    // 检测是否超时（发完数据后启动一个定时器，若是超时则返回）
    void CheckDeadLine();

    // 受到数据后，在三次握手，四次挥手后发出回包
    void WriteResponse();

    // 处理请求，解析请求和包内容
    void HandleReq();

    // 解析url,即取出pair对象
    void PreParseGetParam();

private:
    tcp::socket _socket;
    beast::flat_buffer _buffer{8192};
    http::request<http::dynamic_body> _request;
    http::response<http::dynamic_body> _response;

    net::steady_timer deadline_
    {
        _socket.get_executor(),
        std::chrono::seconds(60)
    };
        
    std::string _get_url;
    std::unordered_map<std::string, std::string> _get_params;
};

#endif // HTTP_CONNECTION_H