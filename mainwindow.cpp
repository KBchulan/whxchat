#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ico设置
    setWindowIcon(QIcon(":/icons/begin.ico"));

    // 登陆页面
    login_diolog = new LoginDialog(this);
    setCentralWidget(login_diolog);

    // 创建和注册信号新连接
    connect(login_diolog, &LoginDialog::SwitchRegister, this, &MainWindow::SlotSwitchReg);

    // 注册界面
    register_dialog = new RegisterDialog(this);

    // 设置Dialog窗口属性
    login_diolog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    register_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    // 初始为登陆界面
    register_dialog->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(register_dialog);
    login_diolog->hide();
    register_dialog->show();
}

