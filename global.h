/******************************************************************************
 *
 * @file       global.h
 * @brief      所有的库文件及一些函数
 *
 * @author     KBchulan
 * @date       2024/10/11
 * @history
 *****************************************************************************/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "QStyle"

// Qt
#include <QUrl>
#include <QWidget>
#include <QString>
#include <QObject>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QNetworkAccessManager>

// C++
#include <mutex>
#include <memory>
#include <iostream>
#include <functional>

// 用来刷新qss属性
extern std::function<void(QWidget*)> repolish;

// 请求种类
enum class ReqId
{
    ID_GET_VARIFY_CODE = 1001,      // 获取验证码
    ID_REGISTER_USER = 1002,        // 注册用户
};

// 功能模块
enum class Modules
{
    REGISTERMOD = 0,         // 注册模块
};

enum class ErrorCodes
{
    SUCCESS = 0,
    ERR_JSON = 1,           // json解析失败
    ERR_NETWORK = 2,        // 网络错误
};

#endif // GLOBAL_H
