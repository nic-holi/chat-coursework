#ifndef FRIEND_INFO_H
#define FRIEND_INFO_H

#include <QDateTime>
#include <string>
#include <ctime>
using namespace std;

class Friend_Info
{
public:
    string      username;        // username
    string      headerPath;      // User random avatar
    bool        online;          // Whether online

    Friend_Info();
    Friend_Info(char* szusername, bool on);

    string getListItemMsg();

};

#endif // FRIEND_INFO_H
