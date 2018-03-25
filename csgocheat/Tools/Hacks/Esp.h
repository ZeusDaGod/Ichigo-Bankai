#pragma once
#include "../../stdafx.h"
#include "CreateMoveETC.h"

int alpha[64];

float Get3DDistanceTo(Vector myCoords, Vector enemyCoords)
{
	return sqrt(
		pow(double(enemyCoords.x - myCoords.x), 2.0) +
		pow(double(enemyCoords.y - myCoords.y), 2.0) +
		pow(double(enemyCoords.z - myCoords.z), 2.0));
}

class Esp
{
public:
	static void Hitmarker()
	{
		if (GVars.hitmarkeralpha < 0.f)
			GVars.hitmarkeralpha = 0.f;
		else if (GVars.hitmarkeralpha > 0.f)
			GVars.hitmarkeralpha -= 0.01f;

		int W, H;
		Interfaces.pEngine->GetScreenSize(W, H);

		if (GVars.hitmarkeralpha > 0.f)
		{
			DrawLine(W / 2 - 10, H / 2 - 10, W / 2 - 5, H / 2 - 5, CColor(ClientVars.Col.Hitmarker[0] * 255, ClientVars.Col.Hitmarker[1] * 255, ClientVars.Col.Hitmarker[2] * 255, (GVars.hitmarkeralpha * 255.f)));
			DrawLine(W / 2 - 10, H / 2 + 10, W / 2 - 5, H / 2 + 5, CColor(ClientVars.Col.Hitmarker[0] * 255, ClientVars.Col.Hitmarker[1] * 255, ClientVars.Col.Hitmarker[2] * 255, (GVars.hitmarkeralpha * 255.f)));
			DrawLine(W / 2 + 10, H / 2 - 10, W / 2 + 5, H / 2 - 5, CColor(ClientVars.Col.Hitmarker[0] * 255, ClientVars.Col.Hitmarker[1] * 255, ClientVars.Col.Hitmarker[2] * 255, (GVars.hitmarkeralpha * 255.f)));
			DrawLine(W / 2 + 10, H / 2 + 10, W / 2 + 5, H / 2 + 5, CColor(ClientVars.Col.Hitmarker[0] * 255, ClientVars.Col.Hitmarker[1] * 255, ClientVars.Col.Hitmarker[2] * 255, (GVars.hitmarkeralpha * 255.f)));

		}
	}

	static void DrawScope()
	{
		if (Hacks.LocalPlayer->m_bIsScoped())
		{
			int width = 0;
			int height = 0;
			Interfaces.pEngine->GetScreenSize(width, height);
			DrawRect((width / 2), 0, (width / 2) + 1, height, CColor(0, 0, 0, 255));
			DrawRect(0, (height / 2), width, (height / 2) + 1, CColor(0, 0, 0, 255));
		}
	}

