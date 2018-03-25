#pragma once
#include "../stdafx.h"

#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin)

class KeyValues
{
public:
	char _pad[0x20];//csgo, for css its a diff size
};

inline void**& getvtable( void* inst, size_t offset = 0 )
{
	return *reinterpret_cast< void*** >( ( size_t )inst + offset );
}

inline const void** getvtable( const void* inst, size_t offset = 0 )
{
	if( !inst && !offset )
		return nullptr;
	return *reinterpret_cast< const void*** >( ( size_t )inst + offset );
}

template< typename Fn >
inline Fn getvfunc( const void* inst, size_t index, size_t offset = 0 )
{
	if( !inst && offset == 0 )
		return NULL;

	return reinterpret_cast< Fn >( getvtable( inst, offset )[ index ] );
}

typedef matrix3x4_t matrix3x4;
typedef float matrix4x4[4][4];

typedef void* (__cdecl* CreateInterface_t)( const char*, int* );

typedef void* (*CreateInterfaceFn)( const char* pName, int* pReturnCode );

typedef __int16 int16;
typedef unsigned __int16 uint16;
typedef __int32 int32;
typedef unsigned __int32 uint32;
typedef __int64 int64;
typedef unsigned __int64 uint64;
typedef float vec_t;

class VMatrix;

//USERCMD OFFSETS
#define USERCMDOFFSET 0xEC
#define VERIFIEDCMDOFFSET 0xF0
#define MULTIPLAYER_BACKUP 150
#define CURRENTCOMMANDOFFSET 0x16E8
#define CURRENTPLAYERCOMMANDOFFSET 0x1640
#define PREIDCTIONSEEDOFFSET 0x30
#define PREDICTIONPLAYEROFFSET 0x54
#define GLOBALSOFFSET 0x53
#define WEAPONDATA_MAXRANGEOFFSET 0x77C
#define WEAPONDATA_DAMAGEOFFSET 0x778
#define WEAPONDATA_RANGEMODIFIEROFFSET 0x780
#define WEAPONDATA_PENETRATIONPOWEROFFSET 0x774
#define INPUTOFFSET 0x5F
#define GETSPREADOFFSET 0x740
#define GETCONEOFFSET 0x744
#define UPDATEACCURACYPENALTYOFFSET 0x748
#define WEAPONIDOFFSET 0x6D8
#define WEAPONDATAOFFSET 0x708
#define GETNAMEOFFSET 0x5CC
#define APPSYSTEMFACTORYOFFSET 0x3D
#define CLIENTFACTORYOFFSET 0x75
#define GLOWINDEXOFFSET 0x1DB8

//LIFESTATE
#define	LIFE_ALIVE				0
#define	LIFE_DYING				1
#define	LIFE_DEAD				2
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY		4

//Player flags
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
#define	FL_INWATER				(1<<10)	// In water

/* MOVE TYPES */
enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

//USERCMD BUTTONS
#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2

#include "SDK Headers/SDK_Others.h"

class ISurface;
class IPanel;
class HLCLient;
class CEntityList;
class CEngineClient;
class CInput;
class CGlowObjectManager;
class IVModelInfo;
class IViewRenderBeams;
class IVModelRender;
class CPrediction;
class CGameMovement;
class IMoveHelper;
class CGlobalVars;
class IEngineTrace;
class IPhysicsSurfaceProps;
class CDebugOverlay;
class IMaterialSystem;;
class IVRenderView;
class ICVar;
class ICvar2;
class IEffects;
class IGameEventManager2;
class IDirect3DDevice9;
class IEngineSound;
class IMDLCache;
class INetChannel;
class IBaseClientDLL;
class CClientState;

