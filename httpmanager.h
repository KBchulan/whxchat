/******************************************************************************
 *
 * @file       httpmanager.h
 * @brief      XXXX Function
 *
 * @author     KBchulan
 * @date       2024/10/11
 * @history
 *****************************************************************************/
#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "singleton.h"

// CRTP:歧义递归模板
class HttpManager : public QObject, public Singleton<HttpManager>
{
    Q_OBJECT
    friend class Singleton<HttpManager>;
public:
    ~HttpManager();

private:
    QNetworkAccessManager manager;

private:
    HttpManager();

signals:
    // 当http信号发送后提供一个信号给其他模块
    void sig_http_finish();

};

#endif // HTTPMANAGER_H
