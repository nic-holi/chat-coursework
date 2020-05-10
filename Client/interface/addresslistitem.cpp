#include "addresslistitem.h"
#include "ui_addresslistitem.h"
#include <QPixmap>
using namespace std;

extern ClientInfo* myClient;

addressListItem::addressListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addressListItem)
{
    ui->setupUi(this);
}

addressListItem::addressListItem(QWidget *parent, Friend_Info* user) :
    QWidget(parent),
    ui(new Ui::addressListItem)
{
    ui->setupUi(this);
    // username
    ui->add_username->setText(user->username.c_str());
    // 头像
     user->headerPath = "./headers/man.png";
    QPixmap header("./images/headers/11.png");
    ui->add_header->setPixmap(header);
  //  ui->add_header->setScaledContents(true);
    //status
    char name[MAX_USERNAME];
    strcpy(name, user->username.c_str());
    Peer_Info* peer = myClient->m_PeerList.GetAPeer(name);
    if(peer != NULL) {
        int nAddrNum =  peer->nAddrNum;
        in_addr LoginAddr;
        LoginAddr.S_un.S_addr = peer->IPAddr[nAddrNum].dwIP;
        string text = "Online";// + string(::inet_ntoa(LoginAddr)) + " : " + QString::number(ntohs(peer->IPAddr[nAddrNum].usPort)).toStdString();
        ui->add_statue->setText(text.c_str());
    }
    else {
        string text = "Offline";
        ui->add_statue->setText(text.c_str());
    }
}

addressListItem::addressListItem(QWidget *parent, Chat_Info* room) :
    QWidget(parent),
    ui(new Ui::addressListItem)
{
    ui->setupUi(this);
    // Room name
    ui->add_username->setText(room->getName().c_str());
    //Avatar
    QPixmap header(room->headerPath.c_str());
    ui->add_header_2->setPixmap(header);
    ui->add_header->setScaledContents(true);
    // status
    ui->add_statue->setText(room->getListItemMsg().c_str());
}

addressListItem::~addressListItem()
{
    delete ui;
}
