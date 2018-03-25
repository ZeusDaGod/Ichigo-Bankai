#pragma once
#include "../../../stdafx.h"
#include "../../Utils/Hitbox.h"
#include "../../Utils/Playerlist.h"
#include "../../Utils/HitboxLists.h"


#define TICK_INTERVAL			( Interfaces.pGlobalVars->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL *( t ) )

template<class T, class U>
inline T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}

class Ragebot
{
private:

	int target_index = -1;
	float best_distance = 8192.f;
	bool aimbotted_in_current_tick;
	bool fired_in_that_tick;
	float current_aim_simulationtime;
	int current_minusticks;
	Vector current_aim_position;
	Vector current_aim_player_origin;
	Vector Angles;

	static bool LineGoesThroughSmoke(Vector pos1, Vector pos2) throw()
	{
		typedef bool(*LineGoesThroughSmokeFn)(float, float, float, float, float, float, short);

		LineGoesThroughSmokeFn LineGoesThroughSmokeEx;
		LineGoesThroughSmokeEx = (LineGoesThroughSmokeFn)(Utils.PFindPattern("client.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0"));
		return LineGoesThroughSmokeEx(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, 1);
	}

	static bool IsVisible(Vector& vecAbsStart, Vector& vecAbsEnd, CBaseEntity* pLocal, CBaseEntity* pBaseEnt, bool smokeCheck) throw()
	{
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;

		filter.pSkip = pLocal;

		ray.Init(vecAbsStart, vecAbsEnd);

		Interfaces.pTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

		bool visible = (tr.m_pEnt == pBaseEnt || tr.fraction >= 0.96f);

		if (visible && smokeCheck)
			visible = !LineGoesThroughSmoke(vecAbsStart, vecAbsEnd);

		return visible;
	}

	std::vector<Vector> MainHitbox(CBaseEntity* pTarget, matrix3x4 BoneMatrix[128])
	{
		std::vector<Vector> Points;
		int Aimspot = ClientVars.Ragebot.Hitbox;

		switch (Aimspot) {
		case 0:
			Points = Misc::GetMultiplePointsForHitbox(pTarget, 0, BoneMatrix);
			break;
		case 1:
			Points = Misc::GetMultiplePointsForHitbox(pTarget, 1, BoneMatrix);
			break;
		case 2:
			Points = Misc::GetMultiplePointsForHitbox(pTarget, 6, BoneMatrix);
			break;
		case 3:
			Points = Misc::GetMultiplePointsForHitbox(pTarget, 3, BoneMatrix);//pelvis
			break;
		case 4:
			Points = Misc::GetMultiplePointsForHitbox(pTarget, 4, BoneMatrix);//stomach
			break;
		case 5:
			Points = Misc::GetMultiplePointsForHitbox(pTarget, 0, BoneMatrix);
			break;
		}
		return Points;
	}

	std::vector<int> GetHitboxesToScan(CBaseEntity* pTarget)
	{
		std::vector<int> HitBoxesToScan;
		int HitScanMode = ClientVars.Ragebot.Hitscan;
		int Aimspot = ClientVars.Ragebot.AimbotSelection;

		switch (HitScanMode) {
		case 0:
			break;
		case 1:
			// head/body
			if (Aimspot != 0)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
			else if (Aimspot != 1)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
			else if (Aimspot != 2)
				HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
			else if (Aimspot != 3)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
			else if (Aimspot != 4)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);

			HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
			break;
		case 2:
			// basic +(arms, thighs)
			if (Aimspot != 0)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
			else if (Aimspot != 1)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
			else if (Aimspot != 2)
				HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
			else if (Aimspot != 3)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
			else if (Aimspot != 4)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);

			HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
		case 3:
			// heaps ++(just all the random shit)
			if (Aimspot != 0)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
			else if (Aimspot != 1)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
			else if (Aimspot != 2)
				HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
			else if (Aimspot != 3)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
			else if (Aimspot != 4)
				HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);

			HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
		}
		return HitBoxesToScan;
	}

	Vector RunAimScan(CBaseEntity* pTarget, float &simtime, Vector& origin)
	{
		Vector vEyePos = Hacks.LocalPlayer->GetEyePosition();
		auto wpn_data = Hacks.LocalWeapon->GetCSWpnData();
		static float minimum_damage = 1.f;

		if (ClientVars.Ragebot.MinDmg == 101) // Enemy HP mode
			minimum_damage = pTarget->GetHealth();
		else
			minimum_damage = ClientVars.Ragebot.MinDmg;

		bool found = false;

		matrix3x4 BoneMatrix[128];

		/*if (Clientvariables->Ragebot.PositionAdjustment)
		{
			std::vector<tick_record> lby_records, trash_records;

			
			float latest_time = 0.0f;
			tick_record latest_record;

			//do it that way to use the latest nonfakelagging record
			for (int j = g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.size() - 1; j >= 0; j--) //works pretty good for nospread
			{
				tick_record record = g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.at(j);

				float lerptime = g_BacktrackHelper->GetLerpTime();
				float desired_time = record.m_flSimulationTime + lerptime;
				float estimated_time = g_BacktrackHelper->GetEstimateServerTime();
				float SV_MAXUNLAG = 1.0f;
				float latency = g_BacktrackHelper->GetNetworkLatency();
				float m_flLerpTime = g_BacktrackHelper->GetLerpTime();
				float correct = clamp<float>(latency + m_flLerpTime, 0.0f, SV_MAXUNLAG);
				float deltaTime = correct - (estimated_time + lerptime - desired_time);

				if (fabs(deltaTime) > 0.2f)
					continue;

				if (record.m_flSimulationTime == g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.back().m_flSimulationTime) {
					latest_time = g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.at(j).m_flSimulationTime;
					latest_record = g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.at(j);
				}

				if (record.needs_extrapolation)
					continue;

				if (record.bLowerBodyYawUpdated)
					lby_records.emplace_back(record);
				else if (j != g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.size() - 1)
					trash_records.emplace_back(record);
			}

			//std::reverse(lby_records.begin(), lby_records.end());

		

			//check if we need to extrapolate, and just fucking do it, as nothing gets extrapoalted otherwise

			bool was_latest_checked_in_lby = false;

			for (int i = 0; i < lby_records.size(); i++) {
				tick_record record = lby_records.at(i);//total_valid_records.at(j);

				if (record.needs_extrapolation)
					continue;

				simtime = record.m_flSimulationTime;
				origin = record.m_vecOrigin;

				bool is_latest_record = record.m_flSimulationTime == latest_record.m_flSimulationTime;

				if (is_latest_record)
					was_latest_checked_in_lby = true;

				for (auto HitBox : MainHitbox(pTarget, record.boneMatrix)) {
					int hitgroup = -1;

					//fix that only latest record gets multipointed OR use the center of the hitbox to do this when using backtrack records
					if (is_latest_record) {

						if (g_pEngineTrace->IsVisible(G::LocalPlayer, vEyePos, HitBox, pTarget, hitgroup)) {
							float modified_damage = wpn_data->iDamage * (float)pow(wpn_data->flRangeModifier, wpn_data->flRange * 0.002);

							ScaleDamage(hitgroup, pTarget, wpn_data->flArmorRatio, modified_damage);

							if (HitBox != Vector(0, 0, 0) && modified_damage >= minimum_damage)
								return HitBox;
						}
					}

					if (is_latest_record) //neded to comment it, as i can't backtrack autowall atm
					{
						static float damage_given = 0.f;

						if (Clientvariables->Ragebot.Autowall && g_Autowall->CanHit(pTarget, HitBox, &damage_given)) {
							if (damage_given >= minimum_damage) {
								if (HitBox != Vector(0, 0, 0))
									return HitBox;
							}
						}
					}
				}
			}

			//only do autowall & hitscan for the latest lagrecord, but do that before we use other records that ain't good
			if (!was_latest_checked_in_lby && !latest_record.needs_extrapolation) {

				was_latest_checked_in_lby = true;

				simtime = latest_record.m_flSimulationTime;
				origin = latest_record.m_vecOrigin;

				for (auto HitBox : MainHitbox(pTarget, latest_record.boneMatrix)) {
					int hitgroup = -1;

					//fix that only latest record gets multipointed OR use the center of the hitbox to do this when using backtrack records

					if (g_pEngineTrace->IsVisible(G::LocalPlayer, vEyePos, HitBox, pTarget, hitgroup)) {
						float modified_damage = wpn_data->iDamage * (float)pow(wpn_data->flRangeModifier, wpn_data->flRange * 0.002);

						ScaleDamage(hitgroup, pTarget, wpn_data->flArmorRatio, modified_damage);

						if (HitBox != Vector(0, 0, 0) && modified_damage >= minimum_damage)
							return HitBox;
					}

					static float damage_given = 0.f;

					if (Clientvariables->Ragebot.Autowall && g_Autowall->CanHit(pTarget, HitBox, &damage_given)) {
						if (damage_given >= minimum_damage) {
							if (HitBox != Vector(0, 0, 0))
								return HitBox;
						}
					}
				}
			}

			//hitscan and autowall only for latest record before trashrecords
			if (!latest_record.needs_extrapolation) {
				Vector vPoint;
				simtime = latest_record.m_flSimulationTime;
				origin = latest_record.m_vecOrigin;
				for (auto HitboxID : GetHitboxesToScan(pTarget)) {
					std::vector<Vector> Points = GameUtils::GetMultiplePointsForHitbox(pTarget, HitboxID, latest_record.boneMatrix);
					for (int k = 0; k < Points.size(); k++) {

						vPoint = Points.at(k);
						float damage = 0.f;

						int hitgroup = -1;
						if (g_pEngineTrace->IsVisible(G::LocalPlayer, vEyePos, vPoint, pTarget, hitgroup)) {
							float modified_damage = wpn_data->iDamage * (float)pow(wpn_data->flRangeModifier, wpn_data->flRange * 0.002);

							ScaleDamage(hitgroup, pTarget, wpn_data->flArmorRatio, modified_damage);



							if (vPoint != Vector(0, 0, 0) && modified_damage >= minimum_damage)
								return vPoint;
						}

						if (k == 0) //fixes that only the center gets autowall
						{
							static float damage_given = 0.f;

							if (Clientvariables->Ragebot.Autowall && Clientvariables->Ragebot.AutowallHitscan && g_Autowall->CanHit(pTarget, vPoint, &damage_given)) {
								if (damage_given >= minimum_damage) {
									if (vPoint != Vector(0, 0, 0))
										return vPoint;
								}
							}
						}
					}
				}
			}


			//check for other records
			for (int j = 0; j < trash_records.size(); j++) {
				tick_record record = trash_records.at(j);//total_valid_records.at(j);

				if (record.needs_extrapolation)
					continue;

				//*(Vector*)((DWORD)pTarget + 0x110) = record.m_vecVelocity;


				simtime = record.m_flSimulationTime;
				origin = record.m_vecOrigin;

				int count = 0; //fix that only center gets autowalled

							   //don't aim at lby records, as we tested for them before

				for (auto HitBox : MainHitbox(pTarget, record.boneMatrix)) {
					int hitgroup = -1;

					//fix that only latest record gets multipointed OR use the center of the hitbox to do this when using backtrack records
					if (g_pEngineTrace->IsVisible(G::LocalPlayer, vEyePos, HitBox, pTarget, hitgroup)) {
						float modified_damage = wpn_data->iDamage * (float)pow(wpn_data->flRangeModifier, wpn_data->flRange * 0.002);

						ScaleDamage(hitgroup, pTarget, wpn_data->flArmorRatio, modified_damage);

						if (HitBox != Vector(0, 0, 0) && modified_damage >= minimum_damage)
							return HitBox;
					}
				}
			}

			if (latest_record.needs_extrapolation) {
				Vector position = latest_record.m_vecOrigin;
				float old_simtime = latest_record.m_flSimulationTime;;
				Vector extr_position = position;
				simtime = latest_record.m_flSimulationTime;
				g_BacktrackHelper->ExtrapolatePosition(pTarget, extr_position, simtime, latest_record.m_vecVelocity);

				Msg("Extrapolating... OldVec(%f, %f, %f) - NewVec(%f, %f, %f)\n", position.x, position.y, position.z, extr_position.x, extr_position.y, extr_position.z);

				for (auto HitBox : MainHitbox(pTarget, latest_record.boneMatrix)) {
					int hitgroup = -1;

					HitBox -= position;
					HitBox += extr_position;

					if (g_pEngineTrace->IsVisible(G::LocalPlayer, vEyePos, HitBox, pTarget, hitgroup)) {
						if (HitBox != Vector(0, 0, 0))
							return HitBox;
					}

				}
			}
		}
		else {*/
			//int* array = reinterpret_cast<int*>(offys.dwOcclusionArray);
			//*(int*)((uintptr_t)pTarget + offys.nWriteableBones) = 0;
			//*(int*)((uintptr_t)pTarget + offys.bDidCheckForOcclusion) = array[1];



			pTarget->SetupBones(BoneMatrix, 128, 0x100, Interfaces.pGlobalVars->curtime);
			simtime = pTarget->GetSimulationTime();

			origin = pTarget->GetVecOrigin();

			for (auto HitBox : MainHitbox(pTarget, BoneMatrix)) {
				if (IsVisible(vEyePos, HitBox, Hacks.LocalPlayer, pTarget, false)) {
					if (HitBox != Vector(0, 0, 0))
						return HitBox;
				}
				int damage_given = Autowall::GetDamage(HitBox);
				if (ClientVars.Ragebot.Autowall && damage_given > 0) {
					if (damage_given >= minimum_damage) {
						if (HitBox != Vector(0, 0, 0))
							return HitBox;
					}
				}
			}
			for (auto HitboxID : GetHitboxesToScan(pTarget)) {

				Vector vPoint;

				std::vector<Vector> Points = Misc::GetMultiplePointsForHitbox(pTarget, HitboxID, BoneMatrix);
				for (int k = 0; k < Points.size(); k++) {

					vPoint = Points.at(k);
					float damage = 0.f;

					int hitgroup = -1;
					if (IsVisible( vEyePos, vPoint, Hacks.LocalPlayer, pTarget, false)) {
						if (vPoint != Vector(0, 0, 0))
							return vPoint;
					}

					int damage_given = Autowall::GetDamage(vPoint);
					if (ClientVars.Ragebot.Autowall && damage_given > 0) {
						if (damage_given >= minimum_damage) {
							if (vPoint != Vector(0, 0, 0))
								return vPoint;
						}
					}
				}
			}
	
		return Vector(0, 0, 0);
	}

