#include "connectioncs.h"
using namespace std;

extern ClientInfo* myClient;
extern QTextBrowser* infoShell;

//Log in and reply if the log interface can jump
string conn_login(string userId, string password) {
    // Contact the server
    char username[MAX_USERNAME];
    strcpy(username, userId.c_str());
    if(false == myClient->Login(username, "192.168.56.1")) {
        return "Login false!";
    }
    return "pass";
}

// Register, reply to reg interface
string conn_register(string userId, string password) {
    char username[MAX_USERNAME];
    strcpy(username, userId.c_str());
    if(false == myClient->Login(username, "192.168.56.1")) {
        return "Login false!";
    }
    return "pass";
}