class CInterfaces
{
private:
	void* GetPointer( const char* Module, const char* InterfaceName )
	{
		void* Interface = nullptr;
		char PossibleInterfaceName[1024];

		CreateInterfaceFn CreateInterface = ( CreateInterfaceFn )GetProcAddress( GetModuleHandleA( Module ), "CreateInterface" );
		for( int i = 1; i < 100; i++ )
		{
			Interface = ( void* )CreateInterface( PossibleInterfaceName, nullptr );
			if( Interface != nullptr )
			{
				cout << white << PossibleInterfaceName << " Found: 0x " << igreen << Interface << endl;
				break;
			}

			Interface = ( void* )CreateInterface( PossibleInterfaceName, nullptr );
			if( Interface != nullptr )
			{
				cout << white << PossibleInterfaceName << " Found: 0x " << igreen << Interface << endl;
				break;
			}
		}

		return Interface;
	}

	void* GetInterfacePtr( const char* interfaceName, const char* ptrName, CreateInterface_t pInterface )
	{
		char szDebugString[1024];

		std::string sinterface = "";
		std::string interfaceVersion = "0";

		for( int i = 0; i <= 99; i++ )
		{
			sinterface = interfaceName;
			sinterface += interfaceVersion;
			sinterface += std::to_string( i );

			void* funcPtr = pInterface( sinterface.c_str(), nullptr );

			if( ( DWORD )funcPtr != 0x0 )
			{
				sprintf_s( szDebugString, "%s: 0x%x (%s%s%i)", ptrName, ( DWORD )funcPtr, interfaceName, interfaceVersion.c_str(), i );
				cout << white << ptrName << ": " << igreen << "0x" << funcPtr << " ( " << white << interfaceName << interfaceVersion << i << igreen << " )" << white << endl;
				return funcPtr;
			}
			if( i >= 99 && interfaceVersion == "0" )
			{
				interfaceVersion = "00";
				i = 0;
			}
			else if( i >= 99 && interfaceVersion == "00" )
			{
				sprintf_s( szDebugString, "%s: 0x%x (error)", ptrName, ( DWORD )funcPtr );
				cout << ired << ptrName << ": 0x" << funcPtr << " (ERROR)" << white << endl;
			}
		}
		return nullptr;
	}
public:
	void InitialiseSDK()
	{
		auto p = Utils.PatternSearch("client.dll", (BYTE*)"\x8B\x0D\x00\x00\x00\x00\xFF\x75\x08\x8B\x01\xFF\x50\x64", "xx????xxxxxxxx", NULL, NULL);
		if (p)
		{
			pClientMode = **(IClientModeShared***)(p + 2);
			pClientMode = pClientMode;
		}
		
		cout << iaqua << "Interfaces:" << endl;
		CreateInterface_t ClientFactory = (CreateInterface_t)GetProcAddress((HMODULE)GetModuleHandle("client.dll"), "CreateInterface");
		CreateInterface_t EngineFactory = (CreateInterface_t)GetProcAddress((HMODULE)GetModuleHandle("engine.dll"), "CreateInterface");
		CreateInterface_t VGUI2Factory = (CreateInterface_t)GetProcAddress((HMODULE)GetModuleHandle("vgui2.dll"), "CreateInterface");
		CreateInterface_t VGUISurfaceFactory = (CreateInterface_t)GetProcAddress((HMODULE)GetModuleHandle("vguimatsurface.dll"), "CreateInterface");
		CreateInterface_t MatFactory = (CreateInterface_t)GetProcAddress((HMODULE)GetModuleHandle("materialsystem.dll"), "CreateInterface");
		CreateInterface_t PhysFactory = (CreateInterface_t)GetProcAddress((HMODULE)GetModuleHandle("vphysics.dll"), "CreateInterface");
		CreateInterface_t StdFactory = (CreateInterface_t)GetProcAddress((HMODULE)GetModuleHandle("vstdlib.dll"), "CreateInterface");
		CreateInterface_t MDLFactory = (CreateInterface_t)GetProcAddress((HMODULE)GetModuleHandle("datacache.dll"), "CreateInterface");

		pSurface = ( ISurface* )GetInterfacePtr( "VGUI_Surface", "g_pSurface", VGUISurfaceFactory);
		g_CHLClient = ( IBaseClientDLL* )GetInterfacePtr( "VClient", "g_CHLClient", ClientFactory);
		pPanel = ( IPanel* )GetInterfacePtr( "VGUI_Panel", "g_pPanel", VGUI2Factory);
		pClient = ( HLCLient* )GetInterfacePtr( "VClient", "g_pClient", ClientFactory );
		pEngine = ( CEngineClient* )GetInterfacePtr( "VEngineClient", "g_pEngine", EngineFactory );
		pEntList = ( CEntityList* )GetInterfacePtr( "VClientEntityList", "g_pEntList", ClientFactory );
		g_pDebugOverlay = ( CDebugOverlay* )GetInterfacePtr( "VDebugOverlay", "g_pDebugOverlay", EngineFactory );
		pTrace = ( IEngineTrace* )GetInterfacePtr( "EngineTraceClient", "g_pEngineTraceClient", EngineFactory );
		g_pModelInfo = ( IVModelInfo* )GetInterfacePtr( "VModelInfoClient", "g_pModelInfo", EngineFactory );
		g_pModelRender = ( IVModelRender* )GetInterfacePtr( "VEngineModel", "g_ModelRender", EngineFactory );
		g_pPred = ( CPrediction* )GetInterfacePtr( "VClientPrediction", "g_pPred", ClientFactory );
		g_pGameMovement = ( CGameMovement* )GetInterfacePtr( "GameMovement", "g_pGameMovement", ClientFactory );
		pPhysProps = ( IPhysicsSurfaceProps* )GetInterfacePtr( "VPhysicsSurfaceProps", "g_pPhysprops", PhysFactory );
		pMaterialSystem = ( IMaterialSystem* )GetInterfacePtr( "VMaterialSystem", "pMaterialSystem", MatFactory );
		g_pRenderView = ( IVRenderView* )GetInterfacePtr( "VEngineRenderView", "g_pRenderView", EngineFactory );
		g_ICVars = (ICVar*)GetInterfacePtr("VEngineCvar", "g_pCVars", StdFactory);
		g_ClientStateTest = *(DWORD*)(getvfunc<uintptr_t>(pEngine, 12) + 0x10);
		cout << white << "g_ClientStateTest" << ": " << igreen << "0x" << g_ClientStateTest << white << endl;

		pMDL = (IMDLCache*)(MDLFactory("MDLCache004", nullptr));
		cout << white << "pMDL" << ": " << igreen << "0x" << pMDL << white << endl;

		cout << endl;

		pSound = (IEngineSound*)(EngineFactory("IEngineSoundClient003", nullptr));
		cout << white << "pSound" << ": " << igreen << "0x" << pSound << white << endl;

		cout << white << "pClientMode" << ": " << igreen << "0x" << pClientMode << white << endl;

		pGlobalVars = *( CGlobalVars** )( ( ( *( PDWORD* )pClient )[ 0 ] ) + 0x1B );
		pGlobalVars = ( CGlobalVars* )*( PDWORD )pGlobalVars;
		cout << white << "pGlobalVars" << ": "<< igreen << "0x" << pGlobalVars << white << endl;

		pInput = *( CInput** )( ( *( DWORD** )pClient )[ 15 ] + 0x1 );
		cout << white << "pInput" << ": " << igreen << "0x" << pInput << white << endl;

		GameResources = ( DWORD )Utils.PatternSearch( "client.dll", ( PBYTE )"\x8B\x3D\x00\x00\x00\x00\x85\xFF\x0F\x84\x00\x00\x00\x00\x81\xC7", "xx????xxxx????xx", NULL, NULL ) - ( DWORD )pClient;
		cout << white << "GameResources" << ": " << igreen << "0x" << GameResources << white << endl;

		g_GameEventMgr = ( IGameEventManager2* )( EngineFactory ( "GAMEEVENTSMANAGER002", nullptr ) );
		cout << white << "g_GameEventMgr" << ": " << igreen << "0x" << g_GameEventMgr << white << endl;

		d3d_device = **(uint32_t**)(Utils.PFindPattern(("shaderapidx9.dll"), ("A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C")) + 1);
		cout << white << "D3D Device" << ": " << igreen << "0x" << d3d_device << white << endl;

		g_pGlowObjectManager = *(DWORD *)(Utils.PFindPattern("client.dll", "0F 11 05 ?? ?? ?? ?? 83 C8 01 C7 05 ?? ?? ?? ?? 00 00 00 00") + 3);
		cout << white << "g_pGlowObjectManager" << ": " << igreen << "0x" << g_pGlowObjectManager << white << endl;

		DLight = (IEffects*)(EngineFactory("VEngineEffects001", nullptr));
		cout << white << "IEffects" << ": " << igreen << "0x" << DLight << white << endl;

		g_pViewRenderBeams = *(IViewRenderBeams**)(Utils.PFindPattern("client.dll", "B9 ?? ?? ?? ?? A1 ?? ?? ?? ?? FF 10 A1 ?? ?? ?? ?? B9") + 1);
		cout << white << "g_pViewRenderBeams" << ": " << igreen << "0x" << g_pViewRenderBeams << white << endl;

		g_ClientState = **(CClientState***)(Utils.PFindPattern("engine.dll", "A1 ?? ?? ?? ?? 8B 80 ?? ?? ?? ?? C3") + 1);
		cout << white << "g_ClientState" << ": " << igreen << "0x" << g_ClientState << white << endl;

	}
private:
	bool InitialisedSuccessfuly = false;
public:
	//IGameEventManager2* GameEventManager;
	ISurface* pSurface;
	IClientModeShared* pClientMode;
	IPanel* pPanel;
	HLCLient* pClient;
	IViewRenderBeams* g_pViewRenderBeams;
	CEntityList* pEntList;
	CEngineClient* pEngine;
	CInput* pInput;
	DWORD g_pGlowObjectManager;
	IVModelInfo* g_pModelInfo;
	IVModelRender* g_pModelRender;
	CPrediction* g_pPred;
	CGameMovement* g_pGameMovement;
	IMoveHelper* g_pMoveHelper;
	CGlobalVars* pGlobalVars;
	IEngineTrace* pTrace;
	IPhysicsSurfaceProps* pPhysProps;
	CDebugOverlay* g_pDebugOverlay;
	IMaterialSystem* pMaterialSystem;
	IVRenderView* g_pRenderView;
	IEffects* DLight;
	ICVar* g_ICVars;
	IEngineSound* pSound;
	IBaseClientDLL* g_CHLClient;
	IGameEventManager2* pGameEventManager;
	IGameEventManager2* g_GameEventMgr;
	DWORD d3d_device;
	DWORD GameResources = 0;
	IMDLCache* pMDL;
	CClientState* g_ClientState;
	DWORD g_ClientStateTest;

