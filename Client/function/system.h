#ifndef SYSTEM_H
#define SYSTEM_H

#include <qdebug.h>
#include <QFile>
#include <QDataStream>
#include <QTextCodec>
#include <stdio.h>
#include "stdlib.h"
#include <stdarg.h>
#include "dataType/ChatInfo.h"
#include "dataType/FriendInfo.h"
#include "dataType/ClientInfo.h"
using namespace std;

void uninstall();   // Eliminate traces

bool deleteRoomRecordFile(string roomId);       //File processing, delete room records
bool deleteFriendRecordFile(string username);     //Delete friend record
bool addRoomRecordFile(Chat_Info* room);         // Add room record
bool addFriendRecordFile(Friend_Info* user);       // Add friend record

bool getFriendAddressList();          //Get the list of friends in the file
bool getRoomAddressList();            // Get room list

string getInputElement(string szCommandLine, int& pos, char end);

bool myPrintf(char* form,... );
#endif // SYSTEM_H
