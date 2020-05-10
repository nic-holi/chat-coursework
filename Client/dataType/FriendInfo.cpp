#include "FriendInfo.h"

//extern ClientInfo* myClient;
int randSeed = 1;

Friend_Info::Friend_Info()
{
    headerPath = "./images/headers/man.png";
}


Friend_Info::Friend_Info(char* szusername, bool on)
{
    username = string(szusername);
    online = on;

    srand((int)time(0) + randSeed);
    randSeed++;
    int hnum = rand()%12;
    headerPath = "./headers/" + QString::number(hnum).toStdString() + ".png";
    //headerPath = "./images/headers/man.png";
}

string Friend_Info::getListItemMsg()
{
    string msg;

    if(online) {
        msg = "Online";
           }
    else {
        msg = "Offline";
    }
    return msg;
}
