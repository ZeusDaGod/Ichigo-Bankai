#include "../../stdafx.h"
#include "IniReader.h"
#include "IniWriter.h"

namespace Config
{
	char* colornames(int col)
	{
		switch (col)
		{
		case 0:
			return "R";
			break;
		case 1:
			return "G";
			break;
		case 2:
			return "B";
			break;
		}
	}
	void Read(char* name)
	{
		static TCHAR path[MAX_PATH];
		std::string folder, file;
		if (strlen(name) > 0)
		{
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
			{
				folder = std::string(path) + strenc("\\frosty.pw\\");
				file = std::string(path) + strenc("\\frosty.pw\\") + std::string(name) + strenc(".frosty");
			}
		}
		else
		{
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
			{
				folder = std::string(path) + strenc("\\frosty.pw\\");
				file = std::string(path) + strenc("\\frosty.pw\\config.frsoty");
			}
		}

		CIniReader reader(file.c_str());



		//	Options::SkinChanger::EnabledKnife = reader.ReadBoolean("SkinChanger"), "|EnabledKnife"), false);
		//	Options::SkinChanger::EnabledGlove = reader.ReadBoolean("SkinChanger"), "|EnabledGlove"), false);
		//	Options::SkinChanger::Knife = reader.ReadInteger("SkinChanger"), "|Knife"), 3);
		//	Options::SkinChanger::Glove = reader.ReadInteger("SkinChanger"), "|Glove"), 5);
		//	Options::SkinChanger::GloveSkin = reader.ReadInteger("SkinChanger"), "|GloveSkin"), 0);

		//Ragebot
		ClientVars.Ragebot.Enable = reader.ReadBoolean("Ragebot", "Active", ClientVars.Ragebot.Enable);
		ClientVars.Ragebot.autofire = reader.ReadBoolean("Ragebot", "AutoShoot", ClientVars.Ragebot.autofire);
		ClientVars.Ragebot.AutoPistol = reader.ReadBoolean("Ragebot", "AutoPistol", ClientVars.Ragebot.AutoPistol);
		ClientVars.Ragebot.autoscope = reader.ReadBoolean("Ragebot", "AutoScope", ClientVars.Ragebot.autoscope);
		//ClientVars.Ragebot.autoduck = reader.ReadBoolean("Ragebot", "AutoDuck", ClientVars.Rage.autoduck);
		ClientVars.Ragebot.AimbotSelection = reader.ReadBoolean("Ragebot", "Aimstep", ClientVars.Ragebot.AimbotSelection);
		ClientVars.Ragebot.pSilent = reader.ReadBoolean("Ragebot", "pSilent", ClientVars.Ragebot.pSilent);
	//	ClientVars.Ragebot. = reader.ReadBoolean("Ragebot", "PosAdjust", ClientVars.Ragebot.Lagfix);
		ClientVars.Ragebot.resolver = reader.ReadBoolean("Ragebot", "Resolver", ClientVars.Ragebot.resolver);
		ClientVars.Ragebot.Hitbox = reader.ReadInteger("Ragebot", "Hitbox", ClientVars.Ragebot.Hitbox);
		ClientVars.Ragebot.Hitscan = reader.ReadInteger("Ragebot", "Hitscan", ClientVars.Ragebot.Hitscan);
		ClientVars.Ragebot.HitChance = reader.ReadInteger("Ragebot", "Hitchance", ClientVars.Ragebot.HitChance);
		ClientVars.Ragebot.MinDmg = reader.ReadInteger("Ragebot", "MinDmg", ClientVars.Ragebot.MinDmg);
		ClientVars.Ragebot.MinDmg = reader.ReadInteger("Ragebot", "MinDmg", ClientVars.Ragebot.MinDmg);
		ClientVars.Ragebot.Bodyscale = reader.ReadInteger("Ragebot", "Baim", ClientVars.Ragebot.Bodyscale);

		//AntiAims
		//Legitbot
		ClientVars.Legitbot.backtracking = reader.ReadBoolean("Legitbot", "Backtracking", ClientVars.Legitbot.backtracking);
		ClientVars.Legitbot.HistoryChams = reader.ReadBoolean("Legitbot", "History Chams", ClientVars.Legitbot.HistoryChams);
		ClientVars.Legitbot.teammates = reader.ReadBoolean("Legitbot", "Teammates", ClientVars.Legitbot.backtracking);

		//Triggerbot
		ClientVars.Triggerbot.Enabled = reader.ReadBoolean("Triggerbot", "Active", ClientVars.Triggerbot.Enabled);
		ClientVars.Triggerbot.Enabled = reader.ReadBoolean("Triggerbot", "Active", ClientVars.Triggerbot.Enabled);
		ClientVars.Triggerbot.Key = reader.ReadInteger("Triggerbot", "TriggerbotKey", ClientVars.Triggerbot.Key);
		ClientVars.Triggerbot.Filter.Head = reader.ReadBoolean("Triggerbot", "TriggerbotHead", ClientVars.Triggerbot.Filter.Head);
		ClientVars.Triggerbot.Filter.Chest = reader.ReadBoolean("Triggerbot", "TriggerbotChest", ClientVars.Triggerbot.Filter.Chest);
		ClientVars.Triggerbot.Filter.Arms = reader.ReadBoolean("Triggerbot", "TriggerbotArms", ClientVars.Triggerbot.Filter.Arms);
		ClientVars.Triggerbot.Filter.Legs = reader.ReadBoolean("Triggerbot", "TriggerbotLegs", ClientVars.Triggerbot.Filter.Legs);
		ClientVars.Triggerbot.Filter.Stomach = reader.ReadBoolean("Triggerbot", "TriggerbotStomach", ClientVars.Triggerbot.Filter.Stomach);
		ClientVars.Triggerbot.Filter.Friendly = reader.ReadBoolean("Triggerbot", "TriggerbotFriendly", ClientVars.Triggerbot.Filter.Friendly);

		//Esp
		ClientVars.Visual.Droppedguns = reader.ReadBoolean("ESP", "DroppedWeapons", ClientVars.Visual.Droppedguns);
		ClientVars.Visual.Bomb = reader.ReadBoolean("ESP", "BombEsp", ClientVars.Visual.Bomb);
		ClientVars.Visual.Grenades = reader.ReadBoolean("ESP", "Grenades", ClientVars.Visual.Grenades);
		ClientVars.Visual.NadePred = reader.ReadBoolean("ESP", "GrenadePrediction", ClientVars.Visual.NadePred);
		ClientVars.Visual.Crosshair = reader.ReadBoolean("ESP", "Crosshair", ClientVars.Visual.Crosshair);
		ClientVars.Visual.InaccuracyCrosshair = reader.ReadBoolean("ESP", "RecoilCrosshair", ClientVars.Visual.InaccuracyCrosshair);
		ClientVars.Visual.LBYIndicator = reader.ReadBoolean("ESP", "LBYIndicator", ClientVars.Visual.LBYIndicator);
		ClientVars.Visual.NoFlash = reader.ReadBoolean("ESP", "Vulnerable", ClientVars.Visual.NoFlash);
		ClientVars.Visual.AimLine = reader.ReadBoolean("ESP", "AimLines", ClientVars.Visual.AimLine);
		ClientVars.Visual.Showteam = reader.ReadBoolean("ESP", "TeamESP", ClientVars.Visual.Showteam);
		ClientVars.Visual.BoundingBox = reader.ReadBoolean("ESP", "BoxESP", ClientVars.Visual.BoundingBox);
		ClientVars.Visual.Box = reader.ReadInteger("ESP", "BoxType", ClientVars.Visual.Box);
		ClientVars.Visual.Skeleton = reader.ReadBoolean("ESP", "SkeletonESP", ClientVars.Visual.Skeleton);
		ClientVars.Visual.Name = reader.ReadBoolean("ESP", "NameESP", ClientVars.Visual.Name);
		ClientVars.Visual.Weapon = reader.ReadBoolean("ESP", "WeaponESP", ClientVars.Visual.Weapon);
		ClientVars.Visual.wpnmode = reader.ReadInteger("ESP", "WeaponType", ClientVars.Visual.wpnmode);
		ClientVars.Visual.Armor = reader.ReadBoolean("ESP", "ArmorESP", ClientVars.Visual.Armor);
		ClientVars.Visual.Health = reader.ReadBoolean("ESP", "HealthESP", ClientVars.Visual.Health);
		ClientVars.Visual.Money = reader.ReadBoolean("ESP", "MoneyESP", ClientVars.Visual.Money);
		ClientVars.Visual.Callout = reader.ReadBoolean("ESP", "CalloutESP", ClientVars.Visual.Callout);

		//Render
		ClientVars.Visual.FOV = reader.ReadFloat("Render", "FieldOfView", ClientVars.Visual.FOV);
		ClientVars.Visual.Thirdperson = reader.ReadFloat("Render", "Thirdperson", ClientVars.Visual.Thirdperson);
		ClientVars.Visual.NoVisRecoil = reader.ReadBoolean("Render", "NoVisualRecoil", ClientVars.Visual.NoVisRecoil);
		ClientVars.Visual.NoSmoke = reader.ReadBoolean("Render", "NoSmoke", ClientVars.Visual.NoSmoke);
		ClientVars.Visual.NoFlash = reader.ReadBoolean("Render", "NoFlash", ClientVars.Visual.NoFlash);
		ClientVars.Visual.NoScope = reader.ReadBoolean("Render", "NoScope", ClientVars.Visual.NoScope);
		ClientVars.Visual.radrenable = reader.ReadBoolean("Render", "RadarEnable", ClientVars.Visual.radrenable);
		ClientVars.Visual.radralpha = reader.ReadInteger("Render", "RadarAlpha", ClientVars.Visual.radralpha);
		ClientVars.Visual.radrsize = reader.ReadInteger("Render", "RadarSize", ClientVars.Visual.radrsize);
		ClientVars.Visual.radrzoom = reader.ReadFloat("Render", "RadarZoom", ClientVars.Visual.radrzoom);
		ClientVars.Visual.DLight = reader.ReadBoolean("Render", "DLight", ClientVars.Visual.DLight);
		ClientVars.Visual.DLightteam = reader.ReadBoolean("Render", "DLightTeam", ClientVars.Visual.DLightteam);
		ClientVars.Visual.ELight = reader.ReadBoolean("Render", "ELight", ClientVars.Visual.ELight);
		ClientVars.Visual.handcham = reader.ReadBoolean("Render", "HandChams", ClientVars.Visual.handcham);
		ClientVars.Visual.handmat = reader.ReadInteger("Render", "HandMaterial", ClientVars.Visual.handmat);
		ClientVars.Visual.weaponviewcham = reader.ReadBoolean("Render", "WeaponViewChams", ClientVars.Visual.weaponviewcham);
		ClientVars.Visual.weaponmat = reader.ReadBoolean("Render", "WeaponViewMaterial", ClientVars.Visual.weaponmat);

		//Misc
		ClientVars.Misc.Antiuntrustedproxy = reader.ReadBoolean("Misc", "AntiUntrust", ClientVars.Misc.Antiuntrustedproxy);
		ClientVars.Misc.Bhop = reader.ReadBoolean("Misc", "Bhop", ClientVars.Misc.Bhop);
		ClientVars.Misc.Strafe = reader.ReadBoolean("Misc", "AutoStrafe", ClientVars.Misc.Strafe);
		ClientVars.Misc.Strafetype = reader.ReadInteger("Misc", "StrafeType", ClientVars.Misc.Strafetype);
		ClientVars.Misc.CircleStrafe = reader.ReadBoolean("Misc", "CStrafe", ClientVars.Misc.CircleStrafe);
		ClientVars.Misc.CStrafeKey = reader.ReadInteger("Misc", "CStrafeKey", ClientVars.Misc.CStrafeKey);
		ClientVars.Misc.RankReveal = reader.ReadBoolean("Misc", "RankRevealer", ClientVars.Misc.RankReveal);
		ClientVars.Misc.AutoAccept = reader.ReadBoolean("Misc", "AutoAccept", ClientVars.Misc.AutoAccept);
		ClientVars.Misc.FakeLagType = reader.ReadInteger("Misc", "FakeLagType", ClientVars.Misc.FakeLagType);
		ClientVars.Misc.Knifebot = reader.ReadBoolean("Misc", "Knifebot", ClientVars.Misc.Knifebot);

		for (int i = 0; i < 3; i++)
		{
		char* section = colornames(i);
		ClientVars.Col.TeamESP[i] = reader.ReadFloat(section, "Team ESP", ClientVars.Col.TeamESP[i]);
		ClientVars.Col.EnemyESP[i] = reader.ReadFloat(section, "Enemy ESP", ClientVars.Col.EnemyESP[i]);
		ClientVars.Col.TeamDLights[i] = reader.ReadFloat(section, "Team DLights", ClientVars.Col.TeamDLights[i]);
		ClientVars.Col.EnemyDLights[i] = reader.ReadFloat(section, "Enemy DLights", ClientVars.Col.EnemyDLights[i]);
		ClientVars.Col.EnemyGlow[i] = reader.ReadFloat(section, "Enemy Glow", ClientVars.Col.EnemyGlow[i]);
		ClientVars.Col.TeamGlow[i] = reader.ReadFloat(section, "Team Glow", ClientVars.Col.TeamGlow[i]);
		ClientVars.Col.WeaponGlow[i] = reader.ReadFloat(section, "Weapon Glow", ClientVars.Col.WeaponGlow[i]);
		ClientVars.Col.WeaponCham[i] = reader.ReadFloat(section, "Weapon Cham", ClientVars.Col.WeaponCham[i]);
		}
		for (int i = 1; i < 520; i++)
		{
		char* section = Misc::GetGunNameByID(i);
		if (strcmp(section, "") == 0)
		continue;



		ClientVars.Skinchanger.Enabled = reader.ReadFloat(section, "ChangerEnabled", ClientVars.Skinchanger.Enabled);
		ClientVars.W[i].Skn.name[32] = *reader.ReadString(section, "ChangerName", ClientVars.W[i].Skn.name);
		ClientVars.W[1].Skn.Seed = reader.ReadFloat(section, "ChangerSeed", ClientVars.W[1].Skn.Seed);
		ClientVars.W[i].Skn.skinID = reader.ReadInteger(section, "ChangerSkin", ClientVars.W[i].Skn.skinID);
		ClientVars.W[1].Skn.StatTrak = reader.ReadInteger(section, "ChangerStatTrak", ClientVars.W[1].Skn.StatTrak);
		ClientVars.W[1].Skn.Wear = reader.ReadFloat(section, "ChangerWear", ClientVars.W[1].Skn.Wear);

		/*
		ClientVars.Skinchanger].Skn[32] = *reader.ReadString(section, "ChangerName", ClientVars.W[i].Skn.name);
		ClientVars.W[i].Skn = reader.ReadInteger(section, "ChangerSeed", ClientVars.W[i].Skn.Seed);
		ClientVars.W[i].Skn = reader.ReadInteger(section, "ChangerSkin", ClientVars.W[i].Skn.skinID);
		ClientVars.W[i].Skn = reader.ReadInteger(section, "ChangerStatTrak", ClientVars.W[i].Skn.StatTrak);
		ClientVars.W[i].Skn = reader.ReadFloat(section, "ChangerWear", ClientVars.W[i].Skn.Wear);*/
		}
	}

