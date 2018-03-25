#pragma once
#include "../../stdafx.h"
#include "Tools\IMGUI\imgui.h"
#include "Tools\IMGUI\DX9\imgui_impl_dx9.h"
#include "Tools\IMGUI\imgui_internal.h"
#include "Config.h"
#include "../Hacks/Parser.h"
#include <ctype.h>
#include <minwindef.h>

const char* keyNames[] =
{
	"Off",
	"Mouse 1",
	"Mouse 2",
	"Cancel",
	"Middle Mouse",
	"Mouse 4",
	"Mouse 5",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",

};

bool IsNonSkinWeapon(int index)
{
	switch (index)
	{
	case WEAPON_NONE:
	case WEAPON_C4:
	case WEAPON_FLASHBANG:
	case WEAPON_HEGRENADE:
	case WEAPON_INCGRENADE:
	case WEAPON_MOLOTOV:
	case WEAPON_SMOKEGRENADE:
	case WEAPON_DECOY:
	case WEAPON_KNIFE_T:
	case WEAPON_KNIFE_CT:
	case GLOVE_T_SIDE:
	case GLOVE_CT_SIDE:
		return true;
	default:
		return false;
	}
}

const char* weaponnames(int id)
{
	switch (id)
	{
	case 1:
		return "deagle";
	case 2:
		return "elite";
	case 3:
		return "fiveseven";
	case 4:
		return "glock";
	case 7:
		return "ak47";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 10:
		return "famas";
	case 11:
		return "g3sg1";
	case 13:
		return "galilar";
	case 14:
		return "m249";
	case 60:
		return "m4a1_silencer";
	case 16:
		return "m4a1";
	case 17:
		return "mac10";
	case 19:
		return "p90";
	case 24:
		return "ump45";
	case 25:
		return "xm1014";
	case 26:
		return "bizon";
	case 27:
		return "mag7";
	case 28:
		return "negev";
	case 29:
		return "sawedoff";
	case 30:
		return "tec9";
	case 32:
		return "hkp2000";
	case 33:
		return "mp7";
	case 34:
		return "mp9";
	case 35:
		return "nova";
	case 36:
		return "p250";
	case 38:
		return "scar20";
	case 39:
		return "sg556";
	case 40:
		return "ssg08";
	case 61:
		return "usp_silencer";
	case 63:
		return "cz75a";
	case 64:
		return "revolver";
	case 508:
		return "knife_m9_bayonet";
	case 500:
		return "bayonet";
	case 505:
		return "knife_flip";
	case 506:
		return "knife_gut";
	case 507:
		return "knife_karambit";
	case 509:
		return "knife_tactical";
	case 512:
		return "knife_falchion";
	case 514:
		return "knife_survival_bowie";
	case 515:
		return "knife_butterfly";
	case 516:
		return "knife_push";
	case 5027:
		return "studded_bloodhound_gloves";
	case 5030:
		return "sporty_gloves";
	case 5031:
		return "slick_gloves";
	case 5032:
		return "leather_handwraps";
	case 5033:
		return "motorcycle_gloves";
	case 5034:
		return "specialist_gloves";
	default:
		return "";
	}
}

bool Contains(const std::string &word, const std::string &sentence) {
	if (word == "" || sentence == "")
		return true;

	return sentence.find(word) != std::string::npos;
}

std::string ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}

#define MENU_SIZE_X 600
#define MENU_SIZE_Y 400
#define TAB_COUNT 5
#define SUBTAB_COUNT 6

void Tab(const char* name, int* v, int tab_id) {

	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4 oldtext = style.Colors[ImGuiCol_Text];
	ImVec4 oldbutton = style.Colors[ImGuiCol_Button];
	if (tab_id != 0)
	{
		ImGui::SameLine();
	}
	style.Colors[ImGuiCol_Button] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
	if (*v != tab_id)
	{
		style.Colors[ImGuiCol_Text] = ImVec4(0.3f, 0.3f, 0.3f, 1.f);
	}
	if (ImGui::Button(name, ImVec2((MENU_SIZE_X - 15) / TAB_COUNT, 25)))
	{
		*v = tab_id;
	}
	style.Colors[ImGuiCol_Button] = oldbutton;
	style.Colors[ImGuiCol_Text] = oldtext;

}
void SubTab(const char* name, int* v, int tab_id) {

	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4 oldtext = style.Colors[ImGuiCol_Text];
	ImVec4 oldbutton = style.Colors[ImGuiCol_Button];
	if (tab_id != 0)
	{
		ImGui::SameLine();
	}
	style.Colors[ImGuiCol_Button] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	if (*v != tab_id)
	{
		style.Colors[ImGuiCol_Text] = ImVec4(0.3f, 0.3f, 0.3f, 1.f);
	}
	if (ImGui::Button(name, ImVec2((MENU_SIZE_X - 30) / SUBTAB_COUNT, 35)))
	{
		*v = tab_id;
	}
	style.Colors[ImGuiCol_Button] = oldbutton;
	style.Colors[ImGuiCol_Text] = oldtext;

}

