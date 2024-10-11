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
    void on_code_btn_clicked();

private:
    void showTip(QString str,bool ok);
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
