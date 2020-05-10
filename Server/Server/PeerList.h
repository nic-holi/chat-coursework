#pragma once


#ifndef __PEER_LIST_H__
#define __PEER_LIST_H__

#include <map>
#include <string>
#include <list>
#include <Windows.h>

#define	MAX_USERNAME		15
#define MAX_ADDNUM			5

struct Addr_Info
{
	unsigned short	usPort;							
	DWORD			dwIP;							

	Addr_Info operator = (const Addr_Info& rAddrInfo)
	{
		usPort = rAddrInfo.usPort;
		dwIP = rAddrInfo.dwIP;

		return *this;
	}
};

struct Peer_Info
{
	Addr_Info		IPAddr[MAX_ADDNUM];				
													
	char			szUserName[MAX_USERNAME];		
	DWORD			dwActiveTime;					
	int				nAddrNum;						
	Addr_Info		P2PAddr;						
	Peer_Info();

	Peer_Info operator=(const Peer_Info& rPeerinfo);
};

class PeerList
{
public:
	PeerList();
	~PeerList();

	bool		AddPeer(const Peer_Info& rPeerInfo);
	bool		DeleteAPeer(const char* pszUserName);
	bool		DeleteAllPeer();
	Peer_Info*	GetAPeer(const char* pszUserName);
	int			GetCurrentSize();
	Peer_Info*	operator[](int nIndex);

private:
	typedef std::list<Peer_Info> PeerInfoList;
	typedef PeerInfoList::iterator PeerInfoListIter;
	PeerInfoList	m_PeerInfoList;
};

#endif // __PEER_LIST_H__
