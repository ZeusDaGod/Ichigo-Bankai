#pragma once
#include "../../stdafx.h"
#include <array>

#define BONE_USED_BY_HITBOX 0x00000100

class IVModelInfo;

enum
{
	deagle = 1,
	p2000 = 32,
	fiveseven = 3,
	glock = 4,
	dualelites = 2,
	ak = 7,
	aug = 8,
	awp = 9,
	famas = 10,
	g3sg1 = 11,
	galil = 13,
	p250 = 36,
	tec9 = 30,
	m249 = 14,
	m4 = 16,
	mac10 = 17,
	p90 = 19,
	ump45 = 24,
	ppbizon = 26,
	negev = 28,
	mp7 = 33,
	mp9 = 34,
	scar30 = 38,
	sg553 = 39,
	ssg08 = 40,
	goldknife = 41,
	ctknife = 42,
	tknife = 59,
	flashgren = 43,
	hegren = 44,
	smoke = 45,
	molotov = 46,
	incendiary = 48,
	decoygren = 47,
	bomb = 49,
	nova = 35,
	xm1014 = 25,
	sawedoff = 29,
	mag7 = 27,
	zeus = 31
};

enum eWeaponType1
{
	WEAPON_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFEGG = 41,
	WEAPON_KNIFE_CT = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_R8REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034
};

struct DefItem_t
{
	DefItem_t(const char* displayName,
		const char* entityName,
		const char* entityModel,
		const char* killIcon,
		const char* name = nullptr)
	{
		this->displayName = displayName;
		this->entityName = entityName;
		this->entityModel = entityModel;
		this->killIcon = killIcon;
		this->name = name;
	}

	const char* displayName = nullptr;
	const char* entityName = nullptr;
	const char* entityModel = nullptr;
	const char* killIcon = nullptr;
	const char* name = nullptr;
};

const std::map<eWeaponType1, DefItem_t> ItemDefinitionIndexMap = 
{
	{ eWeaponType1::WEAPON_NONE,{ "<-Default->", "DEFAULT", "", "" , "All" } },
	{ eWeaponType1::WEAPON_DEAGLE,{ "#SFUI_WPNHUD_DesertEagle", "weapon_deagle", "models/weapons/v_pist_deagle.mdl", "deagle", "Desert Eagle" } },
	{ eWeaponType1::WEAPON_ELITE,{ "#SFUI_WPNHUD_Elites", "weapon_elite", "models/weapons/v_pist_elite.mdl", "elite", "Dual Berettas" } },
	{ eWeaponType1::WEAPON_FIVESEVEN,{ "#SFUI_WPNHUD_FiveSeven", "weapon_fiveseven", "models/weapons/v_pist_fiveseven.mdl", "fiveseven", "Five-SeveN" } },
	{ eWeaponType1::WEAPON_GLOCK,{ "#SFUI_WPNHUD_Glock18", "weapon_glock", "models/weapons/v_pist_glock18.mdl", "glock", "Glock-18" } },
	{ eWeaponType1::WEAPON_AK47,{ "#SFUI_WPNHUD_AK47", "weapon_ak47", "models/weapons/v_rif_ak47.mdl", "ak47", "AK47" } },
	{ eWeaponType1::WEAPON_AUG,{ "#SFUI_WPNHUD_Aug", "weapon_aug", "models/weapons/v_rif_aug.mdl", "aug", "AUG" } },
	{ eWeaponType1::WEAPON_AWP,{ "#SFUI_WPNHUD_AWP", "weapon_awp", "models/weapons/v_snip_awp.mdl", "awp", "AWP" } },
	{ eWeaponType1::WEAPON_FAMAS,{ "#SFUI_WPNHUD_Famas", "weapon_famas", "models/weapons/v_rif_famas.mdl", "famas", "FAMAS" } },
	{ eWeaponType1::WEAPON_G3SG1,{ "#SFUI_WPNHUD_G3SG1", "weapon_g3sg1", "models/weapons/v_snip_g3sg1.mdl", "g3sg1", "G3SG1" } },
	{ eWeaponType1::WEAPON_GALILAR,{ "#SFUI_WPNHUD_GalilAR", "weapon_galilar", "models/weapons/v_rif_galilar.mdl", "galilar", "GALIL-AR" } },
	{ eWeaponType1::WEAPON_M249,{ "#SFUI_WPNHUD_M249", "weapon_m249", "models/weapons/v_mach_m249para.mdl", "m249", "M249" } },
	{ eWeaponType1::WEAPON_M4A1,{ "#SFUI_WPNHUD_M4A1", "weapon_m4a1", "models/weapons/v_rif_m4a1.mdl", "m4a1", "M4A4" } },
	{ eWeaponType1::WEAPON_MAC10,{ "#SFUI_WPNHUD_MAC10", "weapon_mac10", "models/weapons/v_smg_mac10.mdl", "mac10", "MAC-10" } },
	{ eWeaponType1::WEAPON_P90,{ "#SFUI_WPNHUD_P90", "weapon_p90", "models/weapons/v_smg_p90.mdl", "p90", "P90" } },
	{ eWeaponType1::WEAPON_UMP45,{ "#SFUI_WPNHUD_UMP45", "weapon_ump45", "models/weapons/v_smg_ump45.mdl", "ump45", "UMP-45" } },
	{ eWeaponType1::WEAPON_XM1014,{ "#SFUI_WPNHUD_xm1014", "weapon_xm1014", "models/weapons/v_shot_xm1014.mdl", "xm1014", "XM1014" } },
	{ eWeaponType1::WEAPON_BIZON,{ "#SFUI_WPNHUD_Bizon", "weapon_bizon", "models/weapons/v_smg_bizon.mdl", "bizon", "PP-BIZON" } },
	{ eWeaponType1::WEAPON_MAG7,{ "#SFUI_WPNHUD_Mag7", "weapon_mag7", "models/weapons/v_shot_mag7.mdl", "mag7", "MAG-7" } },
	{ eWeaponType1::WEAPON_NEGEV,{ "#SFUI_WPNHUD_Negev", "weapon_negev", "models/weapons/v_mach_negev.mdl", "negev", "Negev" } },
	{ eWeaponType1::WEAPON_SAWEDOFF,{ "#SFUI_WPNHUD_Sawedoff", "weapon_sawedoff", "models/weapons/v_shot_sawedoff.mdl", "sawedoff", "Sawed-Off" } },
	{ eWeaponType1::WEAPON_TEC9,{ "#SFUI_WPNHUD_Tec9", "weapon_tec9", "models/weapons/v_pist_tec9.mdl", "tec9", "TEC-9" } },
	{ eWeaponType1::WEAPON_TASER,{ "#SFUI_WPNHUD_Taser", "weapon_taser", "models/weapons/v_eq_taser.mdl", "taser", "Zeus x27" } },
	{ eWeaponType1::WEAPON_HKP2000,{ "#SFUI_WPNHUD_HKP2000", "weapon_hkp2000", "models/weapons/v_pist_hkp2000.mdl", "hkp2000", "P2000" } },
	{ eWeaponType1::WEAPON_MP7,{ "#SFUI_WPNHUD_MP7", "weapon_mp7", "models/weapons/v_smg_mp7.mdl", "mp7", "MP7" } },
	{ eWeaponType1::WEAPON_MP9,{ "#SFUI_WPNHUD_MP9", "weapon_mp9", "models/weapons/v_smg_mp9.mdl", "mp9", "MP9" } },
	{ eWeaponType1::WEAPON_NOVA,{ "#SFUI_WPNHUD_Nova", "weapon_nova", "models/weapons/v_shot_nova.mdl", "nova", "Nova" } },
	{ eWeaponType1::WEAPON_P250,{ "#SFUI_WPNHUD_P250", "weapon_p250", "models/weapons/v_pist_p250.mdl", "p250", "P250" } },
	{ eWeaponType1::WEAPON_SCAR20,{ "#SFUI_WPNHUD_SCAR20", "weapon_scar20", "models/weapons/v_snip_scar20.mdl", "scar20", "SCAR-20" } },
	{ eWeaponType1::WEAPON_SG556,{ "#SFUI_WPNHUD_SG556", "weapon_sg556", "models/weapons/v_rif_sg556.mdl", "sg556", "SG556" } },
	{ eWeaponType1::WEAPON_SSG08,{ "#SFUI_WPNHUD_SSG08", "weapon_ssg08", "models/weapons/v_snip_ssg08.mdl", "ssg08", "SSG-08" } },
	{ eWeaponType1::WEAPON_KNIFE_CT,{ "#SFUI_WPNHUD_Knife", "weapon_knife", "models/weapons/v_knife_default_ct.mdl", "knife_default_ct", "CT Knife" } },
	{ eWeaponType1::WEAPON_FLASHBANG,{ "#SFUI_WPNHUD_FLASHBANG", "weapon_flashbang", "models/weapons/v_eq_flashbang.mdl", "flashbang", "flashbang" } },
	{ eWeaponType1::WEAPON_HEGRENADE,{ "#SFUI_WPNHUD_HE_Grenade", "weapon_hegrenade", "models/weapons/v_eq_fraggrenade.mdl", "hegrenade", "Grenade" } },
	{ eWeaponType1::WEAPON_SMOKEGRENADE,{ "#SFUI_WPNHUD_Smoke_Grenade", "weapon_smokegrenade", "models/weapons/v_eq_smokegrenade.mdl", "smokegrenade", "Smoke" } },
	{ eWeaponType1::WEAPON_MOLOTOV,{ "#SFUI_WPNHUD_MOLOTOV", "weapon_molotov", "models/weapons/v_eq_molotov.mdl", "inferno", "Molotov" } },
	{ eWeaponType1::WEAPON_DECOY,{ "#SFUI_WPNHUD_DECOY", "weapon_decoy", "models/weapons/v_eq_decoy.mdl", "decoy", "Decoy" } },
	{ eWeaponType1::WEAPON_INCGRENADE,{ "#SFUI_WPNHUD_IncGrenade", "weapon_incgrenade", "models/weapons/v_eq_incendiarygrenade.mdl", "inferno", "Incendiary" } },
	{ eWeaponType1::WEAPON_C4,{ "#SFUI_WPNHUD_C4", "weapon_c4", "models/weapons/v_ied.mdl", "null", "Bomb" } },
	{ eWeaponType1::WEAPON_KNIFE_T,{ "#SFUI_WPNHUD_Knife", "weapon_knife_t", "models/weapons/v_knife_default_t.mdl", "knife_t" , "T Knife" } },
	{ eWeaponType1::WEAPON_M4A1_SILENCER,{ "#SFUI_WPNHUD_M4_SILENCER", "weapon_m4a1_silencer", "models/weapons/v_rif_m4a1_s.mdl", "m4a1_silencer", "M4A1-S" } },
	{ eWeaponType1::WEAPON_USP_SILENCER,{ "#SFUI_WPNHUD_USP_SILENCER", "weapon_usp_silencer", "models/weapons/v_pist_223.mdl", "usp_silencer", "USP-S" } },
	{ eWeaponType1::WEAPON_CZ75A,{ "#SFUI_WPNHUD_CZ75", "weapon_cz75a", "models/weapons/v_pist_cz_75.mdl", "cz75a", "CZ75" } },
	{ eWeaponType1::WEAPON_R8REVOLVER,{ "#SFUI_WPNHUD_REVOLVER", "weapon_revolver", "models/weapons/v_pist_revolver.mdl", "revolver", "R8 Revolver" } },
	{ eWeaponType1::WEAPON_KNIFE_BAYONET,{ "#SFUI_WPNHUD_KnifeBayonet", "weapon_knife_bayonet", "models/weapons/v_knife_bayonet.mdl", "bayonet", "Bayonet" } },
	{ eWeaponType1::WEAPON_KNIFE_FLIP,{ "#SFUI_WPNHUD_KnifeFlip", "weapon_knife_flip", "models/weapons/v_knife_flip.mdl", "knife_flip", "Flip Knife" } },
	{ eWeaponType1::WEAPON_KNIFE_GUT,{ "#SFUI_WPNHUD_KnifeGut", "weapon_knife_gut", "models/weapons/v_knife_gut.mdl", "knife_gut", "Gut Knife" } },
	{ eWeaponType1::WEAPON_KNIFE_KARAMBIT,{ "#SFUI_WPNHUD_KnifeKaram", "weapon_knife_karambit", "models/weapons/v_knife_karam.mdl", "knife_karambit", "Karambit" } },
	{ eWeaponType1::WEAPON_KNIFE_M9_BAYONET,{ "#SFUI_WPNHUD_KnifeM9", "weapon_knife_m9_bayonet", "models/weapons/v_knife_m9_bay.mdl", "knife_m9_bayonet", "M9 Bayonet" } },
	{ eWeaponType1::WEAPON_KNIFE_TACTICAL,{ "#SFUI_WPNHUD_KnifeTactical", "weapon_knife_tactical", "models/weapons/v_knife_tactical.mdl", "knife_tactical", "Huntsman Knife" } },
	{ eWeaponType1::WEAPON_KNIFE_FALCHION,{ "#SFUI_WPNHUD_knife_falchion_advanced", "weapon_knife_falchion", "models/weapons/v_knife_falchion_advanced.mdl", "knife_falchion", "Falchion Knife" } },
	{ eWeaponType1::WEAPON_KNIFE_BOWIE,{ "#SFUI_WPNHUD_knife_survival_bowie", "weapon_knife_survival_bowie", "models/weapons/v_knife_survival_bowie.mdl", "knife_survival_bowie", "Bowie Knife" } },
	{ eWeaponType1::WEAPON_KNIFE_BUTTERFLY,{ "#SFUI_WPNHUD_Knife_Butterfly", "weapon_knife_butterfly", "models/weapons/v_knife_butterfly.mdl", "knife_butterfly", "Butterfly Knife" } },
	{ eWeaponType1::WEAPON_KNIFE_PUSH,{ "#SFUI_WPNHUD_knife_push", "weapon_knife_push", "models/weapons/v_knife_push.mdl", "knife_push", "Shadow Daggers" } },
	{ eWeaponType1::GLOVE_STUDDED_BLOODHOUND,{ "#CSGO_Wearable_t_studdedgloves", "studded_bloodhound_gloves", "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl", "null", "Bloodhound Gloves" } },
	{ eWeaponType1::GLOVE_T_SIDE,{ "#CSGO_Wearable_t_defaultgloves", "t_gloves", "models/weapons/v_models/arms/glove_fingerless/v_glove_fingerless.mdl", "null", "T Gloves" } },
	{ eWeaponType1::GLOVE_CT_SIDE,{ "#CSGO_Wearable_ct_defaultgloves", "ct_gloves", "models/weapons/v_models/arms/glove_hardknuckle/v_glove_hardknuckle.mdl", "null", "CT Gloves" } },
	{ eWeaponType1::GLOVE_SPORTY,{ "#CSGO_Wearable_v_sporty_glove", "sporty_gloves", "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl", "null", "Sport Gloves" } },
	{ eWeaponType1::GLOVE_SLICK,{ "#CSGO_Wearable_v_slick_glove", "slick_gloves", "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl", "null", "Driver Gloves" } },
	{ eWeaponType1::GLOVE_LEATHER_WRAP,{ "#CSGO_Wearable_v_leather_handwrap", "leather_handwraps", "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl", "null", "Leather Handwraps" } },
	{ eWeaponType1::GLOVE_MOTORCYCLE,{ "#CSGO_Wearable_v_motorcycle_glove", "motorcycle_gloves", "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl", "null", "Motorcycle Gloves" } },
	{ eWeaponType1::GLOVE_SPECIALIST,{ "#CSGO_Wearable_v_specialist_glove", "specialist_gloves", "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl", "null", "Specialist Gloves" } }
};

