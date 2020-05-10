#include "chatcell.h"
#include "ui_chatcell.h"

extern ClientInfo* myClient;

ChatCell::ChatCell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatCell)
{
    ui->setupUi(this);
}

ChatCell::ChatCell(QWidget *parent, Chat_Info *room) :
    QWidget(parent),
    ui(new Ui::ChatCell)
{
    ui->setupUi(this);
    this->roomId = room->roomId;
    this->setToolTip(QString::fromStdString(roomId));

    // Room name
    ui->chat_object->setText(room->getName().c_str());



}

ChatCell::~ChatCell()
{
    delete ui;
}

// Show a chat history
void ChatCell::showMessage(string username, string message) {
    QDateTime datetime = QDateTime::currentDateTime();
    ui->recordList->insertPlainText(QString::fromStdString(username)
                                    + " "
                                    + datetime.toString("yyyy-MM-dd hh:mm:ss")
                                    + "\n"
                                    + QString::fromStdString(message)
                                    + QString::fromStdString("\n\n"));
    ui->recordList->moveCursor(QTextCursor::End);
}

// Click the send button
void ChatCell::on_chat_sendButton_clicked()
{
    string message = ui->chat_messageInput->toPlainText().toStdString();
    if(message == "") {
        return;
    }
    myClient->ProcCommand("chat " + roomId + " " + message);
    ui->chat_messageInput->clear();
}

void ChatCell::on_chat_breakButton_clicked()
{

}

void ChatCell::on_chat_refreshButton_clicked()
{
    if(myClient->m_ChatList[roomId]->online == true) {
        ui->chat_information->insertPlainText("The room is already active");
        return;
    }

    // If it is a silent room record, rebuild as a Parent
    string command = "wake ";
    string namelist = " ";
    map<string, char>::iterator i;

    command = command + ("" + myClient->m_ChatList[roomId]->roomSize) + namelist;

    myClient->ProcCommand(command);
}

void ChatCell::on_chat_exitButton_clicked()
{

}

void ChatCell::on_chat_enterButton_clicked()
{
}

void ChatCell::on_chat_information_anchorClicked(const QUrl &arg1)
{

}
