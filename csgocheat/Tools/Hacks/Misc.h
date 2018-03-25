#pragma once
#include "stdafx.h"
#include <chrono>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

class Misc
{
	typedef bool ( __cdecl* ServerRankRevealAllFn)( float* );

public:
	static vec_t Normalize_y( vec_t ang )
	{
		while( ang < -180.0f )
			ang += 360.0f;
		while( ang > 180.0f )
			ang -= 360.0f;
		return ang;
	}

	static void  setName( const char* name )
	{
		auto namevar = Interfaces.g_ICVars->FindVar( "name" );
		*reinterpret_cast< int* >( reinterpret_cast< DWORD >( &namevar->fnChangeCallback ) + 0xC ) = NULL;
		namevar->SetValue( name );
	}

	static float GetFOV(Vector qAngles, Vector vecSource, Vector vecDestination, bool bDistanceBased)
	{
		auto MakeVector = [](Vector qAngles)
		{
			auto ret = Vector();
			auto pitch = float(qAngles[0] * M_PI / 180.f);
			auto yaw = float(qAngles[1] * M_PI / 180.f);
			auto tmp = float(cos(pitch));
			ret.x = float(-tmp * -cos(yaw));
			ret.y = float(sin(yaw)*tmp);
			ret.z = float(-sin(pitch));
			return ret;
		};

		Vector ang, aim;
		double fov;

		ang = g_Math.CalcAngle(vecSource, vecDestination);
		aim = MakeVector(qAngles);
		ang = MakeVector(ang);

		auto mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		auto mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		auto u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];

		fov = acos(u_dot_v / (mag_s*mag_d)) * (180.f / M_PI);

		if (bDistanceBased) {
			fov *= 1.4;
			float xDist = abs(vecSource[0] - vecDestination[0]);
			float yDist = abs(vecSource[1] - vecDestination[1]);
			float Distance = sqrt((xDist * xDist) + (yDist * yDist));

			Distance /= 650.f;

			if (Distance < 0.7f)
				Distance = 0.7f;

			if (Distance > 6.5)
				Distance = 6.5;

			fov *= Distance;
		}