public:

	CBaseEntity* pTarget;

	void DropTarget()
	{
		target_index = -1;
		best_distance = 99999.f;
		aimbotted_in_current_tick = false;
		fired_in_that_tick = false;
		current_aim_position = Vector();
		pTarget = nullptr;
	}


	void Aim( CInput::CUserCmd* cmd )
	{
		if (!ClientVars.Ragebot.Enable) return;

		pTarget = nullptr;

		Interfaces.pEngine->GetViewAngles(Angles);
		CBaseCombatWeapon* pWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();

		for (int i = 1; i < Interfaces.pEngine->GetMaxClients(); i++)
		{

			if (i == Interfaces.pEngine->GetLocalPlayer()) continue; 

			CBaseEntity* target = Interfaces.pEntList->GetClientEntity(i);

			if (!target->IsPlayer()) continue;
			if (target->GetTeam() == Hacks.LocalPlayer->GetTeam()) continue;
			if (target->IsDormant()) continue;
			if (!target->isAlive()) continue;
			if (target->HasGunGameImmunity()) continue;

			float FOV = Misc::GetFOV(Angles, Hacks.LocalPlayer->GetEyePosition(), target->GetEyePosition(), false);

			if (FOV > ClientVars.Ragebot.FOV) continue;

			pTarget = target;
			
			float simtime = 0;
			Vector minus_origin = Vector(0, 0, 0);
			Vector aim_position = RunAimScan(target, simtime, minus_origin);

			if (aim_position == Vector(0, 0, 0))
				continue;


			float selection_value = 0;
			switch (ClientVars.Ragebot.AimbotSelection) {
			case 0:
				selection_value = FOV;
				break;
			case 2:
				selection_value = g_Math.RandomFloat(0, 100);
				break;
			case 3:
				selection_value = target->GetVecVelocity().Length();
				break;
			case 4:
				selection_value = target->GetHealth();
				break;

			default:
				break;
			}

			if (best_distance >= selection_value && aim_position != Vector(0, 0, 0)) {
				best_distance = selection_value;


				target_index = i;
				current_aim_position = aim_position;
				pTarget = target;
				current_aim_simulationtime = simtime;
				current_aim_player_origin = minus_origin;
			}
		}
		if (target_index != -1 && current_aim_position != Vector(0, 0, 0) && pTarget) {
			aimbotted_in_current_tick = true;
			QAngle aim = g_Math.CalcAngle(Hacks.LocalPlayer->GetEyePosition(), current_aim_position);
			
			if (ClientVars.Ragebot.pSilent && cmd->buttons & IN_ATTACK)
				cmd->viewangles = aim;

			if (!ClientVars.Ragebot.pSilent){
				cmd->viewangles = aim;
				Interfaces.pEngine->SetViewAngles(cmd->viewangles);
			}

			if (ClientVars.Ragebot.autofire)
			{
				if (ClientVars.Ragebot.autoscope && pWeapon->isSniper() && !Hacks.LocalPlayer->m_bIsScoped())
					cmd->buttons |= IN_ATTACK2;
				else
				{
					if (ClientVars.Ragebot.HitChance == 0 )/* || Hacks.LocalWeapon->hitchance() < ClientVars.Ragebot.HitChance)*/
					{
						if (ClientVars.Ragebot.pSilent)
							cmd->viewangles = aim;

						cmd->buttons |= IN_ATTACK;
						this->fired_in_that_tick = true;
					}

				}
			}

			//if (Clientvariables->Ragebot.PositionAdjustment)
			//	cmd->tick_count = TIME_TO_TICKS(current_aim_simulationtime) + TIME_TO_TICKS(g_BacktrackHelper->GetLerpTime());// for backtracking
		}
	}
} Ragebot;
