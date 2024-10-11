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
#include <QJsonArray>
#include <QJsonDocument>
#include <QRegularExpression>
#include <QNetworkAccessManager>

// C++
#include <mutex>
#include <memory>
#include <iostream>
#include <functional>

// 用来刷新qss属性
extern std::function<void(QWidget*)> repolish;


#endif // GLOBAL_H