class IHandleEntity;

typedef unsigned long CBaseHandle;

struct model_t
{
};

enum class CSGOHitboxID
{
	Head = 0,
	Neck,
	NeckLower,
	Pelvis,
	Stomach,
	LowerChest,
	Chest,
	UpperChest,
	RightThigh,
	LeftThigh,
	RightShin,
	LeftShin,
	RightFoot,
	LeftFoot,
	RightHand,
	LeftHand,
	RightUpperArm,
	RightLowerArm,
	LeftUpperArm,
	LeftLowerArm,
};

class CCSBomb
{
private:
	template< class T >
	inline T GetFieldValue( int offset )
	{
		return *( T* )( ( DWORD )this + offset );
	}

	template< class T >
	T* GetFieldPointer( int offset )
	{
		return ( T* )( ( DWORD )this + offset );
	}

public:

	/*
	25-Apr-2016
	=========================
	DT_PlantedC4
	|___m_flTimerLength
	|___m_bBombTicking
	|___m_flDefuseCountDown
	|___m_flC4Blow
	|___m_hBombDefuser
	|___m_flDefuseLength
	|___m_bBombDefused
	=========================
	*/
	float GetTimerLength()
	{
		static int m_flTimerLength = Netvar("DT_PlantedC4", "m_flTimerLength");
		return GetFieldValue< float >( m_flTimerLength );
	}

	float GetC4BlowTime()
	{
		static int m_flC4Blow = Netvar("DT_PlantedC4", "m_flC4Blow");
		return GetFieldValue< float >( m_flC4Blow );
	}

	float GetC4DefuseCountDown()
	{
		static int m_flDefuseCountDown = Netvar("DT_PlantedC4", "m_flDefuseCountDown");
		return GetFieldValue< float >( m_flDefuseCountDown );
	}
};

class CBaseEntity;

class CCSWeaponInfo
{
public:
	float GetPen()
	{
		return *( float* )( ( DWORD )this + ( DWORD )0x0f8 );
	}

	int GetDamage()
	{
		return *( int* )( ( DWORD )this + ( DWORD )0x0EC );
	}

	int GetMaxClip()
	{
		return *( int* )( ( DWORD )this + ( DWORD )0x014 );
	}

	float** GetRecoilTable()
	{
		return *( float*** )( ( DWORD )this + ( DWORD )0xA54 );
	}

	float GetRange()
	{
		return *( float* )( ( DWORD )this + ( DWORD )0x104 );
	}

	float GetRangeModifier()
	{
		return *( float* )( ( DWORD )this + ( DWORD )0x108 );
	}

