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
class HttpManager final: public QObject, public Singleton<HttpManager>,
        std::enable_shared_from_this<HttpManager>
{
    Q_OBJECT
    friend class Singleton<HttpManager>;

public:
    virtual ~HttpManager();

private:
    HttpManager();

    // 发送数据,同步和异步，收取回调
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private slots:
    // 槽函数,参数不能超过信号参数数量
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

private:
    // 网络工作管理器
    QNetworkAccessManager manager;

signals:
    // 当http信号发送后提供一个信号给其他模块
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

    // 发送申请模块结束的信号
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMANAGER_H
