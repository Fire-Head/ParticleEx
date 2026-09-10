#include "ParticleEx.h"
#include "_precl.h"
#include "PObjectMgr.h"
#include "settings.h"
#include "inc/CPatch.h"



eParticleSwitch CParticleEx::m_eCurrentParticle = PS_ORIGINAL;

Bool CParticleEx::m_bUseOriginalSystem = false;

REVCXB::tParticleType CParticleEx::TranslateParticleType(tNewParticleType type)
{
	switch ( type )
	{
		case NPARTICLE_SPARK:				return REVCXB::PARTICLE_SPARK;
		case NPARTICLE_SPARK_SMALL:			return REVCXB::PARTICLE_SPARK_SMALL;
		case NPARTICLE_WATER_SPARK:			return REVCXB::PARTICLE_WATER_SPARK;
		case NPARTICLE_WHEEL_DIRT:			return REVCXB::PARTICLE_WHEEL_DIRT;
		case NPARTICLE_SAND:				return REVCXB::PARTICLE_SAND;
		case NPARTICLE_WHEEL_WATER:			return REVCXB::PARTICLE_WHEEL_WATER;
		case NPARTICLE_BLOOD:				return REVCXB::PARTICLE_BLOOD;
		case NPARTICLE_BLOOD_SMALL:			return REVCXB::PARTICLE_BLOOD_SMALL;
		case NPARTICLE_BLOOD_SPURT:			return REVCXB::PARTICLE_BLOOD_SPURT;
		case NPARTICLE_DEBRIS:				return REVCXB::PARTICLE_DEBRIS;
		case NPARTICLE_DEBRIS2:				return REVCXB::PARTICLE_DEBRIS2;
		case NPARTICLE_FLYERS:				return REVCXB::PARTICLE_FLYERS;
		case NPARTICLE_WATER:				return REVCXB::PARTICLE_WATER;
		case NPARTICLE_FLAME:				return REVCXB::PARTICLE_FLAME;
		case NPARTICLE_FIREBALL:			return REVCXB::PARTICLE_FIREBALL;
		case NPARTICLE_GUNFLASH:			return REVCXB::PARTICLE_GUNFLASH;
		case NPARTICLE_GUNFLASH_NOANIM:		return REVCXB::PARTICLE_GUNFLASH_NOANIM;
		case NPARTICLE_GUNSMOKE:			return REVCXB::PARTICLE_GUNSMOKE;
		case NPARTICLE_GUNSMOKE2:			return REVCXB::PARTICLE_GUNSMOKE2;
		case NPARTICLE_CIGARETTE_SMOKE:		return REVCXB::PARTICLE_CIGARETTE_SMOKE;
		case NPARTICLE_SMOKE:				return REVCXB::PARTICLE_SMOKE;
		case NPARTICLE_SMOKE_SLOWMOTION:	return REVCXB::PARTICLE_SMOKE_SLOWMOTION;
		case NPARTICLE_DRY_ICE:				return REVCXB::PARTICLE_DRY_ICE;
		case NPARTICLE_TEARGAS:				return REVCXB::PARTICLE_TEARGAS;
		case NPARTICLE_GARAGEPAINT_SPRAY:	return REVCXB::PARTICLE_GARAGEPAINT_SPRAY;
		case NPARTICLE_SHARD:				return REVCXB::PARTICLE_SHARD;
		case NPARTICLE_SPLASH:				return REVCXB::PARTICLE_SPLASH;
		case NPARTICLE_CARFLAME:			return REVCXB::PARTICLE_CARFLAME;
		case NPARTICLE_STEAM:				return REVCXB::PARTICLE_STEAM;
		case NPARTICLE_STEAM2:				return REVCXB::PARTICLE_STEAM2;
		case NPARTICLE_STEAM_NY:			return REVCXB::PARTICLE_STEAM_NY;
		case NPARTICLE_STEAM_NY_SLOWMOTION:	return REVCXB::PARTICLE_STEAM_NY_SLOWMOTION;
		case NPARTICLE_GROUND_STEAM:		return REVCXB::PARTICLE_GROUND_STEAM;
		case NPARTICLE_ENGINE_STEAM:		return REVCXB::PARTICLE_ENGINE_STEAM;
		case NPARTICLE_RAINDROP:			return REVCXB::PARTICLE_RAINDROP;
		case NPARTICLE_RAINDROP_SMALL:		return REVCXB::PARTICLE_RAINDROP_SMALL;
		case NPARTICLE_RAIN_SPLASH:			return REVCXB::PARTICLE_RAIN_SPLASH;
		case NPARTICLE_RAIN_SPLASH_BIGGROW:	return REVCXB::PARTICLE_RAIN_SPLASH_BIGGROW;
		case NPARTICLE_RAIN_SPLASHUP:		return REVCXB::PARTICLE_RAIN_SPLASHUP;
		case NPARTICLE_WATERSPRAY:			return REVCXB::PARTICLE_WATERSPRAY;
		case NPARTICLE_WATERDROP:			return REVCXB::PARTICLE_WATERDROP;
		case NPARTICLE_BLOODDROP:			return REVCXB::PARTICLE_BLOODDROP;
		case NPARTICLE_EXPLOSION_MEDIUM:	return REVCXB::PARTICLE_EXPLOSION_MEDIUM;
		case NPARTICLE_EXPLOSION_LARGE:		return REVCXB::PARTICLE_EXPLOSION_LARGE;
		case NPARTICLE_EXPLOSION_MFAST:		return REVCXB::PARTICLE_EXPLOSION_MFAST;
		case NPARTICLE_EXPLOSION_LFAST:		return REVCXB::PARTICLE_EXPLOSION_LFAST;
		case NPARTICLE_CAR_SPLASH:			return REVCXB::PARTICLE_CAR_SPLASH;
		case NPARTICLE_BOAT_SPLASH:			return REVCXB::PARTICLE_BOAT_SPLASH;
		case NPARTICLE_BOAT_THRUSTJET:		return REVCXB::PARTICLE_BOAT_THRUSTJET;
		case NPARTICLE_WATER_HYDRANT:		return REVCXB::PARTICLE_WATER_HYDRANT;
		case NPARTICLE_WATER_CANNON:		return REVCXB::PARTICLE_WATER_CANNON;
		case NPARTICLE_EXTINGUISH_STEAM:	return REVCXB::PARTICLE_EXTINGUISH_STEAM;
		case NPARTICLE_PED_SPLASH:			return REVCXB::PARTICLE_PED_SPLASH;
		case NPARTICLE_PEDFOOT_DUST:		return REVCXB::PARTICLE_PEDFOOT_DUST;
		case NPARTICLE_CAR_DUST:			return REVCXB::PARTICLE_CAR_DUST;
		case NPARTICLE_HELI_DUST:			return REVCXB::PARTICLE_HELI_DUST;
		case NPARTICLE_HELI_ATTACK:			return REVCXB::PARTICLE_HELI_ATTACK;
		case NPARTICLE_ENGINE_SMOKE:		return REVCXB::PARTICLE_ENGINE_SMOKE;
		case NPARTICLE_ENGINE_SMOKE2:		return REVCXB::PARTICLE_ENGINE_SMOKE2;
		case NPARTICLE_CARFLAME_SMOKE:		return REVCXB::PARTICLE_CARFLAME_SMOKE;
		case NPARTICLE_FIREBALL_SMOKE:		return REVCXB::PARTICLE_FIREBALL_SMOKE;
		case NPARTICLE_PAINT_SMOKE:			return REVCXB::PARTICLE_PAINT_SMOKE;
		case NPARTICLE_TREE_LEAVES:			return REVCXB::PARTICLE_TREE_LEAVES;
		case NPARTICLE_CARCOLLISION_DUST:	return REVCXB::PARTICLE_CARCOLLISION_DUST;
		case NPARTICLE_CAR_DEBRIS:			return REVCXB::PARTICLE_CAR_DEBRIS;
		case NPARTICLE_BIRD_DEBRIS:			return REVCXB::PARTICLE_BIRD_DEBRIS;
		case NPARTICLE_HELI_DEBRIS:			return REVCXB::PARTICLE_HELI_DEBRIS;
		case NPARTICLE_EXHAUST_FUMES:		return REVCXB::PARTICLE_EXHAUST_FUMES;
		case NPARTICLE_RUBBER_SMOKE:		return REVCXB::PARTICLE_RUBBER_SMOKE;
		case NPARTICLE_BURNINGRUBBER_SMOKE:	return REVCXB::PARTICLE_BURNINGRUBBER_SMOKE;
		case NPARTICLE_BULLETHIT_SMOKE:		return REVCXB::PARTICLE_BULLETHIT_SMOKE;
		case NPARTICLE_GUNSHELL_FIRST:		return REVCXB::PARTICLE_GUNSHELL_FIRST;
		case NPARTICLE_GUNSHELL:			return REVCXB::PARTICLE_GUNSHELL;
		case NPARTICLE_GUNSHELL_BUMP1:		return REVCXB::PARTICLE_GUNSHELL_BUMP1;
		case NPARTICLE_GUNSHELL_BUMP2:		return REVCXB::PARTICLE_GUNSHELL_BUMP2;
		case NPARTICLE_ROCKET_SMOKE:		return REVCXB::PARTICLE_ROCKET_SMOKE;
		case NPARTICLE_TEST:				return REVCXB::PARTICLE_TEST;
		case NPARTICLE_BIRD_FRONT:			return REVCXB::PARTICLE_BIRD_FRONT;
		case NPARTICLE_SHIP_SIDE:			return REVCXB::PARTICLE_SHIP_SIDE;
		case NPARTICLE_BEASTIE:				return REVCXB::PARTICLE_BEASTIE;
		case NPARTICLE_RAINDROP_2D:			return REVCXB::PARTICLE_RAINDROP_2D;
		case NPARTICLE_HEATHAZE:			return REVCXB::PARTICLE_HEATHAZE;
		case NPARTICLE_HEATHAZE_IN_DIST:	return REVCXB::PARTICLE_HEATHAZE_IN_DIST;

		case NPARTICLE_CARFLAME_MOVING:		return REVCXB::PARTICLE_CARFLAME_MOVING;
	}

	FATAL("Unknown Particle Type");

	return (REVCXB::tParticleType)-1;
}

