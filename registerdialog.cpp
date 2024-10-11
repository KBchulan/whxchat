#include "global.h"
#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    // 设置密码输入为密码模式
    ui->pass_regis_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);

    // 设置信息正确与否状态
    ui->error_tip->setProperty("state","normal");
    repolish(ui->error_tip);

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_code_btn_clicked()
{
    auto email = ui->email_edit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(match){
        // 发送验证码
    }
    else{
        showTip(tr("邮箱地址不正确"), false);
    }
}

void RegisterDialog::showTip(QString str, bool ok)
{
    if(ok){
        ui->error_tip->setProperty("state","normal");
    }
    else{
        ui->error_tip->setProperty("state","err");
    }
    ui->error_tip->setText(str);
    repolish(ui->error_tip);
}
