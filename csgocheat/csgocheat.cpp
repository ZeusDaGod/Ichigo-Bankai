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
	Interfaces.pEngine->ClientCmd_Unrestricted( "echo FROSTY has been unloaded successfully", 0 );

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
//		Misc::SetClanTag( "", Hacks.LocalPlayer->GetName().c_str() );
		Sleep( 100 );
	}

	Hacks.UnHook();
	Sleep( 200 );

	SetWindowLongPtr( INIT::Window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( INIT::OldWindow ) );
	Sleep( 200 );

	FreeLibraryAndExitThread( INIT::Dll, 0 );
}

#define DEBUGLMAO

DWORD WINAPI CheatMain( LPVOID lpThreadParameter )
{

#ifdef DEBUGLMAO

	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	SetConsoleTitle("intercrime alhpa debug");
	

#endif

	Interfaces.InitialiseSDK();
	
	CNetvarManager::Instance()->CreateDatabase();
	//CNetvarManager::Instance()->Dump("C:\\dab\\netcucks.txt");
	
	Hacks.CallHooks();
	Knives();
	
		auto u = Interfaces.pEngine->GetEngineBuildNumber();
		Interfaces.pEngine->ClientCmd_Unrestricted( "clear", 0 );
		cout << endl;
		cout << white << "ENGINE BUILD NUMBER: " << iaqua << Interfaces.pEngine->GetEngineBuildNumber() << endl;
		Interfaces.pEngine->ClientCmd_Unrestricted( ( std::string( "echo ENGINE BUILD NUMBER:" ) + std::to_string( u ) ).c_str(), 0 );
		Interfaces.pEngine->ClientCmd_Unrestricted( "echo injection success!", 0 );
		
		Beep(658, 50);
		Beep(658, 50);
		Beep(658, 50);
		Beep(658, 50);
		Beep(658, 50);
		Beep(658, 50);
		Beep(658, 50);

		while( !Unhook_Cheat )
		{
//			Misc::ServerRankReveal();
			Sleep( 15 );
		}

	
	return 0;
}
