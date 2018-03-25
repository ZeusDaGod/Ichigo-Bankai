#include "stdafx.h"
#include "Tools/Hacks/Misc.h"

bool Unhook_Cheat = false;

auto ExitCheat() -> bool;

void Unhook()
{
	Unhook_Cheat = true;
}

bool ExitCheat()
{
	if( !Unhook_Cheat )
		return false;

	Interfaces.pEngine->ClientCmd_Unrestricted( "clear", 0 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "echo Ichigo has been unloaded successfully", 0 );

	Interfaces.pEngine->ClientCmd_Unrestricted( "cl_mouseenable 1", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "crosshair 1", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "firstperson", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "cl_drawhud 1", 0 );
	Sleep( 100 );

	if( Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() )
	{
		Misc::SetClanTag( "", Hacks.LocalPlayer->GetName().c_str() );
		Sleep( 100 );
	}

	Hacks.UnHook();
	Sleep( 200 );

	SetWindowLongPtr( INIT::Window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( INIT::OldWindow ) );
	Sleep( 200 );

	FreeLibraryAndExitThread( INIT::Dll, 0 );
}

#define DEBUG

DWORD WINAPI CheatMain( LPVOID lpThreadParameter )
{

#ifdef DEBUG

	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	SetConsoleTitle("Ichigo alpha debug");

#endif

	Interfaces.InitialiseSDK();
	
	CNetvarManager::Instance()->CreateDatabase();
	//CNetvarManager::Instance()->Dump("C:\\dab\\netvars.txt");
	
	Hacks.CallHooks();
	NetvarHook();
	
		unsigned int BuildNumber = Interfaces.pEngine->GetEngineBuildNumber();
		Interfaces.pEngine->ClientCmd_Unrestricted( "clear", 0 );
		cout << endl;
		cout << white << "ENGINE BUILD NUMBER: " << iaqua << BuildNumber << endl;
		Interfaces.pEngine->ClientCmd_Unrestricted( ( std::string( "echo ENGINE BUILD NUMBER:" ) + std::to_string( BuildNumber ) ).c_str(), 0 );
		Interfaces.pEngine->ClientCmd_Unrestricted( "echo Ichigo loaded successfully", 0 );
		
		Beep(658, 200);

		while( !Unhook_Cheat )
		{
//			Misc::ServerRankReveal();
			Sleep( 15 );
		}
		ExitCheat();
	
	return 0;
}
