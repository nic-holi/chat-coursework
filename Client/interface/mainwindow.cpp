#include "mainwindow.h"
#include "ui_mainwindow.h"

extern ClientInfo* myClient;
extern queue<pair<string, string>> mailBox;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Chat");
    //No new message, hide message prompt
    ui->title_informButton->setVisible(false);

    // Connect sidebar buttons and slots
    QObject::connect(ui->roomAddressList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(roomAddressClick(QListWidgetItem*)));
    QObject::connect(ui->friendAddressList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(friendAddressClick(QListWidgetItem*)));
    // Connect title bar buttons and slots
    //QObject::connect(ui->title_exitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(ui->title_backwardButton, SIGNAL(clicked(bool)), this, SLOT(backward()));
    QObject::connect(ui->title_forwardButton, SIGNAL(clicked(bool)), this, SLOT(forward()));
    // Connect enter key and search function

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Successful login, initialize mainwindow
void MainWindow::receiveLogin() {
    this->show();
    interfaceInitial();
}

//Successful registration, initialize mainwindow
void MainWindow::receiveRegister() {
    this->show();
    interfaceInitial();
}

// initialization
void MainWindow::interfaceInitial() {
    // Set name
    ui->side_clientName->setText(QString::fromStdString(myClient->m_PeerInfo.szUserName));

    // Get friend list, initialize m_FriendList
    getFriendAddressList();

    // Get room list, initialize m_ChatList
    getRoomAddressList();

    // Modify status
    myClient->ProcCommand("getu");

    // Show friend AddressList and room AddressList sidebar
    showAddressList();
    ui->roomAddressList->hide();
    ui->friendAddressList->show();

}

// Get a new message
void MainWindow::receiveMessage(Chat_Info* room, char* username, char* message) {
    deque<QWidget*>::iterator i;
    int pos = 1;
    for(i=desk.begin();i!=desk.end();i++, pos++) {
       if((*i)->toolTip().toStdString() == room->roomId) {
           while(pos != 1) {
               backward();
               pos--;
           }
           ChatCell* temp = (ChatCell*)(*i);
           temp->showMessage(string(username), string(message));
           return;
       }
    }
    ChatCell* newChat = new ChatCell(ui->desk, room);
    newChat->showMessage(string(username), string(message));
    newPage(newChat);
}

// Get a new notification (add friend request or room creation request)
void MainWindow::receiveInform(string type, string message) {
    // Set up message alerts
    ui->title_informButton->setVisible(true);
    pair<string, string> newMail(type, message);
    mailBox.push(newMail);
}

// Click the message prompt in the title bar
void MainWindow::on_title_informButton_clicked()
{
    if(!mailBox.empty()) {
        pair<string, string> newMail = mailBox.front();
        mailBox.pop();

        InformCell* informcell = new InformCell(ui->desk, newMail);
        informcell->move((ui->desk->width() - informcell->width()) / 2,(ui->desk->height() - informcell->height()) / 2);
        informcell->show();
    }

    // If the mailBox is cleared, the message prompt will be hidden
    if(mailBox.empty()) {
        ui->title_informButton->setVisible(false);
    }
}

// Click the title bar settings button
void MainWindow::on_title_settingButton_clicked() {
    SettingCell* newpage = new SettingCell(ui->desk);
    newPage(newpage);
}

// Click on the sidebar to display the friendAddressList button
void MainWindow::on_friendButton_clicked() {
    ui->roomAddressList->hide();
    ui->friendAddressList->show();
}

// Click the sidebar to show roomAddressList button
void MainWindow::on_roomButton_clicked() {
    ui->roomAddressList->show();
    ui->friendAddressList->hide();
}

// Click the Add Friends button in the sidebar
void MainWindow::on_addFriendButton_clicked() {
    AddFriendCell* newpage = new AddFriendCell(ui->desk);
    newPage(newpage);
}

// Click the Add Room button in the sidebar
void MainWindow::on_addRoomButton_clicked() {
    // Modify friend status, reset addressList
    myClient->ProcCommand("getu");
    showAddressList();
    // Show add room page
    AddChatCell* newpage = new AddChatCell(ui->desk);
    newPage(newpage);
}


// Click user
void MainWindow::friendAddressClick(QListWidgetItem* item) {
    string key = item->toolTip().toStdString();
    UserInfoCell* userInfoCell = new UserInfoCell(ui->desk, myClient->m_FriendList[key]);
    newPage(userInfoCell);
}

// Click room
void MainWindow::roomAddressClick(QListWidgetItem* item) {
    string key = item->toolTip().toStdString();
    deque<QWidget*>::iterator i;
    int pos = 1;

    for(i=desk.begin();i!=desk.end();i++, pos++) {
       if((*i)->toolTip().toStdString() == key) {
           while(pos != 1) {
               backward();
               pos--;
           }
           return;
       }
    }

    ChatCell* chatCellTest = new ChatCell(ui->desk, myClient->m_ChatList[key]);
    newPage(chatCellTest);
}

