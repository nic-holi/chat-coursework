#include "settingcell.h"
#include "ui_settingcell.h"

extern ClientInfo* myClient;

SettingCell::SettingCell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingCell)
{
    ui->setupUi(this);

    // username
    ui->setting_username->setText(myClient->m_PeerInfo.szUserName);

    // password
    ui->setting_password->setText(myClient->password.c_str());

    // ip address
    int nAddrNum =  myClient->m_PeerInfo.nAddrNum;
    in_addr LoginAddr;
    LoginAddr.S_un.S_addr = myClient->m_PeerInfo.IPAddr[nAddrNum].dwIP;
    string text = "IP " + string(::inet_ntoa(LoginAddr)) + " : " + QString::number(ntohs(myClient->m_PeerInfo.IPAddr[nAddrNum].usPort)).toStdString();
    ui->setting_ip->setText(text.c_str());

}

SettingCell::~SettingCell()
{
    delete ui;
}


void SettingCell::on_setting_save_clicked()
{

}


void SettingCell::on_setting_disappear_clicked()
{

}


void SettingCell::on_setting_clean_clicked()
{
    uninstall();
}