void CParticleEx::ReloadConfig()
{
	CParticle::ReloadConfig();
	REVC::CParticle::ReloadConfig();
	REVCXB::CParticle::ReloadConfig();
	REVCXB2::CParticle::ReloadConfig();
}

void CParticleEx::Initialise()
{
	CParticle::Initialise();
	REVC::CParticle::Initialise();
	REVCXB::CParticle::Initialise();
	REVCXB2::CParticle::Initialise();

	SetFlame5Fix(CSettings::Get().m_bFixFlame5Bug);
	SetWaterDropsInInteriorsFix(CSettings::Get().m_bFixWaterDropsInInteriors);
}

void CParticleEx::Shutdown()
{
	CParticle::Shutdown();	
	REVC::CParticle::Shutdown();
	REVCXB::CParticle::Shutdown();
	REVCXB2::CParticle::Shutdown();
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
		case PS_PS2:
			{
				ASSERT( type < REVC::MAX_PARTICLES );

				return REVC::CParticle::AddParticle((REVC::tParticleType)type,
							vecPos, vecDir, pEntity, fSize, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
			}
			break;
		case PS_XBOX:
			{
				REVCXB::tParticleType newType = TranslateParticleType((tNewParticleType)type);
				
				if ( newType == -1 )
					return NULL;
				
				ASSERT( newType < REVCXB::MAX_PARTICLES );

				return REVCXB::CParticle::AddParticle(newType,
							vecPos, vecDir, pEntity, fSize, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
			}
			break;
			
		case PS_XBOX2:
			{
				REVCXB2::tParticleType newType = (REVCXB2::tParticleType)TranslateParticleType((tNewParticleType)type);
				
				if ( newType == -1 )
					return NULL;
				
				ASSERT( newType < REVCXB2::MAX_PARTICLES );

				return REVCXB2::CParticle::AddParticle(newType,
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
		case PS_PS2:
			{
				ASSERT( type < REVC::MAX_PARTICLES );

				return REVC::CParticle::AddParticle((REVC::tParticleType)type,
							vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
			}
			break;
		case PS_XBOX:
			{
				REVCXB::tParticleType newType = TranslateParticleType((tNewParticleType)type);
				
				if ( newType == -1 )
					return NULL;
				
				ASSERT( newType < REVCXB::MAX_PARTICLES );

				return REVCXB::CParticle::AddParticle(newType,
							vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
			}
			break;
			
		case PS_XBOX2:
			{
				REVCXB2::tParticleType newType = (REVCXB2::tParticleType)TranslateParticleType((tNewParticleType)type);
				
				if ( newType == -1 )
					return NULL;
				
				ASSERT( newType < REVCXB2::MAX_PARTICLES );

				return REVCXB2::CParticle::AddParticle(newType,
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
		case PS_PS2:
			{
				REVC::CParticle::Update();
				return;
			}
			break;
		case PS_XBOX:
			{
				REVCXB::CParticle::Update();
				return;
			}
			break;
			
		case PS_XBOX2:
			{
				REVCXB2::CParticle::Update();
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
		case PS_PS2:
			{
				REVC::CParticle::Render();
				return;
			}
			break;
		case PS_XBOX:
			{
				REVCXB::CParticle::Render();
				return;
			}
			break;
		case PS_XBOX2:
			{
				REVCXB2::CParticle::Render();
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
		case PS_PS2:
			{
				ASSERT( type < REVC::MAX_PARTICLES );

				REVC::CParticle::RemovePSystem((REVC::tParticleType)type);
				
				return;
			}
			break;
		case PS_XBOX:
			{
				REVCXB::tParticleType newType = TranslateParticleType((tNewParticleType)type);
				
				ASSERT( newType < REVCXB::MAX_PARTICLES );

				REVCXB::CParticle::RemovePSystem(newType);
				
				return;
			}
			
		case PS_XBOX2:
			{
				REVCXB2::tParticleType newType = (REVCXB2::tParticleType)TranslateParticleType((tNewParticleType)type);
				
				ASSERT( newType < REVCXB2::MAX_PARTICLES );

				REVCXB2::CParticle::RemovePSystem(newType);
				
				return;
			}
	}
	
	FATAL("Unknown Particle Switch");
}

void CParticleEx::HandleShipsAtHorizonStuff()
{
	switch ( m_eCurrentParticle )
	{
		case PS_ORIGINAL:
			{
				CParticle::HandleShipsAtHorizonStuff();
				return;
			}
			break;
		case PS_PS2:
			{
				REVC::CParticle::HandleShipsAtHorizonStuff();
				return;
			}
			break;
		case PS_XBOX:
			{
				REVCXB::CParticle::HandleShipsAtHorizonStuff();
				return;
			}
			break;
			
		case PS_XBOX2:
			{
				REVCXB2::CParticle::HandleShipsAtHorizonStuff();
				return;
			}
			break;
	}
	
	FATAL("Unknown Particle Switch");
}

void CParticleEx::HandleShootableBirdsStuff(CEntity *entity, CVector const&camPos)
{
	switch ( m_eCurrentParticle )
	{
		case PS_ORIGINAL:
			{
				CParticle::HandleShootableBirdsStuff(entity, camPos);
				return;
			}
			break;
		case PS_PS2:
			{
				REVC::CParticle::HandleShootableBirdsStuff(entity, camPos);
				return;
			}
			break;
		case PS_XBOX:
			{
				REVCXB::CParticle::HandleShootableBirdsStuff(entity, camPos);
				return;
			}
			break;
			
		case PS_XBOX2:
			{
				REVCXB2::CParticle::HandleShootableBirdsStuff(entity, camPos);
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
		case PS_PS2:
			{
				for ( Int32 i = 0; i < REVC::MAX_PARTICLES; i++ )
					RemoveCustomPSystem(s, i);

				return;
			}
			break;
		case PS_XBOX:
			{
				for ( Int32 i = 0; i < REVCXB::MAX_PARTICLES; i++ )
					RemoveCustomPSystem(s, i);

				return;
			}
			break;
			
		case PS_XBOX2:
			{
				for ( Int32 i = 0; i < REVCXB2::MAX_PARTICLES; i++ )
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
	
	CVector &prevEntityPosition = *(CVector*)AddressByVersion(0x7829E0, 0x7829E0, 0x7819E0);
	prevEntityPosition = CVector(0.0f, 0.0f, 0.0f);
}

void CParticleEx::ClearAllParticles()
{
	for ( Int32 i = 0; i < PS_MAX; i++ )
		ClearPSystem((eParticleSwitch)i);
}


static RwRaster *&gpFlame5Raster = *(RwRaster **)AddressByVersion(0x77E6C8, 0x77E6C8, 0x77D6C8);
static RwTexture *&gpFlame5Tex = *(RwTexture **)AddressByVersion(0x77E6C4, 0x77E6C4, 0x77D6C4);
static RwTexture *&gpFlame1Tex = *(RwTexture **)AddressByVersion(0x77E6BC, 0x77E6BC, 0x77D6BC);

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
	REVC::CParticle::FixFlame5Bug(bEnabled);
	REVCXB::CParticle::FixFlame5Bug(bEnabled);
	REVCXB2::CParticle::FixFlame5Bug(bEnabled);
}

void CParticleEx::SetWaterDropsInInteriorsFix(Bool bEnabled)
{
	static int fakeCurrArea = 0;
	
	if ( bEnabled )
	{
		CPatch::SetPointer(AddressByVersion(0x562165, 0x562185, 0x562055) + 2, &fakeCurrArea);
		CPatch::SetPointer(AddressByVersion(0x5628E3, 0x562903, 0x5627D3) + 2, &fakeCurrArea);
	}
	else
	{
		void *realCurrArea = (void*)AddressByVersion(0x978810, 0x978818, 0x977818);
		
		CPatch::SetPointer(AddressByVersion(0x562165, 0x562185, 0x562055) + 2, realCurrArea);
		CPatch::SetPointer(AddressByVersion(0x5628E3, 0x562903, 0x5627D3) + 2, realCurrArea);
	}
}

void CParticleEx::SetPS2PObjects(Bool bEnabled)
{
	;
}

void CParticleEx::UpdatePObjects_PS2(Bool bReset)
{
	;
}

void CParticleEx::SetXboxPObjects(Bool bEnabled)
{
	if ( bEnabled )
	{
		// POBJECT_FIRE_HYDRANT
		CPatch::SetInt(AddressByVersion(0x4E86AB, 0x4E86CB, 0x4E856B) + 1, 15000); //m_nRemoveTimer
	}
	else
	{
		// POBJECT_FIRE_HYDRANT
		CPatch::SetInt(AddressByVersion(0x4E86AB, 0x4E86CB, 0x4E856B) + 1, 5000); //m_nRemoveTimer
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
			
		case PS_XBOX2:
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
				
				CPatch::SetChar(AddressByVersion(0x48E935, 0x48E945, 0x48E845) + 2, 80); // CFire time
		
				SetPS2PObjects(false);
				SetXboxPObjects(false);
			}
			break;
			
		case PS_PS2:
			{
				m_bUseOriginalSystem = false;
				
				CPatch::SetChar(AddressByVersion(0x48E935, 0x48E945, 0x48E845) + 2, 80); // CFire time
				
				SetXboxPObjects(false);
				SetPS2PObjects(true);
			}
			break;
			
		case PS_XBOX:
			{
				m_bUseOriginalSystem = false;
				
				CPatch::SetChar(AddressByVersion(0x48E935, 0x48E945, 0x48E845) + 2, 50); // CFire time
				
				SetPS2PObjects(false);
				SetXboxPObjects(true);
			}
			break;
			
		case PS_XBOX2:
			{
				m_bUseOriginalSystem = false;
				
				CPatch::SetChar(AddressByVersion(0x48E935, 0x48E945, 0x48E845) + 2, 50); // CFire time
				
				SetPS2PObjects(false);
				SetXboxPObjects(true);
			}
			break;
	}
	
	m_eCurrentParticle = s;
}