	float GetArmorRatio()
	{
		return *( float* )( ( DWORD )this + ( DWORD )0x0F0 );
	}

	float GetStandInacc()
	{
		return *( float* )( ( DWORD )this + ( DWORD )0x9E0 );
	}

	float GetJumpInacc()
	{
		return *( float* )( ( DWORD )this + ( DWORD )0x9E8 );
	}
};

class IHandleEntity
{
public:
	virtual ~IHandleEntity()
	{
	}

	virtual void SetRefEHandle( const HANDLE& handle ) = 0;

	virtual const HANDLE& GetRefEHandle() const = 0;
};

class IClientUnknown : public IHandleEntity
{
public:
	virtual void* GetCollideable() = 0;

	virtual void* GetClientNetworkable() = 0;

	virtual void* GetClientRenderable() = 0;

	virtual void* GetIClientEntity() = 0;

	virtual void* GetBaseEntity() = 0;

	virtual void* GetClientThinkable() = 0;

	virtual void* GetClientAlphaProperty() = 0;
};

class AnimationLayer;

class CBasePlayerAnimState;

class CCSPlayerAnimState;

class CCSGOPlayerAnimState;

class IClientRenderable
{
public:
	virtual IClientUnknown* GetIClientUnknown() = 0;

	virtual Vector const& GetRenderOrigin( void ) = 0;

	virtual Vector const& GetRenderAngles( void ) = 0;

	virtual bool ShouldDraw( void ) = 0;

	virtual int GetRenderFlags( void ) = 0; // ERENDERFLAGS_xxx
	virtual void Unused( void ) const
	{
	}

	virtual HANDLE GetShadowHandle() const = 0;

	virtual HANDLE& RenderHandle() = 0;

	virtual const model_t* GetModel() const = 0;

	virtual int DrawModel( int flags, const int /*RenderableInstance_t*/ & instance ) = 0;

	virtual int GetBody() = 0;

	virtual void GetColorModulation( float* color ) = 0;

	virtual bool LODTest() = 0;

	virtual void SetupWeights( const matrix3x4* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights ) = 0;

	virtual void DoAnimationEvents( void ) = 0;

	virtual void* /*IPVSNotify*/ GetPVSNotifyInterface() = 0;

	virtual void GetRenderBounds( Vector& mins, Vector& maxs ) = 0;

	virtual void GetRenderBoundsWorldspace( Vector& mins, Vector& maxs ) = 0;

	virtual void GetShadowRenderBounds( Vector& mins, Vector& maxs, int /*ShadowType_t*/ shadowType ) = 0;

	virtual bool ShouldReceiveProjectedTextures( int flags ) = 0;

	virtual bool GetShadowCastDistance( float* pDist, int /*ShadowType_t*/ shadowType ) const = 0;

	virtual bool GetShadowCastDirection( Vector* pDirection, int /*ShadowType_t*/ shadowType ) const = 0;

	virtual bool IsShadowDirty() = 0;

	virtual void MarkShadowDirty( bool bDirty ) = 0;

	virtual IClientRenderable* GetShadowParent() = 0;

	virtual IClientRenderable* FirstShadowChild() = 0;

	virtual IClientRenderable* NextShadowPeer() = 0;

	virtual int /*ShadowType_t*/ ShadowCastType() = 0;

	virtual void CreateModelInstance() = 0;

	virtual HANDLE GetModelInstance() = 0;

	virtual const matrix3x4& RenderableToWorldTransform() = 0;

	virtual int LookupAttachment( const char* pAttachmentName ) = 0;

	virtual bool GetAttachment( int number, Vector& origin, Vector& angles ) = 0;

	virtual bool GetAttachment( int number, matrix3x4& matrix ) = 0;

	virtual float* GetRenderClipPlane( void ) = 0;

	virtual int GetSkin() = 0;

	virtual void OnThreadedDrawSetup() = 0;

	virtual bool UsesFlexDelayedWeights() = 0;

	virtual void RecordToolMessage() = 0;

	virtual bool ShouldDrawForSplitScreenUser( int nSlot ) = 0;

	virtual uint8 OverrideAlphaModulation( uint8 nAlpha ) = 0;

	virtual uint8 OverrideShadowAlphaModulation( uint8 nAlpha ) = 0;
};

class IClientNetworkable
{
public:
	virtual IClientUnknown* GetIClientUnknown() = 0;

	virtual void Release() = 0;

	virtual ClientClass* GetClientClass() = 0;

	virtual void NotifyShouldTransmit( int state ) = 0;

	virtual void OnPreDataChanged( int updateType ) = 0;

	virtual void OnDataChanged( int updateType ) = 0;

	virtual void PreDataUpdate( int updateType ) = 0;

	virtual void PostDataUpdate( int updateType ) = 0;

	virtual void __unkn( void ) = 0;

	virtual bool IsDormant( void ) = 0;

	virtual int EntIndex( void ) const = 0;

	virtual void ReceiveMessage( int classID, bf_read& msg ) = 0;

	virtual void* GetDataTableBasePtr() = 0;

	virtual void SetDestroyedOnRecreateEntities( void ) = 0;
};

class CBaseCombatWeapon;

class CBaseEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable
{
public:
	IClientNetworkable* GetNetworkable()
	{
		return ( IClientNetworkable* )( ( DWORD )this + 0x8 );
	}

	template< class T >
	inline T GetFieldValue( int offset )
	{
		return *( T* )( ( DWORD )this + offset );
	}

	template< class T >
	T* GetFieldPointer( int offset )
	{
		return ( T* )( ( DWORD )this + offset );
	}

	Vector GetAbsOrigin()
	{
		//0xAC interpolated getAbsOrigin
		//0xA0 normal abs
		static int VecOrigin = Netvar("DT_BaseEntity", "m_vecOrigin");
		return GetFieldValue< Vector >( VecOrigin );
	}

	void SetModelIndexVirtual(int index)
	{
		typedef void(__thiscall* SetModelIndexFn)(void*, int);
		getvfunc<SetModelIndexFn>(this, 75)(this, index);
	}

	Vector CBaseEntity::GetPredicted(Vector p0)
	{
		return CMath::ExtrapolateTick(p0, this->GetVecVelocity());
	}

	//HANDLE GetObserverTargetHandle() {
	//static int m_hObserverTarget = Netvar("DT_CSPlayer", "m_hObserverTarget");
	//return GetFieldValue<HANDLE>(m_hObserverTarget);
	//}

	Vector GetNetworkOrigin()
	{
		static int offset = Netvar("DT_CSPlayer", "m_flFriction") - sizeof(Vector);
		return GetFieldValue< Vector >( offset );
	}

	HANDLE GetObserverTargetHandle()
	{
		return *(HANDLE*)((DWORD)this + Netvar("DT_BasePlayer", "m_hObserverTarget"));
	}

	unsigned* GetModelIndex()
	{
		int offset = Netvar("CBaseEntity", "m_nModelIndex");
		return GetFieldPointer< unsigned >(offset);
	}

	Vector GetVecOrigin()
	{
		return *( Vector* )( ( DWORD )this + 0x134 );
	}

	Vector3 GetVec3Origin()
	{
		return *(Vector3*)((DWORD)this + 0x134);
	}

	Vector GetVecViewOffset()
	{
		static int iOffset = Netvar("DT_BasePlayer", "localdata", "m_vecViewOffset[0]");
		return *( Vector* )( ( DWORD )this + iOffset );
	}

	Vector GetEyeAngles()
	{
		static int iOffset = Netvar("DT_CSPlayer", "m_angEyeAngles[0]");
		return *( Vector* )( ( DWORD )this + iOffset );
	}

	Vector* GetEyeAnglesPointer()
	{
		static int iOffset = Netvar("DT_CSPlayer", "m_angEyeAngles[0]");
		return GetFieldPointer< Vector >( iOffset );
	}

	Vector GetRotation()
	{
		static int ioffset = Netvar("DT_BaseEntity", "m_angRotation");
		return this->GetFieldValue< Vector >( ioffset );
	}

	int* GetWearables()
	{
		static int iOffset = Netvar("DT_CSPlayer", "m_hMyWearables");
		return GetFieldValue< int* >(iOffset);
	}

	bool IsSpotted()
	{
		static int iOffset = Netvar("DT_BaseEntity", "m_bSpotted");
		return GetFieldValue< bool >( iOffset );
	}

	bool* IsSpottedPtr()
	{
		static int iOffset = Netvar("DT_BaseEntity", "m_bSpotted");
		return GetFieldPointer< bool >( iOffset );
	}

	/*DWORD* GetWearables()
	{
		DWORD iOffset = Netvar("DT_CSPlayer", "m_hMyWearables");
		return GetFieldPointer< DWORD >(iOffset);
	}*/

	Vector GetAbsAngles()
	{
		__asm
		{
			MOV ECX, this;
			MOV EAX, DWORD PTR DS : [ECX];
			CALL DWORD PTR DS : [EAX + 0x2C]
		}
	}

	player_info_t GetPlayerInfo()
	{
		player_info_t pinfo;
		Interfaces.pEngine->GetPlayerInfo( GetIndex(), &pinfo );
		return pinfo;
	}