	HANDLE __FNTHANDLE;
};

extern CInterfaces Interfaces;

#include "Math.h"
#include "../Netchan.h"
#include "SDK Headers\CGlow.h"
#include "SDK Headers/Valve/checksum_crc.h"
#include "SDK Headers/Valve/dt_recv2.h"
#include "SDK Headers/NetVars.h"
#include "SDK Headers/IEffects.h"
#include "SDK Headers/ISurface.h"
#include "SDK Headers/CClient.h"
#include "SDK Headers/EngineClient.h"
#include "SDK Headers/Entitys.h"
#include "../IClientDLL.h"
#include "SDK Headers/EntList.h"
#include "SDK Headers/DebugOverlay.h"
#include "SDK Headers/CTrace.h"
#include "SDK Headers/IVRenderView.h"
#include "SDK Headers/CModelInfo.h"
#include "SDK Headers/CInput.h"
#include "SDK Headers/ICVars.h"
#include "SDK Headers/CGlobleVars.h"
#include "SDK Headers/CGameMovement.h"
#include "SDK Headers/CPred.h"
#include "SDK Headers\IEngineClientSound.h"
#include "SDK Headers\IMDLCache.h"



void UTIL_TraceLine( Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, const IHandleEntity* ignore, int collisionGroup, trace_t* ptr );

