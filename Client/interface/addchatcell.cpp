#include "addchatcell.h"
#include "ui_addchatcell.h"

extern ClientInfo* myClient;

AddChatCell::AddChatCell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddChatCell)
{
    ui->setupUi(this);
    // close the scroll bar
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Add layout and buttongroup
    buttongroup = new QButtonGroup(ui->addC_friendList);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(10);
    buttongroup->setExclusive(false);   // Set multiple choice

    // Set up checkbox for each online friend, set tooltip to id
    map<string, Friend_Info*>::iterator i;
    int j = 0;
    for(i=myClient->m_FriendList.begin();i!=myClient->m_FriendList.end();i++, j++) {
        Friend_Info* user = i->second;
        QCheckBox* checkbox = new QCheckBox(QString::fromStdString(user->username), ui->addC_friendList);
        checkbox->setToolTip(QString::fromStdString(user->username));
        checkbox->setFont(QFont(QString::fromStdString("Isometric"), 10, -1, false));
        checkbox->setStyleSheet("background: rgba(0,0,0,0); color: white; height: 12px;");
        layout->addWidget(checkbox);
        buttongroup->addButton(checkbox, j);
    }
    ui->addC_friendList->setLayout(layout);
}

AddChatCell::~AddChatCell()
{
    delete ui;
}

// Click the confirm button
void AddChatCell::on_addC_addButton_clicked()
{
    string command = "room ";
    string namelist = "";
    int roomSize = 0;
    QList<QAbstractButton*> buttonlist = buttongroup->buttons();
    foreach (QAbstractButton *pCheckBox, buttonlist) {
        if(pCheckBox->isChecked()) {
            namelist = namelist + " " + pCheckBox->toolTip().toStdString();
            roomSize++;
        }
    }
    command = command + QString::number(roomSize).toStdString() + namelist;
    myClient->ProcCommand(command);
}