	unsigned long long GID()
	{
		return GetPlayerInfo().m_nXuidLow;
	}

	std::string GetName()
	{
		string name = GetPlayerInfo().m_szPlayerName;
		std::size_t found = name.find( "\n" );
		while( found != std::string::npos )
		{
			name.replace( found, found + 2, "" );
			found = name.find( "\n" );
		}
		return name;
	}

	char* GetCallout()
	{
		static int iOffset = Netvar("DT_BasePlayer", "m_szLastPlaceName");
		return GetFieldPointer< char >(iOffset); 
	}

	char* GetClan()
	{
		static int iOffset = Netvar("DT_CSPlayerResource", "m_szClan");
		return GetFieldPointer< char >(iOffset);
	}

	bool IsDormant()
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, [EDI + 0x8]
			MOV EDX, DWORD PTR DS : [ecx]
			CALL[EDX + 0x24]
		}
	}

	int GetIndex()
	{
		int iEntIndex;

		PVOID pEnt = ( PVOID )this;

		__asm
		{
			MOV ECX, this
			MOV EAX, DWORD PTR DS : [ECX + 0x8]
			MOV EDX, DWORD PTR DS : [EAX + 0x28]
			LEA ESI, DWORD PTR DS : [ECX + 0x8]
			MOV ECX, ESI
			CALL EDX
			MOV iEntIndex, EAX
		}

		return iEntIndex;
	}

	int GetTickBase( void )
	{
		static int m_nTickBase = Netvar("DT_BasePlayer", "localdata", "m_nTickBase");
		return GetFieldValue< int >( m_nTickBase );
	}

	int GetOwner()
	{
		static int m_nTickBase = Netvar("DT_BaseEntity", "m_hOwnerEntity");
		return GetFieldValue< int >(m_nTickBase);
	}

	bool BombDefused()
	{
		static int m_bBombDefused = Netvar("DT_PlantedC4", "m_bBombDefused");
		return GetFieldValue< bool >( m_bBombDefused );
	}

	float BombTimer()
	{
		static int m_flC4Blow = Netvar("DT_PlantedC4", "m_flC4Blow");
		float flBombTime = GetFieldValue< float >( m_flC4Blow );
		return ( flBombTime > 0 ) ? flBombTime : 0.f;
	}

	bool IsPlayer()
	{
		if( !this )
		{
			return false;
		}
		if( this->IsDormant() )
		{
			return false;
		}
		if( this->GetTeam() == 0 )
		{
			return false;
		}

		player_info_t info;
		if( !( Interfaces.pEngine->GetPlayerInfo( GetIndex(), &info ) ) )
			return false;

		ClientClass* cClass = ( ClientClass* )this->GetClientClass();

		if( cClass->m_ClassID != 35 )
		{
			return false;
		}
		return true;
	}

	bool IsWeapon()
	{
		if( !this )
		{
			return false;
		}
		ClientClass* cClass = ( ClientClass* )this->GetClientClass();

		if( cClass->m_ClassID != ClientClassIDS::CAK47 && cClass->m_ClassID != ClientClassIDS::CBaseCSGrenadeProjectile && cClass->m_ClassID != ClientClassIDS::CC4 && cClass->m_ClassID != ClientClassIDS::CBaseWeaponWorldModel && cClass->m_ClassID != ClientClassIDS::CDEagle && cClass->m_ClassID != ClientClassIDS::CDecoyGrenade && cClass->m_ClassID != ClientClassIDS::CFlashbang && cClass->m_ClassID != ClientClassIDS::CHEGrenade && cClass->m_ClassID != ClientClassIDS::CKnife && cClass->m_ClassID != ClientClassIDS::CMolotovGrenade && cClass->m_ClassID != ClientClassIDS::CWeaponAWP && cClass->m_ClassID != ClientClassIDS::CSmokeGrenade && cClass->m_ClassID != ClientClassIDS::CWeaponAug && cClass->m_ClassID != ClientClassIDS::CWeaponBizon && cClass->m_ClassID != ClientClassIDS::CWeaponElite && cClass->m_ClassID != ClientClassIDS::CWeaponFamas && cClass->m_ClassID != ClientClassIDS::CWeaponFiveSeven && cClass->m_ClassID != ClientClassIDS::CWeaponG3SG1 && cClass->m_ClassID != ClientClassIDS::CWeaponGlock && cClass->m_ClassID != ClientClassIDS::CWeaponGalilAR && cClass->m_ClassID != ClientClassIDS::CWeaponXM1014 && cClass->m_ClassID != ClientClassIDS::CWeaponUMP45 && cClass->m_ClassID != ClientClassIDS::CWeaponTec9 && cClass->m_ClassID != ClientClassIDS::CWeaponTaser && cClass->m_ClassID != ClientClassIDS::CWeaponSawedoff && cClass->m_ClassID != ClientClassIDS::CWeaponSSG08 && cClass->m_ClassID != ClientClassIDS::CWeaponSG556 && cClass->m_ClassID != ClientClassIDS::CWeaponSCAR20 && cClass->m_ClassID != ClientClassIDS::CWeaponP90 && cClass->m_ClassID != ClientClassIDS::CWeaponP250 && cClass->m_ClassID != ClientClassIDS::CWeaponNOVA && cClass->m_ClassID != ClientClassIDS::CWeaponSawedoff && cClass->m_ClassID != ClientClassIDS::CWeaponSG556 && cClass->m_ClassID != ClientClassIDS::CWeaponMP9 && cClass->m_ClassID != ClientClassIDS::CWeaponMag7 && cClass->m_ClassID != ClientClassIDS::CWeaponM4A1 && cClass->m_ClassID != ClientClassIDS::CWeaponNegev && cClass->m_ClassID != ClientClassIDS::CWeaponHKP2000 )
		{
			return false;
		}
		return true;
		//return CallVFunction<bool(__thiscall*)(CBaseEntity*)>(this, 160)(this);
	}

	bool IsHostage()
	{
		if( !this )
		{
			return false;
		}
		ClientClass* cClass = ( ClientClass* )this->GetClientClass();

		return cClass->m_ClassID == ClientClassIDS::CHostage;
	}

	bool IsChicken()
	{
		if( !this )
		{
			return false;
		}
		ClientClass* cClass = ( ClientClass* )this->GetClientClass();

		return cClass->m_ClassID == ClientClassIDS::CChicken;
	}

	bool isValidPlayer()
	{
		if( !isAlive() )
			return false;
		if( !( GetHealth() > 0 ) )
			return false;
		if( IsDormant() )
			return false;
		player_info_t info;
		if( !( Interfaces.pEngine->GetPlayerInfo( GetIndex(), &info ) ) )
			return false;
		return true;
	}

	int GetHealth()
	{
		return *reinterpret_cast< int* >( ( DWORD )this + 0xFC );
	}

	bool isAlive()
	{
		BYTE lifestate = *( BYTE* )( ( DWORD )this + 0x025B );
		return ( lifestate == 0 );
	}

	int GetFlags()
	{
		return *reinterpret_cast< int* >( ( DWORD )this + 0x0100 );
	}

	int* GetFlagsPtr()
	{
		return reinterpret_cast< int* >( ( DWORD )this + 0x0100 );
	}

	int GetTeam()
	{
		return *reinterpret_cast< int* >( ( DWORD )this + 0xF0 );
	}

	float GetFlashDuration()
	{
		return *( float* )( ( DWORD )this + Netvar(("DT_CSPlayer"), ("m_flFlashDuration")) );
	}

	bool IsFlashed()
	{
		return GetFlashDuration() > 0;
	}

	bool IsKnife(int weaponid)
	{
		if (weaponid == WEAPON_KNIFE_CT || weaponid == WEAPON_KNIFE_T || weaponid == WEAPON_KNIFEGG || weaponid == WEAPON_KNIFE_BAYONET || weaponid == WEAPON_KNIFE_BUTTERFLY || weaponid == WEAPON_KNIFE_FALCHION || weaponid == WEAPON_KNIFE_FLIP || weaponid == WEAPON_KNIFE_GUT || weaponid == WEAPON_KNIFE_KARAMBIT || weaponid == WEAPON_KNIFE_M9_BAYONET || weaponid == WEAPON_KNIFE_PUSH || weaponid == WEAPON_KNIFE_BOWIE || weaponid == WEAPON_KNIFE_TACTICAL)
			return true;

		return false;
	}

	bool IsGrenade(int weaponid)
	{
		if (weaponid == WEAPON_FLASHBANG || weaponid == WEAPON_HEGRENADE || weaponid == WEAPON_SMOKEGRENADE || weaponid == WEAPON_MOLOTOV || weaponid == WEAPON_INCGRENADE || weaponid == WEAPON_DECOY)
			return true;

		return false;
	}

	bool IsBomb(int weaponid)
	{
		if (weaponid == WEAPON_C4)
			return true;

		return false;
	}

	bool IsTaser(int weaponid)
	{
		if (weaponid == WEAPON_TASER)
			return true;

		return false;
	}

	bool IsNonAimWeapon(int weaponid)
	{
		if (IsKnife(weaponid) || IsGrenade(weaponid) || IsBomb(weaponid) || IsTaser(weaponid))
			return true;

		return false;
	}

	std::string GetClientClassName()
	{
		uintptr_t pNext = *( uintptr_t* )( ( DWORD )this + 0x8 );
		pNext = *( uintptr_t* )( ( DWORD )pNext + 0x8 );
		pNext = *( uintptr_t* )( ( DWORD )pNext + 0x1 );
		return std::string( *( char** )( ( DWORD )pNext + 0x8 ) );
	}

	Vector GetVecVelocity()
	{
		return *( Vector* )( ( DWORD )this + 0x110 );
	}

	std::array< float, 24 >* CBaseEntity::GetPoseParameters()
	{
		return ( std::array< float, 24 >* ) ( ( DWORD )this + Netvar("DT_BaseAnimating", "m_flPoseParameter") );
	}

	Vector GetPunchAngle()
	{
		static int m_aimPunchAngle = Netvar("DT_BasePlayer", "localdata", "m_Local", "m_aimPunchAngle");
		return *GetFieldPointer< Vector >( m_aimPunchAngle );
	}

	Vector GetPunchAngleVel()
	{
		static int m_aimPunchAngle = Netvar("DT_BasePlayer", "localdata", "m_Local", "m_aimPunchAngleVel");
		return *GetFieldPointer< Vector >( m_aimPunchAngle );
	}

	Vector* GetPunchAnglePtr()
	{
		static int m_aimPunchAngle = Netvar("DT_BasePlayer", "localdata", "m_Local", "m_aimPunchAngle");
		return GetFieldPointer< Vector >( m_aimPunchAngle );
	}

	float GetSimulationTime()
	{
		static int m_flSimulationTime = Netvar("DT_BaseEntity", "m_flSimulationTime");
		return GetFieldValue< float >( m_flSimulationTime );
	}

	void CBaseEntity::InvalidateBoneCache()
	{
		unsigned long g_iModelBoneCounter = **(unsigned long**)(Utils.PFindPattern("client.dll", "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81") + 10);
		*(unsigned int*)((DWORD)this + 0x2914) = 0xFF7FFFFF; // m_flLastBoneSetupTime = -FLT_MAX;
		*(unsigned int*)((DWORD)this + 0x2680) = (g_iModelBoneCounter - 1); // m_iMostRecentModelBoneCounter = g_iModelBoneCounter - 1;
	}

	int CBaseEntity::GetNumAnimOverlays()
	{
		return *(int*)((DWORD)this + 0x297C);
	}

	AnimationLayer* GetAnimOverlays()
	{
		// to find offset: use 9/12/17 dll
		// sig: 55 8B EC 51 53 8B 5D 08 33 C0
		return *(AnimationLayer**)((DWORD)this + 10608);
	}

	int GetSequenceActivity(int sequence, studiohdr_t* hdr)
	{

		if (!hdr)
			return -1;

		// sig for stuidohdr_t version: 53 56 8B F1 8B DA 85 F6 74 55
		// sig for C_BaseAnimating version: 55 8B EC 83 7D 08 FF 56 8B F1 74 3D
		// c_csplayer vfunc 242, follow calls to find the function.

		static auto get_sequence_activity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(Utils.PFindPattern("client.dll", "55 8B EC 83 7D 08 FF 56 8B F1 74 3D"));

		return get_sequence_activity(this, hdr, sequence);
	}

	CBasePlayerAnimState *GetBasePlayerAnimState()
	{
		static int basePlayerAnimStateOffset = 0x3874;
		return *(CBasePlayerAnimState**)((DWORD)this + basePlayerAnimStateOffset);
	}

	CCSPlayerAnimState *GetPlayerAnimState()
	{
		return *(CCSPlayerAnimState**)((DWORD)this + 0x3870);
	}

	void UpdateAnimationState(CCSGOPlayerAnimState *state, Vector angle)
	{
		static auto UpdateAnimState = Utils.PFindPattern("client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54 24");
		if (!UpdateAnimState)
			return;

		__asm
		{
			mov ecx, state

			movss xmm1, dword ptr[angle + 4]
			movss xmm2, dword ptr[angle]

			call UpdateAnimState
		}
	}

	void ResetAnimationState(CCSGOPlayerAnimState *state)
	{
		using ResetAnimState_t = void(__thiscall*)(CCSGOPlayerAnimState*);
		static auto ResetAnimState = (ResetAnimState_t)Utils.PFindPattern("client.dll", "56 6A 01 68 ? ? ? ? 8B F1");
		if (!ResetAnimState)
			return;

		ResetAnimState(state);
	}

	void CreateAnimationState(CCSGOPlayerAnimState *state)
	{
		using CreateAnimState_t = void(__thiscall*)(CCSGOPlayerAnimState*, CBaseEntity*);
		static auto CreateAnimState = (CreateAnimState_t)Utils.PFindPattern("client.dll", "55 8B EC 56 8B F1 B9 ? ? ? ? C7 46");
		if (!CreateAnimState)
			return;

		CreateAnimState(state, this);
	}

	int GetAccount()
	{
		static int m_iAccount = Netvar("DT_CSPlayer", "m_iAccount");
		return GetFieldValue< int >(m_iAccount);
	}

	Vector GetPunchViewAngle()
	{
		static int m_aimPunchAngle = Netvar("DT_BasePlayer", "localdata", "m_Local", "m_viewPunchAngle");
		return *GetFieldPointer< Vector >( m_aimPunchAngle );
	}

	Vector* GetViewPunchAnglePtr()
	{
		static int m_aimPunchAngle = Netvar("DT_BasePlayer", "localdata", "m_Local", "m_viewPunchAngle");
		return GetFieldPointer< Vector >( m_aimPunchAngle );
	}

	int SetFov( int fovvalue )
	{
		static int iOffset = Netvar("DT_BasePlayer", "m_iDefaultFOV");
		*( int* )( ( DWORD )this + iOffset ) = fovvalue;
		static int iOffset2 = Netvar("DT_CSPlayer", "m_bIsScoped");
		bool scopecheck = *( bool* )( ( DWORD )this + iOffset2 );
		if( !scopecheck )
		{
			static int iOffset3 = Netvar("DT_BasePlayer", "m_iFOV");
			*( int* )( ( DWORD )this + iOffset3 ) = fovvalue;
		}
		return true;
	}

	bool GetScope()
	{
		static int iOffset2 = Netvar("DT_CSPlayer", "m_bIsScoped");
		bool scopecheck = *( bool* )( ( DWORD )this + iOffset2 );

		if( scopecheck )
		{
			return true;
		}

		return false;
	}

	int GetiShots()
	{
		static int iOffset = Netvar("DT_CSPlayer", "m_iShotsFired");
		return *( int* )( ( DWORD )this + iOffset );
		
	}

	CColor GetHealthColor(int alpha)
	{
		int nHealth = GetHealth();
		float r = 255.f - float( nHealth ) * 2.55f;
		float g = float( nHealth ) * 2.55f;
		return CColor( int( r ), int( g ), 0, alpha );
	}

	float* flGetHealthColor(float alpha)
	{
		int nHealth = GetHealth();
		float r = 255.f - float(nHealth) * 2.55f;
		float g = float(nHealth) * 2.55f;
		float color[4] = { r / 255, g / 255, 0.f, alpha};
		return color;
	}

	std::vector< CBaseCombatWeapon* > CBaseEntity::GetWeapons();

	CBaseHandle* m_hMyWeapons()
	{
		return (CBaseHandle*)((uintptr_t)this + Netvar("DT_BaseCombatCharacter", "m_hMyWeapons"));
	}

	CBaseCombatWeapon* GetActiveBaseCombatWeapon();

	bool SetupBones( matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime )
	{
		static DWORD m_nWritableBones = Netvar("DT_BaseAnimating", "m_nForceBone");
		static DWORD m_dwOcclusionArray = *( uintptr_t* )( Utils.PatternSearch( "client.dll", ( PBYTE ) "\xA1\x00\x00\x00\x00\x8B\xB7\x00\x00\x00\x00\x89\x75\xF8", "x????xx????xxx", 0, 0 ) + 0x1 ); //"A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8"
		static DWORD m_bDidCheckForOcclusion = *( uintptr_t* )( Utils.PatternSearch( "client.dll", ( PBYTE ) "\xA1\x00\x00\x00\x00\x8B\xB7\x00\x00\x00\x00\x89\x75\xF8", "x????xx????xxx", 0, 0 ) + 0x7 ); //"A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8"

		*( int* )( ( uintptr_t )this + m_nWritableBones ) = 0;
		*( int* )( ( uintptr_t )this + m_bDidCheckForOcclusion ) = reinterpret_cast< int* >( m_dwOcclusionArray )[ 1 ];

		__asm
		{
			mov edi, this
			lea ecx, dword ptr ds : [edi + 0x4]
			mov edx, dword ptr ds : [ecx]
			push currentTime
			push boneMask
			push nMaxBones
			push pBoneToWorldOut
			call dword ptr ds : [edx + 0x34]
		}

		//typedef bool(__thiscall* oSetupBones)(PVOID, matrix3x4*, int, int, float);
		//return getvfunc< oSetupBones>(this, 13)(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}

	Vector GetBonePos( int i )
	{
		matrix3x4 boneMatrix[128];
		if( this->SetupBones( boneMatrix, 128, BONE_USED_BY_HITBOX, ( float )GetTickCount64() ) )
		{
			return Vector( boneMatrix[ i ][ 0 ][ 3 ], boneMatrix[ i ][ 1 ][ 3 ], boneMatrix[ i ][ 2 ][ 3 ] );
		}
		return Vector( 0, 0, 0 );
	}

	Vector GetEntityBone(CBaseEntity* pEntity, CSGOHitboxID* Bone)
	{
		matrix3x4 boneMatrix[128];
		if (!pEntity->SetupBones(boneMatrix, 128, 0x100, GetTickCount64()))
		return Vector();
		auto hitbox = boneMatrix[(int)CSGOHitboxID::Head];
		return Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
		}

	Vector GetEyePosition()
	{
		return GetAbsOrigin() + GetVecViewOffset();
	}

	int GetArmor()
	{
		static int Armor = Netvar("DT_CSPlayerResource", "m_iArmor");
		return GetFieldValue< int >( Armor );
	}

	unsigned long GetViewmodel()
	{
		static int Armor = Netvar("CBasePlayer", "m_hViewModel[0]");
		return GetFieldValue< unsigned long >(Armor);
	}

	int GetArmorValue()
	{
		static int Armor = Netvar("DT_CSPlayer", "m_ArmorValue");
		return GetFieldValue< int >( Armor );
	}

	bool HasHelmet()
	{
		static int Helm = Netvar("DT_CSPlayer", "m_bHasHelmet");
		return GetFieldValue< bool >( Helm );
	}

	char* GetArmorName()
	{
		if( GetArmorValue() > 0 )
		{
			if( HasHelmet() )
				return "K|H";
			else
				return "K";
		}
		else
			return " ";
	}

	bool HasKit()
	{
		static int iOffset = Netvar("DT_CSPlayer", "m_bHasDefuser");
		return GetFieldValue< bool >( iOffset );
	}

	bool HasGunGameImmunity()
	{
		static int m_bGunGameImmun = Netvar("DT_CSPlayer", "m_bGunGameImmunity");
		return *GetFieldPointer< bool >( m_bGunGameImmun );
	}

	Vector BBMin()
	{
		static int m_vecMins = Netvar("DT_BaseEntity", "m_Collision", "m_vecMins");
		return GetFieldValue< Vector >( m_vecMins );
	}

	Vector BBMax()
	{
		static int m_vecMaxs = Netvar("DT_BaseEntity", "m_Collision", "m_vecMaxs");
		return GetFieldValue< Vector >( m_vecMaxs );
	}

	bool m_bIsScoped()
	{
		static int m_bIsScoped = Netvar("DT_CSPlayer", "m_bIsScoped");
		return GetFieldValue< bool >( m_bIsScoped );
	}

	int GetMoveType()
	{
		return GetFieldValue< int >( 0x258 );
	}

	const char* CompRank()
	{
		static const char* Ranks[19] =
		{
			"-",
			"Silver I",
			"Silver II",
			"Silver III",
			"Silver IV",
			"Silver Elite",
			"Silver Elite Master",

			"Gold Nova I",
			"Gold Nova II",
			"Gold Nova III",
			"Gold Nova Master",
			"Master Guardian I",
			"Master Guardian II",

			"Master Guardian Elite",
			"Distinguished Master Guardian",
			"Legendary Eagle",
			"Legendary Eagle Master",
			"Supreme Master First Class",
			"Global Elite"
		};
		static int m_iCompetitiveRanking = Netvar("DT_CSPlayerResource", "m_iCompetitiveRanking");
		int Rank = *( int* )( ( DWORD )Interfaces.GameResources + ( DWORD )Interfaces.pClient + m_iCompetitiveRanking + ( int )GetIndex() * 4 );
		return Ranks[ Rank ];
	}

	Vector WorldSpaceCenter()
	{
		Vector Max = this->BBMax() + this->GetAbsOrigin();
		Vector Min = this->BBMin() + this->GetAbsOrigin();

		Vector Size = Max - Min;

		Size /= 2;

		Size += Min;

		return Size;
	}

	float pelvisangs()
	{
		static int ioffset = Netvar("DT_CSPlayer", "m_flLowerBodyYawTarget");
		return this->GetFieldValue< float >( ioffset );
	}
};

