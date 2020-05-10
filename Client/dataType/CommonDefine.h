#ifndef __COMMON_DEFINE_H__
#define __COMMON_DEFINE_H__

#include <Windows.h>
#include "PeerList.h"

#pragma comment(lib, "WS2_32")	// connected to WS2_32.lib

#define MAX_TRY_NUMBER		5
#define SERVER_PORT			4096
#define MAX_PACKET_SIZE		1024

#define G_UNREACHABLE	1000


#define INVALID_MSG             -1
#define MSG_USERLOGIN           1						// user login
#define MSG_USERLOGACK          2						// Send a message confirming the user's login
#define MSG_GETUSERLIST         3						// Get user list
#define MSG_USERLISTCMP         4						// User list transmission completed
#define MSG_P2PMSG              5						// Send P2P information
#define MSG_P2PCONNECT          6						// A user requested that another user send a hole-punch message to it
#define MSG_P2PMSGACK           7                       // Message ACK
#define MSG_P2PCONNECTACK       8                       // ACK for hole punching
#define MSG_USERLOGOUT          9						// Inform the server user to quit
#define MSG_USERACTIVEQUERY     10                      // Check if the user still exists

#define MSG_NEWFRIENDASK        11                      // Request to add friends
#define MSG_NEWFRIENDAGREE      12                      // Agree to add friends
#define MSG_NEWFRIENDREFUSE     13                      // Refuse to add friends

#define MSG_NEWROOMIDAPPLY		14						// Request room id
#define MSG_NEWROOMIDREPLY      15                      // The room id returned by the server
#define MSG_NEWROOMASK          16                      // Request to create a room (host, id)
#define MSG_NEWROOMAGREE        17                      // Agree to join the room (host, id)
#define MSG_NEWROOMREFUSE       18                      // Refuse to join the room (host, id)
#define MSG_NEWROOMNAMELIST     19                      // Room list
#define MSG_CHATSTARTALERT		20						// Start discussion
#define MSG_LEAVEROOM			21						// Leave the room
#define MSG_ENTERROOM			22						// Enter the room
#define MSG_QUITROOM			23						// Exit the room
// 维护
#define MSG_NODEACTIVEQUE		24
#define MSG_LINKSTATE			25

class MSGDef										// Define the structure of the message
{
public:
#pragma pack(1)										// Align the data of the structure according to 1 byte, saving space

    // Message header
    struct TMSG_HEADER
    {
        char    cMsgID;								// Message ID

        TMSG_HEADER(char MsgID = INVALID_MSG)
            : cMsgID(MsgID)
        {
        }
    };

    // user login
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

    // Send a message confirming the user's login
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

    // Get user list
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

    // Finished updating user list
    struct TMSG_USERLISTCMP
        : TMSG_HEADER
    {
        TMSG_USERLISTCMP()
            : TMSG_HEADER(MSG_USERLISTCMP)
        {

        }
    };

    // A client sends a message to another client
    struct TMSG_P2PMSG
        : TMSG_HEADER
    {
        Peer_Info	PeerInfo;
        char		roomId[NUM_ROOMID];
        char		user[MAX_USERNAME];
        char		szMsg[MAX_PACKET_SIZE - sizeof(TMSG_HEADER) - sizeof(Peer_Info) - sizeof(char[NUM_ROOMID]) - sizeof(char[MAX_USERNAME])];

        TMSG_P2PMSG(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_P2PMSG)
        {
            PeerInfo = rPeerInfo;
            memset(roomId, '\0', NUM_ROOMID);
            memset(user, '\0', MAX_USERNAME);
            memset(szMsg, 0, MAX_PACKET_SIZE - sizeof(TMSG_HEADER) - sizeof(PeerInfo) - sizeof(roomId) - sizeof(user));
        }
    };

    // A user requested that another user send a hole-punch message to it
    struct TMSG_P2PCONNECT
        : TMSG_HEADER
    {
        Peer_Info	PeerInfo;
        char		szUserName[MAX_USERNAME];

        TMSG_P2PCONNECT(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_P2PCONNECT)
        {
            PeerInfo = rPeerInfo;
            memset(szUserName, '\0', MAX_USERNAME);

        }
    };

    // The confirmation after the client receives the message sent by another client
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

    // After receiving the hole punching message from the node, set its P2P communication address here
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

    // Inform the server user to quit
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

    // Check if the user still exists
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

    // Request to add friends
    struct TMSG_NEWFRIENDASK
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;

