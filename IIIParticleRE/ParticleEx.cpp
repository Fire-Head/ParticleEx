#include "ParticleEx.h"
#include "_precl.h"
#include "ParticleArray.h"
#include "PObjectMgr.h"
#include "settings.h"



eParticleSwitch CParticleEx::m_eCurrentParticle = PS_ORIGINAL;

Float CParticleEx::m_fFireSize = 0.8f;
Float CParticleEx::m_fSmokeSize = 1.1f;

Float CParticleEx::m_fPedRainSplashBiggrowMin = -2.5f; //-0.75
Float CParticleEx::m_fPedRainSplashBiggrowMax = 5.0f; //1.5
Float CParticleEx::m_fPedRainSplashVal = 0.5f;


Float CParticleEx::m_fBoatZAdd = 1.5f;
Float CParticleEx::m_fBoatFxSize = 1.5f;
Float CParticleEx::m_fBoatTargetMul = 0.01f;

	
Bool CParticleEx::m_bUseOriginalSystem = false;


void (__cdecl *CParticleEx::AddExtendedDroplets)(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan) = CParticleEx::AddExtendedDropletsNull;	
void __cdecl CParticleEx::AddExtendedDropletsNull(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	// null
}

Bool CParticleEx::m_bWaterdropsInstalled = false;