	static void DLights()
	{
		for (auto i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* pEnt = Interfaces.pEntList->GetClientEntity(i);
			if (pEnt == nullptr)
				continue;
			if (pEnt == Hacks.LocalPlayer)
				continue;
			if (pEnt->IsDormant())
				continue;
			if (!pEnt->IsPlayer())
				continue;
			player_info_t info;
			if (Interfaces.pEngine->GetPlayerInfo(pEnt->GetIndex(), &info))
			{
				if (ClientVars.Visual.DLight)
				{
					dlight_t* pDLight = Interfaces.DLight->CL_AllocDlight(pEnt->GetIndex());
					if (pEnt->GetTeam() == Hacks.LocalPlayer->GetTeam() && ClientVars.Visual.DLightteam)
					{
						pDLight->die = Interfaces.pGlobalVars->curtime + 0.05f;
						pDLight->radius = 300.f;
						pDLight->color.r = ClientVars.Col.TeamDLights[0] * 255;
						pDLight->color.g = ClientVars.Col.TeamDLights[1] * 255;
						pDLight->color.b = ClientVars.Col.TeamDLights[2] * 255;
						pDLight->color.exponent = 5;
						pDLight->key = pEnt->GetIndex();
						pDLight->decay = pDLight->radius / 5.0f;
						pDLight->origin = pEnt->GetVecOrigin() + Vector(0, 0, 5);
					}
					if (!(pEnt->GetTeam() == Hacks.LocalPlayer->GetTeam()))
					{
						pDLight->die = Interfaces.pGlobalVars->curtime + 0.05f;
						pDLight->radius = 300.f;
						pDLight->color.r = ClientVars.Col.EnemyDLights[0] * 255;
						pDLight->color.g = ClientVars.Col.EnemyDLights[1] * 255;
						pDLight->color.b = ClientVars.Col.EnemyDLights[2] * 255;
						pDLight->color.exponent = 5;
						pDLight->key = pEnt->GetIndex();
						pDLight->decay = pDLight->radius / 10.0f;
						pDLight->origin = pEnt->GetVecOrigin() + Vector(0, 0, 5);
					}
				}
				if (ClientVars.Visual.ELight)
				{
					dlight_t* pELight = Interfaces.DLight->CL_AllocElight(pEnt->GetIndex());
					if (pEnt->GetTeam() == Hacks.LocalPlayer->GetTeam() && ClientVars.Visual.DLightteam)
					{
						pELight->die = Interfaces.pGlobalVars->curtime + 0.05f;
						pELight->radius = 300.f;
						pELight->color.r = ClientVars.Col.TeamDLights[0] * 255;
						pELight->color.g = ClientVars.Col.TeamDLights[1] * 255;
						pELight->color.b = ClientVars.Col.TeamDLights[2] * 255;
						pELight->color.exponent = 5;
						pELight->key = pEnt->GetIndex();
						pELight->decay = pELight->radius / 5.0f;
						pELight->origin = pEnt->GetVecOrigin() + Vector(0, 0, 5);
					}
					if (!(pEnt->GetTeam() == Hacks.LocalPlayer->GetTeam()))
					{
						pELight->die = Interfaces.pGlobalVars->curtime + 0.05f;
						pELight->radius = 300.f;
						pELight->color.r = ClientVars.Col.EnemyDLights[0] * 255;
						pELight->color.g = ClientVars.Col.EnemyDLights[1] * 255;
						pELight->color.b = ClientVars.Col.EnemyDLights[2] * 255;
						pELight->color.exponent = 5;
						pELight->key = pEnt->GetIndex();
						pELight->decay = pELight->radius / 5.0f;
						pELight->origin = pEnt->GetVecOrigin() + Vector(0, 0, 5);
					}
				}
			}
		}
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

	static bool LineGoesThroughSmoke(Vector pos1, Vector pos2) throw()
	{
		typedef bool(*LineGoesThroughSmokeFn)(float, float, float, float, float, float, short);

		LineGoesThroughSmokeFn LineGoesThroughSmokeEx;
		LineGoesThroughSmokeEx = (LineGoesThroughSmokeFn)(Utils.PFindPattern("client.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0"));
		return LineGoesThroughSmokeEx(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, 1);
	}

	static void Watermark()
	{
		Interfaces.pSurface->DrawT(10, 10, CColor(255, 255, 255, 120), Hacks.Font_ESP, false, "Ichigo [Counter-Strike: Global Offensive]");
	}

	static void UTCheck()
	{
		if (!ClientVars.Misc.Antiuntrusted)
			Interfaces.pSurface->DrawNotification(0, 100, CColor(255, 0, 0, 255), Hacks.Font_ESP, "UNTRUSTED FEATURES ENABLED");
	}

	static void info()
	{
		if (ClientVars.Visual.Localinfo){

			Interfaces.pSurface->DrawT(0, 500, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, "iChoked: %i", LocalInfo.Choked);

			Interfaces.pSurface->DrawT(0, 510, Hacks.SendPacket ? CColor(0, 255, 0, 255) : CColor(255, 0, 0, 255),
				Hacks.Font_ESP, false, Hacks.SendPacket ? "bSendPacket: true" : "bSendPacket: false");
	
			Interfaces.pSurface->DrawT(0, 520, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, "vecVelocity(2D) %.2f", Hacks.LocalPlayer->GetVecVelocity().Length2D());
			Interfaces.pSurface->DrawT(0, 530, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, "flCurtime %.2f", Interfaces.pGlobalVars->curtime);
		}
	}

	static void DrawCircle(float x, float y, float r, float s, CColor color)
	{
		float Step = M_PI * 2.0 / s;
		for (float a = 0; a < (M_PI*2.0); a += Step)
		{
			float x1 = r * cos(a) + x;
			float y1 = r * sin(a) + y;
			float x2 = r * cos(a + Step) + x;
			float y2 = r * sin(a + Step) + y;

			DrawLine(x1, y1, x2, y2, color);
		}
	}

	static void Crosshair()
	{

		int W, H, cW, cH;
		Interfaces.pEngine->GetScreenSize(W, H);

		cW = W / 2;
		cH = H / 2;

		Interfaces.pSurface->DrawSetColor(0, 0, 0, ClientVars.Col.Crosshair[3] * 255);
		Interfaces.pSurface->DrawFilledRect(cW - 4, cH - 2, cW - 4 + 8, cH - 2 + 4);
		Interfaces.pSurface->DrawFilledRect(cW - 2, cH - 4, cW - 2 + 4, cH - 4 + 8);

		Interfaces.pSurface->DrawSetColor(
			ClientVars.Col.Crosshair[0] * 255,
			ClientVars.Col.Crosshair[1] * 255,
			ClientVars.Col.Crosshair[2] * 255,
			ClientVars.Col.Crosshair[3] * 255);
		Interfaces.pSurface->DrawFilledRect(cW - 3, cH - 1, cW - 3 + 6, cH - 1 + 2);
		Interfaces.pSurface->DrawFilledRect(cW - 1, cH - 3, cW - 1 + 2, cH - 3 + 6);

	}

	static void InaccuracyCrosshair()
	{

		int W, H, cW, cH;
		Interfaces.pEngine->GetScreenSize(W, H);

		cW = W / 2;
		cH = H / 2;

		int dX = W / Hacks.FOV;
		int dY = H / Hacks.FOV;
		int drX, drY;


		if (ClientVars.Visual.NoVisRecoil)
		{
			drX = cW - (int)(dX * (Hacks.LocalPlayer->GetPunchAngle().y * 2.f));
			drY = cH + (int)(dY * (Hacks.LocalPlayer->GetPunchAngle().x * 2.f));
		}
		else
		{
			drX = cW - (int)(dX * (Hacks.LocalPlayer->GetPunchAngle().y));
			drY = cH + (int)(dY * (Hacks.LocalPlayer->GetPunchAngle().x));
		}
	

		CBaseCombatWeapon* pWeapon = Hacks.LocalWeapon;


		auto accuracy = (pWeapon->GetInaccuracy() + pWeapon->GetSpread()) * 500.f;


		if (ClientVars.Visual.InaccuracyCrosshair)
		{
			if (pWeapon->IsGun())
				DrawCircle(drX, drY, accuracy + 3, 30, CColor(
					ClientVars.Col.InaccuracyCrosshair[0] * 255,
					ClientVars.Col.InaccuracyCrosshair[1] * 255,
					ClientVars.Col.InaccuracyCrosshair[2] * 255,
					ClientVars.Col.InaccuracyCrosshair[3] * 255));
		}
	}

	static void DrawInfo(RECT rect, CBaseEntity* pPlayer)
	{
		player_info_t info;
		static class Text
		{
		public:
			string text;
			int side;
			int Font;
			CColor color;

			Text(string text, int side, int Font, CColor color) : text(text), side(side), Font(Font), color(color)
			{
			}
		};
		std::vector< Text > texts;

		int index = pPlayer->GetIndex();
		if (Interfaces.pEngine->GetPlayerInfo(index, &info))
		{
			if (ClientVars.Visual.Name)
				texts.push_back(Text(pPlayer->GetName(), 0, Hacks.Font_ESP, CColor(255, 255, 255, alpha[index])));
			if (pPlayer == Ragebot.pTarget && ClientVars.Ragebot.Enable)
				texts.push_back(Text("<target>", 0, Hacks.Font_ESP, CColor(255, 0, 0, alpha[index])));
			if (ClientVars.Visual.Armor && pPlayer->GetArmorValue() > 0)
				texts.push_back(Text(pPlayer->GetArmorName(), 1, Hacks.Font_ESP, CColor(255, 255, 255, alpha[index])));
			if (ClientVars.Visual.Money)
				texts.push_back(Text(string("$") + std::to_string(pPlayer->GetAccount()), 0, Hacks.Font_ESP, CColor(71, 132, 60, alpha[index])));
			if (ClientVars.Visual.Vulnerabilities && pPlayer->IsFlashed())
				texts.push_back(Text("flashed", 1, Hacks.Font_ESP, CColor(255, 255, 183, alpha[index])));
			if (ClientVars.Visual.Vulnerabilities && pPlayer->m_bIsScoped())
				texts.push_back(Text("scoped", 1, Hacks.Font_ESP, CColor(121, 252, 250, alpha[index])));
			if (ClientVars.Visual.Callout)
				texts.push_back(Text(pPlayer->GetCallout(), 1, Hacks.Font_ESP, CColor(255, 255, 255, alpha[index])));

			CBaseCombatWeapon* weapon = pPlayer->GetActiveBaseCombatWeapon();
			if (weapon)
			{
				if (ClientVars.Visual.Weapon && weapon)
					texts.push_back(Text(weapon->GetGunName(), 2, Hacks.Font_ESP, CColor(255, 255, 255, alpha[index])));
			}
		}

		int middle = ((rect.right - rect.left) / 2) + rect.left;
		int Top[3] = { rect.top, rect.top, rect.bottom };
		for (auto text : texts)
		{
			RECT nameSize = GetTextSize(text.Font, (char*)text.text.c_str());
			switch (text.side)
			{
			case 0:
				Interfaces.pSurface->DrawT(middle, Top[0] - nameSize.bottom, text.color, text.Font, true, (char*)text.text.c_str());
				Top[0] -= nameSize.bottom;
				break;
			case 1:
				Interfaces.pSurface->DrawT(rect.right + 4, Top[1], text.color, text.Font, false, (char*)text.text.c_str());
				Top[1] += nameSize.bottom - 4;
				break;
			case 2:
				Interfaces.pSurface->DrawT(middle,(ClientVars.Visual.Ammo ? Top[2] + 6 : Top[2]), text.color, text.Font, true, (char*)text.text.c_str());
				Top[2] += nameSize.bottom - 4;
				break;
			}
		}
	}

	static void DoEsp()
	{
		DLights();

		info();

		if (ClientVars.Visual.Hitmarker)
			Hitmarker();

		if (ClientVars.Visual.InaccuracyCrosshair)
			InaccuracyCrosshair();


		static bool crosshairchecked = false;

		if (ClientVars.Visual.Crosshair){ 
			Crosshair(); 
			if (!crosshairchecked){ 
				Interfaces.pEngine->ClientCmd_Unrestricted("crosshair 0", 0);
				crosshairchecked = true; 
			} 
		} 
		else{ 
			if (crosshairchecked){ 
				Interfaces.pEngine->ClientCmd_Unrestricted("crosshair 1", 0); 
				crosshairchecked = false; 
			} 
		} 

		int width = 0;
		int height = 0;
		Interfaces.pEngine->GetScreenSize(width, height);
		for (auto i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity(i);
			if (pEntity == nullptr)
				continue;
			if (pEntity == Hacks.LocalPlayer)
				continue;

			Vector pos, pos3D;
			pos3D = pEntity->GetVecOrigin();
			int owner = pEntity->GetOwner();
			int ClassID = pEntity->GetClientClass()->m_ClassID;

			if (owner == -1)
			{
				if (ClientVars.Visual.Droppedguns)
				{

					if (g_Math.WorldToScreen(pos3D, pos))
					{

						if (strstr(pEntity->GetClientClass()->m_pNetworkName, charenc("CWeapon")))
						{
							CBaseCombatWeapon* weapon = static_cast<CBaseCombatWeapon*>(pEntity);
							Interfaces.pSurface->DrawT(pos.x, pos.y, CColor(255, 255, 255, 255), Hacks.Font_ESP, true, "%s" "(" "%i" ")", std::string(pEntity->GetClientClass()->m_pNetworkName).substr(7).c_str(), weapon->ammo());
						}
						if (ClassID == 1)
						{
							CBaseCombatWeapon* weapon = static_cast<CBaseCombatWeapon*>(pEntity);
							Interfaces.pSurface->DrawT(pos.x, pos.y, CColor(255, 255, 255, 255), Hacks.Font_ESP, true, "%s" "(" "%i" ")", charenc("AK-47"), weapon->ammo());
						}
						if (ClassID == 39)
						{
							CBaseCombatWeapon* weapon = static_cast<CBaseCombatWeapon*>(pEntity);
							Interfaces.pSurface->DrawT(pos.x, pos.y, CColor(255, 255, 255, 255), Hacks.Font_ESP, true, "%s" "(" "%i" ")", charenc("Desert Eagle"), weapon->ammo());
						}
						if (ClassID == 29)
						{
							CBaseCombatWeapon* weapon = static_cast<CBaseCombatWeapon*>(pEntity);
							Interfaces.pSurface->DrawT(pos.x, pos.y, CColor(255, 255, 255, 255), Hacks.Font_ESP, true, "%s", charenc("Dropped C4"));
						}
					}
				}
			}

			if (ClientVars.Visual.Grenades)
			{
				if (g_Math.WorldToScreen(pos3D, pos))
				{
					CColor GrenadeColor = CColor(0, 0, 0, 0);
					char* szModelName = "";
					if (strstr(pEntity->GetClientClass()->m_pNetworkName, charenc("Projectile")))
					{
						const model_t* pModel = pEntity->GetModel();
						if (!pModel)
							return;


						const studiohdr_t* pHdr = Interfaces.g_pModelInfo->GetStudioModel(pModel);
						if (!pHdr)
							return;

						if (!strstr(pHdr->name, "thrown") && !strstr(pHdr->name, "dropped"))
							return;



						IMaterial* mats[32];
						Interfaces.g_pModelInfo->GetModelMaterials(pModel, pHdr->numtextures, mats);

						for (int i = 0; i < pHdr->numtextures; i++)
						{
							IMaterial* mat = mats[i];
							if (!mat)
								continue;

							if (strstr(mat->GetName(), "flashbang"))
							{
								GrenadeColor = CColor(255, 255, 0, 255);
								szModelName = "flashbang";
							}
							else if (strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade"))
							{
								szModelName = "grenade";
								GrenadeColor = CColor(255, 0, 0, 255);
								break;
							}
							else if (strstr(mat->GetName(), "smoke"))
							{
								szModelName = "smoke";
								GrenadeColor = CColor(0, 255, 0, 255);
								break;
							}
							else if (strstr(mat->GetName(), "decoy"))
							{
								szModelName = "decoy";
								GrenadeColor = CColor(0, 255, 0, 255);
								break;
							}
							else if (strstr(mat->GetName(), "incendiary"))
							{
								szModelName = "molotov";
								GrenadeColor = CColor(255, 0, 0, 255);
								break;
							}
							else if (strstr(mat->GetName(), "molotov"))
							{
								szModelName = "molotov";
								GrenadeColor = CColor(255, 0, 0, 255);
								break;
							}
						}
						int r, g, b, a;
						GrenadeColor.GetColor(r, g, b, a);
						Interfaces.pSurface->DrawColoredCircle(pos.x, pos.y, 9.f, 0, 0, 0, 170);
						Interfaces.pSurface->DrawColoredCircle(pos.x, pos.y, 10.f, r, g, b, a);
						Interfaces.pSurface->DrawColoredCircle(pos.x, pos.y, 11.f, 0, 0, 0, 170);
						Interfaces.pSurface->DrawT(pos.x, pos.y + 13, GrenadeColor, Hacks.Font_ESP, true, "%s", szModelName);
					}
				}
			}

			if (ClientVars.Visual.Bomb && strstr(pEntity->GetClientClass()->m_pNetworkName, "CPlantedC4"))
			{
				if (!pEntity->BombDefused())
				{
					static float flDamage;
					float flTime = pEntity->BombTimer() - Interfaces.pGlobalVars->curtime;

					if (flTime > 0.f)
					{

						if (g_Math.WorldToScreen(pos3D, pos))
						{

							bool bCanDefuse = (Hacks.LocalPlayer->HasKit() && flTime > 5.5f) || flTime > 10.5f;
							Interfaces.pSurface->DrawT(pos.x, pos.y + 5, bCanDefuse ? CColor(255, 255, 255, 255) : CColor(255, 0, 0, 255), Hacks.Font_ESP, true, "Planted C4");
							Interfaces.pSurface->DrawT(pos.x, pos.y - 5, bCanDefuse ? CColor(255, 255, 255, 255) : CColor(255, 0, 0, 255), Hacks.Font_ESP, true, "%.2f", flTime);
						}
						if (Hacks.LocalPlayer->GetHealth() > 0)
						{
							float flArmor = Hacks.LocalPlayer->GetArmor();
							float flDistance = Hacks.LocalPlayer->GetAbsOrigin().DistTo(pEntity->GetAbsOrigin());
							float a = 450.7f;
							float b = 75.68f;
							float c = 789.2f;
							float d = ((flDistance - b) / c);

							float flDmg = a * exp(-d * d);
							flDamage = flDmg;

							if (flArmor > 0)
							{
								float flNew = flDmg * 0.5f;
								float flArmor = (flDmg - flNew) * 0.5f;

								if (flArmor > static_cast<float>(flArmor))
								{
									flArmor = static_cast<float>(flArmor) * (1.f / 0.5f);
									flNew = flDmg - flArmor;
								}
								flDamage = flNew;
							}
						}
						Interfaces.pSurface->DrawNotification(0, 200, flDamage >= Hacks.LocalPlayer->GetHealth() ? CColor(255, 50, 50, 255) : CColor(255, 255, 255, 255),
							Hacks.Font_ESP, "EXPLOSION IN %.1f SECONDS DEALING %.f DAMAGE ", flTime, (flDamage > 0.f ? flDamage : 0.f));
					}
				}
			}

			if (pEntity->IsPlayer() && pEntity->isAlive())
			{
				//if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() && !ClientVars.Visual.Showteam)
				if (ClientVars.Visual.Arrows)
					DirectionArrow(pEntity);
			}

			player_info_t info;
			if (g_Math.WorldToScreen(pos3D, pos))
			{
				if (!pEntity->IsPlayer())
					continue;

				if (!pEntity->isAlive())
					continue;

				if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() && !ClientVars.Visual.Showteam)
					continue;
				
				if ((!pEntity->IsDormant()) && alpha[pEntity->GetIndex()] < 255)
				{
					alpha[pEntity->GetIndex()] += 5;
				}
				
				if (pEntity->IsDormant() && alpha[pEntity->GetIndex()] > 0)
				{
					alpha[pEntity->GetIndex()] -= 5;
				}

				CColor clr = pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() ?
					CColor(ClientVars.Col.TeamESP[0] * 255, ClientVars.Col.TeamESP[1] * 255, ClientVars.Col.TeamESP[2] * 255, alpha[pEntity->GetIndex()]) :
					CColor(ClientVars.Col.EnemyESPHB ? pEntity->GetHealthColor(alpha[pEntity->GetIndex()]) :
					CColor(ClientVars.Col.EnemyESP[0] * 255, ClientVars.Col.EnemyESP[1] * 255, ClientVars.Col.EnemyESP[2] * 255, alpha[pEntity->GetIndex()]));

				bool PVS = false;
				RECT rect = DynamicBox(pEntity, PVS);

				if (Interfaces.pEngine->GetPlayerInfo(i, &info))
					DrawInfo(rect, pEntity);

				if (ClientVars.Visual.BoundingBox)
					DrawBox(rect, clr);
				
				CColor Aimlines_clr = pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() ? clr :
					CColor(ClientVars.Col.EnemyAimlineHB ? pEntity->GetHealthColor(alpha[pEntity->GetIndex()]) :
						CColor(ClientVars.Col.Aimlines[0] * 255, ClientVars.Col.Aimlines[1] * 255, ClientVars.Col.Aimlines[2] * 255, alpha[pEntity->GetIndex()]));

				if (ClientVars.Visual.AimLine)
					DrawSnapLine(Vector(rect.left + ((rect.right - rect.left) / 2), rect.bottom, 0), Aimlines_clr);

				CColor Skeleton_clr = pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() ? clr :
					CColor(ClientVars.Col.EnemySkeletonHB ? pEntity->GetHealthColor(alpha[pEntity->GetIndex()]) :
						CColor(ClientVars.Col.Skeleton[0] * 255, ClientVars.Col.Skeleton[1] * 255, ClientVars.Col.Skeleton[2] * 255, alpha[pEntity->GetIndex()]));

				if (ClientVars.Visual.Skeleton)
					Skeleton(pEntity, Skeleton_clr);
				//if (ClientVars.Visual.HeadBox) bugged or something even tho i pasted it perfectly ;c
				//	headbox(pEntity, clr);
				if (ClientVars.Visual.Health)
					DrawHealth(rect, pEntity);

				CColor Ammo_clr = CColor(ClientVars.Col.Ammo[0] * 255, ClientVars.Col.Ammo[1] * 255, ClientVars.Col.Ammo[2] * 255, alpha[pEntity->GetIndex()]);

				if (ClientVars.Visual.Ammo)
					DrawAmmo(rect, pEntity, Ammo_clr);
				if (ClientVars.Visual.engineradar)
					*pEntity->IsSpottedPtr() = true;
			}
		}
	}

	static RECT DynamicBox(CBaseEntity* pPlayer, bool& PVS)
	{
		Vector trans = pPlayer->GetVecOrigin();

		Vector min;
		Vector max;

		min = pPlayer->BBMin();
		max = pPlayer->BBMax();

		Vector pointList[] = {
			Vector(min.x, min.y, min.z),
			Vector(min.x, max.y, min.z),
			Vector(max.x, max.y, min.z),
			Vector(max.x, min.y, min.z),
			Vector(max.x, max.y, max.z),
			Vector(min.x, max.y, max.z),
			Vector(min.x, min.y, max.z),
			Vector(max.x, min.y, max.z)
		};

		Vector Distance = pointList[0] - pointList[1];
		int dst = Distance.Length();
		dst /= 1.3f;
		Vector angs;
		Misc::CalcAngle(trans, Hacks.LocalPlayer->GetEyePosition(), angs);

		Vector all[8];
		angs.y += 45;
		for (int i = 0; i < 4; i++)
		{
			g_Math.angleVectors(angs, all[i]);
			all[i] *= dst;
			all[i + 4] = all[i];
			all[i].z = max.z;
			all[i + 4].z = min.z;
			VectorAdd(all[i], trans, all[i]);
			VectorAdd(all[i + 4], trans, all[i + 4]);
			angs.y += 90;
		}

		Vector flb, brt, blb, frt, frb, brb, blt, flt;
		PVS = true;

		if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[3], flb))
			PVS = false;
		if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[0], blb))
			PVS = false;
		if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[2], frb))
			PVS = false;
		if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[6], blt))
			PVS = false;
		if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[5], brt))
			PVS = false;
		if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[4], frt))
			PVS = false;
		if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[1], brb))
			PVS = false;
		if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[7], flt))
			PVS = false;

		Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left = flb.x;
		float top = flb.y;
		float right = flb.x;
		float bottom = flb.y;

		for (int i = 0; i < 8; i++)
		{
			if (left > arr[i].x)
				left = arr[i].x;
			if (top > arr[i].y)
				top = arr[i].y;
			if (right < arr[i].x)
				right = arr[i].x;
			if (bottom < arr[i].y)
				bottom = arr[i].y;
		}
		RECT rect;
		rect.left = left;
		rect.bottom = bottom;
		rect.right = right;
		rect.top = top;
		return rect;
	}

	static void Skeleton(CBaseEntity* pEntity, CColor Color)
	{

		if (ClientVars.Visual.Skeleton)
		{
			studiohdr_t* pStudioHdr = Interfaces.g_pModelInfo->GetStudioModel(pEntity->GetModel());

			if (!pStudioHdr)
				return;

			Vector vParent, vChild, sParent, sChild;

			for (int j = 0; j < pStudioHdr->numbones; j++)
			{
				mstudiobone_t* pBone = pStudioHdr->GetBone(j);

				if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
				{
					vChild = pEntity->GetBonePos(j);
					vParent = pEntity->GetBonePos(pBone->parent);
					Interfaces.g_pDebugOverlay->ScreenPosition(vParent, sParent);
					Interfaces.g_pDebugOverlay->ScreenPosition(vChild, sChild);
					int r, g, b, a;
					Color.GetColor(r, g, b, a);
					Interfaces.pSurface->DrawSetColor(r, g, b, a);
					Interfaces.pSurface->DrawLine(sParent[0], sParent[1], sChild[0], sChild[1]);
				}
			}
		}
	}

	static void DrawSnapLine(Vector to, CColor clr)
	{
		int width = 0;
		int height = 0;
		Interfaces.pEngine->GetScreenSize(width, height);
		Vector From((width / 2), height - 1, 0);
		DrawLine(From.x, From.y, to.x, to.y, clr);
	}

	static void DrawBox(RECT rect, CColor Color)
	{
		int r, g, b, a;
		Color.GetColor(r,g,b,a);
		DrawOutlinedRect(rect.left - 1, rect.top - 1, rect.right + 1, rect.bottom + 1, CColor(0, 0, 0, a / 2));
		DrawOutlinedRect(rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1, CColor(0, 0, 0, a / 2));
		DrawOutlinedRect(rect.left, rect.top, rect.right, rect.bottom, Color);
	}

	static void DrawHealth(RECT rect, CBaseEntity* pPlayer)
	{
		float HealthValue = pPlayer->GetHealth();

		float HealthValue2 = pPlayer->GetHealth();
		if (HealthValue2 > 100)
			HealthValue2 = 100;
		int Red = 255 - (HealthValue2 * 2.55);
		int Green = HealthValue2 * 2.55;

		char hp[256];
		sprintf(hp, "%.0f", HealthValue);
		
		float height = (rect.bottom - rect.top) * (HealthValue2 / 100);
		DrawRect(rect.left - 6, rect.top - 1, rect.left - 2, rect.bottom + 1, CColor(0, 0, 0, alpha[pPlayer->GetIndex()] / 2));
		DrawRect(rect.left - 5, rect.bottom - height, rect.left - 3, rect.bottom, CColor(Red, Green, 0, alpha[pPlayer->GetIndex()]));
		if (HealthValue2 < 100)
			Interfaces.pSurface->DrawT(rect.left - 4, rect.bottom - height - 4, CColor(255, 255, 255, alpha[pPlayer->GetIndex()]), Hacks.Font_Health, true, hp);
	}

	static void DrawAmmo(RECT rect, CBaseEntity* pPlayer, CColor color)
	{
		auto AnimLayer = &pPlayer->GetAnimOverlays()[1]; 

		if (!AnimLayer->m_pOwner) 
			return;

		auto activity = pPlayer->GetSequenceActivity(AnimLayer->m_nSequence, Interfaces.g_pModelInfo->GetStudioModel(pPlayer->GetModel()));

		if (CBaseCombatWeapon* weapon = pPlayer->GetActiveBaseCombatWeapon())
		{	
			if (CCSWeaponInfo* winfo = weapon->GetCSWpnData())
			{
				float currentammo = weapon->ammo();
				float maxammo = winfo->GetMaxClip();
				DrawRect(rect.left - 1, rect.bottom + 2 , rect.right + 1, rect.bottom + 6, CColor(0, 0, 0, alpha[pPlayer->GetIndex()] / 2));

				static float ammob4reload[64]; // for the aesthetic so it doesnt jump to the current ammo before reload animation
				if (activity == 967 && AnimLayer->m_flWeight != 0.f) // if reloading
				{
					float amount = ammob4reload[pPlayer->GetIndex()] / maxammo;
					float cycle = AnimLayer->m_flCycle;
					int length = (rect.right - rect.left) * amount;
					int reloadX = ((rect.right - rect.left) - length) * cycle;
					DrawRect(rect.left, rect.bottom + 3, rect.left + length + reloadX, rect.bottom + 5, color);
					Interfaces.pSurface->DrawT(rect.left + length + reloadX, rect.bottom - 1, CColor(255, 255, 255, alpha[pPlayer->GetIndex()]), Hacks.Font_Health, false, "RELOADING");
				}
				else // if not reloading
				{
					if (currentammo < 0) // draw a bar for weapons that do not have ammo (grenades, knives) for the aesthetic
					{
						DrawRect(rect.left, rect.bottom + 3, rect.right, rect.bottom + 5, color);
					}
					if (currentammo >= 0) // if the bitch got bullets its probably a gun and we shud display the ammo count if it aint full also draw that sexy bar MMMMMM
					{
						float amount = currentammo / maxammo;
						int length = (rect.right - rect.left) * amount;
						ammob4reload[pPlayer->GetIndex()] = currentammo;
						if (currentammo != 0)
							DrawRect(rect.left, rect.bottom + 3, rect.left + length, rect.bottom + 5, color);

						if (currentammo != maxammo)
							Interfaces.pSurface->DrawT(rect.left + length, rect.bottom - 1, CColor(255, 255, 255, alpha[pPlayer->GetIndex()]), Hacks.Font_Health, true, "%.0f", currentammo);
					}
				}
			}
		}
	}

	static void DirectionArrow(CBaseEntity* pEntity)
	{
		constexpr float radius = 360.0f;
		int width, height;
		Interfaces.pEngine->GetScreenSize(width, height);

		Vector origin = pEntity->GetAbsOrigin();

		Vector vRealAngles;
		Interfaces.pEngine->GetViewAngles(vRealAngles);

		Vector vForward, vRight, vUp(0.f, 0.f, 1.f);

		g_Math.angleVectors(vRealAngles, vForward);

		vForward.z = 0.0f;
		vRight = CrossProduct(vUp, vForward);

		float flFront = g_Math.DotProduct(origin, vForward);
		float flSide = g_Math.DotProduct(origin, vRight);
		float flXPosition = radius * -flSide;
		float flYPosition = radius * -flFront;

		float rotation = Hacks.CurrentCmd->viewangles.y;

		rotation = atan2(flXPosition, flYPosition) + M_PI;
		rotation *= 180.0f / M_PI;

		float flYawRadians = -(rotation)* M_PI / 180.0f;
		float flCosYaw = cos(flYawRadians);
		float flSinYaw = sin(flYawRadians);

		flXPosition = (int)((width / 2.0f) + (radius * flSinYaw));
		flYPosition = (int)((height / 2.0f) - (radius * flCosYaw));

		CColor Arrow_clr = pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() ?
			CColor(ClientVars.Col.TeamESP[0] * 255, ClientVars.Col.TeamESP[1] * 255, ClientVars.Col.TeamESP[2] * 255, alpha[pEntity->GetIndex()]) :
			CColor(ClientVars.Col.Arrows[0] * 255, ClientVars.Col.Arrows[1] * 255, ClientVars.Col.Arrows[2] * 255, alpha[pEntity->GetIndex()]);
		int r, g, b, a;
		Arrow_clr.GetColor(r, g, b, a);
		Interfaces.pSurface->DrawSetColor(r, g, b, a);
		Interfaces.pSurface->DrawOutlinedRect(flXPosition - 1, flYPosition - 1, flXPosition + 1, flYPosition + 1);
	}

	static void CallGlow()
	{
		CGlowObjectManager* GlowObjectManager = (CGlowObjectManager*)Interfaces.g_pGlowObjectManager;

		for (int i = 0; i < GlowObjectManager->size; ++i)
		{
			CGlowObjectManager::GlowObjectDefinition_t* glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];
			CBaseEntity* Entity = glowEntity->getEntity();

			if (glowEntity->IsEmpty() || !Entity)
				continue;

			char* EntName = Entity->GetClientClass()->m_pNetworkName;

			if (strstr(EntName, charenc("Projectile")) && ClientVars.Visual.Glow.GrenadeGlow)
			{
				glowEntity->set(CColor(ClientVars.Col.GrenadeGlow[0] * 255, ClientVars.Col.GrenadeGlow[1] * 255, ClientVars.Col.GrenadeGlow[2] * 255, ClientVars.Col.GrenadeGlow[3] * 255), 0);
			}
			if ((strstr(EntName, charenc("CWeapon")) || strstr(EntName, charenc("CAK47")) || strstr(EntName, charenc("CDEagle"))) && ClientVars.Visual.Glow.WeaponGlow)
			{
				glowEntity->set(CColor(ClientVars.Col.WeaponGlow[0] * 255, ClientVars.Col.WeaponGlow[1] * 255, ClientVars.Col.WeaponGlow[2] * 255, ClientVars.Col.WeaponGlow[3] * 255), 0);
			}
			if ((strstr(EntName, charenc("CPlantedC4")) || strstr(EntName, charenc("CC4"))) && ClientVars.Visual.Glow.BombGlow)
			{
				glowEntity->set(CColor(ClientVars.Col.BombGlow[0] * 255, ClientVars.Col.BombGlow[1] * 255, ClientVars.Col.BombGlow[2] * 255, ClientVars.Col.BombGlow[3] * 255), 0);
			}
			if (strstr(EntName, charenc("CCSPlayer")))
			{
				if (Entity->GetTeam() == Hacks.LocalPlayer->GetTeam() && ClientVars.Visual.Glow.GlowTeam)
					glowEntity->set(CColor(ClientVars.Col.TeamGlow[0] * 255, ClientVars.Col.TeamGlow[1] * 255, ClientVars.Col.TeamGlow[2] * 255, ClientVars.Col.TeamGlow[3] * 255), 0);

				if (Entity->GetTeam() != Hacks.LocalPlayer->GetTeam() && ClientVars.Visual.Glow.GlowEnemy)
				{
					if (!ClientVars.Col.EnemyGlowHB)
						glowEntity->set(CColor(ClientVars.Col.EnemyGlow[0] * 255, ClientVars.Col.EnemyGlow[1] * 255, ClientVars.Col.EnemyGlow[2] * 255, ClientVars.Col.EnemyGlow[3] * 255), 0);
					else
						glowEntity->set(Entity->GetHealthColor(ClientVars.Col.EnemyGlow[3] * 255), 0);
				}
			}
		}
	}
};