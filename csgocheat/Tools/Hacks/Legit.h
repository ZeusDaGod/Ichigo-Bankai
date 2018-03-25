#pragma once
#include "../../stdafx.h"
#include "../Utils/Hitbox.h"
#include "../Utils/Playerlist.h"
#include "../Utils/HitboxLists.h"

class Legitbot
{
private:

public:
	Vector Target;
	CBaseEntity* pTarget;
	Vector Angles;

	bool Aim(CInput::CUserCmd* cmd)
	{

	}
} Legitbot;

class Triggerbot
{
private:

public:
	void Run(CInput::CUserCmd* cmd)
	{

		if (!ClientVars.Triggerbot.Enabled || !GetAsyncKeyState(ClientVars.Triggerbot.Key))
			return;

		QAngle ViewAngles = cmd->viewangles + Hacks.LocalPlayer->GetPunchAngle();


		Vector CrosshairForward;
		g_Math.angleVectors(ViewAngles, CrosshairForward);
		CrosshairForward *= Hacks.LocalWeapon->GetCSWpnData()->GetRange();


		Vector TraceSource = Hacks.LocalPlayer->GetEyePosition();
		Vector TraceDestination = TraceSource + CrosshairForward;

		Ray_t Ray;
		trace_t Trace;
		CTraceFilter Filter;

		Filter.pSkip = Hacks.LocalPlayer;

		Ray.Init(TraceSource, TraceDestination);
		Interfaces.pTrace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

		if (!Trace.m_pEnt)
			return;
		if (!Trace.m_pEnt->isAlive())
			return;
		if (Trace.m_pEnt->HasGunGameImmunity())
			return;


		if (Hacks.LocalPlayer->GetTeam() == Trace.m_pEnt->GetTeam() && !ClientVars.Triggerbot.Teammates)
			return;

		bool didHit = false;
		if ((ClientVars.Triggerbot.Filter.Head && Trace.hitgroup == 1)
			|| (ClientVars.Triggerbot.Filter.Chest && Trace.hitgroup == 2)
			|| (ClientVars.Triggerbot.Filter.Stomach && Trace.hitgroup == 3)
			|| (ClientVars.Triggerbot.Filter.Arms && (Trace.hitgroup == 4 || Trace.hitgroup == 5))
			|| (ClientVars.Triggerbot.Filter.Legs && (Trace.hitgroup == 6 || Trace.hitgroup == 7)))
		{
			didHit = true;
		}


		if (didHit)
		{
			cmd->buttons |= IN_ATTACK;
		}
	}
}trigger;