class CBaseAttributableItem : public IClientUnknown, public IClientRenderable, public IClientNetworkable {
public:
	template< class T >
	inline T GetFieldValue(int offset)
	{
		return *(T*)((DWORD)this + offset);
	}

	template< class T >
	T* GetFieldPointer(int offset)
	{
		return (T*)((DWORD)this + offset);
	}

	

};

class AttributeContainer
{
public:

	CBaseAttributableItem* m_Item()
	{
		return (CBaseAttributableItem*)((uintptr_t)this + 0x40);
	}
};

class CBaseViewModel : public CBaseEntity
{
public:
	template< class T >
	inline T GetFieldValue(int offset)
	{
		return *(T*)((DWORD)this + offset);
	}

	template< class T >
	T* GetFieldPointer(int offset)
	{
		return (T*)((DWORD)this + offset);
	}

	unsigned long GetOwner()
	{
		static int owner= Netvar(("CBaseViewmodel"), ("m_hOwner"));
		return GetFieldValue< unsigned long >(owner);
	}

	unsigned long GetWeapon()
	{
		static int weapon = Netvar(("CBaseViewmodel"), ("m_hWeapon"));
		return GetFieldValue< unsigned long>(weapon);
	}
};

class CBaseCombatWeapon : public CBaseEntity, public CBaseAttributableItem
{
public:
	template< class T >
	inline T     GetFieldValue( int offset )
	{
		return *( T* )( ( DWORD )this + offset );
	}