REXBOX::tParticleType CParticleEx::TranslateParticleType(tNewParticleType type)
{
	switch ( type )
	{
		case NPARTICLE_SPARK:               return REXBOX::PARTICLE_SPARK;
		case NPARTICLE_SPARK_SMALL:         return REXBOX::PARTICLE_SPARK_SMALL;
		case NPARTICLE_WHEEL_DIRT:          return REXBOX::PARTICLE_WHEEL_DIRT;
		case NPARTICLE_WHEEL_WATER:         return REXBOX::PARTICLE_WHEEL_WATER;
		case NPARTICLE_BLOOD:               return REXBOX::PARTICLE_BLOOD;
		case NPARTICLE_BLOOD_SMALL:         return REXBOX::PARTICLE_BLOOD_SMALL;
		case NPARTICLE_BLOOD_SPURT:         return REXBOX::PARTICLE_BLOOD_SPURT;
		case NPARTICLE_DEBRIS:              return REXBOX::PARTICLE_DEBRIS;
		case NPARTICLE_DEBRIS2:             return REXBOX::PARTICLE_DEBRIS2;
		case NPARTICLE_WATER:               return REXBOX::PARTICLE_WATER;
		case NPARTICLE_FLAME:               return REXBOX::PARTICLE_FLAME;
		case NPARTICLE_FIREBALL:            return REXBOX::PARTICLE_FIREBALL;
		case NPARTICLE_GUNFLASH:            return REXBOX::PARTICLE_GUNFLASH;
		case NPARTICLE_GUNFLASH_NOANIM:     return REXBOX::PARTICLE_GUNFLASH_NOANIM;
		case NPARTICLE_GUNSMOKE:            return REXBOX::PARTICLE_GUNSMOKE;
		case NPARTICLE_GUNSMOKE2:           return REXBOX::PARTICLE_GUNSMOKE2;
		case NPARTICLE_SMOKE:               return REXBOX::PARTICLE_SMOKE;
		case NPARTICLE_SMOKE_SLOWMOTION:    return REXBOX::PARTICLE_SMOKE_SLOWMOTION;
		case NPARTICLE_GARAGEPAINT_SPRAY:   return REXBOX::PARTICLE_GARAGEPAINT_SPRAY;
		case NPARTICLE_SHARD:               return REXBOX::PARTICLE_SHARD;
		case NPARTICLE_SPLASH:              return REXBOX::PARTICLE_SPLASH;
		case NPARTICLE_CARFLAME:            return REXBOX::PARTICLE_CARFLAME;
		case NPARTICLE_STEAM:               return REXBOX::PARTICLE_STEAM;
		case NPARTICLE_STEAM2:              return REXBOX::PARTICLE_STEAM2;
		case NPARTICLE_STEAM_NY:            return REXBOX::PARTICLE_STEAM_NY;
		case NPARTICLE_STEAM_NY_SLOWMOTION: return REXBOX::PARTICLE_STEAM_NY_SLOWMOTION;
		case NPARTICLE_ENGINE_STEAM:        return REXBOX::PARTICLE_ENGINE_STEAM;
		case NPARTICLE_RAINDROP:            return REXBOX::PARTICLE_RAINDROP;
		case NPARTICLE_RAINDROP_SMALL:      return REXBOX::PARTICLE_RAINDROP_SMALL;
		case NPARTICLE_RAIN_SPLASH:         return REXBOX::PARTICLE_RAIN_SPLASH;
		case NPARTICLE_RAIN_SPLASH_BIGGROW: return REXBOX::PARTICLE_RAIN_SPLASH_BIGGROW;
		case NPARTICLE_RAIN_SPLASHUP:       return REXBOX::PARTICLE_RAIN_SPLASHUP;
		case NPARTICLE_WATERSPRAY:          return REXBOX::PARTICLE_WATERSPRAY;
		case NPARTICLE_EXPLOSION_MEDIUM:    return REXBOX::PARTICLE_EXPLOSION_MEDIUM;
		case NPARTICLE_EXPLOSION_LARGE:     return REXBOX::PARTICLE_EXPLOSION_LARGE;
		case NPARTICLE_EXPLOSION_MFAST:     return REXBOX::PARTICLE_EXPLOSION_MFAST;
		case NPARTICLE_EXPLOSION_LFAST:     return REXBOX::PARTICLE_EXPLOSION_LFAST;
		case NPARTICLE_CAR_SPLASH:          return REXBOX::PARTICLE_CAR_SPLASH;
		case NPARTICLE_BOAT_SPLASH:         return REXBOX::PARTICLE_BOAT_SPLASH;
		case NPARTICLE_BOAT_THRUSTJET:      return REXBOX::PARTICLE_BOAT_THRUSTJET;
		case NPARTICLE_BOAT_WAKE:           return REXBOX::PARTICLE_BOAT_WAKE;
		case NPARTICLE_WATER_HYDRANT:       return REXBOX::PARTICLE_WATER_HYDRANT;
		case NPARTICLE_WATER_CANNON:        return REXBOX::PARTICLE_WATER_CANNON;
		case NPARTICLE_EXTINGUISH_STEAM:    return REXBOX::PARTICLE_EXTINGUISH_STEAM;
		case NPARTICLE_PED_SPLASH:          return REXBOX::PARTICLE_PED_SPLASH;
		case NPARTICLE_PEDFOOT_DUST:        return REXBOX::PARTICLE_PEDFOOT_DUST;
		case NPARTICLE_HELI_DUST:           return REXBOX::PARTICLE_HELI_DUST;
		case NPARTICLE_HELI_ATTACK:         return REXBOX::PARTICLE_HELI_ATTACK;
		case NPARTICLE_ENGINE_SMOKE:        return REXBOX::PARTICLE_ENGINE_SMOKE;
		case NPARTICLE_ENGINE_SMOKE2:       return REXBOX::PARTICLE_ENGINE_SMOKE2;
		case NPARTICLE_CARFLAME_SMOKE:      return REXBOX::PARTICLE_CARFLAME_SMOKE;
		case NPARTICLE_FIREBALL_SMOKE:      return REXBOX::PARTICLE_FIREBALL_SMOKE;
		case NPARTICLE_PAINT_SMOKE:         return REXBOX::PARTICLE_PAINT_SMOKE;
		case NPARTICLE_TREE_LEAVES:         return REXBOX::PARTICLE_TREE_LEAVES;
		case NPARTICLE_CARCOLLISION_DUST:   return REXBOX::PARTICLE_CARCOLLISION_DUST;
		case NPARTICLE_CAR_DEBRIS:          return REXBOX::PARTICLE_CAR_DEBRIS;
		case NPARTICLE_HELI_DEBRIS:         return REXBOX::PARTICLE_HELI_DEBRIS;
		case NPARTICLE_EXHAUST_FUMES:       return REXBOX::PARTICLE_EXHAUST_FUMES;
		case NPARTICLE_RUBBER_SMOKE:        return REXBOX::PARTICLE_RUBBER_SMOKE;
		case NPARTICLE_BURNINGRUBBER_SMOKE: return REXBOX::PARTICLE_BURNINGRUBBER_SMOKE;
		case NPARTICLE_BULLETHIT_SMOKE:     return REXBOX::PARTICLE_BULLETHIT_SMOKE;
		case NPARTICLE_GUNSHELL_FIRST:      return REXBOX::PARTICLE_GUNSHELL_FIRST;
		case NPARTICLE_GUNSHELL:            return REXBOX::PARTICLE_GUNSHELL;
		case NPARTICLE_GUNSHELL_BUMP1:      return REXBOX::PARTICLE_GUNSHELL_BUMP1;
		case NPARTICLE_GUNSHELL_BUMP2:      return REXBOX::PARTICLE_GUNSHELL_BUMP2;
		case NPARTICLE_TEST:                return REXBOX::PARTICLE_TEST;
		case NPARTICLE_BIRD_FRONT:          return REXBOX::PARTICLE_BIRD_FRONT;
		case NPARTICLE_RAINDROP_2D:         return REXBOX::PARTICLE_RAINDROP_2D;
		//
		case NPARTICLE_CARFLAME_MOVING:     return REXBOX::PARTICLE_CARFLAME_MOVING;
	}

	FATAL("Unknown Particle Type");

	return (REXBOX::tParticleType)-1;
}