		return (float)fov;
	}

	static void autoblock(CInput::CUserCmd* cmd)
	{
		if (!GetAsyncKeyState(ClientVars.Misc.autoblock))
			return;

		float bestdist = 250.f;
		int index = -1;

		for (int i = 1; i < Interfaces.pEngine->GetMaxClients(); i++)
		{
			CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity(i);

			if (!pEntity)
				continue;

			if (!pEntity->isAlive() || pEntity->IsDormant() || pEntity == Hacks.LocalPlayer)
				continue;

			float dist = Hacks.LocalPlayer->GetVecOrigin().DistTo(pEntity->GetVecOrigin());

			if (dist < bestdist)
			{
				Vector libtard = g_Math.CalcAngle(Hacks.LocalPlayer->GetVecOrigin(), pEntity->GetVecOrigin());

				libtard.y -= Hacks.LocalPlayer->GetEyeAngles().y;
				g_Math.Normalize2(libtard);

				if (libtard.y < 0.0f)
					cmd->sidemove = 450.f;

				else if (libtard.y > 0.0f)
					cmd->sidemove = -450.f;
			}
		}	
	}

	static void ServerRankReveal()
	{
		if( !Interfaces.pEngine->IsInGame() || !Interfaces.pEngine->IsConnected() )
			return;

		if( GetAsyncKeyState( VK_TAB ) == 0 )
			return;

		static float fArray[ 3 ] = { 0.f, 0.f, 0.f };

		static DWORD ServerRankReveal = ( DWORD )Utils.PatternSearch( "client.dll", ( PBYTE )"\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxx????x????", NULL, NULL );//Utils.PFindPattern( "client.dll", "55 8B EC 8B 0D ? ? ? ? 68 ? ? ? ? ");
		if( ServerRankReveal == 0 )
			ServerRankReveal = ( DWORD )Utils.PatternSearch( "client.dll", ( PBYTE )"\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxx????x????", NULL, NULL );//Utils.PFindPattern( "client.dll", "55 8B EC 8B 0D ? ? ? ? 68 ? ? ? ? ");

		if( ServerRankReveal != 0 )
		{
			Hacks.ServerRankRevealEx = ( ServerRankRevealAllFn )( ServerRankReveal );
			Hacks.ServerRankRevealEx( fArray );
		}
	}

	static void SetClanTag( const char* tag, const char* name )
	{
		static auto pSetClanTag = reinterpret_cast< void(__fastcall*)( const char*, const char* ) >( ( DWORD )( Utils.PFindPattern( "engine.dll", "53 56 57 8B DA 8B F9 FF 15" ) ) );
		pSetClanTag( tag, name );
	}

	static Vector RotatePoint(Vector EntityPos, Vector LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck)
	{
		float r_1, r_2;
		float x_1, y_1;

		r_1 = -(EntityPos.y - LocalPlayerPos.y);
		r_2 = EntityPos.x - LocalPlayerPos.x;
		float Yaw = angle - 90.0f;

		float yawToRadian = Yaw * (float)(M_PI / 180.0F);
		x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
		y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;

		*viewCheck = y_1 < 0;

		x_1 *= zoom;
		y_1 *= zoom;

		int sizX = sizeX / 2;
		int sizY = sizeY / 2;

		x_1 += sizX;
		y_1 += sizY;

		if (x_1 < 5)
			x_1 = 5;

		if (x_1 > sizeX - 5)
			x_1 = sizeX - 5;

		if (y_1 < 5)
			y_1 = 5;

		if (y_1 > sizeY - 5)
			y_1 = sizeY - 5;


		x_1 += posX;
		y_1 += posY;


		return Vector(x_1, y_1, 0);

	}

	static void CL_SendMove()
	{
		typedef void(__fastcall* CL_SendMoveFn)(void);
		static CL_SendMoveFn CL_SendMove = reinterpret_cast<CL_SendMoveFn>(Utils.PFindPattern("engine.dll", "55 8B EC A1 ?? ?? ?? ?? 81 EC ?? ?? ?? ?? B9 ?? ?? ?? ?? 53 8B 98"));

		CL_SendMove();
	}

	static void WriteUsercmd(void* buf, CInput::CUserCmd* in, CInput::CUserCmd* out)
	{
		typedef void(__fastcall* WriteUsercmdFn)(void*, CInput::CUserCmd*, CInput::CUserCmd*);
		static WriteUsercmdFn WriteUsercmd = reinterpret_cast<WriteUsercmdFn>(Utils.PFindPattern("client.dll", "55 8B EC 83 E4 F8 51 53 56 8B D9 8B 0D"));

		__asm
		{
			mov     ecx, buf
			mov     edx, in
			push    out
			call    WriteUsercmd
			add     esp, 4
		}
	}

	static std::vector<Vector> GetMultiplePointsForHitbox(CBaseEntity* pBaseEntity, int iHitbox, matrix3x4 BoneMatrix[128])
	{
		auto VectorTransform_Wrapper = [](const Vector& in1, const matrix3x4 &in2, Vector &out)
		{
			auto VectorTransform = [](const float *in1, const matrix3x4& in2, float *out)
			{
				auto DotProducts = [](const float *v1, const float *v2)
				{
					return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
				};
				out[0] = DotProducts(in1, in2[0]) + in2[0][3];
				out[1] = DotProducts(in1, in2[1]) + in2[1][3];
				out[2] = DotProducts(in1, in2[2]) + in2[2][3];
			};
			VectorTransform(&in1.x, in2, &out.x);
		};

		studiohdr_t* pStudioModel = Interfaces.g_pModelInfo->GetStudioModel(pBaseEntity->GetModel());
		mstudiohitboxset_t* set = pStudioModel->GetHitboxSet(0);
		mstudiobbox_t *hitbox = set->pHitbox(iHitbox);

		std::vector<Vector> vecArray;

		Vector max;
		Vector min;
		VectorTransform_Wrapper(hitbox->bbmax, BoneMatrix[hitbox->bone], max);
		VectorTransform_Wrapper(hitbox->bbmin, BoneMatrix[hitbox->bone], min);

		auto center = (min + max) * 0.5f;

		QAngle CurrentAngles = g_Math.CalcAngle(center, Hacks.LocalPlayer->GetEyePosition());

		Vector Forward;
		g_Math.angleVectors(CurrentAngles, Forward);

		Vector Right = Forward.Cross(Vector(0, 0, 1));
		Vector Left = Vector(-Right.x, -Right.y, Right.z);

		Vector Top = Vector(0, 0, 1);
		Vector Bot = Vector(0, 0, -1);

		switch (iHitbox) {
		case (int)CSGOHitboxID::Head:
			for (auto i = 0; i < 4; ++i)
			{
				vecArray.emplace_back(center);
			}
			vecArray[1] += Top * (hitbox->radius * ClientVars.Ragebot.Headscale);
			vecArray[2] += Right * (hitbox->radius * ClientVars.Ragebot.Headscale);
			vecArray[3] += Left * (hitbox->radius * ClientVars.Ragebot.Headscale);
			break;

		default:

			for (auto i = 0; i < 3; ++i)
			{
				vecArray.emplace_back(center);
			}
			vecArray[1] += Right * (hitbox->radius * ClientVars.Ragebot.Bodyscale);
			vecArray[2] += Left * (hitbox->radius * ClientVars.Ragebot.Bodyscale);
			break;
		}
		return vecArray;
	}

	static void AnimCT()
	{
		if (!ClientVars.Misc.AnimClantag)
			return;

		static int counter = 0;
		static int motion = 0;
		int ServerTime = (float)Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick * 2.5;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 13;
		switch (value) {
		case  0: Misc::SetClanTag(u8"      \u30A4\u30C1\u30B4", u8"\u30A4\u30C1\u30B4"); break;
		case  1: Misc::SetClanTag(u8"     \u30A4\u30C1\u30B4 ", u8"\u30A4\u30C1\u30B4"); break;
		case  2: Misc::SetClanTag(u8"    \u30A4\u30C1\u30B4  ", u8"\u30A4\u30C1\u30B4"); break;
		case  3: Misc::SetClanTag(u8"   \u30A4\u30C1\u30B4   ", u8"\u30A4\u30C1\u30B4"); break;
		case  4: Misc::SetClanTag(u8"  \u30A4\u30C1\u30B4    ", u8"\u30A4\u30C1\u30B4"); break;
		case  5: Misc::SetClanTag(u8" \u30A4\u30C1\u30B4     ", u8"\u30A4\u30C1\u30B4"); break;
		case  6: Misc::SetClanTag(u8"\u30A4\u30C1\u30B4      ", u8"\u30A4\u30C1\u30B4"); break;
		case  7: Misc::SetClanTag(u8" \u30A4\u30C1\u30B4     ", u8"\u30A4\u30C1\u30B4"); break;
		case  8: Misc::SetClanTag(u8"  \u30A4\u30C1\u30B4    ", u8"\u30A4\u30C1\u30B4"); break;
		case  9: Misc::SetClanTag(u8"   \u30A4\u30C1\u30B4   ", u8"\u30A4\u30C1\u30B4"); break;
		case 10: Misc::SetClanTag(u8"    \u30A4\u30C1\u30B4  ", u8"\u30A4\u30C1\u30B4"); break;
		case 11: Misc::SetClanTag(u8"     \u30A4\u30C1\u30B4 ", u8"\u30A4\u30C1\u30B4"); break;
		case 12: Misc::SetClanTag(u8"      \u30A4\u30C1\u30B4", u8"\u30A4\u30C1\u30B4"); break;

		}
		counter++;
	}

	static int TIME_TO_TICKS( int dt )
	{
		return ( int )( 0.5f + ( float )( dt ) / Interfaces.pGlobalVars->interval_per_tick );
	}

	static float GetNetworkLatency()
	{
		INetChannelInfo* nci = Interfaces.pEngine->GetNetChannelInfo();
		if( nci )
		{
			return nci->GetAvgLatency( FLOW_OUTGOING );
		}
		return 0.0f;
	}

	static void Nightmode()
	{
		static bool checked = false;
		static string OGSKy = "";
		if (!(Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected()))
			return;

		if (!checked && ClientVars.Visual.nightmode)
		{
			ConVar* sky = Interfaces.g_ICVars->FindVar("sv_skyname");
			//OGSKy = sky->GetString(); crashes because idk the index for the setstring vfunc
			sky->SetValue("sky_csgo_night02");

			ConVar* staticprop = Interfaces.g_ICVars->FindVar("r_DrawSpecificStaticProp");
			staticprop->SetValue(0);

			for (MaterialHandle_t i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
			{
				IMaterial *pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				if (strstr(pMaterial->GetTextureGroupName(), "World")) {
					pMaterial->ColorModulate(0.1f, 0.1f, 0.1f);
				}
				if (strstr(pMaterial->GetTextureGroupName(), "StaticProp")) {
					pMaterial->ColorModulate(0.3f, 0.3f, 0.3f);
				}
				if (strstr(pMaterial->GetTextureGroupName(), "Model")) {
					pMaterial->ColorModulate(0.6f, 0.6f, 0.6f);
				}
			}
			checked = true;
		}

		if (checked && !ClientVars.Visual.nightmode)
		{
			ConVar* sky = Interfaces.g_ICVars->FindVar("sv_skyname");
			//sky->SetValue(OGSKy.c_str()); this is where id set it to the original sky IF I COULD GET IT

			ConVar* staticprop = Interfaces.g_ICVars->FindVar("r_DrawSpecificStaticProp");
			staticprop->SetValue(1);

			for (MaterialHandle_t i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
			{
				IMaterial *pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				if (strstr(pMaterial->GetTextureGroupName(), "World")) {
					pMaterial->ColorModulate(1.f, 1.f, 1.f);
				}
				if (strstr(pMaterial->GetTextureGroupName(), "StaticProp")) {
					pMaterial->ColorModulate(1.f, 1.f, 1.f);
				}
				if (strstr(pMaterial->GetTextureGroupName(), "Model")) {
					pMaterial->ColorModulate(1.f, 1.f, 1.f);
				}
			}
			checked = false;
		}

	}

	static double GetNumberOfTicksChoked( CBaseEntity* pEntity )
	{
		double flSimulationTime = pEntity->GetSimulationTime();
		double flSimDiff = ( ( double )Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick ) - flSimulationTime;
		return TIME_TO_TICKS( max(0.0f, flSimDiff) );
	}

	static bool Shooting()
	{
		if( Hacks.LocalWeapon->IsKnife() )
		{
			if( Hacks.CurrentCmd->buttons & IN_ATTACK || Hacks.CurrentCmd->buttons & IN_ATTACK2 )
				return true;
		}
		else if( Hacks.LocalWeapon->IsNade() )
		{
			CBaseCSGrenade* csGrenade = ( CBaseCSGrenade* )Hacks.LocalWeapon;
			if( csGrenade->GetThrowTime() > 0.f )
			{
				return true;
			}
		}
		else if( Hacks.CurrentCmd->buttons & IN_ATTACK && bullettime() )
		{
			if( *Hacks.LocalWeapon->GetItemDefinitionIndex() == weapon_revolver && ClientVars.Ragebot.Enable )
			{
				if( Hacks.LocalWeapon->GetPostponeFireReadyTime() - GetServerTime() <= 0.05f )
				{
					return true;
				}
			}
			else
				return true;
		}
		return false;
	}

	static bool CanShoot(CBaseEntity* pLocalPlayer, CBaseCombatWeapon* weapon)
	{
		if (!weapon)
			return false;

		if (weapon->ammo() < 1)
			return false;

		float server_time = Misc::GetServerTime() * Interfaces.pGlobalVars->interval_per_tick;

		float next_shot = weapon->NextPrimaryAttack() - server_time;
		if (next_shot > 0)
			return false;

		return true;
	}

	static char* GetGunNameByID(int weaponid)
	{
		int WeaponId = weaponid;
		switch (WeaponId)
		{
		case WEAPON_AK47:
			return "AK47";
			break;
		case WEAPON_AUG:
			return "AUG";
			break;
		case weapon_revolver:
			return "Revolver";
			break;
		case WEAPON_AWP:
			return "AWP";
			break;
		case WEAPON_BIZON:
			return "Bizon";
			break;
		case WEAPON_C4:
			return "Bomb";
			break;
		case WEAPON_CZ75A:
			return "CZ75";
			break;
		case WEAPON_DEAGLE:
			return "Deagle";
			break;
		case WEAPON_DECOY:
			return "Decoy";
			break;
		case WEAPON_ELITE:
			return "Elites";
			break;
		case WEAPON_FAMAS:
			return "Famas";
			break;
		case WEAPON_FIVESEVEN:
			return "FiveSeven";
			break;
		case WEAPON_FLASHBANG:
			return "Flash";
			break;
		case WEAPON_G3SG1:
			return "G3SG1";
			break;
		case WEAPON_GALILAR:
			return "Galil";
			break;
		case WEAPON_GLOCK:
			return "Glock";
			break;
		case WEAPON_INCGRENADE:
			return "Molotov";
			break;
		case WEAPON_MOLOTOV:
			return "Molotov";
			break;
		case WEAPON_SSG08:
			return "Scout";
			break;
		case WEAPON_HEGRENADE:
			return "Grenade";
			break;
		case WEAPON_M249:
			return "M249";
			break;
		case WEAPON_M4A1:
			return "M4A1";
			break;
		case WEAPON_MAC10:
			return "MAC10";
			break;
		case WEAPON_MAG7:
			return "MAG7";
			break;
		case WEAPON_MP7:
			return "MP7";
			break;
		case WEAPON_MP9:
			return "MP9";
			break;
		case WEAPON_NOVA:
			return "Nova";
			break;
		case WEAPON_NEGEV:
			return "Negev";
			break;
		case WEAPON_P250:
			return "P250";
			break;
		case WEAPON_P90:
			return "P90";
			break;
		case WEAPON_SAWEDOFF:
			return "SawedOff";
			break;
		case WEAPON_SCAR20:
			return "SCAR20";
			break;
		case WEAPON_SMOKEGRENADE:
			return "Smoke";
			break;
		case WEAPON_SG556:
			return "SG556";
			break;
		case WEAPON_TEC9:
			return "TEC9";
			break;
		case WEAPON_HKP2000:
			return "P2000";
			break;
		case WEAPON_USP_SILENCER:
			return "USP";
			break;
		case WEAPON_UMP45:
			return "UMP";
			break;
		case WEAPON_XM1014:
			return "XM1014";
			break;
		case WEAPON_TASER:
			return "Zeus";
			break;
		case WEAPON_M4A1_SILENCER:
			return "M4A1-S";
			break;
		case WEAPON_KNIFE_T:
		case WEAPON_KNIFE_BAYONET:
		case WEAPON_KNIFE_FLIP:
		case WEAPON_KNIFE_GUT:
		case WEAPON_KNIFE_KARAMBIT:
		case WEAPON_KNIFE_M9_BAYONET:
		case WEAPON_KNIFE_TACTICAL:
		case WEAPON_KNIFE_FALCHION:
		case WEAPON_KNIFE_BOWIE:
		case WEAPON_KNIFE_BUTTERFLY:
		case WEAPON_KNIFE_PUSH:
			return "Knife";
		}
		return "";
	}

	static Vector Normalize( Vector& angs )
	{
		while( angs.y < -180.0f )
			angs.y += 360.0f;
		while( angs.y > 180.0f )
			angs.y -= 360.0f;
		if( angs.x > 89.0f )
			angs.x = 89.0f;
		if( angs.x < -89.0f )
			angs.x = -89.0f;
		angs.z = 0;
		return angs;
	}

	static bool AimStep( Vector angSource, Vector& angDestination )
	{
		Vector angDelta = Normalize( angDestination - angSource );
		if( angDelta.Abs() > 40.f )
		{
			angDestination = Normalize( angSource + angDelta / angDelta.Abs() * 40.f );
			return false;
		}
		return true;
	}

	static float GetServerTime()
	{
		return ( float )Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
	}

	static bool bullettime()
	{
		if( !Hacks.LocalWeapon )
			return false;
		float flNextPrimaryAttack = Hacks.LocalWeapon->NextPrimaryAttack();

		return flNextPrimaryAttack <= GetServerTime();
	}

	static void MoveFix( CInput::CUserCmd* cmd, Vector& realvec )
	{
		Vector vMove( cmd->forwardmove, cmd->sidemove, cmd->upmove );
		float flSpeed = sqrt( vMove.x * vMove.x + vMove.y * vMove.y ), flYaw;
		Vector vMove2;
		g_Math.vectorAnglesVec( vMove, vMove2 );
		Normalize( vMove2 );
		flYaw = DEG2RAD(cmd->viewangles.y - realvec.y + vMove2.y);
		cmd->forwardmove = cos( flYaw ) * flSpeed;
		cmd->sidemove = sin( flYaw ) * flSpeed;
		if( 90 < abs( cmd->viewangles.x ) && 180 > abs( cmd->viewangles.x ) )
			cmd->forwardmove *= -1;
	}

	static void CalcAngle( Vector src, Vector dst, Vector& angles )
	{
		Vector delta = src - dst;
		double hyp = delta.Length2D();
		angles.y = atan( delta.y / delta.x ) * 57.295779513082f;
		angles.x = atan( delta.z / hyp ) * 57.295779513082f;
		if( delta.x >= 0.0 )
			angles.y += 180.0f;
		angles.z = 0;
	}

	static Vector CalcAngle2(Vector src, Vector dst, Vector& angles)
	{
		Vector delta = src - dst;
		double hyp = delta.Length();
		angles.y = atan(delta.y / delta.x) * 57.295779513082f;
		angles.x = atan(delta.z / hyp) * 57.295779513082f;
		if (delta.x >= 0.0)
			angles.y += 180.0f;
		angles.z = 0;
		return angles;
	}

	static Vector CalcAngle3(const Vector& in, Vector out)
	{
		double delta[3] = { (in[0] - out[0]), (in[1] - out[1]), (in[2] - out[2]) };
		double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
		Vector ret = Vector();
		ret.x = (float)(asinf(delta[2] / hyp) * 57.295779513082f);
		ret.y = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
		ret.z = 0.0f;

		if (delta[0] >= 0.0)
			ret.y += 180.0f;
		return ret;
	}

	static int FovTo( Vector From, Vector To )
	{
		From -= To;
		Normalize( From );
		return ( abs( From.y ) + abs( From.x ) );
	}
};
