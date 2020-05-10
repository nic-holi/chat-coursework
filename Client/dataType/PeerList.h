#ifndef __PEER_LIST_H__
#define __PEER_LIST_H__

#include <map>
#include <string>
#include <list>
#include <Windows.h>
//#include "CommonDefine.h"

#define MAX_ADDNUM	5
#define MAX_USERNAME	15
#define MIN_USERNAME	1
#define NUM_ROOMSIZECHAR	2
#define MAX_ROOMMATE	5
#define NUM_ROOMID	5
#define MAX_COMMAND 100

struct Addr_Info
{
    unsigned short	usPort;							// The port number
    DWORD			dwIP;							// IP address

    Addr_Info operator = (const Addr_Info& rAddrInfo)
    {
        usPort = rAddrInfo.usPort;
        dwIP   = rAddrInfo.dwIP;

        return *this;
    }
};

struct Peer_Info
{
    Addr_Info		IPAddr[MAX_ADDNUM];				// IP address and port number of all adapters of this machine,
                                                    // The nAddrNum + 1st element of the array is the IP address and port number assigned by the server of this communication
    char			szUserName[MAX_USERNAME];		// username
    DWORD			dwActiveTime;					// Active time
    int				nAddrNum;						// Number of adapters
    Addr_Info		P2PAddr;						//
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