void UTIL_ClipTraceToPlayers( Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr );

bool TraceToExit( Vector& end, trace_t& tr, Vector start, Vector vEnd, trace_t* trace );

/* FIRE BULLET DATA */
struct FireBulletData
{
	FireBulletData( const Vector& eye_pos ) : src( eye_pos )
	{
	}

	Vector src;
	trace_t enter_trace;
	Vector direction;
	CTraceFilter filter;
	float trace_length;
	float trace_length_remaining;
	float current_damage;
	int penetrate_count;
};

struct ColorRGBExp32
{
	byte r, g, b;
	signed char exponent;

};

struct dlight_t
{
	int flags;
	Vector origin;
	float radius;
	ColorRGBExp32 color;
	float die;
	float decay;
	float minlight;
	int key;
	int style;
	Vector m_Direction;
	float m_InnerAngle;
	float m_OuterAngle;

	float GetRadius() const
	{
		return radius;
	}

	float GetRadiusSquared() const
	{
		return radius * radius;
	}

	float IsRadiusGreaterThanZero() const
	{
		return radius > 0.0f;
	}
};

class IEffects
{
public:
	dlight_t* CL_AllocDlight(int key)
	{
		typedef dlight_t*(__thiscall* OriginalFn)(PVOID, int);
		return getvfunc< OriginalFn >(this, 4)(this, key);
	}

