#include "system.h"
using namespace std;

extern ClientInfo* myClient;

void uninstall() {
    qDebug("uninstall, unfinished");
}

bool deleteFriendRecordFile(string username) {
    return true;
}

bool deleteRoomRecordFile(string roomId) {
    return true;
}

bool addFriendRecordFile(Friend_Info* user) {
    return true;
}

bool addRoomRecordFile(Chat_Info* room) {
    return true;
}

bool getFriendAddressList() {
    myClient->m_FriendList.clear();

    myClient->m_FriendList["Bobi"] = new Friend_Info("Bobi", false);
    myClient->m_FriendList["Maria"] = new Friend_Info("Maria", false);
    myClient->m_FriendList["Fedor"] = new Friend_Info("Fedor", false);
    myClient->m_FriendList["Bruice"] = new Friend_Info("Bruice", false);
    myClient->m_FriendList["Sia"] = new Friend_Info("Sia", false);
    myClient->m_FriendList["Andrew"] = new Friend_Info("Andrew", false);
    myClient->m_FriendList["Heros"] = new Friend_Info("Heros", false);
    myClient->m_FriendList["Diana"] = new Friend_Info("Diana", false);
    myClient->m_FriendList["Cap"] = new Friend_Info("Cap", false);
    myClient->m_FriendList["Bucky"] = new Friend_Info("Bucky", false);

    return true;
}

bool getRoomAddressList() {
    myClient->m_ChatList.clear();

    set<char*> roommates;
    roommates.insert("Bobi");
    roommates.insert("Grayson");
    roommates.insert("Bucky");
    myClient->m_ChatList["8483"] = new Chat_Info("8483", "Bobi", roommates, 3, 'F', QDateTime::fromString("2020/04/21 11:15:30", "yyyy/mm/dd hh:mm:ss"));

    roommates.clear();
    roommates.insert("Maria");
    roommates.insert("Grayson");
    roommates.insert("Cap");
    myClient->m_ChatList["8586"] = new Chat_Info("8586", "Grayson", roommates, 3, 'F', QDateTime::fromString("2017/12/23 09:07:30", "yyyy/mm/dd hh:mm:ss"));

    return true;
}

void static EraseNewLine(char szChar[])
{
    for (int i = 0; i < strlen(szChar); ++i)
    {
        if (szChar[i] == '\n')
        {
            szChar[i] = '\0';
            break;
        }
    }
}

string getInputElement(string szCommandLine, int& pos, char end)
{
    string element = "";
    for (int i = pos; i < pos + MAX_USERNAME; ++i) {
        char c = szCommandLine[i];
        if (end != c) {
            char temp[2];
            temp[0] = c;
            temp[1] = '\0';
            element = element + string(temp);
        }
        else {
            pos = i;
            return element;
        }
    }
}

bool myPrintf(char* form,... )
{
    va_list args;
    va_start(args,form);

    string sform = string(form);

    int start = 0;
    int end = sform.find("%", start);
    while (end != string::npos) {
        string temp = sform.substr(start, end - start - 1);


        end++;
        if(form[end] == 's') {
            char* tmp = va_arg(args,char*);

        }
        else if(form[end] == 'd') {
            int tmp = va_arg(args,int);

        }

        start = end + 1;
        end = sform.find("%", start);
    }
    va_end(args);
    return true;
}
