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

// singleton
#include "singleton.h"

// 简化一些常用的命名空间
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

#endif // CONST_H