	dlight_t* CL_AllocElight(int key)
	{
		typedef dlight_t*(__thiscall* OriginalFn)(PVOID, int);
		return getvfunc< OriginalFn >(this, 5)(this, key);
	}

	dlight_t* GetElightByKey(int key)
	{
		typedef dlight_t*(__thiscall* OriginalFn)(PVOID, int);
		return getvfunc< OriginalFn >(this, 8)(this, key);
	}
};

struct INetMessage {
	virtual ~INetMessage();
};

template<typename T>
class CNetMessagePB : public INetMessage, public T {};

class CCLCMsg_Move {
private:
	char __PAD0[0x8];
public:
	int numBackupCommands;
	int numNewCommands;
};

using CCLCMsg_Move_t = CNetMessagePB<CCLCMsg_Move>;

/* HITGROUP DEFINITIONS */
#define		HITGROUP_GENERIC    0
#define		HITGROUP_HEAD       1
#define		HITGROUP_CHEST      2
#define		HITGROUP_STOMACH    3
#define		HITGROUP_LEFTARM    4
#define		HITGROUP_RIGHTARM   5
#define		HITGROUP_LEFTLEG    6
#define		HITGROUP_RIGHTLEG   7
#define		HITGROUP_GEAR       10

typedef bool (*ShouldHitFunc_t)( IHandleEntity* pHandleEntity, int contentsMask );