void CParticleEx::ReloadConfig()
{
	CParticle::ReloadConfig();
	REXBOX::CParticle::ReloadConfig();
	REPS2::CParticle::ReloadConfig();

	CParticleArray::InitOriginalParticleArray(&CParticleArray::GetPC()[0], CParticleArray::GetPC().size());
}

void CParticleEx::Initialise()
{
	CParticle::Initialise();
	REXBOX::CParticle::Initialise();
	REPS2::CParticle::Initialise();

	SetFlame5Fix(CSettings::Get().m_bFixFlame5Bug);
	
	if ( CSettings::Get().m_bVCJet )
		SetVCJetPos();
	else
		SetPS2JetPos(CSettings::Get().m_bPS2JetPos);
	
	SetPS2Rain(CSettings::Get().m_bPS2Rain);
}

void CParticleEx::Shutdown()
{
	CParticle::Shutdown();	
	REXBOX::CParticle::Shutdown();
	REPS2::CParticle::Shutdown();
}

void *CParticleEx::AddParticle(Int32 type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	switch ( m_eCurrentParticle )
	{
		case PS_ORIGINAL:
			{
				ASSERT( type < MAX_PARTICLES );
				
				return CParticle::AddParticle((tParticleType)type,
							vecPos, vecDir, pEntity, fSize, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
			}
			break;
		case PS_XBOX:
			{
				REXBOX::tParticleType newType = TranslateParticleType((tNewParticleType)type);
				
				ASSERT( newType < REXBOX::MAX_PARTICLES );
				
				return REXBOX::CParticle::AddParticle(newType,
							vecPos, vecDir, pEntity, fSize, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
			}
			break;
		case PS_PS2:
			{
				ASSERT( type < REPS2::MAX_PARTICLES );

				return REPS2::CParticle::AddParticle((REPS2::tParticleType)type,
							vecPos, vecDir, pEntity, fSize, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
			}
			break;
	}
	
	FATAL("Unknown Particle Switch");

	return NULL;
}

void *CParticleEx::AddParticle(Int32 type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	switch ( m_eCurrentParticle )
	{
		case PS_ORIGINAL:
			{
				ASSERT( type < MAX_PARTICLES );

				return CParticle::AddParticle((tParticleType)type,
							vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
			}
			break;
		case PS_XBOX:
			{
				REXBOX::tParticleType newType = TranslateParticleType((tNewParticleType)type);
				
				ASSERT( newType < REXBOX::MAX_PARTICLES );

				return REXBOX::CParticle::AddParticle(newType,
							vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
			}
			break;
		case PS_PS2:
			{
				ASSERT( type < REPS2::MAX_PARTICLES );

				return REPS2::CParticle::AddParticle((REPS2::tParticleType)type,
							vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
			}
			break;
	}
	
	FATAL("Unknown Particle Switch");

	return NULL;
}

void CParticleEx::Update()
{
	switch ( m_eCurrentParticle )
	{
		case PS_ORIGINAL:
			{
				CParticle::Update();
				return;
			}
			break;
		case PS_XBOX:
			{
				REXBOX::CParticle::Update();
				return;
			}
			break;
		case PS_PS2:
			{
				REPS2::CParticle::Update();
				return;
			}
			break;
	}
	
	FATAL("Unknown Particle Switch");
}

void CParticleEx::Render()
{
	switch ( m_eCurrentParticle )
	{
		case PS_ORIGINAL:
			{
				CParticle::Render();
				return;
			}
			break;
		case PS_XBOX:
			{
				REXBOX::CParticle::Render();
				return;
			}
			break;
		case PS_PS2:
			{
				REPS2::CParticle::Render();
				return;
			}
			break;
	}
	
	FATAL("Unknown Particle Switch");
}


void CParticleEx::RemoveCustomPSystem(eParticleSwitch s, Int32 type)
{
	switch ( s )
	{
		case PS_ORIGINAL:
			{
				ASSERT( type < MAX_PARTICLES );

				CParticle::RemovePSystem((tParticleType)type);
				
				return;
			}
			break;
		case PS_XBOX:
			{
				REXBOX::tParticleType newType = TranslateParticleType((tNewParticleType)type);
				
				ASSERT( newType < REXBOX::MAX_PARTICLES );

				REXBOX::CParticle::RemovePSystem(newType);
				
				return;
			}
			break;
		case PS_PS2:
			{
				ASSERT( type < REPS2::MAX_PARTICLES );

				REPS2::CParticle::RemovePSystem((REPS2::tParticleType)type);
				
				return;
			}
			break;
	}
	
	FATAL("Unknown Particle Switch");
}

void CParticleEx::RemovePSystem(Int32 type)
{
	RemoveCustomPSystem(m_eCurrentParticle, type);
}

void CParticleEx::ClearPSystem(eParticleSwitch s)
{
	switch ( s )
	{
		case PS_ORIGINAL:
			{
				for ( Int32 i = 0; i < MAX_PARTICLES; i++ )
					RemoveCustomPSystem(s, i);

				return;
			}
			break;
		case PS_XBOX:
			{
				for ( Int32 i = 0; i < REXBOX::MAX_PARTICLES; i++ )
					RemoveCustomPSystem(s, i);

				return;
			}
			break;
		case PS_PS2:
			{
				for ( Int32 i = 0; i < REPS2::MAX_PARTICLES; i++ )
					RemoveCustomPSystem(s, i);
				
				return;
			}
			break;
	}
	
	FATAL("Unknown Particle Switch");
}

void CParticleEx::ClearParticles()
{
	ClearPSystem(m_eCurrentParticle);
	
	CVector &prevEntityPosition = *(CVector*)AddressByVersion(0x6503A4, 0x6503A4, 0x6603AC); // III
	prevEntityPosition = CVector(0.0f, 0.0f, 0.0f);
}

void CParticleEx::ClearAllParticles()
{
	for ( Int32 i = 0; i < PS_MAX; i++ )
		ClearPSystem((eParticleSwitch)i);
}


static RwRaster *&gpFlame5Raster = *(RwRaster **)AddressByVersion(0x648ED8, 0x648ED8, 0x658ED8);
static RwTexture *&gpFlame5Tex = *(RwTexture **)AddressByVersion(0x648ED4, 0x648ED4, 0x658ED4);
static RwTexture *&gpFlame1Tex = *(RwTexture **)AddressByVersion(0x648ECC, 0x648ECC, 0x658ECC);

static void _FixFlame5Bug(Bool enable)
{
	if ( gpFlame5Tex == NULL || gpFlame1Tex == NULL )
		return;

	if ( enable )
		gpFlame5Raster = RwTextureGetRaster(gpFlame5Tex);
	else
		gpFlame5Raster = RwTextureGetRaster(gpFlame1Tex);
}

void CParticleEx::SetFlame5Fix(Bool bEnabled)
{
	_FixFlame5Bug(bEnabled);
	REXBOX::CParticle::FixFlame5Bug(bEnabled);
	REPS2::CParticle::FixFlame5Bug(bEnabled);
}

void CParticleEx::SetPS2JetPos(Bool bEnabled)
{
	if ( bEnabled )
	{
		//WING_LF
		CPatch::SetInt(AddressByVersion(0x55982E, 0x55995E, 0x55990E) + 4, 13); // CExplosion::AddExplosion
		CPatch::SetInt(AddressByVersion(0x55A348, 0x55A478, 0x55A428) + 1, 13); // CExplosion::Update
	}
	else
	{
		//WING_LR
		CPatch::SetInt(AddressByVersion(0x55982E, 0x55995E, 0x55990E) + 4, 14); // CExplosion::AddExplosion
		CPatch::SetInt(AddressByVersion(0x55A348, 0x55A478, 0x55A428) + 1, 14); // CExplosion::Update
	}
}

void CParticleEx::SetVCJetPos()
{
	SetPS2JetPos(false);
	CPatch::SetInt(AddressByVersion(0x55982E, 0x55995E, 0x55990E) + 4, 18); // BOOT
}

void CParticleEx::SetPS2Rain(Bool bEnabled)
{
	if ( bEnabled )
		CPatch::SetChar(AddressByVersion(0x524A0A, 0x524C4A, 0x524BDA) + 4, 50);
	else
		CPatch::SetChar(AddressByVersion(0x524A0A, 0x524C4A, 0x524BDA) + 4, 35);
}

void CParticleEx::GenerateFlameThrowerParticles(CVector pos, CVector dir)
{
	if ( GetCurrentParticle() == PS_XBOX )
	{
		dir *= 0.4f;
	
		CVector posStep = dir * 0.15f;
	
		for ( Int32 i = 0; i < 10; i++ )
		{
			pos += posStep;

			AddParticle(NPARTICLE_FIREBALL,
				pos,
				dir,
				NULL,
				0.0f,
				0,
				Int32(CGeneral::GetRandomNumberInRange(0.0f, 360.0f)),
				0,
				0);
	
		}
	}
	else
	{
		for ( Int32 i = 0; i < 5; i++ )
		{
			dir *= 0.7f;

			AddParticle(NPARTICLE_FIREBALL,
					pos,
					dir,
					NULL,
					0.0f,
					0,
					0,
					0,
					0);
		}
	}
}

void CParticleEx::SetXboxPObjects(Bool bEnabled)
{
	if ( bEnabled )
	{
		// POBJECT_DARK_SMOKE
		CPatch::SetInt(AddressByVersion(0x4BC728, 0x4BC818, 0x4BC7A8) + 3, NPARTICLE_ENGINE_SMOKE2); //m_ParticleType
		CPatch::SetChar(AddressByVersion(0x4BC72F, 0x4BC81F, 0x4BC7AF) + 3, 4); //1, m_nNumEffectCycles
		
		CPatch::RedirectJump(AddressByVersion(0x4BC73E, 0x4BC82E, 0x4BC7BE), AddressByVersion(0x4BC9B0, 0x4BCAA0, 0x4BCA30));
		
		// POBJECT_FIRE_HYDRANT
		CPatch::SetInt(AddressByVersion(0x4BC7A7, 0x4BC897, 0x4BC827) + 1, 15000); //m_nRemoveTimer
	}
	else
	{
		// POBJECT_DARK_SMOKE
		CPatch::SetInt(AddressByVersion(0x4BC728, 0x4BC818, 0x4BC7A8) + 3, NPARTICLE_STEAM_NY); //m_ParticleType
		CPatch::SetChar(AddressByVersion(0x4BC72F, 0x4BC81F, 0x4BC7AF) + 3, 1); //m_nNumEffectCycles
		
		CPatch::SetChar(AddressByVersion(0x4BC73E, 0x4BC82E, 0x4BC7BE), 0xA1);
		CPatch::SetPointer(AddressByVersion(0x4BC73E, 0x4BC82E, 0x4BC7BE) + 1, (void *)AddressByVersion(0x5F7EA0, 0x5F7C88, 0x604C80));
		
		// POBJECT_FIRE_HYDRANT
		CPatch::SetInt(AddressByVersion(0x4BC7A7, 0x4BC897, 0x4BC827) + 1, 5000); //m_nRemoveTimer
	}
}

void CParticleEx::UpdatePObjects_Xbox(Bool bReset)
{
	if ( bReset == false )
	{
		for ( Int32 i = 0; i < getMaxPObjects(); i++ )
		{
			CParticleObject *pobj = &getPObject(i);
			
			if ( pobj->m_nState != PARTICLEOBJECTSTATE_UPDATE_CLOSE && pobj->m_nState != PARTICLEOBJECTSTATE_UPDATE_FAR )
				continue;
			
			switch ( pobj->m_Type )
			{
				case POBJECT_DARK_SMOKE:
					{
						pobj->m_ParticleType = NPARTICLE_ENGINE_SMOKE2;
						pobj->m_nNumEffectCycles = 4;
						pobj->m_Color.colorInt = 0x00000000;
					}
					break;
				case POBJECT_FIRE_HYDRANT:
					{
						if ( pobj->m_nRemoveTimer != 0 && pobj->m_nRemoveTimer > CTimer::m_snTimeInMilliseconds )
							pobj->m_nRemoveTimer += 15000 - 5000;
					}
					break;
			}
		}
	}
	else
	{
		for ( Int32 i = 0; i < getMaxPObjects(); i++ )
		{
			CParticleObject *pobj = &getPObject(i);
			
			if ( pobj->m_nState != PARTICLEOBJECTSTATE_UPDATE_CLOSE && pobj->m_nState != PARTICLEOBJECTSTATE_UPDATE_FAR )
				continue;
			
			switch ( pobj->m_Type )
			{
				case POBJECT_DARK_SMOKE:
					{
						pobj->m_ParticleType = NPARTICLE_STEAM_NY;
						pobj->m_nNumEffectCycles = 1;
						pobj->m_Color.colorInt = 0xFF101010;
					}
					break;
				case POBJECT_FIRE_HYDRANT:
					{
						if ( pobj->m_nRemoveTimer != 0 && pobj->m_nRemoveTimer > CTimer::m_snTimeInMilliseconds )
							pobj->m_nRemoveTimer -= 15000 - 5000;
					}
					break;
			}
		}
	}
}

void CParticleEx::SetPS2PObjects(Bool bEnabled)
{
	if ( bEnabled )
	{
		//POBJECT_PAVEMENT_STEAM
		CPatch::SetChar(AddressByVersion(0x4BC6C7, 0x4BC7B7, 0x4BC747) + 3, 1); // m_nSkipFrames to 1

		//POBJECT_WALL_STEAM
		CPatch::SetChar(AddressByVersion(0x4BC6FD, 0x4BC7ED, 0x4BC77D) + 3, 1); //m_nSkipFrames to 1

		//POBJECT_DARK_SMOKE
		CPatch::SetChar(AddressByVersion(0x4BC733, 0x4BC823, 0x4BC7B3) + 3, 1); //m_nSkipFrames to 1

		//POBJECT_CAR_WATER_SPLASH
		//POBJECT_PED_WATER_SPLASH
		CPatch::SetChar(AddressByVersion(0x4BC7C5, 0x4BC8B5, 0x4BC845) + 3, 3); //m_nSkipFrames to 3

		//POBJECT_SPLASHES_AROUND
		CPatch::SetChar(AddressByVersion(0x4BC7DC, 0x4BC8CC, 0x4BC85C) + 3, 30); //m_nNumEffectCycles to 30

		//POBJECT_SMALL_FIRE
		CPatch::SetChar(AddressByVersion(0x4BC7FB, 0x4BC8EB, 0x4BC87B) + 3, 1); //m_nSkipFrames to 1

		//POBJECT_BIG_FIRE
		CPatch::SetChar(AddressByVersion(0x4BC82B, 0x4BC91B, 0x4BC8AB) + 3, 1); //m_nSkipFrames to 1

		//POBJECT_FIRE_TRAIL
		CPatch::SetChar(AddressByVersion(0x4BC8BB, 0x4BC9AB, 0x4BC93B) + 3, 1); //m_nSkipFrames to 1
	}
	else
	{
		//POBJECT_PAVEMENT_STEAM
		CPatch::SetChar(AddressByVersion(0x4BC6C7, 0x4BC7B7, 0x4BC747) + 3, 3); // m_nSkipFrames to 1
		
		//POBJECT_WALL_STEAM
		CPatch::SetChar(AddressByVersion(0x4BC6FD, 0x4BC7ED, 0x4BC77D) + 3, 3); //m_nSkipFrames to 1
		
		//POBJECT_DARK_SMOKE
		CPatch::SetChar(AddressByVersion(0x4BC733, 0x4BC823, 0x4BC7B3) + 3, 3); //m_nSkipFrames to 1
		
		//POBJECT_CAR_WATER_SPLASH
		//POBJECT_PED_WATER_SPLASH
		CPatch::SetChar(AddressByVersion(0x4BC7C5, 0x4BC8B5, 0x4BC845) + 3, 1); //m_nSkipFrames to 3
		
		//POBJECT_SPLASHES_AROUND
		CPatch::SetChar(AddressByVersion(0x4BC7DC, 0x4BC8CC, 0x4BC85C) + 3, 15); //m_nNumEffectCycles to 30
		
		//POBJECT_SMALL_FIRE
		CPatch::SetChar(AddressByVersion(0x4BC7FB, 0x4BC8EB, 0x4BC87B) + 3, 2); //m_nSkipFrames to 1
		
		//POBJECT_BIG_FIRE
		CPatch::SetChar(AddressByVersion(0x4BC82B, 0x4BC91B, 0x4BC8AB) + 3, 2); //m_nSkipFrames to 1
		
		//POBJECT_FIRE_TRAIL
		CPatch::SetChar(AddressByVersion(0x4BC8BB, 0x4BC9AB, 0x4BC93B) + 3, 3); //m_nSkipFrames to 1
	}
}


void CParticleEx::UpdatePObjects_PS2(Bool bReset)
{
	if ( bReset == false )
	{
		for ( Int32 i = 0; i < getMaxPObjects(); i++ )
		{
			CParticleObject *pobj = &getPObject(i);
			
			if ( pobj->m_nState != PARTICLEOBJECTSTATE_UPDATE_CLOSE && pobj->m_nState != PARTICLEOBJECTSTATE_UPDATE_FAR )
				continue;
			
			
			switch ( pobj->m_Type )
			{
				case POBJECT_PAVEMENT_STEAM:
					{
						pobj->m_nSkipFrames = 1;
					}
					break;
				
				case POBJECT_WALL_STEAM:
					{
						pobj->m_nSkipFrames = 1;
					}
					break;
					
				case POBJECT_DARK_SMOKE:
					{
						pobj->m_nSkipFrames = 1;
					}
					break;

				case POBJECT_CAR_WATER_SPLASH:
				case POBJECT_PED_WATER_SPLASH:
					{
						pobj->m_nSkipFrames = 3;
					}
					break;
					
				case POBJECT_SPLASHES_AROUND:
					{
						pobj->m_nNumEffectCycles = 30;
					}
					break;
					
				case POBJECT_SMALL_FIRE:
					{
						pobj->m_nSkipFrames = 1;
					}
					break;
					
				case POBJECT_BIG_FIRE:
					{
						pobj->m_nSkipFrames = 1;
					}
					break;
					
				case POBJECT_FIRE_TRAIL:
					{
						pobj->m_nSkipFrames = 1;
					}
					break;
			}
		}
	}
	else
	{
		for ( Int32 i = 0; i < getMaxPObjects(); i++ )
		{
			CParticleObject *pobj = &getPObject(i);
			
			if ( pobj->m_nState != PARTICLEOBJECTSTATE_UPDATE_CLOSE && pobj->m_nState != PARTICLEOBJECTSTATE_UPDATE_FAR )
				continue;
			
			switch ( pobj->m_Type )
			{
				case POBJECT_PAVEMENT_STEAM:
					{
						pobj->m_nSkipFrames = 3;
					}
					break;

				case POBJECT_WALL_STEAM:
					{
						pobj->m_nSkipFrames = 3;
					}
					break;
			

				case POBJECT_DARK_SMOKE:
					{
						pobj->m_nSkipFrames = 3;
					}
					break;
		
				case POBJECT_CAR_WATER_SPLASH:
				case POBJECT_PED_WATER_SPLASH:
					{
						pobj->m_nSkipFrames = 1;
					}
					break;
		
				case POBJECT_SPLASHES_AROUND:
					{
						pobj->m_nNumEffectCycles = 15;
					}
					break;
		
				case POBJECT_SMALL_FIRE:
					{
						pobj->m_nSkipFrames = 2;
					}
					break;
		
				case POBJECT_BIG_FIRE:
					{
						pobj->m_nSkipFrames = 2;
					}
					break;
		
				case POBJECT_FIRE_TRAIL:
					{
						pobj->m_nSkipFrames = 3;
					}
					break;
			}
		}
	}
}

void CParticleEx::ResetPObjects()
{
	UpdatePObjects_Xbox(true);
	UpdatePObjects_PS2(true);
}

void CParticleEx::UpdatePObjects(eParticleSwitch s)
{
	switch ( s )
	{
		case PS_ORIGINAL:
			{
				ResetPObjects();
			}
			break;
			
		case PS_PS2:
			{
				ResetPObjects();
				UpdatePObjects_PS2();
			}
			break;
			
		case PS_XBOX:
			{
				ResetPObjects();
				UpdatePObjects_Xbox();
			}
			break;
			
	}
}

void CParticleEx::LoadPObjects()
{
	UpdatePObjects(GetCurrentParticle());
}

void CParticleEx::SetParticleSwitch(eParticleSwitch s)
{
	switch ( s )
	{
		case PS_ORIGINAL:
			{
				m_bUseOriginalSystem = true;
		
				m_fFireSize = 1.8f;
				m_fSmokeSize = 0.5f;
				
				CPatch::SetChar(AddressByVersion(0x479AB6, 0x479AB6, 0x479AB6) + 2, 80); // CFire time
				
				CPatch::RedirectJZ(AddressByVersion(0x535A7F, 0x535CBF, 0x535C4F), (void *)AddressByVersion(0x535B0B, 0x535D4B, 0x535CDB)); // WATERSPRAY
				
				//
				CPatch::SetInt(AddressByVersion(0x4C88B7, 0x4C8957, 0x4C88E7) + 1, 1500);
				m_fPedRainSplashVal = 0.25f;
				m_fPedRainSplashBiggrowMin = -0.75f;
				m_fPedRainSplashBiggrowMax = 1.5f;
				CPatch::SetFloat(AddressByVersion(0x5F84FC, 0x5F82E4, 0x6052DC), 2.2f);
				CPatch::SetInt(AddressByVersion(0x4C8619, 0x4C86B9, 0x4C8649) + 1, 200);
				//

				//
				m_fBoatZAdd = 1.5f;
				m_fBoatFxSize = 1.5f;
				m_fBoatTargetMul = 0.01f;
				//
				
				SetXboxPObjects(false);
				SetPS2PObjects(false);
			}
			break;
			
		case PS_PS2:
			{
				m_bUseOriginalSystem = false;
		
				m_fFireSize = 1.8f;
				m_fSmokeSize = 0.5f;
				
				CPatch::SetChar(AddressByVersion(0x479AB6, 0x479AB6, 0x479AB6) + 2, 80); // CFire time
				
				CPatch::RedirectJZ(AddressByVersion(0x535A7F, 0x535CBF, 0x535C4F), (void *)AddressByVersion(0x535A85, 0x535CC5, 0x535C55)); // WATERSPRAY
				
				//
				CPatch::SetInt(AddressByVersion(0x4C88B7, 0x4C8957, 0x4C88E7) + 1, 2500);
				m_fPedRainSplashVal = 0.5f;
				m_fPedRainSplashBiggrowMin = -2.5f;
				m_fPedRainSplashBiggrowMax = 5.0f;
				CPatch::SetFloat(AddressByVersion(0x5F84FC, 0x5F82E4, 0x6052DC), 1.6f);
				CPatch::SetInt(AddressByVersion(0x4C8619, 0x4C86B9, 0x4C8649) + 1, 350);
				//
				
				//
				m_fBoatZAdd = 1.0f;
				m_fBoatFxSize = 0.0f;
				m_fBoatTargetMul = 0.03f;
				//
				
				SetXboxPObjects(false);
				SetPS2PObjects(true);
			}
			break;
			
		case PS_XBOX:
			{
				m_bUseOriginalSystem = false;
		
				//xboxvalue
				//m_fFireSize = 0.8f;
		
				m_fFireSize = 1.8f;
				m_fSmokeSize = 1.1f;
				
				CPatch::SetChar(AddressByVersion(0x479AB6, 0x479AB6, 0x479AB6) + 2, 50); // CFire time
				
				CPatch::RedirectJZ(AddressByVersion(0x535A7F, 0x535CBF, 0x535C4F), (void *)AddressByVersion(0x535B0B, 0x535D4B, 0x535CDB)); // WATERSPRAY
				
				
				//
				CPatch::SetInt(AddressByVersion(0x4C88B7, 0x4C8957, 0x4C88E7) + 1, 1500);
				m_fPedRainSplashVal = 0.25f;
				m_fPedRainSplashBiggrowMin = -0.75f;
				m_fPedRainSplashBiggrowMax = 1.5f;
				CPatch::SetFloat(AddressByVersion(0x5F84FC, 0x5F82E4, 0x6052DC), 2.2f);
				CPatch::SetInt(AddressByVersion(0x4C8619, 0x4C86B9, 0x4C8649) + 1, 200);
				//
				
				//
				m_fBoatZAdd = 1.5f;
				m_fBoatFxSize = 1.5f;
				m_fBoatTargetMul = 0.01f;
				//
				
				SetPS2PObjects(false);
				SetXboxPObjects(true);
			}
			break;
	}
	
	m_eCurrentParticle = s;
}