	template< class T >
	T* GetFieldPointer( int offset )
	{
		return ( T* )( ( DWORD )this + offset );
	}

	CBaseEntity* GetOwner()
	{
		//static int m_hOwnerEntity = Netvar(("DT_BaseEntity"), ("m_hOwnerEntity"));
		//return (CBaseEntity*)Interfaces.pEntList->GetClientEntityFromHandle(GetFieldValue<CHandle<CBaseEntity>>(m_hOwnerEntity));
		return nullptr;
	}

	HANDLE GetOwnerHandle()
	{
		static int m_hOwnerEntity = Netvar(("DT_BaseEntity"), ("m_hOwnerEntity"));
		return GetFieldValue< HANDLE >( m_hOwnerEntity );
	}

	float GetAccuracyPenalty()
	{
		static int offset = Netvar("DT_WeaponCSBase", "m_flAccuracyPenalty");
		return GetFieldValue< float >(offset);
	}

	int* GetViewmodelindex()
	{
		static int offset = Netvar("DT_BaseCombatWeapon", "m_iViewModelIndex");
		return GetFieldPointer< int >(offset);
	}

	AttributeContainer* m_AttributeManager()
	{
		return (AttributeContainer*)((uintptr_t)this + 0x2D70);
	}

	HANDLE m_hWeaponWorldModel()
	{
		return *(HANDLE*)((uintptr_t)this + Netvar("DT_BaseCombatWeapon", "m_hWeaponWorldModel"));
	}

	int* GetWorldmodelindex()
	{
		static int offset = Netvar("DT_BaseCombatWeapon", "m_iWorldModelIndex");
		return GetFieldPointer< int >(offset);
	}

	float GetPostponeFireReadyTime()
	{
		static int offset = Netvar("DT_WeaponCSBase", "m_flPostponeFireReadyTime");
		return *(float*)((uintptr_t)this + offset);
	}

	float NextPrimaryAttack()
	{
		return *(float*)((DWORD)this + Netvar(("DT_BaseCombatWeapon"), ("LocalActiveWeaponData"), ("m_flNextPrimaryAttack")));
	}

