/******************************************************************************
 *
 * @file       mainwindow.h
 * @brief      主窗口
 *
 * @author     KBchulan
 * @date       2024/10/11
 * @history
 *****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"
#include "registerdialog.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void SlotSwitchReg();

private:
    Ui::MainWindow *ui;
    LoginDialog* login_diolog;
    RegisterDialog* register_dialog;
};
#endif // MAINWINDOW_H
