#pragma once
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include "../IMGUI/imgui.h"

struct skinInfo
{
	int seed = -1;
	int paintkit;
	std::string tagName;
};

struct MenuVars
{
	MenuVars()
	{ }

	struct Ragebot
	{
		bool Enable;
		float FOV = 180.f;
		bool pSilent;
		bool Norecoil;
		bool Autowall;
		bool AutoPistol;

		bool resolver;
		
		int MinDmg;
		int HitChance;

		int Hitscan;
		int AimbotSelection;

		int Hitbox;

		float Headscale;
		float Bodyscale;

		bool autofire;
		bool autoscope;

	}Ragebot;

	struct AntiAim
	{
		bool enabled;
		int FakeAngleChams;
		
		int Pitch;
		
		struct StandAA
		{
			int Yaw;
			float YawAdd;
			float JitterRange;
			float speed;
		}Stand;

		struct MoveAA
		{
			int Yaw;
			float YawAdd;
			float JitterRange;
			float speed;
		}Move;

		struct FakeAA
		{
			int Yaw;
			float YawAdd;
			float JitterRange;
			float speed;
		}Fake;

	}AntiAim;

	struct FakeLag
	{
		bool Enabled;

		int Choke;
		int ChokeMode;

		bool WhileShooting;
		bool Onground;
		bool WhileStill;

	}FakeLag;

	struct Legitbot
	{
		bool backtracking;
		bool teammates;

		bool HistoryChams;
	}Legitbot;

	struct Triggerbot
	{
		bool Enabled;
		bool Teammates;
		int Key;
		struct Filters
		{
			bool Head;
			bool Chest;
			bool Stomach;
			bool Arms;
			bool Legs;
			bool Friendly;
		}Filter;
	}Triggerbot;

	struct Skinchanger
	{
		bool Enabled;

		int CurrentMenuWeapon;

		int KnifeModel;

		int GloveType;


		std::unordered_map<std::string, std::set<std::string>> weaponSkins;
		std::unordered_map<std::string, skinInfo> skinMap;
		std::unordered_map<std::string, std::string> skinNames;
		std::vector<std::string> weaponNames;
	}Skinchanger;

	class WeaponConfigs
	{
	public:
		struct Skins
		{
			int skinID = 0;
			char name[32] = "";
			int StatTrak = -1;
			int Seed = 0.0001f;
			float Wear = 0.f;
		}Skn;
	};
	WeaponConfigs* W = new WeaponConfigs[5034];

	struct Visuals
	{
		bool BoundingBox;
		int Box;
		bool Showteam;
		bool Health;
		bool Ammo;
		bool Armor;
		bool Money;
		bool Name;
		bool Callout;
		bool Weapon;
		int wpnmode;
		bool Vulnerabilities;
		bool AimLine;
		bool Skeleton;

		bool Arrows;

		bool Localinfo;

		bool SpreadCircle;
		bool Hitmarker;
		bool BulletTracers;

		bool Droppedguns;
		bool Grenades;
		bool Crosshair;
		bool InaccuracyCrosshair;

		bool Bomb;
		bool NadePred;
		bool soundesp;

		bool speclist;
		bool nightmode;

		struct Chams
		{
			bool Enabled;
			int Player_mat;
			bool Team;
			bool Player_weapon;
			bool XQZ;
		}Chams;

		bool handcham;
		bool weaponviewcham;
		int weaponmat;
		int handmat;

		bool NoVisRecoil;
		bool NoFlash;
		bool NoSmoke;
		bool LBYIndicator;
		int Thirdperson;
		int tpdist = 150;
		int tpkey;
		bool NoScope;
		bool DrawScope;
		float FOV;
		float viewFOV;
		bool engineradar;
		bool DLight;
		bool DLightteam;
		bool ELight;

		struct Glow
		{
			bool GlowEnemy;
			bool GlowTeam;

			bool WeaponGlow;

			bool BombGlow;

			bool GrenadeGlow;
		}Glow;
		

		bool radrenable;
		int radrsize = 200;
		float radralpha = 1.f;
		float radrzoom = 2.f;
	}Visual;

	struct Misc
	{
		bool Enabled;
		bool Bhop;
		bool RankReveal;
		bool Strafe;
		int slomokey;
		bool slomo;
		int Strafetype;
		bool CircleStrafe;
		int CStrafeKey;
		bool zStrafe;
		int Crashmode;
		int FakeLagAmt;
		bool inairfl;
		int FakeLagType;
		bool AutoAccept;
		bool Clantag;
		int ClanType;
		bool AnimClantag;
		bool AnimName;
		bool largespam;
		bool Knifebot;
		bool walkbot;
		int walkbotdist;
		int walkbotturn;
		int autoblock;

		int Lagexploit;
		float lagamount;

		bool fakelatency;
		int desiredlatency;

		bool Antiuntrusted = true;
		bool Antiuntrustedproxy = true;
	}Misc;

	struct Colors
	{
		float TeamESP[3] = { 0, 1.f, 0 };
		float EnemyESP[3] = { 1.f, 0.f, 0.f };
		bool EnemyESPHB = false;

		float Aimlines[3] = { 1.f, 1.f, 1.f };
		bool EnemyAimlineHB = false;

		float Skeleton[3] = { 1.f, 1.f, 1.f };
		bool EnemySkeletonHB = false;

		float Ammo[3] = { 1.f, 1.f, 1.f };
		float Hitmarker[3] = { 1.f, 1.f, 1.f };

		float Arrows[3] = { 1.f, 1.f, 1.f };

		float Crosshair[4] = { 1.f, 1.f, 1.f, 1.f };
		float InaccuracyCrosshair[4] = {1.f, 1.f, 1.f, 1.f};

		float TeamDLights[3] = { 0, 1.f, 0 };
		float EnemyDLights[3] = { 1.f, 0, 0 };

		float EnemyGlow[4] = { 1.f, 1.f, 1.f, 1.f };
		bool EnemyGlowHB = false;

		float TeamGlow[4] = { 1.f, 1.f, 1.f, 1.f };
		float WeaponGlow[4] = { 1.f, 1.f, 1.f, 1.f };
		float BombGlow[4] = { 1.f, 1.f, 1.f, 1.f };
		float GrenadeGlow[4] = { 1.f, 1.f, 1.f, 1.f };

		float EnemyChams[4] = { 1.f, 1.f, 1.f, 1.f };
		bool EnemyChamsHB = false;

		float EnemyChamsXQZ[4] = { 1.f, 0, 0, 1.f };
		bool EnemyChamsXQZHB = false;

		float TeamChams[4] = { 0.f, 1.f, 0.f, 1.f };

		float WeaponCham[3] = { 1.f, 0, 0 };
		float HandCham[3] = { 0, 0, 0 };
		float WeaponViewCham[3] = { 1.f, 1.f, 1.f };

		float AngleChams[4] = { 1.f, 1.f, 1.f };
	}Col;

};

extern MenuVars ClientVars;

struct GlobalVariables
{
	GlobalVariables()
	{ }

	bool PressedKeys[256] = {};
	float hitmarkeralpha;
	bool MenuOpened = false;
	bool UTchecked = false;
};

extern GlobalVariables GVars;