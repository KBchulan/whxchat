#include "global.h"
#include "httpmanager.h"
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

    // 注册逻辑
    connect(HttpManager::GetInstance().get(), &HttpManager::sig_reg_mod_finish,
            this, &RegisterDialog::slot_reg_mod_finish);

    // http处理器初始化
    initHttpHandles();
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

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS)
    {
        showTip(tr("网络请求错误"), false);
        return;
    }

    // 解析json字符串, res转化为QBytyeArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull())
    {
        showTip(tr("json解析失败"), false);
        return;
    }
    // json解析错误
    if(!jsonDoc.isObject())
    {
        showTip(tr("json解析错误"), false);
        return;
    }

    // 成功
    jsonDoc.object();
    handlers[id](jsonDoc.object());
    return;
}

void RegisterDialog::initHttpHandles()
{
    // 注册获取验证码回包的逻辑
    handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != (int)ErrorCodes::SUCCESS){
            showTip(tr("参数错误"), false);
            return;
        }

        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送，请注意查收"), true);
        qDebug() << "email is:" << email;
    });
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
