#pragma once
#include <vector>
#include <algorithm>
#include "stdafx.h"
#include "resource.h"
#include "SDK/SDK Headers/CGameEvent.h"

int __fastcall Hooked_SendDatagram(INetChannel* netchan, void*, bf_write* datagram);

void __fastcall Hooked_Createmove( CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active );

void __stdcall Hooked_PaintTraverse( unsigned int vguiPanel, bool forceRepaint, bool allowForce );

void __stdcall Hooked_Frame_Stage_Notify( ClientFrameStage_t curStage );

extern void RecvProxyViewModel(CRecvProxyData* pData, void* pStruct, void* pOut);

float __fastcall hkGetViewModelFOV(void* ecx, void* edx);

void __stdcall Hooked_OverrideView( CViewSetup* pSetup );

LRESULT __stdcall Hooked_WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

void __fastcall Hooked_DrawModelExecute( void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld );

void __stdcall Hooked_ClientCmdUnrestricted( const char* szCmdString, char flag );

void __stdcall Hooked_PlaySound( const char* pSample );

HRESULT __stdcall hkEndScene(IDirect3DDevice9* thisptr);

HRESULT __stdcall hkReset(IDirect3DDevice9* thisptr, D3DPRESENT_PARAMETERS* pPresentationParameters);

int __stdcall Hook_EmitSound1(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM, const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1);

int __stdcall Hook_EmitSound2(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, float flAttenuation, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM, const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1);

bool __fastcall WriteUsercmdDeltaToBuffer_hook(void* ecx, void* edx, int nSlot, void* buf, int from, int to, bool isNewCmd);

MDLHandle_t __fastcall FindMDL(void*, void*, char*);

int  __stdcall Hooked_DoPostScreenEffects(int a1);

void GUI_Init(IDirect3DDevice9* thisptr);

IMaterial* Create_Material(bool Ignore, bool Lit, bool Wireframe);

void Init();
void NetvarHook();

void DrawBeam(Vector src, Vector end, CColor color);

extern VTHookManager VMTClientMode;
extern VTHookManager VMTGameEvent;

struct SoundLog;

extern vector<SoundLog> SoundLogs;

class FontsXD
{
public:
	ImFont* tahoma = nullptr;
	ImFont* impact = nullptr;
	ImFont* icons = nullptr;
};

class CHackManager
{
private:
	/* Typedefs */
	typedef void (__thiscall *iPaintTraverse)( void*, unsigned int, bool, bool );

	typedef void (__stdcall *iCreateMoveFn)( CInput*, void*, int, float, bool );

	typedef void (__stdcall *iFrameStageNotifyFn)( ClientFrameStage_t );

	typedef void (__stdcall *iOverRideViewFn)( CViewSetup* );

	typedef float( __thiscall *get_fovFn)(void*);

	typedef void (__thiscall* IDrawModelExecute)( void*, void*, void*, const ModelRenderInfo_t&, matrix3x4* );

	typedef void (__stdcall* ClientCmdUnresticted)( const char* szCmdString, char flag );

	typedef bool ( __cdecl* ServerRankRevealAllFn)( float* );

	typedef int(__thiscall* DoPostScreenEffects)(IClientModeShared*, int);

	typedef void ( __stdcall* PlaySoundFn )( const char* pSample );

	typedef void ( __stdcall* IsReadyFn )();

	typedef void(__stdcall* EndSceneFn)(IDirect3DDevice9*);

	typedef void(__stdcall* ResetFn)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

	typedef int(__stdcall* Emit1)(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags, int iPitch, const Vector *pOrigin, const Vector *pDirection, CUtlVector< Vector >* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity);

	typedef int (__stdcall* Emit2)(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const Vector *pOrigin, const Vector *pDirection, CUtlVector< Vector >* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity);
	
	typedef bool(__thiscall* WriteUsercmdDeltaToBufferFn)(void* ecx, int nSlot, void* buf, int from, int to, bool isNewCmd);

	typedef MDLHandle_t (__fastcall* iFindMdl)(void*, void*, char*);
	

public:
	std::vector<IGameEventListener2*> listeners = {};

	typedef int(__thiscall* SendDatagramFn)(INetChannel*, bf_write*);

	/* Original Functions */
	DWORD oCreateMove;
	iPaintTraverse oPaintTraverse;
	iFrameStageNotifyFn oFrameStageNotify;
	IDrawModelExecute oDrawModelExecute;
	iOverRideViewFn oOverrideView;
	get_fovFn oGetFOV;
	ClientCmdUnresticted oClientCmdUnresticted;
	PlaySoundFn oPlaySound;
	ServerRankRevealAllFn ServerRankRevealEx;
	DoPostScreenEffects oDoPostScreenEffects;
	SendDatagramFn oSendDatagram;
	IsReadyFn IsReadyEx;
	EndSceneFn oEndScene;
	ResetFn oReset;
	Emit1 oEmit1;
	Emit2 oEmit2;
	WriteUsercmdDeltaToBufferFn oWriteUsercmdDeltaToBuffer;
	iFindMdl oFindMDL;

