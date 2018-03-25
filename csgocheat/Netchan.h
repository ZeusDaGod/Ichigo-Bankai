//========= Copyright 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//
#include "stdafx.h"

class bf_read;
class bf_write;
typedef unsigned char uint8;
typedef unsigned char BYTE;
typedef unsigned char byte;

#if !defined( INETCHANNELINFO_H )
#define INETCHANNELINFO_H
#ifdef _WIN32
#pragma once
#endif

#define FLOW_OUTGOING	0
#define FLOW_INCOMING	1
#define MAX_FLOWS		2		// in & out

class INetChannelInfo
{
public:

	enum
	{
		GENERIC = 0, // must be first and is default group
		LOCALPLAYER, // bytes for local player entity update
		OTHERPLAYERS, // bytes for other players update
		ENTITIES, // all other entity bytes
		SOUNDS, // game sounds
		EVENTS, // event messages
		USERMESSAGES, // user messages
		ENTMESSAGES, // entity messages
		VOICE, // voice data
		STRINGTABLE, // a stringtable update
		MOVE, // client move cmds
		STRINGCMD, // string command
		SIGNON, // various signondata
		TOTAL, // must be last and is not a real group
	};

	virtual const char* GetName(void) const = 0; // get channel name
	virtual const char* GetAddress(void) const = 0; // get channel IP address as string
	virtual float GetTime(void) const = 0; // current net time
	virtual float GetTimeConnected(void) const = 0; // get connection time in seconds
	virtual int GetBufferSize(void) const = 0; // netchannel packet history size
	virtual int GetDataRate(void) const = 0; // send data rate in byte/sec

	virtual bool IsLoopback(void) const = 0; // true if loopback channel
	virtual bool IsTimingOut(void) const = 0; // true if timing out
	virtual bool IsPlayback(void) const = 0; // true if demo playback

