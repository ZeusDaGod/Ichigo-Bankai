#pragma once
#include "../../stdafx.h"

struct backtrackData
{
	float simtime;
	Vector hitboxPos;
};

// pasted phook trash because im lazy and want to backtrack in prime

class Backtracking
{
private:
	backtrackData headPositions[64][12];

	Vector GetHitboxPosition(CBaseEntity* pEntity, int Hitbox)
	{
		matrix3x4 matrix[128];


		if (!pEntity->SetupBones(matrix, 128, 0x00000100, pEntity->GetSimulationTime()))
			return Vector(0, 0, 0);



		studiohdr_t* hdr = Interfaces.g_pModelInfo->GetStudioModel(pEntity->GetModel());
		mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

		mstudiobbox_t* hitbox = set->pHitbox(Hitbox);

		if (!hitbox)
			return Vector(0, 0, 0);

		Vector vMin, vMax, vCenter, sCenter;
		g_Math.VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
		g_Math.VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
		vCenter = (vMin + vMax) *0.5f;
		return vCenter;
	}

	inline float distance_point_to_line(Vector Point, Vector LineOrigin, Vector Dir)
	{
		auto PointDir = Point - LineOrigin;

		auto TempOffset = PointDir.Dot(Dir) / (Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
		if (TempOffset < 0.000001f)
			return FLT_MAX;

		auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

		return (Point - PerpendicularPoint).Length();
	}

public:
	void Run(CInput::CUserCmd* cmd)
	{
		if (!ClientVars.Legitbot.backtracking)
			return;
		
		int bestTargetIndex = -1;
		float bestFov = FLT_MAX;
		player_info_t info;


		for (int i = 1; i < Interfaces.pEngine->GetMaxClients(); i++)
		{
			CBaseEntity* entity = Interfaces.pEntList->GetClientEntity(i);

			if (entity == nullptr)
				continue;
			if (!entity->IsPlayer())
				continue;
			if (entity->GetTeam() == Hacks.LocalPlayer->GetTeam() && !ClientVars.Legitbot.teammates)
				continue;
			if (entity->IsDormant())
				continue;
			if (!entity->isAlive())
				continue;
			if (entity->HasGunGameImmunity())
				continue;

			float simtime = entity->GetSimulationTime();
			Vector hitboxPos = GetHitboxPosition(entity, 0);

			headPositions[i][cmd->command_number % 13] = backtrackData{ simtime, hitboxPos };
			Vector ViewDir;
			g_Math.angleVectors(cmd->viewangles + (Hacks.LocalPlayer->GetPunchAngle() * 2.f), ViewDir);
			float FOVDistance = distance_point_to_line(hitboxPos, Hacks.LocalPlayer->GetEyePosition(), ViewDir);

			if (bestFov > FOVDistance)
			{
				bestFov = FOVDistance;
				bestTargetIndex = i;
			}
			
		}

		float bestTargetSimTime = 0.f;
		if (bestTargetIndex != -1)
		{
			float tempFloat = FLT_MAX;
			Vector ViewDir;
			g_Math.angleVectors(cmd->viewangles + (Hacks.LocalPlayer->GetPunchAngle() * 2.f), ViewDir);

			for (int t = 0; t < 12; ++t)
			{
				float tempFOVDistance = distance_point_to_line(headPositions[bestTargetIndex][t].hitboxPos, Hacks.LocalPlayer->GetEyePosition(), ViewDir);

				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > Hacks.LocalPlayer->GetSimulationTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}
			if (bestTargetSimTime != 0.f)
				cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
		}
		
	}
}backtrack;