#include "logindialog.h"
#include "httpmanager.h"
#include "ui_logindialog.h"

#include <QDebug>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // 注册按钮
    connect(ui->reg_btn, &QPushButton::clicked, this, &LoginDialog::switchRegister);

    // 忘记密码的样式
    ui->forget_label->SetState("normal", "hover", "hover", "selected", "selected_hover", "selected_hover");

    // 跳转到reset界面
    connect(ui->forget_label, &ClickedLabel::sig_clicked, this, &LoginDialog::slot_forget_pwd);

    // 设置头像
    initHead();

    // 初始化httphandler
    initHttpHandlers();

    // 连接登录回包的信号
    connect(HttpManager::GetInstance().get(), &HttpManager::sig_login_mod_finish, this,
            &LoginDialog::slot_login_mod_finish);
}

LoginDialog::~LoginDialog()
{
    qDebug() << "login destruce";
    delete ui;
}

void LoginDialog::initHead()
{
    QPixmap pixmap(":/resources/Login/3.jpg");

    // 纵横比缩放
    pixmap = pixmap.scaled(ui->head_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 空白透明的pixmap作为画布
    QSize targetSize = ui->head_label->size();
    QPixmap rounded(targetSize);
    rounded.fill(Qt::transparent);

    // 创建画家，抗锯齿
    QPainter painter(&rounded);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置圆角矩形路径
    QPainterPath path;
    std::uint32_t radius = 20;
    path.addRoundedRect(0, 0, targetSize.width(), targetSize.height(), radius, radius);

    // 裁减路径
    painter.setClipPath(path);

    // 绘制图片
    painter.drawPixmap(125, 0, pixmap);

    ui->head_label->setPixmap(rounded);

//    // 图片一圈阴影
//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//    shadow->setBlurRadius(15);
//    shadow->setColor(QColor(0, 0, 0, 80));
//    shadow->setOffset(0, 0);
//    ui->head_label->setGraphicsEffect(shadow);
}

void LoginDialog::showTip(QString str, bool b_ok)
{
    if(b_ok)
    {
        ui->err_tip->setProperty("state", "normal");
    }
    else
    {
        ui->err_tip->setProperty("state", "err");
    }
    ui->err_tip->setText(str);
    repolish(ui->err_tip);
}

void LoginDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void LoginDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty())
    {
        ui->err_tip->clear();
        return;
    }
    showTip(_tip_errs.first(), false);
}

bool LoginDialog::enableBtn(bool enabled)
{
    ui->login_btn->setEnabled(enabled);
    ui->reg_btn->setEnabled(enabled);
    return true;
}

void LoginDialog::initHttpHandlers()
{
    _handlers.insert(ReqId::ID_LOGIN_USER, [this](QJsonObject jsonObj)
    {
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS)
        {
            showTip("参数错误", false);
            enableBtn(true);
            return;
        }

        auto email = jsonObj["email"].toString();

        ServerInfo si;
        si.Uid = jsonObj["uid"].toInt();
        si.Host = jsonObj["host"].toString();
        si.Port = jsonObj["port"].toString();
        si.Token = jsonObj["token"].toString();

        _uid = si.Uid;
        _token = si.Token;

        qDebug() << "email: " << email << " uid: " << si.Uid << " token: " << si.Token;

        emit sig_connect_tcp(si);
    });
}

bool LoginDialog::checkUserValid()
{
    auto email = ui->email_edit->text();

    // （nums + letters + specials) + '@' + （nums + letters + specials) + '.' + (at least two letter)
    QRegularExpression regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    bool match = regex.match(email).hasMatch();

    if(!match)
    {
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址不正确"));
        return false;
    }

    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool LoginDialog::checkPwdVaild()
{
    auto password = ui->pass_edit->text();

    // 先检测长度
    if(password.length() < 6 || password.length() > 15)
    {
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度不准确,应在6~15位"));
        return false;
    }

    QRegularExpression regex("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d)[A-Za-z\\d!@#$%^&*()_+\\-=\\[\\]{};':\"\\\\|,.<>\\/?]{6,15}$");
    bool match = regex.match(password).hasMatch();

    if(!match)
    {
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码必须包含大小写字母和数字"));
        return false;
    }

    DelTipErr(TipErr::TIP_PWD_ERR);
    return true;
}

void LoginDialog::slot_forget_pwd()
{
    emit switchReset();
}

void LoginDialog::on_login_btn_clicked()
{
    if(!checkUserValid())
        return;

    if(!checkPwdVaild())
        return;

    enableBtn(false);
    auto email = ui->email_edit->text();
    auto passwd = ui->pass_edit->text();

    QJsonObject json_obj;
    json_obj["email"] = email;
    json_obj["passwd"] = xorString(passwd);
    HttpManager::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/user_login"),
                                            json_obj, ReqId::ID_LOGIN_USER, Modules::LOGINMOD);
}

void LoginDialog::slot_login_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS)
    {
        showTip(tr("网络请求错误"), false);
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());

    if(jsonDoc.isNull())
    {
        showTip(tr("json解析错误"), false);
        return;
    }

    _handlers[id](jsonDoc.object());
    return;
}