// Refresh addresslist
void MainWindow::refreshAddressList()
{
    showAddressList();
}

// Show addressList
void MainWindow::showAddressList() {
    // Cancel scroll bar
    ui->friendAddressList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->roomAddressList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Empty
    ui->friendAddressList->clear();
    ui->roomAddressList->clear();

    // Buddy
    map<string, Friend_Info*>::iterator i;
    for(i=myClient->m_FriendList.begin();i!=myClient->m_FriendList.end();i++) {
        addIntoFriendAddressList(i->second, false);
    }

    // room
    map<string, Chat_Info*>::iterator j;
    for(j=myClient->m_ChatList.begin();j!=myClient->m_ChatList.end();j++) {
        addIntoRoomAddressList(j->second, false);
    }
}

// Add a friend item to the sidebar
void MainWindow::addIntoFriendAddressList(Friend_Info* user, bool fouce) {
    addressListItem* newFriend = new addressListItem(0, user);

    QListWidgetItem* newitem = new QListWidgetItem(ui->friendAddressList);
    newitem->setToolTip(user->username.c_str());      // tooltip is id
    ui->friendAddressList->addItem(newitem);
    ui->friendAddressList->setItemWidget(newitem, newFriend);
    newitem->setSizeHint(QSize(0, 60));

    // Display friendAddressList and focus on the newly added item
    if(fouce) {
        ui->friendButton->click();
        ui->friendAddressList->setCurrentItem(newitem);
    }
}

// Add a room item to the sidebar
void MainWindow::addIntoRoomAddressList(Chat_Info* room, bool fouce) {
    addressListItem* newRoom = new addressListItem(0, room);

    QListWidgetItem* newitem = new QListWidgetItem(ui->roomAddressList);
    newitem->setToolTip(room->roomId.c_str());      // tooltip为id
    ui->roomAddressList->addItem(newitem);
    ui->roomAddressList->setItemWidget(newitem, newRoom);
    newitem->setSizeHint(QSize(0, 60));

    // Display roomAddressList and focus on the newly added item
    if(fouce) {
        ui->roomButton->click();
        ui->roomAddressList->setCurrentItem(newitem);
    }
}

// add friend
void MainWindow::addFriend(Friend_Info* user) {
    addIntoFriendAddressList(user, true);
    addFriendRecordFile(user);
}

// delete friend
void MainWindow::deleteFriend(string username) {
    // Find the user's serial number in friendList
    map<string, Friend_Info*>::iterator i;
    int row = 0;
    for(i=myClient->m_FriendList.begin();i!=myClient->m_FriendList.end();i++, row++) {
        if(i->second->username == username) {
            break;
        }
    }
    // Remove from sidebar
    QListWidgetItem* item = ui->friendAddressList->item(row);
    ui->friendAddressList->removeItemWidget(item);
    //Remove from friendList
    myClient->m_FriendList.erase(username);
    //Delete from file system
    deleteFriendRecordFile(username);

    // Refresh addressList
    showAddressList();
    // Delete current page
    deleteCurrentPage();
}

// Add room
void MainWindow::addRoom(Chat_Info* room)
{
    addIntoRoomAddressList(room, true);
    addRoomRecordFile(room);
}

// Delete room
void MainWindow::deleteRoom(string roomid) {
    //Find the serial number of the room in chatList
    map<string, Chat_Info*>::iterator i;
    int row = 0;
    for(i=myClient->m_ChatList.begin();i!=myClient->m_ChatList.end();i++, row++) {
        if(i->second->roomId == roomid) {
            break;
        }
    }
    // Remove from sidebar
    QListWidgetItem* item = ui->roomAddressList->item(row);
    ui->roomAddressList->removeItemWidget(item);
    // Remove from roomList
    myClient->m_ChatList.erase(roomid);
    // Delete from file system
    deleteRoomRecordFile(roomid);

    // Refresh addressList
    showAddressList();
    // Delete current page
    deleteCurrentPage();
}

// Newly added page
void MainWindow::newPage(QWidget *newpage) {
    if(!desk.empty()) {
        QWidget* lastpage = desk.front();
        lastpage->hide();
    }
    newpage->show();
    desk.push_front(newpage);

    //too much widget
    if(desk.size() > 10) {
        desk.pop_back();
    }
}

// Previous page
void MainWindow::forward() {
    QWidget* lastpage = desk.front();
    lastpage->hide();
    QWidget* newpage = desk.back();
    desk.pop_back();
    newpage->show();
    desk.push_front(newpage);
}

// Go back one page
void MainWindow::backward() {
    QWidget* lastpage = desk.front();
    desk.pop_front();
    lastpage->hide();
    desk.push_back(lastpage);
    QWidget* newpage = desk.front();
    newpage->show();
}

// Go back and delete the current page
void MainWindow::deleteCurrentPage() {
    QWidget* lastpage = desk.front();
    desk.pop_front();
    lastpage->hide();
    QWidget* newpage = desk.front();
    newpage->show();
}




void MainWindow::on_friendAddressList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

}
