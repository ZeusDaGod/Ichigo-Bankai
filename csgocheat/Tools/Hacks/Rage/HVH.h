#pragma once
#include "../../stdafx.h"
#include "../Misc.h"
#include "Aimbot.h"
#include "../../Utils/LocalInfo.h"

class Fakelag
{
private:
	void Choke()
	{
		static int choked = 0;

		if (choked > 13)
			choked = 0;

		switch (ClientVars.FakeLag.ChokeMode)
		{
		case 0:
			ClientVars.AntiAim.enabled ? choked = ( Interfaces.pGlobalVars->tickcount % 2) : choked = 0;
			break;
		case 1:
			ClientVars.FakeLag.Choke <= choked ? choked = 0 : choked++;
			break;
		}

		Hacks.SendPacket = choked == 0;
		
	}
public:
	void Run(CInput::CUserCmd* cmd)
	{
		if (!ClientVars.FakeLag.Enabled && ClientVars.AntiAim.enabled)
		{
			Hacks.SendPacket = (Interfaces.pGlobalVars->tickcount % 2) == 1;
			return;
		}
		if (!ClientVars.FakeLag.WhileShooting && Misc::Shooting())
			return;
		if (!ClientVars.FakeLag.WhileStill && Hacks.LocalPlayer->GetVecVelocity().Length2D() == 0.f)
			return;
		if (!ClientVars.FakeLag.Onground && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
			return;

		Choke();
	}
} FakeLag;


class AntiAim
{
private:

public:
	void Run(CInput::CUserCmd* cmd)
	{
		if (!ClientVars.AntiAim.enabled)
			return;
		if (Misc::Shooting())
			return;
		if (cmd->buttons & IN_USE)
			return;
		if (Hacks.LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
			return;

	}
} AntiAim;
