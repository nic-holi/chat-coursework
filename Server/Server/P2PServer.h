#pragma once


#ifndef __P2P_SERVER_H__
#define __P2P_SERVER_H__

#include "CommonDefine.h"

class P2PServer
{
public:
	P2PServer();
	~P2PServer();

	bool ProcMsg();

private:
	bool Initialize();
	static DWORD WINAPI RecvThreadProc(LPVOID lpParam);

	
	bool ProcUserLoginMsg(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& remoteAddr);
	bool ProcGetUserListMsg(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& remoteAddr);
	bool ProcP2PConnectMsg(MSGDef::TMSG_HEADER *pMsgHeader, sockaddr_in& remoteAddr);
	bool ProcUserLogoutMsg(MSGDef::TMSG_HEADER *pMsgHeader, sockaddr_in& remoteAddr);
	bool ProcUserActiveQueryMsg(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& remoteAddr);
	bool ProcNewRoomIdApply(MSGDef::TMSG_HEADER *pMsgHeader, const sockaddr_in& remoteAddr);

private:
	SOCKET				m_sSocket;			
	HANDLE				m_hThread;			
	CRITICAL_SECTION	m_PeerListLock;		
	PeerList			m_PeerList;			

	bool				roomIdOccupy[10000]; 
};

#endif	// __P2P_SERVER_H__
