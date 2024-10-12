/******************************************************************************
 *
 * @file       registerdialog.h
 * @brief      注册界面
 *
 * @author     KBchulan
 * @date       2024/10/11
 * @history
 *****************************************************************************/
#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "global.h"

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog final: public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    // 获取验证码按钮点击
    void on_code_btn_clicked();

    // 注册模块结束槽函数
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);

private:
    // 设置http处理器
    void initHttpHandles();

    // 展示错误信息
    void showTip(QString str,bool ok);

private:
    Ui::RegisterDialog *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers;
};

#endif // REGISTERDIALOG_H