	int* GetItemDefinitionIndex()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemDefinitionIndex
		static int m_iItemDefinitionIndex = Netvar("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex");
		return GetFieldPointer< int >(m_iItemDefinitionIndex);
	}

	int* GetItemIDHigh()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemIDHigh
		static int m_iItemIDHigh = Netvar(("DT_BaseAttributableItem"), ("m_AttributeManager"), ("m_Item"), ("m_iItemIDHigh"));
		return GetFieldPointer< int >(m_iItemIDHigh);
	}

	int* GetAccountID()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iAccountID
		static int m_iAccountID = Netvar(("DT_BaseAttributableItem"), ("m_AttributeManager"), ("m_Item"), ("m_iAccountID"));
		return GetFieldPointer< int >(m_iAccountID);
	}

	int* GetEntityQuality()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iEntityQuality
		static int m_iEntityQuality = Netvar(("DT_BaseAttributableItem"), ("m_AttributeManager"), ("m_Item"), ("m_iEntityQuality"));
		return GetFieldPointer< int >(m_iEntityQuality);
	}

	char* GetCustomName()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_szCustomName
		static int m_szCustomName = Netvar(("DT_BaseAttributableItem"), ("m_AttributeManager"), ("m_Item"), ("m_szCustomName"));
		return GetFieldPointer< char >(m_szCustomName);
	}

	int* GetOriginalOwnerXuidLow()
	{
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidLow
		static int m_OriginalOwnerXuidLow = Netvar(("DT_BaseAttributableItem"), ("m_OriginalOwnerXuidLow"));
		return GetFieldPointer< int >(m_OriginalOwnerXuidLow);
	}

	int* GetOriginalOwnerXuidHigh()
	{
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidHigh
		static int m_OriginalOwnerXuidHigh = Netvar(("DT_BaseAttributableItem"), ("m_OriginalOwnerXuidHigh"));
		return GetFieldPointer< int >(m_OriginalOwnerXuidHigh);
	}

	int* GetFallbackPaintKit()
	{
		// DT_BaseAttributableItem -> m_nFallbackPaintKit
		static int m_nFallbackPaintKit = Netvar(("DT_BaseAttributableItem"), ("m_nFallbackPaintKit"));
		return GetFieldPointer< int >(m_nFallbackPaintKit);
	}

	int* GetFallbackSeed()
	{
		// DT_BaseAttributableItem -> m_nFallbackSeed
		static int m_nFallbackSeed = Netvar(("DT_BaseAttributableItem"), ("m_nFallbackSeed"));
		return GetFieldPointer< int >(m_nFallbackSeed);
	}

	float* GetFallbackWear()
	{
		// DT_BaseAttributableItem -> m_flFallbackWear
		static int m_flFallbackWear = Netvar("DT_BaseAttributableItem", "m_flFallbackWear");
		return GetFieldPointer< float >(m_flFallbackWear);
	}

	int* GetFallbackStatTrak()
	{
		// DT_BaseAttributableItem -> m_nFallbackStatTrak
		static int m_nFallbackStatTrak = Netvar(("DT_BaseAttributableItem"), ("m_nFallbackStatTrak"));
		return GetFieldPointer< int >(m_nFallbackStatTrak);
	}

	int* GetModelIndex()
	{
		int offset = Netvar("DT_BaseCombatWeapon", "m_nModelIndex");
		return GetFieldPointer< int >(offset);
	}

	int GetClip()
	{
		return *( int* )( ( DWORD )this + Netvar(("DT_BaseCombatWeapon"), ("m_iClip1")) );
	}

	int GetId()
	{
		typedef int (__thiscall* tGetId)( void* );
		return getvfunc< tGetId >( this, 458 )( this );
	}

	const char* GetName()
	{
		typedef const char* (__thiscall* tGetName)( void* );
		return getvfunc< tGetName >( this, 378 )( this );
	}

	void SetModelIndexVirtual(int index)
	{
		typedef void(__thiscall* SetModelIndexFn)(void*, int);
		getvfunc<SetModelIndexFn>(this, 75)(this, index);
	}

	int SafeWeaponID()
	{
		int meme = *this->GetItemDefinitionIndex();
		return meme;
	}

	char* GetPName()
	{
		typedef char* (__thiscall* tGetName)( void* );
		return getvfunc< tGetName >( this, 378 )( this );
	}

	void CBaseCombatWeapon::UpdateAccuracyPenalty()
	{
		typedef void (__thiscall* OriginalFn)( void* );
		getvfunc< OriginalFn >( this, 470 )( this );
	}

	float CBaseCombatWeapon::GetInaccuracy()
	{
		if( !this )
			return 1.f;

		typedef float (__thiscall* OriginalFn)( void* );
		return getvfunc< OriginalFn >( this, 469 )( this );
	}

	float CBaseCombatWeapon::GetSpread()
	{
		if( !this )
			return 1.f;

		typedef float (__thiscall* OriginalFn)( void* );
		return getvfunc< OriginalFn >( this, 439 )( this );
	}

	int ammo()
	{
		static int m_Clip = Netvar("DT_BaseCombatWeapon", "m_iClip1");
		return *GetFieldPointer< int >( m_Clip );
	}

	int ammo2()
	{
		static int m_Clip = Netvar("DT_BaseCombatWeapon", "m_iClip2");
		return *GetFieldPointer< int >( m_Clip );
	}

	int reserveammo()
	{
		static int m_iPrimaryReserveAmmoCount = Netvar("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
		return *GetFieldPointer< int >(m_iPrimaryReserveAmmoCount);
	}

	bool HasAmmo()
	{
		if( IsMiscWeapon() )
			return 1;
		return ammo() > 0;
	}

	bool isPistol()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_DEAGLE || WeaponId == WEAPON_ELITE || WeaponId == WEAPON_FIVESEVEN || WeaponId == WEAPON_P250 ||
			WeaponId == WEAPON_GLOCK || WeaponId == WEAPON_USP_SILENCER || WeaponId == WEAPON_HKP2000 || WeaponId == WEAPON_CZ75A || WeaponId == WEAPON_TEC9 || WeaponId == weapon_revolver;
	}

	bool isShotgun()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_XM1014 || WeaponId == WEAPON_NOVA || WeaponId == WEAPON_SAWEDOFF || WeaponId == WEAPON_MAG7;
	}

	bool isSniper()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_AWP || WeaponId == WEAPON_SCAR20 || WeaponId == WEAPON_G3SG1 || WeaponId == WEAPON_SSG08;
	}

	bool isScoped()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_AWP || WeaponId == WEAPON_SCAR20 || WeaponId == WEAPON_G3SG1 || WeaponId == WEAPON_SSG08 || WeaponId == WEAPON_SG556 || WeaponId == WEAPON_AUG;
	}

	bool isAWP()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_AWP;
	}

	bool isCZ()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_CZ75A;
	}

	bool isScout()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_SSG08;
	}

	bool isDak()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_SCAR20 || WeaponId == WEAPON_G3SG1;
	}

	bool IsGun()
	{
		if (!this)
		{
			return false;
		}

		int id = *this->GetItemDefinitionIndex();

		if( id == WEAPON_KNIFE_CT || id == WEAPON_HEGRENADE || id == WEAPON_DECOY || id == WEAPON_INCGRENADE || id == WEAPON_MOLOTOV || id == WEAPON_C4 || id == WEAPON_TASER || id == WEAPON_FLASHBANG || id == WEAPON_SMOKEGRENADE || id == WEAPON_KNIFEGG )
			return false;
		else
			return true;
	}

	bool isRifle()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_AK47 || WeaponId == WEAPON_M4A1 || WeaponId == WEAPON_M4A1_SILENCER || WeaponId == WEAPON_GALILAR || WeaponId == WEAPON_FAMAS ||
			WeaponId == WEAPON_AUG || WeaponId == WEAPON_SG556;
	}

	bool isSmgW()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_MAC10 || WeaponId == WEAPON_MP7 || WeaponId == WEAPON_MP9 || WeaponId == WEAPON_P90 ||
			WeaponId == WEAPON_BIZON || WeaponId == WEAPON_UMP45;
	}

	bool isMachineW()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_NEGEV || WeaponId == WEAPON_M249;
	}

	bool IsNade()
	{
		if (!this)
			return false;

		int WeaponId = *this->GetItemDefinitionIndex();

		if (!WeaponId)
			return false;

		if (WeaponId == WEAPON_FLASHBANG || WeaponId == WEAPON_HEGRENADE || WeaponId == WEAPON_SMOKEGRENADE ||WeaponId == WEAPON_MOLOTOV || WeaponId == WEAPON_DECOY || WeaponId == WEAPON_INCGRENADE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsNonAutopistolWeapon()
	{
		int WeaponId = *this->GetItemDefinitionIndex();

		return WeaponId == WEAPON_FLASHBANG || WeaponId == WEAPON_HEGRENADE || WeaponId == WEAPON_SMOKEGRENADE ||
			WeaponId == WEAPON_MOLOTOV || WeaponId == WEAPON_DECOY || WeaponId == WEAPON_INCGRENADE || WeaponId == WEAPON_KNIFE_CT || WeaponId == WEAPON_HEGRENADE || WeaponId == WEAPON_DECOY || WeaponId == weapon_revolver;
	}

	char* GetGunName()
	{
		int WeaponId = *this->GetItemDefinitionIndex();
		switch( WeaponId )
		{
			case WEAPON_AK47:
				return "ak47";
				break;
			case WEAPON_AUG:
				return "aug";
				break;
			case weapon_revolver:
				return "revolver";
				break;
			case WEAPON_AWP:
				return "awp";
				break;
			case WEAPON_BIZON:
				return "ppbizon";
				break;
			case WEAPON_C4:
				return "c4";
				break;
			case WEAPON_CZ75A:
				return "cz75";
				break;
			case WEAPON_DEAGLE:
				return "deagle";
				break;
			case WEAPON_DECOY:
				return "decoygrenade";
				break;
			case WEAPON_ELITE:
				return "dual berettas";
				break;
			case WEAPON_FAMAS:
				return "famas";
				break;
			case WEAPON_FIVESEVEN:
				return "fiveseven";
				break;
			case WEAPON_FLASHBANG:
				return "flashbang";
				break;
			case WEAPON_G3SG1:
				return "g3sg1";
				break;
			case WEAPON_GALILAR:
				return "galilar";
				break;
			case WEAPON_GLOCK:
				return "glock18";
				break;
			case WEAPON_INCGRENADE:
				return "molotov";
				break;
			case WEAPON_MOLOTOV:
				return "molotov";
				break;
			case WEAPON_SSG08:
				return "ssg08";
				break;
			case WEAPON_HEGRENADE:
				return "hegrenade";
				break;
			case WEAPON_M249:
				return "m249";
				break;
			case WEAPON_M4A1:
				return "m4a1";
				break;
			case WEAPON_MAC10:
				return "mac10";
				break;
			case WEAPON_MAG7:
				return "mag7";
				break;
			case WEAPON_MP7:
				return "mp7";
				break;
			case WEAPON_MP9:
				return "mp9";
				break;
			case WEAPON_NOVA:
				return "nova";
				break;
			case WEAPON_NEGEV:
				return "negev";
				break;
			case WEAPON_P250:
				return "p250";
				break;
			case WEAPON_P90:
				return "p90";
				break;
			case WEAPON_SAWEDOFF:
				return "sawedoff";
				break;
			case WEAPON_SCAR20:
				return "scar20";
				break;
			case WEAPON_SMOKEGRENADE:
				return "smokegrenade";
				break;
			case WEAPON_SG556:
				return "sg553";
				break;
			case WEAPON_TEC9:
				return "tec9";
				break;
			case WEAPON_HKP2000:
				return "hkp2000";
				break;
			case WEAPON_USP_SILENCER:
				return "usp";
				break;
			case WEAPON_UMP45:
				return "ump45";
				break;
			case WEAPON_XM1014:
				return "xm1014";
				break;
			case WEAPON_TASER:
				return "taser";
				break;
			case WEAPON_M4A1_SILENCER:
				return "m4a1s";
		}
		if( IsKnife() )
			return "knife";
		return "invalid";
	}

	char* GetGunIcon()
	{
		int WeaponId = *this->GetItemDefinitionIndex();
		switch (WeaponId)
		{
		case WEAPON_AK47:
			return "B";
			break;
		case WEAPON_AUG:
			return "E";
			break;
		case weapon_revolver:
			return "F";
			break;
		case WEAPON_AWP:
			return "E";
			break;
		case WEAPON_BIZON:
			return "D";
			break;
		case WEAPON_C4:
			return "j";
			break;
		case WEAPON_CZ75A:
			return "Y";
			break;
		case WEAPON_DEAGLE:
			return "F";
			break;
		case WEAPON_DECOY:
			return "G";
			break;
		case WEAPON_ELITE:
			return "S";
			break;
		case WEAPON_FAMAS:
			return "T";
			break;
		case WEAPON_FIVESEVEN:
			return "U";
			break;
		case WEAPON_FLASHBANG:
			return "G";
			break;
		case WEAPON_G3SG1:
			return "I";
			break;
		case WEAPON_GALILAR:
			return "V";
			break;
		case WEAPON_GLOCK:
			return "C";
			break;
		case WEAPON_INCGRENADE:
			return "H";
			break;
		case WEAPON_MOLOTOV:
			return "H";
			break;
		case WEAPON_SSG08:
			return "N";
			break;
		case WEAPON_HEGRENADE:
			return "H";
			break;
		case WEAPON_M249:
			return "Z";
			break;
		case WEAPON_M4A1:
			return "W";
			break;
		case WEAPON_MAC10:
			return "L";
			break;
		case WEAPON_MAG7:
			return "K";
			break;
		case WEAPON_MP7:
			return "K";
			break;
		case WEAPON_MP9:
			return "D";
			break;
		case WEAPON_NOVA:
			return "K";
			break;
		case WEAPON_NEGEV:
			return "Z";
			break;
		case WEAPON_P250:
			return "Y";
			break;
		case WEAPON_P90:
			return "M";
			break;
		case WEAPON_SAWEDOFF:
			return "K";
			break;
		case WEAPON_SCAR20:
			return "I";
			break;
		case WEAPON_SMOKEGRENADE:
			return "P";
			break;
		case WEAPON_SG556:
			return "[";
			break;
		case WEAPON_TEC9:
			return "C";
			break;
		case WEAPON_HKP2000:
			return "Y";
			break;
		case WEAPON_USP_SILENCER:
			return "Y";
			break;
		case WEAPON_UMP45:
			return "Q";
			break;
		case WEAPON_XM1014:
			return "]";
			break;
		case WEAPON_TASER:
			return "";
			break;
		case WEAPON_M4A1_SILENCER:
			return "W";
		}
		if (IsKnife())
			return "J";
		return "";
	}

	

	bool IsMiscWeapon()
	{
		int iWeaponID = *this->GetItemDefinitionIndex();
		return ( iWeaponID == tknife || iWeaponID == ctknife
			|| iWeaponID == goldknife || iWeaponID == bomb
			|| iWeaponID == hegren || iWeaponID == decoygren
			|| iWeaponID == flashgren || iWeaponID == molotov
			|| iWeaponID == smoke || iWeaponID == incendiary || iWeaponID == 59
			|| iWeaponID == 500 || iWeaponID == 505 || iWeaponID == 506
			|| iWeaponID == 507 || iWeaponID == 508 || iWeaponID == 509
			|| iWeaponID == 515 );
	}

	bool IsGrenade()
	{
		int iWeaponID = *this->GetItemDefinitionIndex();
		return ( iWeaponID == decoygren
			|| iWeaponID == flashgren || iWeaponID == molotov
			|| iWeaponID == smoke || iWeaponID == incendiary );
	}

	bool IsKnife()
	{
		int iWeaponID = *this->GetItemDefinitionIndex();
		return ( iWeaponID == tknife || iWeaponID == ctknife
			|| iWeaponID == goldknife || iWeaponID == 59 || iWeaponID == 41
			|| iWeaponID == 500 || iWeaponID == 505 || iWeaponID == 506
			|| iWeaponID == 507 || iWeaponID == 508 || iWeaponID == 509
			|| iWeaponID == 515 );
	}

	bool IsReloading()
	{
		return GetFieldValue< bool >(0x3235);
	}

	CCSWeaponInfo* GetCSWpnData()
	{
		if (!this) return nullptr;
		typedef CCSWeaponInfo*(__thiscall* OriginalFn)(void*);
		return  getvfunc<OriginalFn>(this, 446)(this);
	}
};

class CBaseCSGrenade : CBaseCombatWeapon
{
public:
	float GetPinPulled()
	{
		static int m_bPinPulled = Netvar(("DT_BaseCSGrenade"), ("m_bPinPulled"));
		return GetFieldValue< bool >( m_bPinPulled );
	}

	float GetThrowTime()
	{
		static int m_fThrowTime = Netvar(("DT_BaseCSGrenade"), ("m_fThrowTime"));
		return *( float* )( ( uintptr_t )this + m_fThrowTime );
	}
};

class AnimationLayer
{
public:
	char  pad_0000[20];
	// These should also be present in the padding, don't see the use for it though
	//float	m_flLayerAnimtime;
	//float	m_flLayerFadeOuttime;
	uint32_t m_nOrder; //0x0014
	uint32_t m_nSequence; //0x0018
	float_t m_flPrevCycle; //0x001C
	float_t m_flWeight; //0x0020
	float_t m_flWeightDeltaRate; //0x0024
	float_t m_flPlaybackRate; //0x0028
	float_t m_flCycle; //0x002C
	void *m_pOwner; //0x0030 // player's thisptr
	char  pad_0038[4]; //0x0034
}; //Size: 0x0038

class CBasePlayerAnimState
{
public:
	// Class has no vtable.
	char pad_0x0000[0x28]; //0x0000
	float_t m_flTimeMoving; //0x0028 // unsure, seemed like it, unreliable
	char pad_0x002C[0x30]; //0x002C
	CBaseCombatWeapon *Weapon0; //0x005C All the weapons are the ptr to the same weapon, like, what?
	CBaseEntity *player; //0x0060 // didnt check indepth but probably the this ptr
	CBaseCombatWeapon *Weapon1; //0x0064 
	CBaseCombatWeapon *Weapon2; //0x0068 
	float_t m_flUnknownTimer1; //0x006C 
	float m_flLastAnimationStateClearTime; // not sure if this is it exactly but dumps say shit
	char pad_0x0074[0x4]; //0x0074
	float_t m_flEyeYaw; //0x0078 
	float_t m_flEyePitch; //0x007C 
	float_t m_flGoalFeetYaw; //0x0080 // both feet yaws go from 0 to 360 so -180 when using
	float_t m_flCurrentFeetYaw; //0x0084 
	bool  m_bCurrentFeetYawInitialized; //0x0088 
	float_t m_flLastMoveYaw; //0x008C // unsure.
	char pad_0x0090[0x5C]; //0x0090
	float m_flVelocity;
};

class CCSPlayerAnimState
{
public:

	virtual ~CCSPlayerAnimState() = 0;
	virtual void Update(float_t eyeYaw, float_t eyePitch) = 0;
};

class CCSGOPlayerAnimState
{
public:

	Vector GetVecVelocity()
	{
		// Only on ground velocity
		return *(Vector*)((uintptr_t)this + 0xC8);
	}

	float GetVelocity()
	{
		return *(float*)((uintptr_t)this + 0xEC);
	}

	char pad_0x0000[0x344]; //0x0000
}; //Size=0x344