namespace DXM
{
	void FullUpdate()
	{
		ConVar* fullupdate = Interfaces.g_ICVars->FindVar("cl_fullupdate");
		fullupdate->nFlags &= ~FCVAR_CHEAT;
		Interfaces.pEngine->ClientCmd_Unrestricted("cl_fullupdate", 0);
	}

	void Menu()
	{
		POINT Mouse;
		POINT mp;
		GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x;
		Mouse.y = mp.y;
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos.x = (float)(mp.x);
		io.MousePos.y = (float)(mp.y);
		auto& style = ImGui::GetStyle();

		bool open = true;
		ImVec4 defaultborder = style.Colors[ImGuiCol_Border];
		style.Colors[ImGuiCol_Border] = style.Colors[ImGuiCol_WindowBg];
		ImGui::PushFont(fontskek.tahoma);
		if (!ClientVars.Misc.Antiuntrustedproxy && !GVars.UTchecked)
		{
			ImGui::OpenPopup("Untrusted Warning");
			bool yeet = true;
			if (ImGui::BeginPopupModal("Untrusted Warning", &yeet, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
			{
				ImGui::Text("Anti-Untrusted clamps your angles to prevent bans from\nValve's server-side anticheat, if you disable protection\nyou WILL be banned forever if you are on a VALVE server \n(this doesnt include community servers)");
				if (ImGui::Button("I am NOT on a VALVE server"))
				{
					GVars.UTchecked = true;
					ClientVars.Misc.Antiuntrusted = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("Stay Safe"))
				{
					GVars.UTchecked = false;
					ClientVars.Misc.Antiuntrustedproxy = true;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
		if (ClientVars.Misc.Antiuntrustedproxy)
		{
			ClientVars.Misc.Antiuntrusted = true;
			GVars.UTchecked = false;
		}

		ImGui::Begin(charenc(u8"Ichigo"), &open, ImVec2(MENU_SIZE_X, MENU_SIZE_Y), 0.7f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
		style.WindowPadding = ImVec2(0.f, 0.f);
		style.Colors[ImGuiCol_Border] = defaultborder;
		ImGui::BeginChild(charenc("##tabs"), ImVec2(MENU_SIZE_X - 15, MENU_SIZE_Y - 34), true, ImGuiWindowFlags_AlwaysUseWindowPadding);

		style.FrameBorderSize = 0.f;
		ImVec2 defaultspacing = style.ItemSpacing;
		style.ItemSpacing = ImVec2(0.f, 0.f);

		static int current_tab = 0;
		ImGui::PushFont(fontskek.impact);
		Tab(charenc("RAGE"), &current_tab, 0);
		Tab(charenc("LEGIT"), &current_tab, 1);
		Tab(charenc("VISUALS"), &current_tab, 2);
		Tab(charenc("MISC"), &current_tab, 3);
		Tab(charenc("SKINS"), &current_tab, 4);
		ImGui::PopFont();
		style.WindowPadding = ImVec2(8.f, 8.f);
		style.ItemSpacing = defaultspacing;
		ImGui::BeginChild(charenc("##main"), ImVec2(-1, -1), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
		if (current_tab == 0)
		{

			style.ItemSpacing = ImVec2(0.f, 0.f);
			style.WindowPadding = ImVec2(0.f, 0.f);
			ImGui::BeginChild(charenc("##weaponcfg0"), ImVec2(570, 35), true);
			static int subtab0 = 0;
			ImGui::PushFont(fontskek.icons);
			SubTab(charenc(u8"\uE001"), &subtab0, 0);
			SubTab(charenc(u8"\uE009"), &subtab0, 1);
			SubTab(charenc(u8"\uE00B"), &subtab0, 2);
			SubTab(charenc(u8"\uE007"), &subtab0, 3);
			SubTab(charenc(u8"\uE011"), &subtab0, 4);
			SubTab(charenc(u8"\uE023"), &subtab0, 5);
			ImGui::PopFont();
			ImGui::EndChild();
			style.WindowPadding = ImVec2(8.f, 8.f);
			style.ItemSpacing = ImVec2(8.f, 8.f);

			ImGui::Spacing();

			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
			ImGui::BeginChild(charenc("##0groupbox0"), ImVec2(555 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Checkbox(charenc("Ragebot Enable"), &ClientVars.Ragebot.Enable);
		//	ImGui::Checkbox(charenc("Aimstep"), &ClientVars.Ragebot.aimstep);
			ImGui::SliderFloat(charenc("##FOV"), &ClientVars.Ragebot.FOV, 0, 180, "FOV: %.0f");
			ImGui::Checkbox(charenc("Autowall"), &ClientVars.Ragebot.Autowall);
			ImGui::Combo("Selection", &ClientVars.Ragebot.AimbotSelection, "FOV\0\rDistance\0\rCylcle\0\0", -1);
			ImGui::Checkbox(charenc("Autopistol"), &ClientVars.Ragebot.AutoPistol);
			ImGui::Checkbox(charenc("No Recoil"), &ClientVars.Ragebot.Norecoil);
			ImGui::Checkbox(charenc("pSilent"), &ClientVars.Ragebot.pSilent);
			ImGui::Checkbox(charenc("Autoshoot"), &ClientVars.Ragebot.autofire);
			ImGui::Checkbox(charenc("Autoscope"), &ClientVars.Ragebot.autoscope);
			ImGui::Checkbox(charenc("Resolver"), &ClientVars.Ragebot.resolver);
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##0groupbox1"), ImVec2(555 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Combo("Hitbox", &ClientVars.Ragebot.Hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
			ImGui::Combo("Hitscan", &ClientVars.Ragebot.Hitscan, "Disabled\0\rRegualr\0\rMedium\0\rExtreme\0\0", -1);
			ImGui::SliderInt(charenc("##Hitchance"), &ClientVars.Ragebot.HitChance, 0, 100, "Hitchance: %0.f");
			ImGui::SliderInt(charenc("##Minimum Damage"), &ClientVars.Ragebot.MinDmg, 0, 100, "Minimum damage: %0.f");

			ImGui::SliderFloat(charenc("##headscale"), &ClientVars.Ragebot.Headscale, 0.f, 1.f, "Head Scale: %.2f");
			ImGui::SliderFloat(charenc("##bodyscale"), &ClientVars.Ragebot.Bodyscale, 0.f, 1.f, "Body Scale: %.2f");
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##0groupbox2"), ImVec2(555 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Checkbox(charenc("AA On"), &ClientVars.AntiAim.enabled);
			ImGui::PushItemWidth(ImGui::GetWindowWidth() - 33); // for le epic dropbox + color picker 
			ImGui::Combo("Fake Angle Chams", &ClientVars.AntiAim.FakeAngleChams, "Off\0\rViewangles\0\rLBY\0\0", -1);
			ImGui::PopItemWidth();
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##fake angle chams", ClientVars.Col.AngleChams, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.WindowPadding = ImVec2(8.f, 8.f);
			style.ItemSpacing = defaultspacing;
		}
		if (current_tab == 1)
		{
			ImVec2 defaultspacing2 = style.ItemSpacing;
			style.ItemSpacing = ImVec2(0.f, 0.f);
			style.WindowPadding = ImVec2(0.f, 0.f);
			ImGui::BeginChild(charenc("##weaponcfg1"), ImVec2(570, 35), true);
			static int subtab1 = 0;
			ImGui::PushFont(fontskek.icons);
			SubTab(charenc(u8"\uE001"), &subtab1, 0);
			SubTab(charenc(u8"\uE009"), &subtab1, 1);
			SubTab(charenc(u8"\uE00B"), &subtab1, 2);
			SubTab(charenc(u8"\uE007"), &subtab1, 3);
			SubTab(charenc(u8"\uE011"), &subtab1, 4);
			SubTab(charenc(u8"\uE023"), &subtab1, 5);
			ImGui::PopFont();
			ImGui::EndChild();
			style.WindowPadding = ImVec2(8.f, 8.f);
			style.ItemSpacing = ImVec2(8.f, 8.f);

			ImGui::Spacing();
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
			ImGui::BeginChild(charenc("##1groupbox0"), ImVec2(555 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Checkbox(charenc("History Ticks"), &ClientVars.Legitbot.backtracking);
			ImGui::Checkbox(charenc("Legitbot team"), &ClientVars.Legitbot.teammates);
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##1groupbox1"), ImVec2(555 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##1groupbox2"), ImVec2((555 / 3) - 1, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Checkbox(charenc("Triggerbot"), &ClientVars.Triggerbot.Enabled);
			ImGui::Checkbox(charenc("Trigger Team"), &ClientVars.Triggerbot.Teammates);
			ImGui::Combo(charenc("Trigger Key"), &ClientVars.Triggerbot.Key, keyNames, ARRAYSIZE(keyNames));

			ImGui::Text(charenc("Filter:"));
			ImGui::Selectable(charenc(" Head"), &ClientVars.Triggerbot.Filter.Head);
			ImGui::Selectable(charenc(" Arms"), &ClientVars.Triggerbot.Filter.Arms);
			ImGui::Selectable(charenc(" Chest"), &ClientVars.Triggerbot.Filter.Chest);
			ImGui::Selectable(charenc(" Stomach"), &ClientVars.Triggerbot.Filter.Stomach);
			ImGui::Selectable(charenc(" Legs"), &ClientVars.Triggerbot.Filter.Legs);
		
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.WindowPadding = ImVec2(8.f, 8.f);
			style.ItemSpacing = defaultspacing2;
		}
		if (current_tab == 2)
		{

			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
			ImGui::BeginChild(charenc("##2groupbox0"), ImVec2(555 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Checkbox(charenc("Team ESP"), &ClientVars.Visual.Showteam);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp team", ClientVars.Col.TeamESP, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview );
			ImGui::Checkbox(charenc("Box"), &ClientVars.Visual.BoundingBox);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp enemy", ClientVars.Col.EnemyESP, true, &ClientVars.Col.EnemyESPHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Aimlines"), &ClientVars.Visual.AimLine);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp aimlines", ClientVars.Col.Aimlines, true, &ClientVars.Col.EnemyAimlineHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Skeleton"), &ClientVars.Visual.Skeleton);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp skeleton", ClientVars.Col.Skeleton, true, &ClientVars.Col.EnemySkeletonHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			//ImGui::Checkbox(charenc("HeadBox"), &ClientVars.Visual.HeadBox);
			ImGui::Checkbox(charenc("Name"), &ClientVars.Visual.Name);
			ImGui::Checkbox(charenc("Weapon"), &ClientVars.Visual.Weapon);
			ImGui::Checkbox(charenc("Armor"), &ClientVars.Visual.Armor);
			ImGui::Checkbox(charenc("Vulnerabilities"), &ClientVars.Visual.Vulnerabilities);
			ImGui::Checkbox(charenc("Health"), &ClientVars.Visual.Health);
			ImGui::Checkbox(charenc("Money"), &ClientVars.Visual.Money);
			ImGui::Checkbox(charenc("Callout"), &ClientVars.Visual.Callout);
			ImGui::Checkbox(charenc("Ammo"), &ClientVars.Visual.Ammo);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp ammo", ClientVars.Col.Ammo, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::NewLine();
			ImGui::Checkbox(charenc("Sound ESP"), &ClientVars.Visual.soundesp);
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##2groupbox1"), ImVec2(555 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Checkbox(charenc("Dropped Weapons"), &ClientVars.Visual.Droppedguns);
			ImGui::Checkbox(charenc("Bomb ESP"), &ClientVars.Visual.Bomb);
			ImGui::Checkbox(charenc("Grenades"), &ClientVars.Visual.Grenades);
			ImGui::Checkbox(charenc("Crosshair"), &ClientVars.Visual.Crosshair);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##esp crosshair", ClientVars.Col.Crosshair, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Inaccuracy Crosshair"), &ClientVars.Visual.InaccuracyCrosshair);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##esp inaccuracycrosshair", ClientVars.Col.InaccuracyCrosshair, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Spectators"), &ClientVars.Visual.speclist);
			ImGui::Checkbox(charenc("Hitmarker"), &ClientVars.Visual.Hitmarker);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp hitmarker", ClientVars.Col.Hitmarker, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Off-Screen ESP"), &ClientVars.Visual.Arrows);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp arrows", ClientVars.Col.Arrows, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Localinfo"), &ClientVars.Visual.Localinfo);

			ImGui::NewLine();
			ImGui::Checkbox(charenc("Glow Enemy"), &ClientVars.Visual.Glow.GlowEnemy);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##glow enemy", ClientVars.Col.EnemyGlow, true, &ClientVars.Col.EnemyGlowHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Glow Team"), &ClientVars.Visual.Glow.GlowTeam);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##glow team", ClientVars.Col.TeamGlow, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Glow Weapons"), &ClientVars.Visual.Glow.WeaponGlow);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##glow weapons", ClientVars.Col.WeaponGlow, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Glow Bomb"), &ClientVars.Visual.Glow.BombGlow);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##glow bomb", ClientVars.Col.BombGlow, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Glow Grenades"), &ClientVars.Visual.Glow.GrenadeGlow);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##glow nades", ClientVars.Col.GrenadeGlow, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##2groupbox2"), ImVec2((555 / 3) - 1, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			
			ImGui::Text("Removals:");
			ImGui::Selectable(charenc("Visual Recoil"), &ClientVars.Visual.NoVisRecoil);
			ImGui::Selectable(charenc("Smokes"), &ClientVars.Visual.NoSmoke);
			ImGui::Selectable(charenc("Flashbangs"), &ClientVars.Visual.NoFlash);
			ImGui::Selectable(charenc("Scope"), &ClientVars.Visual.NoScope);
			

			ImGui::NewLine();

			ImGui::Checkbox(charenc("Chams Enabled"), &ClientVars.Visual.Chams.Enabled);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##cham enemy", ClientVars.Col.EnemyChams, true, &ClientVars.Col.EnemyChamsHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Chams Team"), &ClientVars.Visual.Chams.Team);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##cham team", ClientVars.Col.TeamChams, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);

			ImGui::Combo("Player Mat", &ClientVars.Visual.Chams.Player_mat, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rCrystal\0\0", -1);
			ImGui::Checkbox(charenc("XQZ"), &ClientVars.Visual.Chams.XQZ);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##cham xqz", ClientVars.Col.EnemyChamsXQZ, true, &ClientVars.Col.EnemyChamsXQZHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Weapon Chams"), &ClientVars.Visual.Chams.Player_weapon);

			ImGui::NewLine();
			ImGui::Checkbox(charenc("Hand Chams"), &ClientVars.Visual.handcham);

			ImGui::Combo("Arm Mat", &ClientVars.Visual.handmat, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rCrystal\0\0", -1);
			ImGui::Checkbox(charenc("Gun Chams"), &ClientVars.Visual.weaponviewcham);

			ImGui::Combo("Weapon Mat", &ClientVars.Visual.weaponmat, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rCrystal\0\0", -1);
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		}
		if (current_tab == 3)
		{
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
			ImGui::BeginChild(charenc("##3groupbox0"), ImVec2(555 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Checkbox(charenc("Anti Untrusted"), &ClientVars.Misc.Antiuntrustedproxy);
			static char buff[128];
			ImGui::InputText("##cfgname", buff, 20);

			if (ImGui::Button("Save CFG"))
				Config::Save(buff);

			ImGui::SameLine();

			if (ImGui::Button("Load CFG"))
				Config::Read(buff);
			ImGui::Checkbox(charenc("Rank Reveal"), &ClientVars.Misc.RankReveal);
			ImGui::Checkbox(charenc("Autoaccept"), &ClientVars.Misc.AutoAccept);

			ImGui::Checkbox("Radar", &ClientVars.Visual.radrenable);
			ImGui::SliderFloat("##radrzom", &ClientVars.Visual.radrzoom, 0.f, 4.f, "zoom: %.2f");
			ImGui::SliderFloat("##radralpha", &ClientVars.Visual.radralpha, 0.f, 1.f, "Alpha: %.2f");
			ImGui::SliderInt(charenc("##Size"), &ClientVars.Visual.radrsize, 100, 500, "Size: %.0f");

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##3groupbox1"), ImVec2(555 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			//ImGui::Checkbox("Fake Latency", &ClientVars.Misc.fakelatency);

			ImGui::Checkbox(charenc("Fakelag"), &ClientVars.FakeLag.Enabled);
			ImGui::Combo(charenc("Mode"), &ClientVars.FakeLag.ChokeMode, "Off\0\rStatic\0\0", -1);
			ImGui::SliderInt(charenc("##choke"), &ClientVars.FakeLag.Choke, 1, 13, "Choke: %0.f");
			ImGui::Checkbox(charenc("While Shooting"), &ClientVars.FakeLag.WhileShooting);
			ImGui::Checkbox(charenc("While Still"), &ClientVars.FakeLag.WhileStill);
			ImGui::Checkbox(charenc("On Ground"), &ClientVars.FakeLag.Onground);
			ImGui::NewLine();
			ImGui::SliderFloat(charenc("##fov"), &ClientVars.Visual.FOV, 0, 40, "FOV: %.0f");
			ImGui::SliderFloat(charenc("##viewfov"), &ClientVars.Visual.viewFOV, 0, 170, "View FOV: %.0f");
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##3groupbox2"), ImVec2((555 / 3) - 1, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);

			ImGui::Checkbox("Night Mode", &ClientVars.Visual.nightmode);

			if (ImGui::Button("Release Name"))
				Misc::setName("\n\xAD\xAD\xAD­­­");
			if (ImGui::Button("AYYWARE Crasher"))
				Misc::setName(u8"------------------------------------------------------------\u30A4\u30C1\u30B4-------------------------------------------------------------");

			ImGui::Checkbox("Animated Clan", &ClientVars.Misc.AnimClantag);
			if (ImGui::Button("Panic Button"))
			{
				GVars.MenuOpened = false;
				Unhook();
			}
			ImGui::Combo(charenc("Autoblock"), &ClientVars.Misc.autoblock, keyNames, ARRAYSIZE(keyNames));
			ImGui::Combo(charenc("Lag Exploit"), &ClientVars.Misc.Lagexploit, keyNames, ARRAYSIZE(keyNames));
			ImGui::SliderFloat(charenc("##lagamt"), &ClientVars.Misc.lagamount, 0, 1000, "Lag Amt: %.0f");
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		}
		if (current_tab == 4)
		{
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
			ImGui::BeginChild(charenc("##3groupbox0"), ImVec2((555 / 3), ImGui::GetContentRegionAvail().y ), false); style.FrameBorderSize = 0.f; ImGui::PushItemWidth(-1);
			ImGui::BeginChild(charenc("##3subgroupbox0"), ImVec2((555 / 3), (ImGui::GetContentRegionAvail().y / 2) - 10), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImVec2 defaultpadding = style.ItemSpacing;
			style.ItemSpacing = ImVec2(0.f, defaultpadding.y);
			ImGui::BeginChild(charenc("##weapons"), ImVec2(-1, -1));
			for (auto it : ItemDefinitionIndexMap)
			{
				if (IsNonSkinWeapon(it.first))
					continue;

				const bool item_selected = ((int)it.first == (int)ClientVars.Skinchanger.CurrentMenuWeapon);
				std::string formattedName;
				
				formattedName = ItemDefinitionIndexMap.at(it.first).name;
				if (ImGui::Selectable(formattedName.c_str(), item_selected))
				{
					ClientVars.Skinchanger.CurrentMenuWeapon = (int)it.first;
				}
			}
			ImGui::EndChild();
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::BeginChild(charenc("##3subgroupbox1"), ImVec2((555 / 3), -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Checkbox("Skinchanger", &ClientVars.Skinchanger.Enabled);
			ImGui::SliderFloat("##skinwear", &ClientVars.W[ClientVars.Skinchanger.CurrentMenuWeapon].Skn.Wear, 0.f, 1.f, "Wear: %.3f");
			ImGui::Text("Seed:");
			ImGui::InputInt("##seed", &ClientVars.W[ClientVars.Skinchanger.CurrentMenuWeapon].Skn.Seed);
			ImGui::Text("StatTrak:");
			ImGui::InputInt("##stattrak", &ClientVars.W[ClientVars.Skinchanger.CurrentMenuWeapon].Skn.StatTrak);
			ImGui::Text("Name:");
			ImGui::InputText("##name", ClientVars.W[ClientVars.Skinchanger.CurrentMenuWeapon].Skn.name, 32);

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			style.ItemSpacing = defaultpadding;
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			
			ImGui::SameLine();
			static char filterSkins[32];
			std::string skinName = weaponnames(ClientVars.Skinchanger.CurrentMenuWeapon);
			ImGui::BeginChild(charenc("##3groupbox2"), ImVec2((555 / 3), -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			if (ImGui::Button("Update", ImVec2(-1, 17)))
			{
				FullUpdate();
			}
			ImGui::InputText(charenc("##FILTERSKINS"), filterSkins, IM_ARRAYSIZE(filterSkins));
			ImGui::InputInt(charenc("##custom ID"), &ClientVars.W[ClientVars.Skinchanger.CurrentMenuWeapon].Skn.skinID);
			ImGui::BeginChild(charenc("##SKINS"), ImVec2(-1, -1));
			std::string skinStr = "";
			int curItem = -1;
			int s = 0;
			for (auto skin : ClientVars.Skinchanger.weaponSkins[skinName])
			{
				int pk = ClientVars.Skinchanger.skinMap[skin].paintkit;
				if (pk == ClientVars.W[ClientVars.Skinchanger.CurrentMenuWeapon].Skn.skinID)
					curItem = s;
				bool selected = ClientVars.W[ClientVars.Skinchanger.CurrentMenuWeapon].Skn.skinID == pk;

				skinStr = ClientVars.Skinchanger.skinNames[ClientVars.Skinchanger.skinMap[skin].tagName].c_str();
				skinStr += "##";
				skinStr += std::to_string(ClientVars.Skinchanger.skinMap[skin].paintkit);
				if (!Contains(ToLower(std::string(filterSkins)), ToLower(skinStr)))
					continue;
				if (ImGui::Selectable(skinStr.c_str(), selected))
				{
					pk = ClientVars.Skinchanger.skinMap[skin].paintkit;
					ClientVars.W[ClientVars.Skinchanger.CurrentMenuWeapon].Skn.skinID = pk;
					FullUpdate();
					break;
				}
				s++;
			}
			ImGui::EndChild();
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##3groupbox3"), ImVec2((555 / 3) - 1, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);

			ImGui::BeginChild(charenc("##knives"), ImVec2(-1, (ImGui::GetContentRegionAvail().y / 2) + 20));
			if (ImGui::Selectable(charenc("Default Knife"), ClientVars.Skinchanger.KnifeModel == 0))
			{
				ClientVars.Skinchanger.KnifeModel = 0;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Bayonet"), ClientVars.Skinchanger.KnifeModel == 500))
			{
				ClientVars.Skinchanger.KnifeModel = 500;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Flip Knife"), ClientVars.Skinchanger.KnifeModel == 505))
			{
				ClientVars.Skinchanger.KnifeModel = 505;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Gut Knife"), ClientVars.Skinchanger.KnifeModel == 506))
			{
				ClientVars.Skinchanger.KnifeModel = 506;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Karambit"), ClientVars.Skinchanger.KnifeModel == 507))
			{
				ClientVars.Skinchanger.KnifeModel = 507;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("M9 Bayonet"), ClientVars.Skinchanger.KnifeModel == 508))
			{
				ClientVars.Skinchanger.KnifeModel = 508;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Huntsman"), ClientVars.Skinchanger.KnifeModel == 509))
			{
				ClientVars.Skinchanger.KnifeModel = 509;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Falchion"), ClientVars.Skinchanger.KnifeModel == 512))
			{
				ClientVars.Skinchanger.KnifeModel = 512;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Bowie"), ClientVars.Skinchanger.KnifeModel == 514))
			{
				ClientVars.Skinchanger.KnifeModel = 514;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Butterfly Knife"), ClientVars.Skinchanger.KnifeModel == 515))
			{
				ClientVars.Skinchanger.KnifeModel = 515;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Shadow Daggers"), ClientVars.Skinchanger.KnifeModel == 516))
			{
				ClientVars.Skinchanger.KnifeModel = 516;
				FullUpdate();
			}
			ImGui::EndChild();

			ImGui::BeginChild(charenc("##gloves"), ImVec2(-1, -1));
			if (ImGui::Selectable(charenc("Default Gloves"), ClientVars.Skinchanger.GloveType == 0))
			{
				ClientVars.Skinchanger.GloveType = 0;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Bloodhound Gloves"), ClientVars.Skinchanger.GloveType == 5027))
			{
				ClientVars.Skinchanger.GloveType = 5027;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Sport Gloves"), ClientVars.Skinchanger.GloveType == 5030))
			{
				ClientVars.Skinchanger.GloveType = 5030;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Driver Gloves"), ClientVars.Skinchanger.GloveType == 5031))
			{
				ClientVars.Skinchanger.GloveType = 5031;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Leather Handwraps"), ClientVars.Skinchanger.GloveType == 5032))
			{
				ClientVars.Skinchanger.GloveType = 5032;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Motorcycle Gloves"), ClientVars.Skinchanger.GloveType == 5033))
			{
				ClientVars.Skinchanger.GloveType = 5033;
				FullUpdate();
			}
			if (ImGui::Selectable(charenc("Specialist Gloves"), ClientVars.Skinchanger.GloveType == 5034))
			{
				ClientVars.Skinchanger.GloveType = 5034;
				FullUpdate();
			}
			ImGui::EndChild();

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		}

		ImGui::EndChild();

		ImGui::EndChild();

		ImGui::End();
		ImGui::PopFont();
	}

	void DrawRadar()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec2 oldPadding = style.WindowPadding;
		float oldAlpha = style.Colors[ImGuiCol_WindowBg].w;
		style.WindowPadding = ImVec2(0, 0);
		style.Colors[ImGuiCol_WindowBg].w = (float)ClientVars.Visual.radralpha;
		ImGui::SetNextWindowSize(ImVec2(ClientVars.Visual.radrsize, ClientVars.Visual.radrsize));
		if (ImGui::Begin(charenc("Radar"), &GVars.MenuOpened))
		{
			ImVec2 siz = ImGui::GetWindowSize();
			ImVec2 pos = ImGui::GetWindowPos();

			ImGui::GetWindowDrawList()->AddRect(ImVec2(pos.x - 6, pos.y - 6), ImVec2(pos.x + siz.x + 6, pos.y + siz.y + 6), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), 0.0F, -1, 1.5f);

			ImDrawList* windowDrawList = ImGui::GetWindowDrawList();
			windowDrawList->AddLine(ImVec2(pos.x + (siz.x / 2), pos.y + 0), ImVec2(pos.x + (siz.x / 2), pos.y + siz.y), ImGui::GetColorU32(ImVec4(50, 50, 150, 100)), 1.f);
			windowDrawList->AddLine(ImVec2(pos.x + 0, pos.y + (siz.y / 2)), ImVec2(pos.x + siz.x, pos.y + (siz.y / 2)), ImGui::GetColorU32(ImVec4(50, 50, 150, 100)), 1.f);

			// Rendering players

			if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
			{
				
				if (Hacks.LocalPlayer)
				{
					Vector LocalPos = Hacks.LocalPlayer->GetEyePosition();
					Vector ang;
					Interfaces.pEngine->GetViewAngles(ang);
					for (int i = 0; i < Interfaces.pEngine->GetMaxClients(); i++) {
						CBaseEntity* pBaseEntity = Interfaces.pEntList->GetClientEntity(i);

						if (!pBaseEntity)
							continue;
						if (pBaseEntity->IsDormant())
							continue;
						if (!pBaseEntity->GetHealth() > 0)
							continue;
						if (pBaseEntity == Hacks.LocalPlayer)
							continue;
						
						if (Hacks.LocalPlayer->GetTeam() == pBaseEntity->GetTeam())
							continue;

						bool viewCheck = false;
						Vector EntityPos = Misc::RotatePoint(pBaseEntity->GetVecOrigin(), LocalPos, pos.x, pos.y, siz.x, siz.y, ang.y, ClientVars.Visual.radrzoom, &viewCheck);

						
						ImU32 clr = ImGui::GetColorU32(ImVec4(255, 0, 0, 255));

						int s = 3;

						windowDrawList->AddCircleFilled(ImVec2(EntityPos.x, EntityPos.y), s, clr);

					}
				}
			}
		}
		ImGui::End();
		style.WindowPadding = oldPadding;
		style.Colors[ImGuiCol_WindowBg].w = oldAlpha;
	}

	std::list<int> GetObservervators(int playerId)
	{
		std::list<int> list;

		if (!Interfaces.pEngine->IsInGame())
			return list;

		CBaseEntity* player = Interfaces.pEntList->GetClientEntity(playerId);
		if (!player)
			return list;

		if (!player->isAlive())
		{
			CBaseEntity* observerTarget = Interfaces.pEntList->GetClientEntityFromHandle(player->GetObserverTargetHandle());
			if (!observerTarget)
				return list;

			player = observerTarget;
		}

		for (int i = 1; i < Interfaces.pEngine->GetMaxClients(); i++)
		{
			CBaseEntity* pPlayer = Interfaces.pEntList->GetClientEntity(i);
			if (!pPlayer)
				continue;

			if (pPlayer->IsDormant() || pPlayer->isAlive())
				continue;

			CBaseEntity* target = Interfaces.pEntList->GetClientEntityFromHandle(pPlayer->GetObserverTargetHandle());
			if (player != target)
				continue;

			list.push_back(i);
		}

		return list;
	}

	void SpecList()
	{

		ImGuiStyle& style = ImGui::GetStyle();
		if (ImGui::Begin(charenc("Spectators"), &ClientVars.Visual.speclist, ImVec2(200, 150), 0.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar ))
		{
			if (Interfaces.pEngine->IsInGame())
			{
				for (int playerId : GetObservervators(Interfaces.pEngine->GetLocalPlayer()))
				{
					CBaseEntity* player = Interfaces.pEntList->GetClientEntity(playerId);

					player_info_t entityInformation;
					Interfaces.pEngine->GetPlayerInfo(playerId, &entityInformation);

					char buf[255]; sprintf_s(buf, u8"%s", entityInformation.m_szPlayerName);
					ImGui::Text((u8"%s"), buf);
				}
			}
			else
			{
				ImGui::Text("Not ingame");
			}
			ImGui::End();
		}
	}

	void OpenMenu()
	{
		static bool is_down = false;
		static bool is_clicked = false;
		static bool lastCursor = false;
		static bool firsttime = true;

		if (firsttime)
		{
			firsttime = !firsttime;
		}

		if (GVars.PressedKeys[VK_INSERT])
		{
			is_clicked = false;
			is_down = true;
		}
		else if (!GVars.PressedKeys[VK_INSERT] && is_down)
		{
			is_clicked = true;
			is_down = false;
		}
		else
		{
			is_clicked = false;
			is_down = false;
		}

		if (is_clicked)
		{
			GVars.MenuOpened = !GVars.MenuOpened;
			std::string msg = strenc("cl_mouseenable ") + std::to_string(!GVars.MenuOpened);
			Interfaces.pEngine->ClientCmd_Unrestricted(msg.c_str(), 0);
		}
	}
}