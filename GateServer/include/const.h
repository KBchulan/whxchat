#ifndef CONST_H
#define CONST_H

// boost
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

// C++
#include <map>
#include <memory>
#include <iostream>
#include <functional>
#include <unordered_map>

// personal
#include "singleton.h"

// jsoncpp
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>

// 简化一些常用的命名空间
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

// 错误码
enum class ErrorCodes
{
    Success = 0,
    Error_Json = 1001,      // json
    RPCFailed = 1002,       // 远程过程调用，即调用远程服务的函数
};

#endif // CONST_H