enum class CSGOClassID
{
	CTestTraceline = 189,
	CTEWorldDecal = 190,
	CTESpriteSpray = 187,
	CTESprite = 186,
	CTESparks = 185,
	CTESmoke = 184,
	CTEShowLine = 182,
	CTEProjectedDecal = 179,
	CTEPlayerDecal = 178,
	CTEPhysicsProp = 175,
	CTEParticleSystem = 174,
	CTEMuzzleFlash = 173,
	CTELargeFunnel = 171,
	CTEKillPlayerAttachments = 170,
	CTEImpact = 169,
	CTEGlowSprite = 168,
	CTEShatterSurface = 181,
	CTEFootprintDecal = 165,
	CTEFizz = 164,
	CTEExplosion = 162,
	CTEEnergySplash = 161,
	CTEEffectDispatch = 160,
	CTEDynamicLight = 159,
	CTEDecal = 157,
	CTEClientProjectile = 156,
	CTEBubbleTrail = 155,
	CTEBubbles = 154,
	CTEBSPDecal = 153,
	CTEBreakModel = 152,
	CTEBloodStream = 151,
	CTEBloodSprite = 150,
	CTEBeamSpline = 149,
	CTEBeamRingPoint = 148,
	CTEBeamRing = 147,
	CTEBeamPoints = 146,
	CTEBeamLaser = 145,
	CTEBeamFollow = 144,
	CTEBeamEnts = 143,
	CTEBeamEntPoint = 142,
	CTEBaseBeam = 141,
	CTEArmorRicochet = 140,
	CTEMetalSparks = 172,
	CSteamJet = 135,
	CSmokeStack = 128,
	DustTrail = 238,
	CFireTrail = 62,
	SporeTrail = 244,
	SporeExplosion = 243,
	RocketTrail = 241,
	SmokeTrail = 242,
	CPropVehicleDriveable = 117,
	ParticleSmokeGrenade = 240,
	CParticleFire = 96,
	MovieExplosion = 239,
	CTEGaussExplosion = 167,
	CEnvQuadraticBeam = 55,
	CEmbers = 45,
	CEnvWind = 59,
	CPrecipitation = 111,
	CPrecipitationBlocker = 112,
	CBaseTempEntity = 18,
	NextBotCombatCharacter = 0,
	CBaseAttributableItem = 4,
	CEconEntity = 44,
	CWeaponXM1014 = 236,
	CWeaponTaser = 231,
	CSmokeGrenade = 126,
	CWeaponSG552 = 228,
	CWeaponSawedoff = 224,
	CWeaponNOVA = 220,
	CIncendiaryGrenade = 85,
	CMolotovGrenade = 93,
	CWeaponM3 = 212,
	CKnifeGG = 90,
	CKnife = 89,
	CHEGrenade = 82,
	CFlashbang = 64,
	CWeaponElite = 203,
	CDecoyGrenade = 40,
	CDEagle = 39,
	CWeaponUSP = 235,
	CWeaponM249 = 211,
	CWeaponUMP45 = 234,
	CWeaponTMP = 233,
	CWeaponTec9 = 232,
	CWeaponSSG08 = 230,
	CWeaponSG556 = 229,
	CWeaponSG550 = 227,
	CWeaponScout = 226,
	CWeaponSCAR20 = 225,
	CSCAR17 = 122,
	CWeaponP90 = 223,
	CWeaponP250 = 222,
	CWeaponP228 = 221,
	CWeaponNegev = 219,
	CWeaponMP9 = 218,
	CWeaponMP7 = 217,
	CWeaponMP5Navy = 216,
	CWeaponMag7 = 215,
	CWeaponMAC10 = 214,
	CWeaponM4A1 = 213,
	CWeaponHKP2000 = 210,
	CWeaponGlock = 209,
	CWeaponGalilAR = 208,
	CWeaponGalil = 207,
	CWeaponG3SG1 = 206,
	CWeaponFiveSeven = 205,
	CWeaponFamas = 204,
	CWeaponBizon = 199,
	CWeaponAWP = 198,
	CWeaponAug = 197,
	CAK47 = 1,
	CWeaponCSBaseGun = 201,
	CWeaponCSBase = 200,
	CC4 = 29,
	CBaseCSGrenade = 8,
	CSmokeGrenadeProjectile = 127,
	CMolotovProjectile = 94,
	CDecoyProjectile = 41,
	CFireCrackerBlast = 60,
	CInferno = 86,
	CChicken = 31,
	CFootstepControl = 66,
	CCSGameRulesProxy = 34,
	CWeaponCubemap = 0,
	CWeaponCycler = 202,
	CTEPlantBomb = 176,
	CTEFireBullets = 163,
	CTERadioIcon = 180,
	CPlantedC4 = 105,
	CCSTeam = 38,
	CCSPlayerResource = 36,
	CCSPlayer = 35,
	CCSRagdoll = 37,
	CTEPlayerAnimEvent = 177,
	CHostage = 83,
	CHostageCarriableProp = 84,
	CBaseCSGrenadeProjectile = 9,
	CHandleTest = 81,
	CTeamplayRoundBasedRulesProxy = 139,
	CSpriteTrail = 133,
	CSpriteOriented = 132,
	CSprite = 131,
	CRagdollPropAttached = 120,
	CRagdollProp = 119,
	CPredictedViewModel = 113,
	CPoseController = 109,
	CGameRulesProxy = 80,
	CInfoLadderDismount = 87,
	CFuncLadder = 72,
	CTEFoundryHelpers = 166,
	CEnvDetailController = 51,
	CWorld = 237,
	CWaterLODControl = 196,
	CWaterBullet = 195,
	CVoteController = 194,
	CVGuiScreen = 193,
	CPropJeep = 116,
	CPropVehicleChoreoGeneric = 0,
	CTriggerSoundOperator = 192,
	CBaseVPhysicsTrigger = 22,
	CTriggerPlayerMovement = 191,
	CBaseTrigger = 20,
	CTest_ProxyToggle_Networkable = 188,
	CTesla = 183,
	CBaseTeamObjectiveResource = 17,
	CTeam = 138,
	CSunlightShadowControl = 137,
	CSun = 136,
	CParticlePerformanceMonitor = 97,
	CSpotlightEnd = 130,
	CSpatialEntity = 129,
	CSlideshowDisplay = 125,
	CShadowControl = 124,
	CSceneEntity = 123,
	CRopeKeyframe = 121,
	CRagdollManager = 118,
	CPhysicsPropMultiplayer = 102,
	CPhysBoxMultiplayer = 100,
	CPropDoorRotating = 115,
	CBasePropDoor = 16,
	CDynamicProp = 43,
	CProp_Hallucination = 114,
	CPostProcessController = 110,
	CPointCommentaryNode = 108,
	CPointCamera = 107,
	CPlayerResource = 106,
	CPlasma = 105,
	CPhysMagnet = 103,
	CPhysicsProp = 101,
	CStatueProp = 134,
	CPhysBox = 99,
	CParticleSystem = 98,
	CMovieDisplay = 95,
	CMaterialModifyControl = 92,
	CLightGlow = 91,
	CInfoOverlayAccessor = 88,
	CFuncTrackTrain = 79,
	CFuncSmokeVolume = 78,
	CFuncRotating = 77,
	CFuncReflectiveGlass = 76,
	CFuncOccluder = 75,
	CFuncMoveLinear = 74,
	CFuncMonitor = 73,
	CFunc_LOD = 68,
	CTEDust = 158,
	CFunc_Dust = 67,
	CFuncConveyor = 71,
	CFuncBrush = 70,
	CBreakableSurface = 28,
	CFuncAreaPortalWindow = 69,
	CFish = 63,
	CFireSmoke = 61,
	CEnvTonemapController = 58,
	CEnvScreenEffect = 56,
	CEnvScreenOverlay = 57,
	CEnvProjectedTexture = 54,
	CEnvParticleScript = 53,
	CFogController = 65,
	CEnvDOFController = 52,
	CCascadeLight = 30,
	CEnvAmbientLight = 50,
	CEntityParticleTrail = 49,
	CEntityFreezing = 48,
	CEntityFlame = 47,
	CEntityDissolve = 46,
	CEconWearable = 45,
	CDynamicLight = 42,
	CColorCorrectionVolume = 33,
	CColorCorrection = 32,
	CBreakableProp = 27,
	CBeamSpotlight = 25,
	CBaseButton = 5,
	CBaseToggle = 19,
	CBasePlayer = 15,
	CBaseFlex = 12,
	CBaseEntity = 11,
	CBaseDoor = 10,
	CBaseCombatCharacter = 6,
	CBaseAnimatingOverlay = 3,
	CBoneFollower = 26,
	CBaseAnimating = 2,
	CAI_BaseNPC = 0,
	CBeam = 24,
	CBaseViewModel = 21,
	CBaseParticleEntity = 14,
	CBaseGrenade = 13,
	CBaseCombatWeapon = 7,
	CBaseWeaponWorldModel = 23
};

class ICollideable
{
public:
	virtual void pad0();

	virtual const Vector& OBBMins() const;

	virtual const Vector& OBBMaxs() const;
};