	void Save(char* name)
	{
		static TCHAR path[MAX_PATH];
		std::string folder, file;
		if (strlen(name) > 0)
		{
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
			{
				folder = std::string(path) + strenc("\\frosty.pw\\");
				file = std::string(path) + strenc("\\frosty.pw\\") + std::string(name) + strenc(".frosty");
			}
		}
		else
		{
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
			{
				folder = std::string(path) + strenc("\\frosty.pw\\");
				file = std::string(path) + strenc("\\frosty.pw\\config.frosty");
			}
		}

		CreateDirectory(folder.c_str(), NULL);

		CIniWriter writer(file.c_str());




		//	writer.WriteBoolean(strenc("SkinChanger"), strenc("|EnabledKnife"), Options::SkinChanger::EnabledKnife);
		//	writer.WriteBoolean(strenc("SkinChanger"), strenc("|EnabledGlove"), Options::SkinChanger::EnabledGlove);
		//	writer.WriteInteger(strenc("SkinChanger"), strenc("|Knife"), Options::SkinChanger::Knife);
		//	writer.WriteInteger(strenc("SkinChanger"), strenc("|Glove"), Options::SkinChanger::Glove);
		//	writer.WriteInteger(strenc("SkinChanger"), strenc("|GloveSkin"), Options::SkinChanger::GloveSkin);

		//Ragebot
		writer.WriteBoolean("Ragebot", "Active", ClientVars.Ragebot.Enable);
		writer.WriteBoolean("Ragebot", "AutoShoot", ClientVars.Ragebot.autofire);
		writer.WriteBoolean("Ragebot", "AutoPistol", ClientVars.Ragebot.AutoPistol);
		writer.WriteBoolean("Ragebot", "AutoScope", ClientVars.Ragebot.AutoPistol);
		writer.WriteBoolean("Ragebot", "Aimstep", ClientVars.Ragebot.AimbotSelection);
		writer.WriteBoolean("Ragebot", "pSilent", ClientVars.Ragebot.pSilent);
		writer.WriteBoolean("Ragebot", "Resolver", ClientVars.Ragebot.resolver);
		writer.WriteInteger("Ragebot", "Hitbox", ClientVars.Ragebot.Hitbox);
		writer.WriteInteger("Ragebot", "Hitscan", ClientVars.Ragebot.Hitscan);
		writer.WriteInteger("Ragebot", "Hitchance", ClientVars.Ragebot.HitChance);
		writer.WriteInteger("Ragebot", "MinDmg", ClientVars.Ragebot.MinDmg);
		writer.WriteInteger("Ragebot", "MinDmg", ClientVars.Ragebot.MinDmg);
		writer.WriteInteger("Ragebot", "Baim", ClientVars.Ragebot.Bodyscale);

		//AntiAims

		//Legitbot

		writer.WriteBoolean("Legitbot", "Backtracking", ClientVars.Legitbot.backtracking);
		writer.WriteBoolean("Legitbot", "History Chams", ClientVars.Legitbot.HistoryChams);
		writer.WriteBoolean("Legitbot", "Teammates", ClientVars.Legitbot.teammates);
		//Triggerbot
		writer.WriteBoolean("Triggerbot", "Active", ClientVars.Triggerbot.Enabled);
		writer.WriteBoolean("Triggerbot", "Active", ClientVars.Triggerbot.Enabled);
		writer.WriteInteger("Triggerbot", "TriggerKey", ClientVars.Triggerbot.Key);
		writer.WriteBoolean("Triggerbot", "TriggerHead", ClientVars.Triggerbot.Filter.Head);
		writer.WriteBoolean("Triggerbot", "TriggerChest", ClientVars.Triggerbot.Filter.Chest);
		writer.WriteBoolean("Triggerbot", "TriggerArms", ClientVars.Triggerbot.Filter.Arms);
		writer.WriteBoolean("Triggerbot", "TriggerLegs", ClientVars.Triggerbot.Filter.Legs);
		writer.WriteBoolean("Triggerbot", "TriggerStomach", ClientVars.Triggerbot.Filter.Stomach);
		writer.WriteBoolean("Triggerbot", "TriggerFriendly", ClientVars.Triggerbot.Filter.Friendly);

		//Esp
		writer.WriteBoolean("ESP", "DroppedWeapons", ClientVars.Visual.Droppedguns);
		writer.WriteBoolean("ESP", "BombEsp", ClientVars.Visual.Bomb);
		writer.WriteBoolean("ESP", "Grenades", ClientVars.Visual.Grenades);
		writer.WriteBoolean("ESP", "GrenadePrediction", ClientVars.Visual.NadePred);
		writer.WriteBoolean("ESP", "Crosshair", ClientVars.Visual.Crosshair);
		writer.WriteBoolean("ESP", "RecoilCrosshair", ClientVars.Visual.InaccuracyCrosshair);
		writer.WriteBoolean("ESP", "LBYIndicator", ClientVars.Visual.LBYIndicator);
		writer.WriteBoolean("ESP", "Vulnerable", ClientVars.Visual.NoFlash);
		writer.WriteBoolean("ESP", "AimLines", ClientVars.Visual.AimLine);
		writer.WriteBoolean("ESP", "TeamESP", ClientVars.Visual.Showteam);
		writer.WriteBoolean("ESP", "BoxESP", ClientVars.Visual.BoundingBox);
		writer.WriteInteger("ESP", "BoxType", ClientVars.Visual.Box);
		writer.WriteBoolean("ESP", "SkeletonESP", ClientVars.Visual.Skeleton);
		writer.WriteBoolean("ESP", "NameESP", ClientVars.Visual.Name);
		writer.WriteBoolean("ESP", "WeaponESP", ClientVars.Visual.Weapon);
		writer.WriteInteger("ESP", "WeaponType", ClientVars.Visual.wpnmode);
		writer.WriteBoolean("ESP", "ArmorESP", ClientVars.Visual.Armor);
		writer.WriteBoolean("ESP", "HealthESP", ClientVars.Visual.Health);
		writer.WriteBoolean("ESP", "MoneyESP", ClientVars.Visual.Money);
		writer.WriteBoolean("ESP", "CalloutESP", ClientVars.Visual.Callout);

		//Render
		writer.WriteFloat("Render", "FieldOfView", ClientVars.Visual.FOV);
		writer.WriteFloat("Render", "Thirdperson", ClientVars.Visual.Thirdperson);
		writer.WriteBoolean("Render", "NoVisRecoil", ClientVars.Visual.NoVisRecoil);
		writer.WriteBoolean("Render", "NoSmoke", ClientVars.Visual.NoSmoke);
		writer.WriteBoolean("Render", "NoFlash", ClientVars.Visual.NoFlash);
		writer.WriteBoolean("Render", "NoScope", ClientVars.Visual.NoScope);
		writer.WriteBoolean("Render", "RadarEnable", ClientVars.Visual.radrenable);
		writer.WriteInteger("Render", "RadarAlpha", ClientVars.Visual.radralpha);
		writer.WriteInteger("Render", "RadarSize", ClientVars.Visual.radrsize);
		writer.WriteFloat("Render", "RadarZoom", ClientVars.Visual.radrzoom);
		writer.WriteBoolean("Render", "GlowWeapon", ClientVars.Visual.Weapon);
		writer.WriteBoolean("Render", "DLight", ClientVars.Visual.DLight);
		writer.WriteBoolean("Render", "DLightTeam", ClientVars.Visual.DLightteam);
		writer.WriteBoolean("Render", "ELight", ClientVars.Visual.ELight);
		writer.WriteBoolean("Render", "HandChams", ClientVars.Visual.handcham);
		writer.WriteInteger("Render", "HandMaterial", ClientVars.Visual.handmat);
		writer.WriteBoolean("Render", "WeaponViewChams", ClientVars.Visual.weaponviewcham);
		writer.WriteBoolean("Render", "WeaponViewMaterial", ClientVars.Visual.weaponmat);

		//Misc
		writer.WriteBoolean("Misc", "AntiUntrust", ClientVars.Misc.Antiuntrustedproxy);
		writer.WriteBoolean("Misc", "Bhop", ClientVars.Misc.Bhop);
		writer.WriteBoolean("Misc", "AutoStrafe", ClientVars.Misc.Strafe);
		writer.WriteInteger("Misc", "StrafeType", ClientVars.Misc.Strafetype);
		writer.WriteBoolean("Misc", "CStrafe", ClientVars.Misc.CircleStrafe);
		writer.WriteInteger("Misc", "CStrafeKey", ClientVars.Misc.CStrafeKey);
		writer.WriteBoolean("Misc", "RankRevealer", ClientVars.Misc.RankReveal);
		writer.WriteBoolean("Misc", "AutoAccept", ClientVars.Misc.AutoAccept);
		writer.WriteInteger("Misc", "FakeLagType", ClientVars.Misc.FakeLagType);
		writer.WriteBoolean("Misc", "Knifebot", ClientVars.Misc.Knifebot);

		for (int i = 0; i < 3; i++)
		{
		char* section = colornames(i);
		//Colors
		writer.WriteFloat(section, "Team ESP", ClientVars.Col.TeamESP[i]);
		writer.WriteFloat(section, "Enemy ESP", ClientVars.Col.EnemyESP[i]);
		writer.WriteFloat(section, "Team DLights", ClientVars.Col.TeamDLights[i]);
		writer.WriteFloat(section, "Enemy DLights", ClientVars.Col.EnemyDLights[i]);
		writer.WriteFloat(section, "Enemy Glow", ClientVars.Col.EnemyGlow[i]);
		writer.WriteFloat(section, "Team Glow", ClientVars.Col.TeamGlow[i]);
		writer.WriteFloat(section, "Weapon Glow", ClientVars.Col.WeaponGlow[i]);
		writer.WriteFloat(section, "Weapon Cham", ClientVars.Col.WeaponCham[i]);
		}

		for (int i = 1; i < 520; i++)
		{
		char* section = Misc::GetGunNameByID(i);
		if (strcmp(section, "") == 0)
		continue;



		
		writer.WriteInteger(section, ("ChangerEnabled"), ClientVars.Skinchanger.Enabled);
		writer.WriteInteger(section, ("ChangerSkin"), ClientVars.W[i].Skn.skinID);
		writer.WriteString(section, ("ChangerName"), ClientVars.W[i].Skn.name);
		writer.WriteInteger(section, ("ChangerStatTrak"), ClientVars.W[i].Skn.StatTrak);
		writer.WriteInteger(section, ("ChangerSeed"), ClientVars.W[i].Skn.Seed);
	    writer.WriteFloat(section, ("ChangerWear"), ClientVars.W[i].Skn.Wear);



		}
	}
}