        TMSG_NEWFRIENDASK(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_NEWFRIENDASK)
        {
            PeerInfo = rPeerInfo;
        }
    };

    // Agree to add friends
    struct TMSG_NEWFRIENDAGREE
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;

        TMSG_NEWFRIENDAGREE(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_NEWFRIENDAGREE)
        {
            PeerInfo = rPeerInfo;
        }
    };

    // Refuse to add friends
    struct TMSG_NEWFRIENDREFUSE
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;

        TMSG_NEWFRIENDREFUSE(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_NEWFRIENDREFUSE)
        {
            PeerInfo = rPeerInfo;
        }
    };

    // Request room id
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

    // The room id returned by the server
    struct TMSG_NEWROOMIDREPLY
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char      roomId[NUM_ROOMID];

        TMSG_NEWROOMIDREPLY(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_NEWROOMIDREPLY)
        {
            PeerInfo = rPeerInfo;
            memset(roomId, '\0', NUM_ROOMID);
        }
    };

    // Request to create a room (host, id)
    struct TMSG_NEWROOMASK
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char      roomId[NUM_ROOMID];

        TMSG_NEWROOMASK(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_NEWROOMASK)
        {
            PeerInfo = rPeerInfo;
            memset(roomId, '\0', NUM_ROOMID);
        }
    };

    // Agree to join the room (host, id)
    struct TMSG_NEWROOMAGREE
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char      roomId[NUM_ROOMID];

        TMSG_NEWROOMAGREE(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_NEWROOMAGREE)
        {
            PeerInfo = rPeerInfo;
            memset(roomId, '\0', NUM_ROOMID);
        }
    };

    // Refuse to join the room (host)
    struct TMSG_NEWROOMREFUSE
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char      roomId[NUM_ROOMID];

        TMSG_NEWROOMREFUSE(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_NEWROOMREFUSE)
        {
            PeerInfo = rPeerInfo;
            memset(roomId, '\0', NUM_ROOMID);
        }
    };
    //Room list
    struct TMSG_NEWROOMNAMELIST
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char      roomId[NUM_ROOMID];
        int       roomSize;
        char      namelist[MAX_ROOMMATE][MAX_USERNAME];

        TMSG_NEWROOMNAMELIST(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_NEWROOMNAMELIST)
        {
            PeerInfo = rPeerInfo;
            memset(roomId, '\0', NUM_ROOMID);
            memset(namelist, '\0', MAX_ROOMMATE * MAX_USERNAME);

        }
    };
    // The room started to discuss
    struct TMSG_CHATSTARTALERT
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char      roomId[NUM_ROOMID];

        TMSG_CHATSTARTALERT(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_CHATSTARTALERT)
        {
            PeerInfo = rPeerInfo;
            memset(roomId, '\0', NUM_ROOMID);
        }
    };
    // Leave the room
    struct TMSG_LEAVEROOM
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char      roomId[NUM_ROOMID];

        TMSG_LEAVEROOM(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_LEAVEROOM)
        {
            PeerInfo = rPeerInfo;
            memset(roomId, '\0', NUM_ROOMID);
        }
    };
    // Enter the room
    struct TMSG_ENTERROOM
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char      roomId[NUM_ROOMID];

        TMSG_ENTERROOM(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_ENTERROOM)
        {
            PeerInfo = rPeerInfo;
            memset(roomId, '\0', NUM_ROOMID);
        }
    };
    // Retreat
    struct TMSG_QUITROOM
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char      roomId[NUM_ROOMID];

        TMSG_QUITROOM(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_QUITROOM)
        {
            PeerInfo = rPeerInfo;
            memset(roomId, '\0', NUM_ROOMID);
        }
    };
    //Node survival confirmation
    struct TMSG_NODEACTIVEQUE
        : TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char	  roomId[NUM_ROOMID];
        char	  type; // o represents the daily inquiry of the parent node, s represents the inquiry of the reselection process

        TMSG_NODEACTIVEQUE(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_NODEACTIVEQUE)
        {
            PeerInfo = rPeerInfo;
        }
    };
    // Link state
    struct TMSG_LINKSTATE
        :TMSG_HEADER
    {
        Peer_Info PeerInfo;
        char			roomId[NUM_ROOMID];
        int				edge[MAX_ROOMMATE][MAX_ROOMMATE];

        TMSG_LINKSTATE(const Peer_Info& rPeerInfo)
            : TMSG_HEADER(MSG_LINKSTATE)
        {
            PeerInfo = rPeerInfo;
            for (int i = 0; i < MAX_ROOMMATE; i++) {
                for (int j = 0; j < MAX_ROOMMATE; j++) {
                    edge[i][j] = G_UNREACHABLE;
                }
            }
        }
    };
#pragma pack()
};

#endif // __COMMON_DEFINE_H__