	virtual float GetLatency(int flow) const = 0; // current latency (RTT), more accurate but jittering
	virtual float GetAvgLatency(int flow) const = 0; // average packet latency in seconds
	virtual float GetAvgLoss(int flow) const = 0; // avg packet loss[0..1]
	virtual float GetAvgChoke(int flow) const = 0; // avg packet choke[0..1]
	virtual float GetAvgData(int flow) const = 0; // data flow in bytes/sec
	virtual float GetAvgPackets(int flow) const = 0; // avg packets/sec
	virtual int GetTotalData(int flow) const = 0; // total flow in/out in bytes
	virtual int GetSequenceNr(int flow) const = 0; // last send seq number
	virtual bool IsValidPacket(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float GetPacketTime(int flow, int frame_number) const = 0; // time when packet was send
	virtual int GetPacketBytes(int flow, int frame_number, int group) const = 0; // group size of this packet
	virtual bool GetStreamProgress(int flow, int* received, int* total) const = 0; // TCP progress if transmitting
	virtual float GetTimeSinceLastReceived(void) const = 0; // get time since last recieved packet in seconds
	virtual float GetCommandInterpolationAmount(int flow, int frame_number) const = 0;

	virtual void GetPacketResponseLatency(int flow, int frame_number, int* pnLatencyMsecs, int* pnChoke) const = 0;

	virtual void GetRemoteFramerate(float* pflFrameTime, float* pflFrameTimeStdDeviation) const = 0;

	virtual float GetTimeoutSeconds() const = 0;
};

#endif // INETCHANNELINFO_H

#ifndef INETCHANNEL_H
#define INETCHANNEL_H
#ifdef _WIN32
#pragma once
#endif

#undef SetPort

#define PROCESS_NET_MESSAGE( name )	\
	virtual bool Process##name( NET_##name *msg )

#define PROCESS_SVC_MESSAGE( name )	\
	virtual bool Process##name( SVC_##name *msg )

#define PROCESS_CLC_MESSAGE( name )	\
	virtual bool Process##name( CLC_##name *msg )


#define REGISTER_NET_MSG( name )				\
	NET_##name * p##name = new NET_##name();	\
	p##name->m_pMessageHandler = this;			\
	chan->RegisterMessage( p##name );			\

#define REGISTER_SVC_MSG( name )				\
	SVC_##name * p##name = new SVC_##name();	\
	p##name->m_pMessageHandler = this;			\
	chan->RegisterMessage( p##name );			\

#define REGISTER_CLC_MSG( name )				\
	CLC_##name * p##name = new CLC_##name();	\
	p##name->m_pMessageHandler = this;			\
	chan->RegisterMessage( p##name );			\


class NET_Tick;
class NET_StringCmd;
class NET_SetConVar;
class NET_SignonState;
class NET_SplitScreenUser;

typedef enum
{
	NA_NULL = 0,
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
} netadrtype_t;

typedef struct netadr_s
{
public:
	netadrtype_t	type;
	unsigned char	ip[4];
	unsigned short	port;
} netadr_t;

class	IDemoRecorder;
class	INetMessage;
class	INetChannelHandler;
class	INetChannelInfo;
class	INetMessageBinder;
typedef struct netpacket_s netpacket_t;

class bf_read
{
};

#ifndef NET_PACKET_ST_DEFINED
#define NET_PACKET_ST_DEFINED
typedef struct netpacket_s
{
	netadr_t		from;		// sender IP
	int				source;		// received source 
	double			received;	// received time
	unsigned char	*data;		// pointer to raw packet data
	bf_read			message;	// easy bitbuf data access
	int				size;		// size in bytes
	int				wiresize;   // size in bytes before decompression
	bool			stream;		// was send as stream
	struct netpacket_s *pNext;	// for internal use, should be NULL in public
} netpacket_t;
#endif // NET_PACKET_ST_DEFINED

/*
class INetChannel : public INetChannelInfo
{
public:
	virtual	~INetChannel(void) {};

	virtual void	SetDataRate(float rate) = 0;
	virtual bool	RegisterMessage(INetMessageBinder *msg) = 0;
	virtual bool	UnregisterMessage(INetMessageBinder *msg) = 0;
	virtual bool	StartStreaming(unsigned int challengeNr) = 0;
	virtual void	ResetStreaming(void) = 0;
	virtual void	SetTimeout(float seconds, bool bForceExact = false) = 0;
	virtual void	SetDemoRecorder(IDemoRecorder *recorder) = 0;
	virtual void	SetChallengeNr(unsigned int chnr) = 0;

	virtual void	Reset(void) = 0;
	virtual void	Clear(void) = 0;
	virtual void	Shutdown(const char *reason) = 0;

	virtual void	ProcessPlayback(void) = 0;
	virtual bool	ProcessStream(void) = 0;
	virtual void	ProcessPacket(struct netpacket_s* packet, bool bHasHeader) = 0;

	virtual bool	SendNetMsg(INetMessage &msg, bool bForceReliable = false, bool bVoice = false) = 0;
#ifdef POSIX
	FORCEINLINE bool SendNetMsg(INetMessage const &msg, bool bForceReliable = false, bool bVoice = false) { return SendNetMsg(*((INetMessage *)&msg), bForceReliable, bVoice); }
#endif
	virtual bool	SendData(bf_write &msg, bool bReliable = true) = 0;
	virtual bool	SendFile(const char *filename, unsigned int transferID, bool isReplayDemo) = 0;
	virtual void	DenyFile(const char *filename, unsigned int transferID, bool isReplayDemo) = 0;
	virtual void	RequestFile_OLD(const char *filename, unsigned int transferID) = 0;	// get rid of this function when we version the 
	virtual void	SetChoked(void) = 0;
	virtual int		SendDatagram(bf_write *data) = 0;
	virtual bool	Transmit(bool onlyReliable = false) = 0;

	virtual const netadr_t	&GetRemoteAddress(void) const = 0;
	virtual INetChannelHandler *GetMsgHandler(void) const = 0;
	virtual int				GetDropNumber(void) const = 0;
	virtual int				GetSocket(void) const = 0;
	virtual unsigned int	GetChallengeNr(void) const = 0;
	virtual void			GetSequenceData(int &nOutSequenceNr, int &nInSequenceNr, int &nOutSequenceNrAck) = 0;
	virtual void			SetSequenceData(int nOutSequenceNr, int nInSequenceNr, int nOutSequenceNrAck) = 0;

	virtual void	UpdateMessageStats(int msggroup, int bits) = 0;
	virtual bool	CanPacket(void) const = 0;
	virtual bool	IsOverflowed(void) const = 0;
	virtual bool	IsTimedOut(void) const = 0;
	virtual bool	HasPendingReliableData(void) = 0;

	virtual void	SetFileTransmissionMode(bool bBackgroundMode) = 0;
	virtual void	SetCompressionMode(bool bUseCompression) = 0;
	virtual unsigned int RequestFile(const char *filename, bool isReplayDemoFile) = 0;
	virtual float	GetTimeSinceLastReceived(void) const = 0;	// get time since last received packet in seconds

	virtual void	SetMaxBufferSize(bool bReliable, int nBytes, bool bVoice = false) = 0;

	virtual bool	IsNull() const = 0;
	virtual int		GetNumBitsWritten(bool bReliable) = 0;
	virtual void	SetInterpolationAmount(float flInterpolationAmount) = 0;
	virtual void	SetRemoteFramerate(float flFrameTime, float flFrameTimeStdDeviation) = 0;

	// Max # of payload bytes before we must split/fragment the packet
	virtual void	SetMaxRoutablePayloadSize(int nSplitSize) = 0;
	virtual int		GetMaxRoutablePayloadSize() = 0;

	// For routing messages to a different handler
	virtual bool	SetActiveChannel(INetChannel *pNewChannel) = 0;
	virtual void	AttachSplitPlayer(int nSplitPlayerSlot, INetChannel *pChannel) = 0;
	virtual void	DetachSplitPlayer(int nSplitPlayerSlot) = 0;

	virtual bool	IsRemoteDisconnected() const = 0;

	virtual bool	WasLastMessageReliable() const = 0;


	//char pad_0000[24];//DWORD *vtable; //0x0000
	char pad_0000[20];
	int m_nOutSequenceNr; //0x0018
	int m_nInSequenceNr; //0x001C
	int m_nOutSequenceNrAck; //0x0020
	int m_nOutReliableState; //0x0024
	int m_nInReliableState; //0x0028
	int m_nChokedPackets; //0x002C
	char pad_0030[108]; //0x0030
	int m_Socket; //0x009C
	int m_StreamSocket; //0x00A0
	int m_MaxReliablePayloadSize; //0x00A4
	char pad_00A8[100]; //0x00A8
	float last_received; //0x010C
	float connect_time; //0x0110
	char pad_0114[4]; //0x0114
	int m_Rate; //0x0118
	char pad_011C[4]; //0x011C
	float m_fClearTime; //0x0120
	char pad_0124[16688]; //0x0124
	char m_Name[32]; //0x4254
	unsigned int m_ChallengeNr; //0x4274
	float m_flTimeout; //0x4278
	char pad_427C[32]; //0x427C
	float m_flInterpolationAmount; //0x429C
	float m_flRemoteFrameTime; //0x42A0
	float m_flRemoteFrameTimeStdDeviation; //0x42A4
	int m_nMaxRoutablePayloadSize; //0x42A8
	int m_nSplitPacketSequence; //0x42AC
	char pad_42B0[40]; //0x42B0
	bool m_bIsValveDS; //0x42D8
	char pad_42D9[65]; //0x42D9
};
*/
//should work u let me kno man. thanks man. peace out man.
class INetChannel : public INetChannelInfo
{
public:
	char pad_0000[20];           //0x0000
	bool m_bProcessingMessages;  //0x0014
	bool m_bShouldDelete;        //0x0015
	char pad_0016[2];            //0x0016
	int32_t m_nOutSequenceNr;    //0x0018 last send outgoing sequence number
	int32_t m_nInSequenceNr;     //0x001C last received incoming sequnec number
	int32_t m_nOutSequenceNrAck; //0x0020 last received acknowledge outgoing sequnce number
	int32_t m_nOutReliableState; //0x0024 state of outgoing reliable data (0/1) flip flop used for loss detection
	int32_t m_nInReliableState;  //0x0028 state of incoming reliable data
	int32_t m_nChokedPackets;    //0x002C number of choked packets

	bool Transmit(bool onlyReliable)
	{
		typedef bool(__thiscall* fn)(void*, bool);
		return getvfunc<fn>(this, 49)(this, onlyReliable);
	}
	char pad_0030[1044];         //0x0030
}; //Size: 0x0444

class CClockDriftMgr
{
public:
	float m_ClockOffsets[17];   //0x0000
	uint32_t m_iCurClockOffset; //0x0044
	uint32_t m_nServerTick;     //0x0048
	uint32_t m_nClientTick;     //0x004C
}; //Size: 0x0050

class CClientState
{
public:
	void ForceFullUpdate()
	{
		*(uint32_t*)((uintptr_t)this + 0x174) = -1;
	}

	char pad_0000[156];             //0x0000
	uint32_t m_NetChannel;          //0x009C
	uint32_t m_nChallengeNr;        //0x00A0
	char pad_00A4[100];             //0x00A4
	uint32_t m_nSignonState;        //0x0108
	char pad_010C[8];               //0x010C
	float m_flNextCmdTime;          //0x0114
	uint32_t m_nServerCount;        //0x0118
	uint32_t m_nCurrentSequence;    //0x011C
	char pad_0120[8];               //0x0120
	CClockDriftMgr m_ClockDriftMgr; //0x0128
	uint32_t m_nDeltaTick;          //0x0178
	bool m_bPaused;                 //0x017C
	char pad_017D[3];               //0x017D
	uint32_t m_nViewEntity;         //0x0180
	uint32_t m_nPlayerSlot;         //0x0184
	char m_szLevelName[260];        //0x0188
	char m_szLevelNameShort[40];    //0x028C
	char m_szGroupName[40];         //0x02B4
	char pad_02DC[52];              //0x02DC
	uint32_t m_nMaxClients;         //0x0310
	char pad_0314[18820];           //0x0314
	float m_flLastServerTickTime;   //0x4C98
	bool insimulation;              //0x4C9C
	char pad_4C9D[3];               //0x4C9D
	uint32_t oldtickcount;          //0x4CA0
	float m_tickRemainder;          //0x4CA4
	float m_frameTime;              //0x4CA8
	uint32_t lastoutgoingcommand;   //0x4CAC
	uint32_t chokedcommands;        //0x4CB0
	uint32_t last_command_ack;      //0x4CB4
	uint32_t command_ack;           //0x4CB8
	uint32_t m_nSoundSequence;      //0x4CBC
	char pad_4CC0[80];              //0x4CC0
	Vector viewangles;              //0x4D10
}; //Size: 0x4D1C
#endif // INETCHANNEL_H