	/* Holding Varialbles */
	CInput::CUserCmd* CurrentCmd;
	CBaseEntity* LocalPlayer;
	CBaseCombatWeapon* LocalWeapon;
	Vector LastFakeAngles;
	Vector LastRealAngles;
	bool SendPacket = true;
	float FOV;
	float VFOV;

	IMaterial* mat_Lit;
	IMaterial* mat_Flat;
	IMaterial* mat_Wire;
	IMaterial* mat_Glass;
	IMaterial* mat_Gold;
	IMaterial* mat_Plat;
	IMaterial* mat_Crystal;

	DWORD Font_ESP;
	DWORD Font_Health;
	
	void MakeFonts()
	{
		Font_ESP = Interfaces.pSurface->Create_Font();
		Font_Health = Interfaces.pSurface->Create_Font();

		Interfaces.pSurface->SetFontGlyphSet(Font_ESP, "Courier New", 14, FW_DONTCARE, 0, 0, FONTFLAG_OUTLINE);
		Interfaces.pSurface->SetFontGlyphSet(Font_Health, "Smallest Pixel-7", 10, FW_DONTCARE, 0, 0, FONTFLAG_OUTLINE);
	}

	/* Hooking */
	void CallHooks()
	{
		MakeFonts();

		cout << endl;
		cout << iaqua << "Hooks:" << endl;

		// Hooks
		if( Interfaces.pClient )
		{
			VMTClient.bInitialize( reinterpret_cast< DWORD** >( Interfaces.pClient ) );
			oCreateMove = VMTClient.dwHookMethod( reinterpret_cast< DWORD >( &Hooked_Createmove ), 21 );
			cout << white << "Create Move, Hooked <21>:" << iaqua << " 0x" << oCreateMove << " ( " << white << "oCreateMove" << iaqua << " )" << white << endl;
			oFrameStageNotify = reinterpret_cast< iFrameStageNotifyFn >( VMTClient.dwHookMethod( reinterpret_cast< DWORD >( &Hooked_Frame_Stage_Notify ), 36 ) );
			cout << white << "Frame Stage Notfiy, Hooked <36>:" << iaqua << " 0x" << oFrameStageNotify << " ( " << white << "oFrameStageNotify" << iaqua << " )" << white << endl;
		}

		if( Interfaces.pEngine )
		{
			VMTEngine.bInitialize( reinterpret_cast< DWORD** >( Interfaces.pEngine ) );
			oClientCmdUnresticted = reinterpret_cast< ClientCmdUnresticted >( VMTEngine.dwHookMethod( reinterpret_cast< DWORD >( &Hooked_ClientCmdUnrestricted ), 114 ) );
			cout << white << "Client Command, Hooked <114>:" << iaqua << " 0x" << oClientCmdUnresticted << " ( " << white << "oClientCmdUnresticted" << iaqua << " )" << white << endl;
		}

		if( Interfaces.pPanel )
		{
			VMTPanel.bInitialize( reinterpret_cast< unsigned long** >( Interfaces.pPanel ) );
			oPaintTraverse = reinterpret_cast< iPaintTraverse >( VMTPanel.dwHookMethod( reinterpret_cast< DWORD >( &Hooked_PaintTraverse ), 41 ) );
			cout << white << "Paint Traverse, Hooked <41>:" << iaqua << " 0x" << oPaintTraverse << " ( " << white << "oPaintTraverse" << iaqua << " )" << white << endl;
		}

		if( Interfaces.g_pModelRender )
		{
			VMTModelRender.bInitialize( reinterpret_cast< DWORD** >( Interfaces.g_pModelRender ) );
			oDrawModelExecute = reinterpret_cast< IDrawModelExecute >( VMTModelRender.dwHookMethod( reinterpret_cast< DWORD >( &Hooked_DrawModelExecute ), 21 ) );
			cout << white << "Draw Model Execute, Hooked <21>:" << iaqua << " 0x" << oDrawModelExecute << " ( " << white << "oDrawModelExecute" << iaqua << " )" << white << endl;
		}

		if( Interfaces.pClientMode )
		{
			VMTClientMode.bInitialize( reinterpret_cast< DWORD** >( Interfaces.pClientMode ) );
			oOverrideView = reinterpret_cast< iOverRideViewFn >( VMTClientMode.dwHookMethod( reinterpret_cast< DWORD >( &Hooked_OverrideView ), 18 ) );
			cout << white << "Override View, Hooked <18>:" << iaqua << " 0x" << oOverrideView << " ( " << white << "oOverrideView" << iaqua << " )" << white << endl;
			oGetFOV = reinterpret_cast< get_fovFn >(VMTClientMode.dwHookMethod(reinterpret_cast< DWORD >(&hkGetViewModelFOV), 35));
			cout << white << "Get View Fov, Hooked <18>:" << iaqua << " 0x" << oGetFOV << " ( " << white << "oGetFOV" << iaqua << " )" << white << endl;
			oDoPostScreenEffects = reinterpret_cast<DoPostScreenEffects>(VMTClientMode.dwHookMethod(reinterpret_cast<DWORD>(&Hooked_DoPostScreenEffects), 44));
			cout << white << "DoPostScreenEffects, Hooked <44>:" << iaqua << " 0x" << oDoPostScreenEffects << " ( " << white << "oDoPostScreenEffects" << iaqua << " )" << white << endl;
		}

		if (Interfaces.pMDL)
		{
			VMTMDL.bInitialize((DWORD**)Interfaces.pMDL);
			oFindMDL = (iFindMdl)VMTMDL.dwHookMethod((DWORD)&FindMDL, 10);
			cout << white << "FindMDL, Hooked <10>:" << iaqua << " 0x" << oFindMDL << " ( " << white << "oFindMDL" << iaqua << " )" << white << endl;
		}

		if( Interfaces.pSurface )
		{
			VMTSurface.bInitialize( ( DWORD** )Interfaces.pSurface );
			oPlaySound = ( PlaySoundFn )VMTSurface.dwHookMethod( ( DWORD )&Hooked_PlaySound, 82 );
			cout << white << "Play Sound, Hooked <82>:" << iaqua << " 0x" << oPlaySound << " ( " << white << "oPlaySound" << iaqua << " )" << white << endl;
		}

		while( !( INIT::Window = FindWindowA( "Valve001", nullptr ) ) )
			Sleep( 100 );
		if( INIT::Window )
			INIT::OldWindow = ( WNDPROC )SetWindowLongPtr( INIT::Window, GWL_WNDPROC, ( LONG_PTR )Hooked_WndProc );

		if (Interfaces.d3d_device)
		{
			VMTD3D.bInitialize(reinterpret_cast<DWORD**>(Interfaces.d3d_device));
			oEndScene = (EndSceneFn)VMTD3D.dwHookMethod((DWORD)&hkEndScene, 42);
			cout << white << "EndScene, Hooked <42>:" << iaqua << " 0x" << oEndScene << " ( " << white << "oEndScene" << iaqua << " )" << white << endl;
		}

		if (Interfaces.d3d_device)
		{
			VMTD3D.bInitialize(reinterpret_cast<DWORD**>(Interfaces.d3d_device));
			oReset = (ResetFn)VMTD3D.dwHookMethod((DWORD)&hkReset, 16);
			cout << white << "Reset, Hooked <16>:" << iaqua << " 0x" << oReset << " ( " << white << "oReset" << iaqua << " )" << white << endl;
		}
		if (Interfaces.pSound)
		{
			VMTSOUND.bInitialize(reinterpret_cast<DWORD**>(Interfaces.pSound));
			oEmit1 = (Emit1)VMTSOUND.dwHookMethod((DWORD)&Hook_EmitSound1, 5);
			cout << white << "EmitSound1, Hooked <5>:" << iaqua << " 0x" << oEmit1 << " ( " << white << "oEmit1" << iaqua << " )" << white << endl;
			oEmit2 = (Emit2)VMTSOUND.dwHookMethod((DWORD)&Hook_EmitSound2, 6);
			cout << white << "EmitSound2, Hooked <6>:" << iaqua << " 0x" << oEmit2 << " ( " << white << "oEmit2" << iaqua << " )" << white << endl;
		}
		if (Interfaces.g_CHLClient)
		{
			VMTSendMove.bInitialize(reinterpret_cast<DWORD**>(Interfaces.g_CHLClient));
			oWriteUsercmdDeltaToBuffer = (WriteUsercmdDeltaToBufferFn)VMTSendMove.dwHookMethod((DWORD)&WriteUsercmdDeltaToBuffer_hook, 23);
			cout << white << "WriteUsercmdDeltaToBuffer, Hooked <23>:" << iaqua << " 0x" << oWriteUsercmdDeltaToBuffer << " ( " << white << "oWriteUsercmdDeltaToBuffer" << iaqua << " )" << white << endl;
		}

		Init();

		MakeMaterials();
	}

	void MakeMaterials()
	{
		mat_Lit = Create_Material(false, true, false);
		mat_Flat = Create_Material(false, false, false);
		mat_Wire = Create_Material(false, false, true);
		mat_Glass = Interfaces.pMaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", nullptr);
		mat_Gold = Interfaces.pMaterialSystem->FindMaterial("models/inventory_items/trophy_majors/gold", nullptr);
		mat_Plat = Interfaces.pMaterialSystem->FindMaterial("models/player/ct_fbi/ct_fbi_glass", nullptr);
		mat_Crystal = Interfaces.pMaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", nullptr);
	}

	void UnHook()
	{
		VMTClient.UnHook();
		Sleep( 150 );
		VMTClientMode.UnHook();
		Sleep( 150 );
		VMTEngine.UnHook();
		Sleep( 150 );
		VMTModelRender.UnHook();
		Sleep( 150 );
		VMTPanel.UnHook();
		Sleep( 150 );
		VMTGameEvent.UnHook();
		Sleep( 150 );
		VMTSurface.UnHook();
		Sleep( 150 );
		VMTD3D.UnHook();
		Sleep( 150 );
	}
};
