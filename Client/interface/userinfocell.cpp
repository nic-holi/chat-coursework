#include "userinfocell.h"
#include "ui_userinfocell.h"

extern ClientInfo* myClient;
extern MainWindow* mainwindowPointer;

UserInfoCell::UserInfoCell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfoCell)
{
    ui->setupUi(this);
}

UserInfoCell::UserInfoCell(QWidget *parent, Friend_Info *user) :
    QWidget(parent),
    ui(new Ui::UserInfoCell)
{
    ui->setupUi(this);
    this->username = user->username;

    // username
    ui->user_username->setText(user->username.c_str());

    char name[MAX_USERNAME];
    strcpy(name, user->username.c_str());
    Peer_Info* peer = myClient->m_PeerList.GetAPeer(name);
    if(peer != NULL) {
        int nAddrNum =  peer->nAddrNum;
        in_addr LoginAddr;
        LoginAddr.S_un.S_addr = peer->IPAddr[nAddrNum].dwIP;
        string text = "Online IP " + string(::inet_ntoa(LoginAddr)) + " : " + QString::number(ntohs(peer->IPAddr[nAddrNum].usPort)).toStdString();
        ui->user_ip->setText(text.c_str());
    }
    else {
        string text = "Offline";
        ui->user_ip->setText(text.c_str());
    }

}

UserInfoCell::~UserInfoCell()
{
    delete ui;
}

// Click to delete friend
void UserInfoCell::on_user_deleteFriendButton_clicked()
{
    mainwindowPointer->deleteFriend(username);
}
