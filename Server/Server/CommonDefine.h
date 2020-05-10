#pragma once


#ifndef __COMMON_DEFINE_H__
#define __COMMON_DEFINE_H__

#include <Windows.h>
#include "PeerList.h"

#pragma comment(lib, "WS2_32")	

#define MAX_TRY_NUMBER		10

#define SERVER_PORT			4096
#define MAX_PACKET_SIZE		1024


#define INVALID_MSG			-1
#define MSG_USERLOGIN		1						
#define MSG_USERLOGACK		2						
#define MSG_GETUSERLIST		3						
#define MSG_USERLISTCMP		4						
#define MSG_P2PMSG			5						
#define MSG_P2PCONNECT		6						
#define MSG_P2PMSGACK		7
#define MSG_P2PCONNECTACK	8
#define MSG_USERLOGOUT		9						
#define MSG_USERACTIVEQUERY	10						


#define MSG_NEWROOMIDAPPLY      14                      
#define MSG_NEWROOMIDREPLY      15                     

class MSGDef										
{
public:
#pragma pack(1)										

	
	struct TMSG_HEADER
	{
		char    cMsgID;								

		TMSG_HEADER(char MsgID = INVALID_MSG)
			: cMsgID(MsgID)
		{
		}
	};

	
	struct TMSG_USERLOGIN
		: TMSG_HEADER
	{
		Peer_Info PeerInfo;

		TMSG_USERLOGIN(const Peer_Info &rPeerinfo)
			: TMSG_HEADER(MSG_USERLOGIN)
		{
			PeerInfo = rPeerinfo;
		}
	};

	
	struct TMSG_USERLOGACK
		: TMSG_HEADER
	{
		Peer_Info PeerInfo;

		TMSG_USERLOGACK(const Peer_Info& rPeerInfo)
			: TMSG_HEADER(MSG_USERLOGACK)
		{
			PeerInfo = rPeerInfo;
		}
	};

	
	struct TMSG_GETUSERLIST
		: TMSG_HEADER
	{
		Peer_Info PeerInfo;

		TMSG_GETUSERLIST(const Peer_Info& rPeerInfo)
			: TMSG_HEADER(MSG_GETUSERLIST)
		{
			PeerInfo = rPeerInfo;
		}
	};

	
	struct TMSG_USERLISTCMP
		: TMSG_HEADER
	{
		TMSG_USERLISTCMP()
			: TMSG_HEADER(MSG_USERLISTCMP)
		{

		}
	};

	
	struct TMSG_P2PMSG
		: TMSG_HEADER
	{
		Peer_Info	PeerInfo;
		char		szMsg[MAX_PACKET_SIZE - sizeof(TMSG_HEADER) - sizeof(Peer_Info)];

		TMSG_P2PMSG(const Peer_Info& rPeerInfo)
			: TMSG_HEADER(MSG_P2PMSG)
		{
			PeerInfo = rPeerInfo;
			memset(szMsg, 0, MAX_PACKET_SIZE - sizeof(TMSG_HEADER) - sizeof(PeerInfo));
		}
	};

	
	struct TMSG_P2PCONNECT
		: TMSG_HEADER
	{
		Peer_Info	PeerInfo;
		char		szUserName[MAX_USERNAME];

		TMSG_P2PCONNECT(const Peer_Info& rPeerInfo)
			: TMSG_HEADER(MSG_P2PCONNECT)
		{
			PeerInfo = rPeerInfo;
		}
	};

	
	struct TMSG_P2PMSGACK
		: TMSG_HEADER
	{
		Peer_Info PeerInfo;

		TMSG_P2PMSGACK(const Peer_Info& rPeerInfo)
			: TMSG_HEADER(MSG_P2PMSGACK)
		{
			PeerInfo = rPeerInfo;
		}
	};

	
	struct TMSG_P2PCONNECTACK
		: TMSG_HEADER
	{
		Peer_Info PeerInfo;

		TMSG_P2PCONNECTACK(const Peer_Info& rPeerInfo)
			: TMSG_HEADER(MSG_P2PCONNECTACK)
		{
			PeerInfo = rPeerInfo;
		}
	};

	
	struct TMSG_USERLOGOUT
		: TMSG_HEADER
	{
		Peer_Info PeerInfo;
		TMSG_USERLOGOUT(const Peer_Info& rPeerInfo)
			: TMSG_HEADER(MSG_USERLOGOUT)
		{
			PeerInfo = rPeerInfo;
		}
	};

	
	struct TMSG_USERACTIVEQUERY
		: TMSG_HEADER
	{
		Peer_Info PeerInfo;

		TMSG_USERACTIVEQUERY(const Peer_Info& rPeerInfo = Peer_Info())
			: TMSG_HEADER(MSG_USERACTIVEQUERY)
		{
			PeerInfo = rPeerInfo;
		}
	};
	
	struct TMSG_NEWROOMIDAPPLY
		: TMSG_HEADER
	{
		Peer_Info PeerInfo;

		TMSG_NEWROOMIDAPPLY(const Peer_Info& rPeerInfo)
			: TMSG_HEADER(MSG_NEWROOMIDAPPLY)
		{
			PeerInfo = rPeerInfo;
		}
	};

	
	struct TMSG_NEWROOMIDREPLY
		: TMSG_HEADER
	{
		Peer_Info PeerInfo;
		char      roomId[5];

		TMSG_NEWROOMIDREPLY(const Peer_Info& rPeerInfo = Peer_Info())
			: TMSG_HEADER(MSG_NEWROOMIDREPLY)
		{
			PeerInfo = rPeerInfo;
		}
	};

#pragma pack()
};

#endif // __COMMON_DEFINE_H__
