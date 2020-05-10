#ifndef __P2P_CLIENT_H__
#define __P2P_CLIENT_H__

#include <WinSock2.h>
#include <list>
#include <QObject>
#include "CommonDefine.h"
#include "ChatInfo.h"
#include "FriendInfo.h"
#include "function/system.h"
using namespace std;

class ClientInfo : public QObject
{
    Q_OBJECT

public:
    // initialization
    ClientInfo();
    ~ClientInfo();
    bool Initialize();
    static DWORD WINAPI RecvThreadProc(LPVOID lpParam);
    bool ProcCommand(string command);


    bool UDP_breakHold(char* pszUserName, Peer_Info* pPeerInfo);
    bool ProcP2PConnectMsg(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);
    bool ProcP2PConnectAckMsg(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);

    // Login
    bool Login(char *pszUserName, char *pszServerIP);
    bool Logout();
    bool ProcUserLogAckMsg(MSGDef::TMSG_HEADER *pMsgHeader);
    bool ProcUserActiveQueryMsg(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);

    // Get peerInfo
    bool GetUserList();
    bool ProcGetUserList(MSGDef::TMSG_HEADER *pMsgHeader);
    bool ProcUserListCmpMsg();

    // 
    bool SendNewFriendAsk(char *pszUserName);
    bool SendNewFriendReply(bool answer, char *pszUserName);
    bool ProNewFriendAsk(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);
    bool ProNewFriendReply(bool answer, MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);

    // Add room
    bool SetUpARoom(char szRoommate[MAX_ROOMMATE][MAX_USERNAME], int roomSize);
    char* SendNewRoomIdApply();
    bool SendNewRoomAsk(char *pszUserName, char *roomId);
    bool SendNewRoomReply(bool answer, char *pszUserName, char *roomId);
    bool SetNameList(char* roomId);
    bool SendNameList(char *pszUserName, MSGDef::TMSG_NEWROOMNAMELIST *tNameList);
    bool SetChatStart(char* roomId);
    bool SendChatStart(char *pszUserName, MSGDef::TMSG_CHATSTARTALERT *tChatStart);
    bool ProNewRoomIdReply(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);
    bool ProNewRoomAsk(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);
    bool ProNewRoomReply(bool answer, MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);
    bool ProNamelist(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);
    bool ProStartChat(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);

    // Send a message
    bool SetSendText(char *roomid, char *pszText, int nTextLen);
    bool SendText(char *pszUserName, MSGDef::TMSG_P2PMSG *msg);
    bool ProcP2PMsg(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);

    // Manage the room
    static DWORD WINAPI ManageRoom_Parent(LPVOID lpParam);
    static DWORD WINAPI ManageRoom_Child(LPVOID lpParam);
    bool ManageSelection(Chat_Info* chat);
    bool SendNodeQue(char *pszUserName, char *roomId, char type);
    bool ProActiveQue(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);
    bool SendLinkState(char *pszUserName, char *roomId);
    bool ProLinkState(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);

    // temp
    bool SendRoomGuestOperation(char* roomId, string op);
    bool ProGuestOperation(string op, MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& sockAddr);

    map<string, Chat_Info*>     m_ChatList;
    map<string, Friend_Info*>   m_FriendList;

    string                      headerPath = "./images/headers/10.png";
    string                      password = "123456";

    Peer_Info                   m_PeerInfo;				// Local information
    PeerList                    m_PeerList;				// Linked list of nodes connected to this machine
    SOCKET                      m_sSocket;				// Socket
    HANDLE                      m_hThread;				// Thread handle
    DWORD                       m_dwServerIP;			// server IP address
    WSAOVERLAPPED               m_ol;					// Overlapping structure for waiting for network events
    CRITICAL_SECTION            m_PeerListLock;			// Critical section object for reading m_PeerList
    bool                        m_bExitThread;			// Whether to exit the thread
    bool                        m_bLogin;				// Have you logged in to the server
    bool                        m_bUserListCmp;			// Did you get the user list
    bool                        m_bMessageACK;			// Whether a message reply is received

    bool                        m_bParent_roomIdReady;
    char                        m_bParent_roomId[NUM_ROOMID];

signals:
    void messageAlert(Chat_Info* room, char* username, char* message);   // Get new news and inform mainwindow
    void informAlert(string type, string message);                    // Get new notifications to inform mainwindwo
    void NewFriendAlert(Friend_Info* newFriend);              // Inform interface
    void NewRoomAlert(Chat_Info* newRoom);              // Inform interface
    void refreshStatus();       // Refresh user and room addresslist status
};

#endif // __P2P_CLIENT_H__
