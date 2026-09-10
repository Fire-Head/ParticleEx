#pragma once
#include "_config.h"
#include "ParticlePS2.h"
#include "ParticleXB.h"
#include "ParticleXB2.h"

enum eParticleSwitch
{
	PS_ORIGINAL = 0,
	PS_PS2,
	PS_XBOX,
	PS_XBOX2,
	PS_MAX,
};

enum tNewParticleType
{
	NPARTICLE_SPARK = 0,
	NPARTICLE_SPARK_SMALL,
	NPARTICLE_WATER_SPARK,
	NPARTICLE_WHEEL_DIRT,
	NPARTICLE_SAND,
	NPARTICLE_WHEEL_WATER,
	NPARTICLE_BLOOD,
	NPARTICLE_BLOOD_SMALL,
	NPARTICLE_BLOOD_SPURT,
	NPARTICLE_DEBRIS,
	NPARTICLE_DEBRIS2,
	NPARTICLE_FLYERS,
	NPARTICLE_WATER,
	NPARTICLE_FLAME,
	NPARTICLE_FIREBALL,
	NPARTICLE_GUNFLASH,
	NPARTICLE_GUNFLASH_NOANIM,
	NPARTICLE_GUNSMOKE,
	NPARTICLE_GUNSMOKE2,
	NPARTICLE_CIGARETTE_SMOKE,
	NPARTICLE_SMOKE,
	NPARTICLE_SMOKE_SLOWMOTION,
	NPARTICLE_DRY_ICE,
	NPARTICLE_TEARGAS,
	NPARTICLE_GARAGEPAINT_SPRAY,
	NPARTICLE_SHARD,
	NPARTICLE_SPLASH,
	NPARTICLE_CARFLAME,
	NPARTICLE_STEAM,
	NPARTICLE_STEAM2,
	NPARTICLE_STEAM_NY,
	NPARTICLE_STEAM_NY_SLOWMOTION,
	NPARTICLE_GROUND_STEAM,
	NPARTICLE_ENGINE_STEAM,
	NPARTICLE_RAINDROP,
	NPARTICLE_RAINDROP_SMALL,
	NPARTICLE_RAIN_SPLASH,
	NPARTICLE_RAIN_SPLASH_BIGGROW,
	NPARTICLE_RAIN_SPLASHUP,
	NPARTICLE_WATERSPRAY,
	NPARTICLE_WATERDROP,
	NPARTICLE_BLOODDROP,
	NPARTICLE_EXPLOSION_MEDIUM,
	NPARTICLE_EXPLOSION_LARGE,
	NPARTICLE_EXPLOSION_MFAST,
	NPARTICLE_EXPLOSION_LFAST,
	NPARTICLE_CAR_SPLASH,
	NPARTICLE_BOAT_SPLASH,
	NPARTICLE_BOAT_THRUSTJET,
	NPARTICLE_WATER_HYDRANT,
	NPARTICLE_WATER_CANNON,
	NPARTICLE_EXTINGUISH_STEAM,
	NPARTICLE_PED_SPLASH,
	NPARTICLE_PEDFOOT_DUST,
	NPARTICLE_CAR_DUST,
	NPARTICLE_HELI_DUST,
	NPARTICLE_HELI_ATTACK,
	NPARTICLE_ENGINE_SMOKE,
	NPARTICLE_ENGINE_SMOKE2,
	NPARTICLE_CARFLAME_SMOKE,
	NPARTICLE_FIREBALL_SMOKE,
	NPARTICLE_PAINT_SMOKE,
	NPARTICLE_TREE_LEAVES,
	NPARTICLE_CARCOLLISION_DUST,
	NPARTICLE_CAR_DEBRIS,
	NPARTICLE_BIRD_DEBRIS,
	NPARTICLE_HELI_DEBRIS,
	NPARTICLE_EXHAUST_FUMES,
	NPARTICLE_RUBBER_SMOKE,
	NPARTICLE_BURNINGRUBBER_SMOKE,
	NPARTICLE_BULLETHIT_SMOKE,
	NPARTICLE_GUNSHELL_FIRST,
	NPARTICLE_GUNSHELL,
	NPARTICLE_GUNSHELL_BUMP1,
	NPARTICLE_GUNSHELL_BUMP2,
	NPARTICLE_ROCKET_SMOKE,
	NPARTICLE_TEST,
	NPARTICLE_BIRD_FRONT,
	NPARTICLE_SHIP_SIDE,
	NPARTICLE_BEASTIE,
	NPARTICLE_RAINDROP_2D,
	NPARTICLE_HEATHAZE,
	NPARTICLE_HEATHAZE_IN_DIST,
	
	//WARNING: add new particles to the end for compatibility with the original code
	NPARTICLE_CARFLAME_MOVING,
	//...
};

class CParticleEx
{
	static eParticleSwitch m_eCurrentParticle;
	
	static REVCXB::tParticleType TranslateParticleType(tNewParticleType type);
public:
	
	static Bool m_bUseOriginalSystem;
	
	
	static void ClearPSystem(eParticleSwitch s);
	static void ClearParticles();
	static void ClearAllParticles();
	
	static void SetFlame5Fix(Bool bEnabled);
	static void SetWaterDropsInInteriorsFix(Bool bEnabled);
	
	static void SetPS2PObjects(Bool bEnabled);
	static void SetXboxPObjects(Bool bEnabled);
	
	static void UpdatePObjects_PS2(Bool bReset = false);
	static void UpdatePObjects_Xbox(Bool bReset = false);
	
	static void ResetPObjects();
	static void UpdatePObjects(eParticleSwitch s);
	
	static void LoadPObjects();

	static void SetParticleSwitch(eParticleSwitch s);
	
	static eParticleSwitch GetCurrentParticle()       { return m_eCurrentParticle; }

	static void ReloadConfig();
	static void Initialise();
	static void Shutdown();
	
	static void *AddParticle(Int32 type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan);
	static void *AddParticle(Int32 type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan);

	static void Update();
	static void Render();

	static void RemoveCustomPSystem(eParticleSwitch s, Int32 type);
	static void RemovePSystem(Int32 type);
	
	static void HandleShipsAtHorizonStuff();
	static void HandleShootableBirdsStuff(CEntity *entity, CVector const&camPos);
	
	static bool IsOrig() { return GetCurrentParticle() == PS_ORIGINAL; }
	static bool IsPS2() { return GetCurrentParticle() == PS_PS2; }
	static bool IsXbox() { return GetCurrentParticle() == PS_XBOX; }
	static bool IsXbox2() { return GetCurrentParticle() == PS_XBOX2; }
};