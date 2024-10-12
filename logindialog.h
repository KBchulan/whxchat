/******************************************************************************
 *
 * @file       logindialog.h
 * @brief      登录界面
 *
 * @author     KBchulan
 * @date       2024/10/11
 * @history
 *****************************************************************************/
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog final: public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;

signals:
    // 选择注册按钮
    void SwitchRegister();

};

#endif // LOGINDIALOG_H
