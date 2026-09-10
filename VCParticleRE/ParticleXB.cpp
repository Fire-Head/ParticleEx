#include "ParticleXB.h"
#include "_config.h"
#include "Settings.h"


#define MAX_PARTICLES_ON_SCREEN   (1000)



//(5)
#define MAX_SMOKE_FILES           ARRAY_SIZE(SmokeFiles)

//(5) 
#define MAX_RUBBER_FILES          ARRAY_SIZE(RubberFiles)
//(5)
#define MAX_RAINSPLASH_FILES      ARRAY_SIZE(RainSplashFiles)
//(3)
#define MAX_WATERSPRAY_FILES      ARRAY_SIZE(WatersprayFiles)
//(6)
#define MAX_EXPLOSIONMEDIUM_FILES ARRAY_SIZE(ExplosionMediumFiles)
//(4)
#define MAX_GUNFLASH_FILES        ARRAY_SIZE(GunFlashFiles)
//(2)
#define MAX_RAINSPLASHUP_FILES    ARRAY_SIZE(RainSplashupFiles)
//(4)
#define MAX_BIRDFRONT_FILES       ARRAY_SIZE(BirdfrontFiles)
//(8)
#define MAX_BOAT_FILES            ARRAY_SIZE(BoatFiles)
//(4)
#define MAX_CARDEBRIS_FILES       ARRAY_SIZE(CardebrisFiles)
//(4)
#define MAX_CARSPLASH_FILES       ARRAY_SIZE(CarsplashFiles)

#define MAX_RAINDRIP_FILES       (2)

//46
#define MAX_FLAME_FILES           ARRAY_SIZE(FlameFiles)


#define Kprintf(...) 


namespace REVCXB
{
	
const Char SmokeFiles[][6+1] =
{
	"smoke1",
	"smoke2",
	"smoke3",
	"smoke4",
	"smoke5"
};


const Char RubberFiles[][7+1] =
{
	"rubber1",
	"rubber2",
	"rubber3",
	"rubber4",
	"rubber5"
};

const Char RainSplashFiles[][7+1] =
{
	"splash1",
	"splash2",
	"splash3",
	"splash4",
	"splash5"
};

const Char WatersprayFiles[][11+1] =
{
	"waterspray1",
	"waterspray2",
	"waterspray3"
};

const Char ExplosionMediumFiles[][7+1] =
{
	"explo01",
	"explo02",
	"explo03",
	"explo04",
	"explo05",
	"explo06"
};

const Char GunFlashFiles[][9+1] =
{
	"gunflash1",
	"gunflash2",
	"gunflash3",
	"gunflash4"
};

const Char RainSplashupFiles[][10+1] =
{
	"splash_up1",
	"splash_up2"
};

const Char BirdfrontFiles[][8+1] =
{
	"birdf_01",
	"birdf_02",
	"birdf_03",
	"birdf_04"
};

const Char BoatFiles[][8+1] =
{
	"boats_01",
	"boats_02",
	"boats_03",
	"boats_04",
	"boats_05",
	"boats_06",
	"boats_07",
	"boats_08"
};

const Char CardebrisFiles[][12+1] =
{
	"cardebris_01",
	"cardebris_02",
	"cardebris_03",
	"cardebris_04"
};
				
const Char CarsplashFiles[][12+1] =
{
	"carsplash_01",
	"carsplash_02",
	"carsplash_03",
	"carsplash_04"
};


const Char FlameFiles[][8+1] =
{
	"flame01",
	"flame02",
	"flame03",
	"flame04",
	"flame05",
	"flame06",
	"flame07",
	"flame08",
	"flame09",
	"flame10",
	"flame11",
	"flame12",
	"flame13",
	"flame14",
	"flame15",
	"flame16",
	"flame17",
	"flame18",
	"flame19",
	"flame20",
	"flame21",
	"flame22",
	"flame23",
	"flame24",
	"flame25",
	"flame26",
	"flame27",
	"flame28",
	"flame29",
	"flame30",
	"flame31",
	"flame32",
	"flame33",
	"flame34",
	"flame35",
	"flame36",
	"flame37",
	"flame38",
	"flame39",
	"flame40",
	"flame41",
	"flame42",
	"flame43",
	"flame44",
	"flame45"
};

CParticle gParticleArray[MAX_PARTICLES_ON_SCREEN];

RwTexture *gpSmokeTex[MAX_SMOKE_FILES];
RwTexture *gpSmoke2Tex;
RwTexture *gpRubberTex[MAX_RUBBER_FILES];
RwTexture *gpRainSplashTex[MAX_RAINSPLASH_FILES];
RwTexture *gpWatersprayTex[MAX_WATERSPRAY_FILES];
RwTexture *gpExplosionMediumTex[MAX_EXPLOSIONMEDIUM_FILES];
RwTexture *gpGunFlashTex[MAX_GUNFLASH_FILES];
RwTexture *gpRainSplashupTex[MAX_RAINSPLASHUP_FILES];
RwTexture *gpBirdfrontTex[MAX_BIRDFRONT_FILES];
RwTexture *gpBoatTex[MAX_BOAT_FILES];
RwTexture *gpCarDebrisTex[MAX_CARDEBRIS_FILES];
RwTexture *gpCarSplashTex[MAX_CARSPLASH_FILES];

RwTexture *gpBoatWakeTex;
RwTexture *gpFlame1Tex;
RwTexture *gpFlame5Tex;
RwTexture *gpRainDropSmallTex;
RwTexture *gpBloodTex;
RwTexture *gpLeafTex;
RwTexture *gpCloudTex1;
RwTexture *gpCloudTex4;
RwTexture *gpBloodSmallTex;
RwTexture *gpGungeTex;
RwTexture *gpCollisionSmokeTex;
RwTexture *gpBulletHitTex;
RwTexture *gpGunShellTex;
RwTexture *gpPointlightTex;

RwRaster  *gpSmokeRaster[MAX_SMOKE_FILES];
RwRaster  *gpSmoke2Raster;
RwRaster  *gpRubberRaster[MAX_RUBBER_FILES];
RwRaster  *gpRainSplashRaster[MAX_RAINSPLASH_FILES];
RwRaster  *gpWatersprayRaster[MAX_WATERSPRAY_FILES];
RwRaster  *gpExplosionMediumRaster[MAX_EXPLOSIONMEDIUM_FILES];
RwRaster  *gpGunFlashRaster[MAX_GUNFLASH_FILES];
RwRaster  *gpRainSplashupRaster[MAX_RAINSPLASHUP_FILES];
RwRaster  *gpBirdfrontRaster[MAX_BIRDFRONT_FILES];
RwRaster  *gpBoatRaster[MAX_BOAT_FILES];
RwRaster  *gpCarDebrisRaster[MAX_CARDEBRIS_FILES];
RwRaster  *gpCarSplashRaster[MAX_CARSPLASH_FILES];

RwRaster  *gpBoatWakeRaster;
RwRaster  *gpFlame1Raster;
RwRaster  *gpFlame5Raster;
RwRaster  *gpRainDropSmallRaster;
RwRaster  *gpBloodRaster;
RwRaster  *gpLeafRaster;
RwRaster  *gpCloudRaster1;
RwRaster  *gpCloudRaster4;
RwRaster  *gpBloodSmallRaster;
RwRaster  *gpGungeRaster;
RwRaster  *gpCollisionSmokeRaster;
RwRaster  *gpBulletHitRaster;
RwRaster  *gpGunShellRaster;
RwRaster  *gpPointlightRaster;

RwTexture *gpRainDropTex;
RwRaster  *gpRainDropRaster;

RwTexture *gpLetterTex;
RwRaster *gpLetterRaster;

RwTexture *gpSparkTex;
RwTexture *gpNewspaperTex;
RwTexture *gpGunSmokeTex;
RwTexture *gpDotTex;
RwTexture *gpHeathazeTex;
RwTexture *gpBeastieTex;
RwTexture *gpRaindripTex1[MAX_RAINDRIP_FILES];
RwTexture *gpRaindripTex2[MAX_RAINDRIP_FILES];

RwRaster *gpSparkRaster;
RwRaster *gpNewspaperRaster;
RwRaster *gpGunSmokeRaster;
RwRaster *gpDotRaster;
RwRaster *gpHeathazeRaster;
RwRaster *gpBeastieRaster;
RwRaster *gpRaindripRaster1[MAX_RAINDRIP_FILES];
RwRaster *gpRaindripRaster2[MAX_RAINDRIP_FILES];

Float      CParticle::ms_afRandTable[CParticle::RAND_TABLE_SIZE];
CParticle *CParticle::m_pUnusedListHead;
Float      CParticle::m_SinTable[CParticle::SIN_COS_TABLE_SIZE];
Float      CParticle::m_CosTable[CParticle::SIN_COS_TABLE_SIZE];

RwTexture *gpFlameTex[MAX_FLAME_FILES];
RwRaster *gpFlameRaster[MAX_FLAME_FILES];

Int32 Randomizer;
Int32 nParticleCreationInterval = 1;
Float PARTICLE_WIND_TEST_SCALE  = 0.002f;
Float fParticleScaleLimit       = 0.5f;

Bool clearWaterDrop;
Int32 numWaterDropOnScreen;

void CParticle::FixFlame5Bug(Bool enable)
{
	if ( gpFlame5Tex == NULL || gpFlame1Tex == NULL )
		return;

	if ( enable )
		gpFlame5Raster = RwTextureGetRaster(gpFlame5Tex);
	else
		gpFlame5Raster = RwTextureGetRaster(gpFlame1Tex);
}

void CParticle::ReloadConfig()
{
	Kprintf("Initialising CParticleMgr...");
	
	mod_ParticleSystemManager.Initialise();
	
	Kprintf("Initialising CParticle...");
	
	m_pUnusedListHead = gParticleArray;
	
	for ( Int32 i = 0; i < MAX_PARTICLES_ON_SCREEN; i++ )
	{
		if ( i == MAX_PARTICLES_ON_SCREEN - 1 )
			gParticleArray[i].m_pNext = NULL;
		else
			gParticleArray[i].m_pNext = &gParticleArray[i + 1];
		
		gParticleArray[i].m_vecPosition = CVector(0.0f, 0.0f, 0.0f);

		gParticleArray[i].m_vecVelocity = CVector(0.0f, 0.0f, 0.0f);

		gParticleArray[i].m_nTimeWhenWillBeDestroyed = 0;

		gParticleArray[i].m_nTimeWhenColorWillBeChanged = 0;

		gParticleArray[i].m_fSize = 0.2f;

		gParticleArray[i].m_fExpansionRate = 0.0f;

		gParticleArray[i].m_nColorIntensity = 255;

		gParticleArray[i].m_nFadeToBlackTimer = 0;

		gParticleArray[i].m_nAlpha = 255;

		gParticleArray[i].m_nFadeAlphaTimer = 0;

		gParticleArray[i].m_nCurrentZRotation = 0;

		gParticleArray[i].m_nZRotationTimer = 0;

		gParticleArray[i].m_fCurrentZRadius = 0.0f;

		gParticleArray[i].m_nZRadiusTimer = 0;

		gParticleArray[i].m_nCurrentFrame = 0;

		gParticleArray[i].m_nAnimationSpeedTimer = 0;

		gParticleArray[i].m_nRotation = 0;

		gParticleArray[i].m_nRotationStep = 0;
	}
}

void CParticle::Initialise()
{
	ReloadConfig();

#if INJECT_PARTICLE == FALSE
	CParticleObject::Initialise();
#endif

	Float randVal = -1.0f;
	for ( Int32 i = 0; i < RAND_TABLE_SIZE; i++ )
	{
		ms_afRandTable[i] = randVal;
		randVal += 0.1f;
	}
	
	for ( Int32 i = 0; i < SIN_COS_TABLE_SIZE; i++ )
	{
		Float angle = DEG2RAD(Float(i) * Float(360.0f / SIN_COS_TABLE_SIZE));

		m_SinTable[i] = sin(angle);
		m_CosTable[i] = cos(angle);
	}
	
#if USE_CUSTOM_DIR == FALSE
	Int32 slot = CTxdStore::FindTxdSlot("particle");
#else
	Int32 slot = CTxdStore::AddTxdSlot("particleVCXB");
	
	Char Path[MAX_PATH];
	sprintf(Path,"%s\\ParticleEx\\XBOX\\PARTICLE.TXD", GetAsiPath().c_str());
	
	if ( !file_exists(Path) )
		FATAL("Can't Open: %s", Path);

	CTxdStore::LoadTxd(slot, Path);
	
	CTxdStore::AddRef(slot);
#endif

	CTxdStore::PushCurrentTxd();
	CTxdStore::SetCurrentTxd(slot);
	
	for ( Int32 i = 0; i < MAX_SMOKE_FILES; i++ )
	{
		gpSmokeTex[i] = RwTextureRead(SmokeFiles[i], NULL);
		gpSmokeRaster[i] = RwTextureGetRaster(gpSmokeTex[i]);
	}
	
	gpSmoke2Tex = RwTextureRead("smokeII_3", NULL);
	gpSmoke2Raster = RwTextureGetRaster(gpSmoke2Tex);
	
	for ( Int32 i = 0; i < MAX_RUBBER_FILES; i++ )
	{
		gpRubberTex[i] = RwTextureRead(RubberFiles[i], NULL);
		gpRubberRaster[i] = RwTextureGetRaster(gpRubberTex[i]);
	}
	
	for ( Int32 i = 0; i < MAX_RAINSPLASH_FILES; i++ )
	{
		gpRainSplashTex[i] = RwTextureRead(RainSplashFiles[i], NULL);
		gpRainSplashRaster[i] = RwTextureGetRaster(gpRainSplashTex[i]);
	}
	
	for ( Int32 i = 0; i < MAX_WATERSPRAY_FILES; i++ )
	{
		gpWatersprayTex[i] = RwTextureRead(WatersprayFiles[i], NULL);
		gpWatersprayRaster[i] = RwTextureGetRaster(gpWatersprayTex[i]);
	}
	
	for ( Int32 i = 0; i < MAX_EXPLOSIONMEDIUM_FILES; i++ )
	{
		gpExplosionMediumTex[i] = RwTextureRead(ExplosionMediumFiles[i], NULL);
		gpExplosionMediumRaster[i] = RwTextureGetRaster(gpExplosionMediumTex[i]);
	}
	
	for ( Int32 i = 0; i < MAX_GUNFLASH_FILES; i++ )
	{
		gpGunFlashTex[i] = RwTextureRead(GunFlashFiles[i], NULL);
		gpGunFlashRaster[i] = RwTextureGetRaster(gpGunFlashTex[i]);
	}
	
	gpRainDropTex = RwTextureRead("raindrop4", NULL);
	gpRainDropRaster = RwTextureGetRaster(gpRainDropTex);

	
	for ( Int32 i = 0; i < MAX_RAINSPLASHUP_FILES; i++ )
	{
		gpRainSplashupTex[i] = RwTextureRead(RainSplashupFiles[i], NULL);
		gpRainSplashupRaster[i] = RwTextureGetRaster(gpRainSplashupTex[i]);
	}
	
	for ( Int32 i = 0; i < MAX_BIRDFRONT_FILES; i++ )
	{
		gpBirdfrontTex[i] = RwTextureRead(BirdfrontFiles[i], NULL);
		gpBirdfrontRaster[i] = RwTextureGetRaster(gpBirdfrontTex[i]);
	}
	
	for ( Int32 i = 0; i < MAX_BOAT_FILES; i++ )
	{
		gpBoatTex[i] = RwTextureRead(BoatFiles[i], NULL);
		gpBoatRaster[i] = RwTextureGetRaster(gpBoatTex[i]);
	}
	
	for ( Int32 i = 0; i < MAX_CARDEBRIS_FILES; i++ )
	{
		gpCarDebrisTex[i] = RwTextureRead(CardebrisFiles[i], NULL);
		gpCarDebrisRaster[i] = RwTextureGetRaster(gpCarDebrisTex[i]);
	}
	
	for ( Int32 i = 0; i < MAX_CARSPLASH_FILES; i++ )
	{
		gpCarSplashTex[i] = RwTextureRead(CarsplashFiles[i], NULL);
		gpCarSplashRaster[i] = RwTextureGetRaster(gpCarSplashTex[i]);
	}
	
	for ( Int32 i = 0; i < MAX_FLAME_FILES; i++ )
	{
		gpFlameTex[i] = RwTextureRead(FlameFiles[i], NULL);

		if ( gpFlameTex[i] != NULL )
			gpFlameRaster[i] = RwTextureGetRaster(gpFlameTex[i]);
	}
	
	gpBoatWakeTex = RwTextureRead("boatwake2", NULL);
	gpBoatWakeRaster = RwTextureGetRaster(gpBoatWakeTex);

	gpFlame1Tex = RwTextureRead("flame1", NULL);
	gpFlame1Raster = RwTextureGetRaster(gpFlame1Tex);

	gpFlame5Tex = RwTextureRead("flame5", NULL);
#if FIX_FLAME5_BUG == FALSE
	gpFlame5Raster = RwTextureGetRaster(gpFlame1Tex);	// copy-paste bug ?
#else
	gpFlame5Raster = RwTextureGetRaster(gpFlame5Tex);
#endif
	
	gpRainDropSmallTex = RwTextureRead("rainsmall", NULL);
	gpRainDropSmallRaster = RwTextureGetRaster(gpRainDropSmallTex);

	gpBloodTex = RwTextureRead("blood", NULL);
	gpBloodRaster = RwTextureGetRaster(gpBloodTex);

	gpLeafTex = RwTextureRead("gameleaf01_64", NULL);
	gpLeafRaster = RwTextureGetRaster(gpLeafTex);
	
	gpLetterTex = RwTextureRead("letter", NULL);
	gpLetterRaster = RwTextureGetRaster(gpLetterTex);

	gpCloudTex1 = RwTextureRead("cloud3", NULL);
	gpCloudRaster1 = RwTextureGetRaster(gpCloudTex1);

	gpCloudTex4 = RwTextureRead("cloudmasked", NULL);
	gpCloudRaster4 = RwTextureGetRaster(gpCloudTex4);

	gpBloodSmallTex = RwTextureRead("bloodsplat2", NULL);
	gpBloodSmallRaster = RwTextureGetRaster(gpBloodSmallTex);

	gpGungeTex = RwTextureRead("gunge", NULL);
	gpGungeRaster = RwTextureGetRaster(gpGungeTex);

	gpCollisionSmokeTex = RwTextureRead("collisionsmoke", NULL);
	gpCollisionSmokeRaster = RwTextureGetRaster(gpCollisionSmokeTex);

	gpBulletHitTex = RwTextureRead("bullethitsmoke", NULL);
	gpBulletHitRaster = RwTextureGetRaster(gpBulletHitTex);

	gpGunShellTex = RwTextureRead("gunshell", NULL);
	gpGunShellRaster = RwTextureGetRaster(gpGunShellTex);

	gpPointlightTex = RwTextureRead("pointlight", NULL);
	gpPointlightRaster = RwTextureGetRaster(gpPointlightTex);
	
	//
	gpSparkTex = RwTextureRead("spark", NULL);
	gpSparkRaster = RwTextureGetRaster(gpSparkTex);
	
	gpNewspaperTex = RwTextureRead("newspaper02_64", NULL);
	gpNewspaperRaster = RwTextureGetRaster(gpNewspaperTex);
	
	gpGunSmokeTex = RwTextureRead("gunsmoke3", NULL);
	gpGunSmokeRaster = RwTextureGetRaster(gpGunSmokeTex);
	
	gpDotTex = RwTextureRead("dot", NULL);
	gpDotRaster = RwTextureGetRaster(gpDotTex);
	
	gpHeathazeTex = RwTextureRead("heathaze", NULL);
	gpHeathazeRaster = RwTextureGetRaster(gpHeathazeTex);
	
	gpBeastieTex = RwTextureRead("beastie", NULL);
	gpBeastieRaster = RwTextureGetRaster(gpBeastieTex);
	
	gpRaindripTex1[0] = RwTextureRead("raindrip64", NULL);
	gpRaindripRaster1[0] = RwTextureGetRaster(gpRaindripTex1[0]);
	
	gpRaindripTex1[1] = RwTextureRead("raindripb64", NULL);
	gpRaindripRaster1[1] = RwTextureGetRaster(gpRaindripTex1[1]);
	
	gpRaindripTex2[0] = RwTextureRead("raindrip64_d", NULL);
	gpRaindripRaster2[0] = RwTextureGetRaster(gpRaindripTex2[0]);
	
	gpRaindripTex2[1] = RwTextureRead("raindripb64_d", NULL);
	gpRaindripRaster2[1] = RwTextureGetRaster(gpRaindripTex2[1]);
	//
	
	CTxdStore::PopCurrentTxd();
	
	for ( Int32 i = 0; i < MAX_PARTICLES; i++ )
	{
		tParticleSystemData *entry = &mod_ParticleSystemManager.m_aParticles[i];
		
		switch ( i )
		{
			case PARTICLE_SPARK:
			case PARTICLE_SPARK_SMALL:
			case PARTICLE_RAINDROP_SMALL:
			case PARTICLE_HELI_ATTACK:
				entry->m_ppRaster = &gpRainDropSmallRaster;
				break;
			
			case PARTICLE_WATER_SPARK:
				entry->m_ppRaster = &gpSparkRaster;
				break;
			
			case PARTICLE_WHEEL_DIRT:
			case PARTICLE_SAND:
			case PARTICLE_STEAM2:
			case PARTICLE_STEAM_NY:
			case PARTICLE_STEAM_NY_SLOWMOTION:
			case PARTICLE_GROUND_STEAM:
			case PARTICLE_ENGINE_STEAM:
			case PARTICLE_PEDFOOT_DUST:
			case PARTICLE_CAR_DUST:
			case PARTICLE_EXHAUST_FUMES:
				entry->m_ppRaster = &gpSmoke2Raster;
				break;
			
			case PARTICLE_WHEEL_WATER:
			case PARTICLE_WATER:
			case PARTICLE_SMOKE:
			case PARTICLE_SMOKE_SLOWMOTION:
			case PARTICLE_DRY_ICE:
			case PARTICLE_GARAGEPAINT_SPRAY:
			case PARTICLE_STEAM:
			case PARTICLE_WATER_CANNON:
			case PARTICLE_EXTINGUISH_STEAM:
			case PARTICLE_HELI_DUST:
			case PARTICLE_PAINT_SMOKE:
			case PARTICLE_BULLETHIT_SMOKE:
				entry->m_ppRaster = gpSmokeRaster;
				break;
			
			case PARTICLE_BLOOD:
				entry->m_ppRaster = &gpBloodRaster;
				break;
			
			case PARTICLE_BLOOD_SMALL:
			case PARTICLE_BLOOD_SPURT:
				entry->m_ppRaster = &gpBloodSmallRaster;
				break;
			
			case PARTICLE_DEBRIS:
			case PARTICLE_TREE_LEAVES:
				entry->m_ppRaster = &gpLeafRaster;
				break;
			
			case PARTICLE_DEBRIS2:
				entry->m_ppRaster = &gpGungeRaster;
				break;
			
			case PARTICLE_FLYERS:
				entry->m_ppRaster = &gpNewspaperRaster;
				break;
			
			case PARTICLE_FLAME:
			case PARTICLE_FIREBALL:
			case PARTICLE_CARFLAME:
			case PARTICLE_CARFLAME_MOVING:
				if ( gpFlameRaster )
					entry->m_ppRaster = gpFlameRaster;
				else
					entry->m_ppRaster = &gpFlame1Raster;
				break;
			
			//case PARTICLE_FIREBALL:
			//	entry->m_ppRaster = &gpFlame5Raster;
			//	break;
			
			case PARTICLE_GUNFLASH:
			case PARTICLE_GUNFLASH_NOANIM:
				entry->m_ppRaster = gpGunFlashRaster;
				break;
			
			
			case PARTICLE_GUNSMOKE:
			case PARTICLE_WATERDROP:
			case PARTICLE_BLOODDROP:
			case PARTICLE_HEATHAZE:
			case PARTICLE_HEATHAZE_IN_DIST:
				entry->m_ppRaster = NULL;
				break;
			
			case PARTICLE_GUNSMOKE2:
			case PARTICLE_BOAT_THRUSTJET:
			case PARTICLE_RUBBER_SMOKE:
				entry->m_ppRaster = gpRubberRaster;
				break;
			
			case PARTICLE_CIGARETTE_SMOKE:
				entry->m_ppRaster = &gpGunSmokeRaster;
				break;
			
			case PARTICLE_TEARGAS:
				entry->m_ppRaster = &gpHeathazeRaster;
				break;
			
			case PARTICLE_SHARD:
			case PARTICLE_RAINDROP:
			case PARTICLE_RAINDROP_2D:
				entry->m_ppRaster = &gpRainDropRaster;
				break;
			
			case PARTICLE_SPLASH:
			case PARTICLE_PED_SPLASH:
			case PARTICLE_CAR_SPLASH:
			case PARTICLE_WATER_HYDRANT:
				entry->m_ppRaster = gpCarSplashRaster;
				break;
			
			case PARTICLE_RAIN_SPLASH:
			case PARTICLE_RAIN_SPLASH_BIGGROW:
				entry->m_ppRaster = gpRainSplashRaster;
				break;
			
			case PARTICLE_RAIN_SPLASHUP:
				entry->m_ppRaster = gpRainSplashupRaster;
				break;
			
			case PARTICLE_WATERSPRAY:
				entry->m_ppRaster = gpWatersprayRaster;
				break;
			
			case PARTICLE_EXPLOSION_MEDIUM:
			case PARTICLE_EXPLOSION_LARGE:
			case PARTICLE_EXPLOSION_MFAST:
			case PARTICLE_EXPLOSION_LFAST:
				entry->m_ppRaster = gpExplosionMediumRaster;
				break;
			
			case PARTICLE_BOAT_SPLASH:
				entry->m_ppRaster = &gpBoatWakeRaster;
				break;
			
			case PARTICLE_ENGINE_SMOKE:
			case PARTICLE_ENGINE_SMOKE2:
			case PARTICLE_CARFLAME_SMOKE:
			case PARTICLE_FIREBALL_SMOKE:
			case PARTICLE_ROCKET_SMOKE:
			case PARTICLE_TEST:
				entry->m_ppRaster = &gpCloudRaster4;
				break;
			
			case PARTICLE_CARCOLLISION_DUST:
			case PARTICLE_BURNINGRUBBER_SMOKE:
				entry->m_ppRaster = &gpCollisionSmokeRaster;
				break;
			
			case PARTICLE_CAR_DEBRIS:
			case PARTICLE_HELI_DEBRIS:
			case PARTICLE_BIRD_DEBRIS:
				entry->m_ppRaster = gpCarDebrisRaster;
				break;
			
			case PARTICLE_GUNSHELL_FIRST:
			case PARTICLE_GUNSHELL:
			case PARTICLE_GUNSHELL_BUMP1:
			case PARTICLE_GUNSHELL_BUMP2:
				entry->m_ppRaster = &gpGunShellRaster;
				break;
			
			
			case PARTICLE_BIRD_FRONT:
				entry->m_ppRaster = gpBirdfrontRaster;
				break;
			
			case PARTICLE_SHIP_SIDE:
				entry->m_ppRaster = gpBoatRaster;
				break;
			
			case PARTICLE_BEASTIE:
				entry->m_ppRaster = &gpBeastieRaster;
				break;
		}
	}

	Kprintf("CParticle ready");
}

void CParticle::Shutdown()
{
	Kprintf("Shutting down CParticle...");

	for ( Int32 i = 0; i < MAX_SMOKE_FILES; i++ )
	{
		RwTextureDestroy(gpSmokeTex[i]);
		gpSmokeTex[i] = NULL;
	}

	RwTextureDestroy(gpSmoke2Tex);
	gpSmoke2Tex = NULL;
	 
	for ( Int32 i = 0; i < MAX_RUBBER_FILES; i++ )
	{
		RwTextureDestroy(gpRubberTex[i]);
		gpRubberTex[i] = NULL;
	}
	
	for ( Int32 i = 0; i < MAX_RAINSPLASH_FILES; i++ )
	{
		RwTextureDestroy(gpRainSplashTex[i]);
		gpRainSplashTex[i] = NULL;
	}
	
	for ( Int32 i = 0; i < MAX_WATERSPRAY_FILES; i++ )
	{
		RwTextureDestroy(gpWatersprayTex[i]);
		gpWatersprayTex[i] = NULL;
	}
	
	for ( Int32 i = 0; i < MAX_EXPLOSIONMEDIUM_FILES; i++ )
	{
		RwTextureDestroy(gpExplosionMediumTex[i]);
		gpExplosionMediumTex[i] = NULL;
	}
	
	for ( Int32 i = 0; i < MAX_GUNFLASH_FILES; i++ )
	{
		RwTextureDestroy(gpGunFlashTex[i]);
		gpGunFlashTex[i] = NULL;
	}
	
	RwTextureDestroy(gpRainDropTex);
	gpRainDropTex = NULL;
	
	for ( Int32 i = 0; i < MAX_RAINSPLASHUP_FILES; i++ )
	{
		RwTextureDestroy(gpRainSplashupTex[i]);
		gpRainSplashupTex[i] = NULL;
	}
	
	for ( Int32 i = 0; i < MAX_BIRDFRONT_FILES; i++ )
	{
		RwTextureDestroy(gpBirdfrontTex[i]);
		gpBirdfrontTex[i] = NULL;
	}
	
	for ( Int32 i = 0; i < MAX_BOAT_FILES; i++ )
	{
		RwTextureDestroy(gpBoatTex[i]);
		gpBoatTex[i] = NULL;
	}
	
	for ( Int32 i = 0; i < MAX_CARDEBRIS_FILES; i++ )
	{
		RwTextureDestroy(gpCarDebrisTex[i]);
		gpCarDebrisTex[i] = NULL;
	}
	
	for ( Int32 i = 0; i < MAX_CARSPLASH_FILES; i++ )
	{
		RwTextureDestroy(gpCarSplashTex[i]);
		gpCarSplashTex[i] = NULL;
	}
	
	for ( Int32 i = 0; i < MAX_FLAME_FILES; i++ )
	{	
		RwTextureDestroy(gpFlameTex[i]);
		gpFlameTex[i] = NULL;
	}
	
	for ( Int32 i = 0; i < MAX_RAINDRIP_FILES; i++ )
	{
		RwTextureDestroy(gpRaindripTex1[i]);
		gpRaindripTex1[i] = NULL;

		RwTextureDestroy(gpRaindripTex2[i]);
		gpRaindripTex2[i] = NULL;
	}
	
	//
	
	RwTextureDestroy(gpBoatWakeTex);
	gpBoatWakeTex = NULL;

	RwTextureDestroy(gpFlame1Tex);
	gpFlame1Tex = NULL;

	RwTextureDestroy(gpFlame5Tex);
	gpFlame5Tex = NULL;
	
	RwTextureDestroy(gpRainDropSmallTex);
	gpRainDropSmallTex = NULL;
	
	RwTextureDestroy(gpBloodTex);
	gpBloodTex = NULL;
	
	RwTextureDestroy(gpLeafTex);
	gpLeafTex = NULL;

	RwTextureDestroy(gpLetterTex);
	gpLetterTex = NULL;
	
	RwTextureDestroy(gpCloudTex1);
	gpCloudTex1 = NULL;
	
	RwTextureDestroy(gpCloudTex4);
	gpCloudTex4 = NULL;
	
	RwTextureDestroy(gpBloodSmallTex);
	gpBloodSmallTex = NULL;
	
	RwTextureDestroy(gpGungeTex);
	gpGungeTex = NULL;
	
	RwTextureDestroy(gpCollisionSmokeTex);
	gpCollisionSmokeTex = NULL;
	
	RwTextureDestroy(gpBulletHitTex);
	gpBulletHitTex = NULL;
	
	RwTextureDestroy(gpGunShellTex);
	gpGunShellTex = NULL;
	
	RwTextureDestroy(gpPointlightTex);
	gpPointlightTex = NULL;

	RwTextureDestroy(gpSparkTex);
	gpSparkTex = NULL;
	
	RwTextureDestroy(gpNewspaperTex);
	gpNewspaperTex = NULL;

	RwTextureDestroy(gpGunSmokeTex);
	gpGunSmokeTex = NULL;
	
	RwTextureDestroy(gpDotTex);
	gpDotTex = NULL;
	
	RwTextureDestroy(gpHeathazeTex);
	gpHeathazeTex = NULL;
	
	RwTextureDestroy(gpBeastieTex);
	gpBeastieTex = NULL;

	Int32 slot;

#if USE_CUSTOM_DIR == FALSE
	slot = CTxdStore::FindTxdSlot("particle");
#else
	slot = CTxdStore::FindTxdSlot("particleVCXB");
#endif
	CTxdStore::RemoveTxdSlot(slot);

	Kprintf("CParticle shut down");
}

void CParticle::AddParticlesAlongLine(tParticleType type, CVector const &vecStart, CVector const &vecEnd, CVector const &vecDir, Float fPower, CEntity *pEntity, Float fSize, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	CVector vecDist = vecEnd - vecStart;
	
	Float fDist = vecDist.Magnitude();
	
	Float fSteps = fDist / fPower;
	
	if ( fSteps < 1.0f )
		fSteps = 1.0f;
	
	Int32 nSteps = (Int32)fSteps;
	
	CVector vecStep = vecDist * (1.0f / (Float)nSteps); 

	for ( Int32 i = 0; i < nSteps; i++ )
	{		
		CVector vecPos = Float(i) * vecStep + vecStart;
		
		AddParticle(type, vecPos, vecDir, pEntity, fSize, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	}
}

void CParticle::AddParticlesAlongLine(tParticleType type, CVector const &vecStart, CVector const &vecEnd, CVector const &vecDir, Float fPower, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	CVector vecDist = vecEnd - vecStart;
	
	Float fDist = vecDist.Magnitude();
	
	Float fSteps = fDist / fPower;
	
	if ( fSteps < 1.0f )
		fSteps = 1.0f;
	
	Int32 nSteps = (Int32)fSteps;
	
	CVector vecStep = vecDist * (1.0f / (Float)nSteps); 

	for ( Int32 i = 0; i < nSteps; i++ )
	{		
		CVector vecPos = Float(i) * vecStep + vecStart;
		
		AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	}
}
	
CParticle *CParticle::AddParticle(tParticleType type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	CRGBA color(0, 0, 0, 0);
	return AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

CParticle *CParticle::AddParticle(tParticleType type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CTimer::m_UserPause || CTimer::m_CodePause )
		return NULL;

	if ( ( type == PARTICLE_ENGINE_SMOKE
		|| type == PARTICLE_ENGINE_SMOKE2
		|| type == PARTICLE_ENGINE_STEAM
		|| type == PARTICLE_CARFLAME_SMOKE
		|| type == PARTICLE_RUBBER_SMOKE
		|| type == PARTICLE_BURNINGRUBBER_SMOKE
		|| type == PARTICLE_EXHAUST_FUMES
		|| type == PARTICLE_CARCOLLISION_DUST )
		&& nParticleCreationInterval & CTimer::m_FrameCounter )
	{
		return NULL;
	}
	
	if ( CReplay::Mode != 1 )
		CReplay::RecordParticle((::tParticleType)type, vecPos, vecDir, fSize, color);
	
	CParticle *pParticle = m_pUnusedListHead;
	
	if ( pParticle == NULL )
		return NULL;
	
	tParticleSystemData *psystem = &mod_ParticleSystemManager.m_aParticles[type];
	
	if ( psystem->m_fCreateRange != 0.0f && psystem->m_fCreateRange < ( TheCamera.m_sCoords.pos - vecPos ).MagnitudeSqr() )
		return NULL;
	
	
	pParticle->m_fSize = psystem->m_fDefaultInitialRadius;
	pParticle->m_fExpansionRate = psystem->m_fExpansionRate;
	
	if ( nLifeSpan != 0 )
		pParticle->m_nTimeWhenWillBeDestroyed = CTimer::m_snTimeInMilliseconds + nLifeSpan;
	else
		pParticle->m_nTimeWhenWillBeDestroyed = CTimer::m_snTimeInMilliseconds + psystem->m_nLifeSpan;

	pParticle->m_nColorIntensity = psystem->m_nFadeToBlackInitialIntensity;
	
	pParticle->m_nFadeToBlackTimer = psystem->m_nFadeToBlackAmount;
	
	if ( psystem->m_nFadeToBlackTime )
		pParticle->m_nFadeToBlackTimer /= psystem->m_nFadeToBlackTime;
	
	pParticle->m_nAlpha = psystem->m_nFadeAlphaInitialIntensity;
	
	pParticle->m_nFadeAlphaTimer = psystem->m_nFadeAlphaAmount;
	
	if ( psystem->m_nFadeAlphaTime )
		pParticle->m_nFadeAlphaTimer /= psystem->m_nFadeAlphaTime;

	pParticle->m_nCurrentZRotation = psystem->m_nZRotationInitialAngle;
	pParticle->m_fCurrentZRadius = psystem->m_fInitialZRadius;
	
	if ( nCurFrame != 0 )
		pParticle->m_nCurrentFrame = nCurFrame;
	else
		pParticle->m_nCurrentFrame = psystem->m_nStartAnimationFrame;
	
	
	pParticle->m_nZRotationTimer = 0;
	pParticle->m_nZRadiusTimer = 0;
	pParticle->m_nAnimationSpeedTimer = 0;
	pParticle->m_fZGround = 0.0f;
	
	if ( type != PARTICLE_HEATHAZE )
		pParticle->m_vecPosition = vecPos;
	else
	{
		CVector screen;
		Float w;
		Float h;

		if ( !CSprite::CalcScreenCoors(vecPos, (RwV3d *)&screen, &w, &h, true) )
			return NULL;
		
		pParticle->m_vecPosition = screen;
		psystem->m_vecTextureStretch.x = w;
		psystem->m_vecTextureStretch.y = h;
	}
	
	pParticle->m_vecVelocity = vecDir;
	
	pParticle->m_nTimeWhenColorWillBeChanged = 0;
	
	pParticle->m_vecParticleMovementOffset = CVector(0.0f, 0.0f, 0.0f);
	
	
	if ( color.alpha != 0 )
		RwRGBAAssign(&pParticle->m_Color, &color);
	else
	{
		RwRGBAAssign(&pParticle->m_Color, &psystem->m_RenderColouring);

		if ( psystem->m_ColorFadeTime != 0 )
			pParticle->m_nTimeWhenColorWillBeChanged = CTimer::m_snTimeInMilliseconds + psystem->m_ColorFadeTime;

		if ( psystem->m_InitialColorVariation != 0 )
		{
			Int32 ColorVariation = CGeneral::GetRandomNumberInRange(-psystem->m_InitialColorVariation, psystem->m_InitialColorVariation);
			//Float ColorVariation = CGeneral::GetRandomNumberInRange((Float)-psystem->m_InitialColorVariation, (Float)psystem->m_InitialColorVariation);
  
			pParticle->m_Color.red   = clamp(pParticle->m_Color.red +
				PERCENT(pParticle->m_Color.red, ColorVariation),
				0, 255);
			
			pParticle->m_Color.green = clamp(pParticle->m_Color.green +
				PERCENT(pParticle->m_Color.green, ColorVariation),
				0, 255);
			
			pParticle->m_Color.blue  = clamp(pParticle->m_Color.blue +
				PERCENT(pParticle->m_Color.blue, ColorVariation),
				0, 255);
		}
	}

	pParticle->m_nRotation = nRotation;
	
	if ( nRotationSpeed != 0 )
		pParticle->m_nRotationStep = nRotationSpeed;
	else
		pParticle->m_nRotationStep = psystem->m_nRotationSpeed;
	
	if ( CGeneral::GetRandomNumber() & 1 )
		pParticle->m_nRotationStep = -pParticle->m_nRotationStep;
	
	if ( psystem->m_fPositionRandomError != 0.0f )
	{
		pParticle->m_vecPosition.x += psystem->m_fPositionRandomError * ms_afRandTable[(UInt16)CGeneral::GetRandomNumber() % RAND_TABLE_SIZE];
		pParticle->m_vecPosition.y += psystem->m_fPositionRandomError * ms_afRandTable[(UInt16)CGeneral::GetRandomNumber() % RAND_TABLE_SIZE];
		
		if ( psystem->Flags & RAND_VERT_V )
			pParticle->m_vecPosition.z += psystem->m_fPositionRandomError * ms_afRandTable[(UInt16)CGeneral::GetRandomNumber() % RAND_TABLE_SIZE];
	}
	
	if ( psystem->m_fVelocityRandomError != 0.0f )
	{
		pParticle->m_vecVelocity.x += psystem->m_fVelocityRandomError * ms_afRandTable[(UInt16)CGeneral::GetRandomNumber() % RAND_TABLE_SIZE];
		pParticle->m_vecVelocity.y += psystem->m_fVelocityRandomError * ms_afRandTable[(UInt16)CGeneral::GetRandomNumber() % RAND_TABLE_SIZE];
    
		if ( psystem->Flags & RAND_VERT_V )
			pParticle->m_vecVelocity.z += psystem->m_fVelocityRandomError * ms_afRandTable[(UInt16)CGeneral::GetRandomNumber() % RAND_TABLE_SIZE];
	}
	
	if ( psystem->m_fExpansionRateError != 0.0f && !(psystem->Flags & SCREEN_TRAIL) ) // WTF vienna ?
		pParticle->m_fExpansionRate += psystem->m_fExpansionRateError * (ms_afRandTable[(UInt16)CGeneral::GetRandomNumber() % RAND_TABLE_SIZE] + 1.0f);
	
	if ( psystem->m_nRotationRateError != 0 )
		pParticle->m_nRotationStep += CGeneral::GetRandomNumberInRange(-psystem->m_nRotationRateError, psystem->m_nRotationRateError);

	if ( psystem->m_nLifeSpanErrorShape > 0 )
	{
		Float randVal = ms_afRandTable[(UInt16)CGeneral::GetRandomNumber() % RAND_TABLE_SIZE];
		if ( randVal > 0.0f )
			pParticle->m_nTimeWhenWillBeDestroyed += Int32(Float(psystem->m_nLifeSpan) * randVal * Float(psystem->m_nLifeSpanErrorShape));
		else
			pParticle->m_nTimeWhenWillBeDestroyed += Int32(Float(psystem->m_nLifeSpan) * randVal / Float(psystem->m_nLifeSpanErrorShape));
	}
	
	if ( psystem->Flags & ZCHECK_FIRST )
	{
		static Bool bValidGroundFound = false;
		static CVector LastTestCoors;
		static Float LastTestGroundZ;
		
		if ( bValidGroundFound 
			&& vecPos.x == LastTestCoors.x 
			&& vecPos.y == LastTestCoors.y 
			&& vecPos.z == LastTestCoors.z )
		{
			pParticle->m_fZGround = LastTestGroundZ;
		}
		else
		{
			bValidGroundFound = false;
			
			CColPoint point;
			CEntity *entity;
			
			if ( !CWorld::ProcessVerticalLine(
						pParticle->m_vecPosition + CVector(0.0f, 0.0f, 0.5f),
						-100.0f, point, entity, true, true, false, false, true, false, NULL) )
			{
				return NULL;
			}
			
			if ( point.m_vecPosition.z >= pParticle->m_vecPosition.z )
				return NULL;
			
			pParticle->m_fZGround = point.m_vecPosition.z;
			bValidGroundFound = true;
			LastTestCoors = vecPos;
			LastTestGroundZ = point.m_vecPosition.z;
		}
	}
	
	if ( psystem->Flags & ZCHECK_BUMP )
	{
		static Float Z_Ground = 0.0f;
		
		if ( psystem->Flags & ZCHECK_BUMP_FIRST )
		{
			Bool bZFound = false;

			Z_Ground = CWorld::FindGroundZFor3DCoord(vecPos.x, vecPos.y, vecPos.z, (bool *)&bZFound);

			if ( bZFound == false )
				return NULL;

			pParticle->m_fZGround = Z_Ground;
		}
		
		pParticle->m_fZGround = Z_Ground;
	}
	
	switch ( type )
	{
		case PARTICLE_DEBRIS:
			pParticle->m_vecVelocity.z *= CGeneral::GetRandomNumberInRange(0.5f, 3.0f);
			break;
		
		case PARTICLE_EXPLOSION_MEDIUM:
			pParticle->m_nColorIntensity -= 30 * (CGeneral::GetRandomNumber() & 1); // mb "+= -30 * rand" here ?
			pParticle->m_nAnimationSpeedTimer = CGeneral::GetRandomNumber() & 7;
			pParticle->m_fSize = CGeneral::GetRandomNumberInRange(0.3f, 0.8f);
			pParticle->m_vecPosition.z -= CGeneral::GetRandomNumberInRange(-0.1f, 0.1f);
			break;
		
		case PARTICLE_EXPLOSION_LARGE:
			pParticle->m_nColorIntensity -= 30 * (CGeneral::GetRandomNumber() & 1); // mb "+= -30 * rand" here ?
			pParticle->m_nAnimationSpeedTimer = CGeneral::GetRandomNumber() & 7;
			pParticle->m_fSize = CGeneral::GetRandomNumberInRange(0.8f, 1.4f);
			pParticle->m_vecPosition.z -= CGeneral::GetRandomNumberInRange(-0.3f, 0.3f);
			break;
		
		case PARTICLE_WATER_HYDRANT:
			pParticle->m_vecPosition.z += 20.0f * psystem->m_fPositionRandomError * ms_afRandTable[(UInt16)CGeneral::GetRandomNumber() % RAND_TABLE_SIZE];
			break;
	}
	
	if ( fSize != 0.0f )
		pParticle->m_fSize = fSize;
	
	m_pUnusedListHead = pParticle->m_pNext;

	pParticle->m_pNext = psystem->m_pParticles;

	psystem->m_pParticles = pParticle;
	
	return pParticle;
}

void CParticle::Update()
{
	if ( CTimer::m_UserPause || CTimer::m_CodePause )
		return;

	CRGBA color(0, 0, 0, 0);
	
	Float fFricDeccel50 = pow(0.50f, CTimer::ms_fTimeStep);
	Float fFricDeccel80 = pow(0.80f, CTimer::ms_fTimeStep);
	Float fFricDeccel90 = pow(0.90f, CTimer::ms_fTimeStep);
	Float fFricDeccel95 = pow(0.95f, CTimer::ms_fTimeStep);
	Float fFricDeccel96 = pow(0.96f, CTimer::ms_fTimeStep);
	Float fFricDeccel99 = pow(0.99f, CTimer::ms_fTimeStep);
	
	CParticleObject::UpdateAll();
	
	
	// ejaculation at 23:00, 23:15, 23:30, 23:45 
	if ( CClock::ms_nGameClockHours == 23 &&
			(	   CClock::ms_nGameClockMinutes == 0 
				|| CClock::ms_nGameClockMinutes == 15 
				|| CClock::ms_nGameClockMinutes == 30
				|| CClock::ms_nGameClockMinutes == 45 )
		)
    {
		AddParticle(PARTICLE_CAR_SPLASH,
					CVector(557.03f, -4.0f, 151.46f),
					CVector(0.0f, 0.0f, 2.5f),
					NULL,
					2.0f,
					CRGBA(255, 255, 255, 255),
					0,
					0,
					1,
					1000);
    }

	for ( Int32 i = 0; i < MAX_PARTICLES; i++ )
	{
		tParticleSystemData *psystem = &mod_ParticleSystemManager.m_aParticles[i];
		CParticle *particle = psystem->m_pParticles;
		CParticle *prevParticle = NULL;
		Bool bRemoveParticle;
		
		if ( particle == NULL )
			continue;
				
		for ( ; particle != NULL; _Next(particle, prevParticle, psystem, bRemoveParticle) )
		{
			CVector vecWind(0.0f, 0.0f, 0.0f);
			
			bRemoveParticle = false;

			//CVector vecPos = particle->m_vecPosition + ( particle->m_vecVelocity * CTimer::ms_fTimeStep );
			
			CVector vecMoveStep = particle->m_vecVelocity * CTimer::ms_fTimeStep;
			CVector vecPos = particle->m_vecPosition;
			
			if ( numWaterDropOnScreen == 0 )
				clearWaterDrop = false;
			
			if ( psystem->m_Type == PARTICLE_WATERDROP )
			{
				extern int GetFixedArea();
#ifdef FIX_BUGS
				if ( GetFixedArea() != 0 || clearWaterDrop == true )
#else
				if ( CGame::currArea != 0 || clearWaterDrop == true )
#endif
				{
					bRemoveParticle = true;
					continue;
				}
				
				static UInt8 nWaterDropCount;

				if ( nWaterDropCount == 5 )
				{
					vecMoveStep = CVector(0.0f, 0.0f, 0.0f);
					particle->m_nTimeWhenWillBeDestroyed += 1250;
					nWaterDropCount = 0;
				}
				else
				{
					if ( TheCamera.m_CameraAverageSpeed > 0.35f )
					{
						if ( vecMoveStep.Magnitude() > 0.5f )
						{
							if ( vecMoveStep.Magnitude() > 0.4f && vecMoveStep.Magnitude() < 0.8f )
							{
								vecMoveStep.x += TheCamera.m_CameraAverageSpeed * 1.5f;
								vecMoveStep.y += TheCamera.m_CameraAverageSpeed * 1.5f;
							}
							else if ( vecMoveStep.Magnitude() != 0.0f )
							{
								vecMoveStep.x += CGeneral::GetRandomNumberInRange(0.01f, 0.05f);
								vecMoveStep.y += CGeneral::GetRandomNumberInRange(0.01f, 0.05f);
							}
						}
					}
					
					nWaterDropCount++;
				}
				
				if ( vecPos.z <= 1.5f )
					vecMoveStep.z = 0.0f;
			}
			
			if ( psystem->m_Type == PARTICLE_HEATHAZE || psystem->m_Type == PARTICLE_HEATHAZE_IN_DIST )
			{
#ifdef FIX_BUGS
				Int32 nSinCosIndex = (Int32(DEG2RAD((Float)particle->m_nRotation) * Float(SIN_COS_TABLE_SIZE) / _2PI) + SIN_COS_TABLE_SIZE) % SIN_COS_TABLE_SIZE;
#else
				Int32 nSinCosIndex = Int32(DEG2RAD((Float)particle->m_nRotation) * Float(SIN_COS_TABLE_SIZE) / _2PI) % SIN_COS_TABLE_SIZE;
#endif

				vecMoveStep.x = CParticle::m_SinTable[nSinCosIndex];
				vecMoveStep.y = CParticle::m_SinTable[nSinCosIndex];
				
				if ( psystem->m_Type == PARTICLE_HEATHAZE_IN_DIST )
					particle->m_nRotation = Int16((Float)particle->m_nRotation + 0.75f);
				else
					particle->m_nRotation = Int16((Float)particle->m_nRotation + 1.0f);
			}
			
			if ( psystem->m_Type == PARTICLE_BEASTIE )
			{
#ifdef FIX_BUGS
				Int32 nSinCosIndex = (Int32(DEG2RAD((Float)particle->m_nRotation) * Float(SIN_COS_TABLE_SIZE) / _2PI) + SIN_COS_TABLE_SIZE) % SIN_COS_TABLE_SIZE;
#else
				Int32 nSinCosIndex = Int32(DEG2RAD((Float)particle->m_nRotation) * Float(SIN_COS_TABLE_SIZE) / _2PI) % SIN_COS_TABLE_SIZE;
#endif

				particle->m_vecVelocity.x = 0.5f * CParticle::m_CosTable[nSinCosIndex];
				particle->m_vecVelocity.y = CParticle::m_CosTable[nSinCosIndex];
				particle->m_vecVelocity.z = 0.25f * CParticle::m_SinTable[nSinCosIndex];
				
				if ( particle->m_vecVelocity.Magnitude() > 2.0f
						|| vecPos.z > 40.0f
						|| (TheCamera.m_sCoords.pos - vecPos).Magnitude() < 60.0f
					)
				{
					bRemoveParticle = true;
					continue;
				}
			}
			
			vecPos += vecMoveStep;
			
			if ( psystem->m_Type == PARTICLE_FIREBALL )
			{
				  AddParticle(PARTICLE_HEATHAZE,
								particle->m_vecPosition,
								CVector(0.0f, 0.0f, 0.0f),
								NULL,
								particle->m_fSize * 5.0f,
								0,
								0,
								0,
								0);
			}
			
			if ( psystem->m_Type == PARTICLE_GUNSMOKE2 )
			{
				if ( CTimer::m_FrameCounter & 10 )
				{
#ifdef FIX_BUGS
					if ( FindPlayerPed() && FindPlayerPed()->m_aWeapons[FindPlayerPed()->m_nActiveWeapon].m_Type == WEAPONTYPE_MINIGUN )
#else
					if ( FindPlayerPed()->m_aWeapons[FindPlayerPed()->m_nActiveWeapon].m_Type == WEAPONTYPE_MINIGUN )
#endif
					{
						AddParticle(PARTICLE_HEATHAZE,
										particle->m_vecPosition,
										CVector(0.0f, 0.0f, 0.0f),
										NULL,
										0.0f,
										0,
										0,
										0,
										0);
					}
				}
			}
			
			if ( CWeather::Wind > 0.0f )
			{
				if ( vecMoveStep.Magnitude() != 0.0f )
				{
					vecWind.x = CGeneral::GetRandomNumberInRange(0.75f, 1.25f) * -CWeather::Wind;
					vecWind.y = CGeneral::GetRandomNumberInRange(0.75f, 1.25f) * -CWeather::Wind;
					vecWind *= PARTICLE_WIND_TEST_SCALE * psystem->m_fWindFactor * CTimer::ms_fTimeStep;
					particle->m_vecVelocity += vecWind;
				}
			}
			
			
			if ( psystem->m_Type == PARTICLE_RAINDROP
				|| psystem->m_Type == PARTICLE_RAINDROP_SMALL
				|| psystem->m_Type == PARTICLE_RAIN_SPLASH
				|| psystem->m_Type == PARTICLE_RAIN_SPLASH_BIGGROW
				|| psystem->m_Type == PARTICLE_CAR_SPLASH
				|| psystem->m_Type == PARTICLE_BOAT_SPLASH
				|| psystem->m_Type == PARTICLE_RAINDROP_2D )
			{
				Int32 nMaxDrops = Int32(6.0f * TheCamera.m_CameraAverageSpeed + 1.0f);
				Float fDistToCam = 0.0f;
				
				if ( psystem->m_Type == PARTICLE_BOAT_SPLASH || psystem->m_Type == PARTICLE_CAR_SPLASH )
				{
					if ( vecPos.z + particle->m_fSize < 5.0f )
					{
						bRemoveParticle = true;
						continue;
					}
					
					switch ( TheCamera.GetLookDirection() )
					{
						case 1:
						case 2:
						case 3:
							nMaxDrops /= 2;
							break;
						
						default:
							nMaxDrops = 0;
							break;
					}
					
					fDistToCam = (TheCamera.m_sCoords.pos - vecPos).Magnitude();
				}

				extern int GetFixedArea();
				if ( numWaterDropOnScreen < nMaxDrops && numWaterDropOnScreen < 63
					&& fDistToCam < 10.0f
					&& clearWaterDrop == false
#ifdef FIX_BUGS
					&& GetFixedArea() == 0 )
#else
					&& CGame::currArea == 0 )
#endif
				{
					CVector vecWaterdropTarget
					(
						CGeneral::GetRandomNumberInRange(-0.25f, 0.25f),
						CGeneral::GetRandomNumberInRange(0.1f, 0.75f),
						-0.01f
					);
					
					CVector vecWaterdropPos;
					
					if ( TheCamera.m_CameraAverageSpeed < 0.35f )
						vecWaterdropPos.x = (Float)CGeneral::GetRandomNumberInRange(50, RsGlobal.w - 50);
					else
						vecWaterdropPos.x = (Float)CGeneral::GetRandomNumberInRange(200, RsGlobal.w - 200);
					
					if ( psystem->m_Type == PARTICLE_BOAT_SPLASH || psystem->m_Type == PARTICLE_CAR_SPLASH )
						vecWaterdropPos.y = (Float)CGeneral::GetRandomNumberInRange(RsGlobal.h / 2, RsGlobal.h);
					else
					{
						if ( TheCamera.m_CameraAverageSpeed < 0.35f )
							vecWaterdropPos.y  = (Float)CGeneral::GetRandomNumberInRange(0, RsGlobal.h);
						else
							vecWaterdropPos.y  = (Float)CGeneral::GetRandomNumberInRange(150, RsGlobal.h - 200);
					}
					
					vecWaterdropPos.z = 2.0f;

					if ( AddParticle(PARTICLE_WATERDROP,
										vecWaterdropPos,
										vecWaterdropTarget,
										NULL,
										CGeneral::GetRandomNumberInRange(0.1f, 0.15f),
										0,
										0,
										CGeneral::GetRandomNumber() & 1,
										0) != NULL )
					{
						numWaterDropOnScreen++;
					}
				}
			}
			
			
			if (  CTimer::m_snTimeInMilliseconds > particle->m_nTimeWhenWillBeDestroyed || particle->m_nAlpha == 0 )
			{
				bRemoveParticle = true;
				continue;
			}

			if ( particle->m_nTimeWhenColorWillBeChanged != 0 )
			{
				if ( particle->m_nTimeWhenColorWillBeChanged > CTimer::m_snTimeInMilliseconds )
				{
					Float colorMul = 1.0f - Float(particle->m_nTimeWhenColorWillBeChanged - CTimer::m_snTimeInMilliseconds) / Float(psystem->m_ColorFadeTime);
				
					particle->m_Color.red = clamp(
						psystem->m_RenderColouring.red + Int32(Float(psystem->m_FadeDestinationColor.red - psystem->m_RenderColouring.red) * colorMul),
						0, 255);
					
					particle->m_Color.green = clamp(
						psystem->m_RenderColouring.green + Int32(Float(psystem->m_FadeDestinationColor.green - psystem->m_RenderColouring.green) * colorMul),
						0, 255);
						
					particle->m_Color.blue = clamp(
						psystem->m_RenderColouring.blue + Int32(Float(psystem->m_FadeDestinationColor.blue - psystem->m_RenderColouring.blue) * colorMul),
						0, 255);
				}
				else
					RwRGBAAssign(&particle->m_Color, &psystem->m_FadeDestinationColor);
			}
			
			if ( psystem->Flags & CLIPOUT2D )
			{
				if ( particle->m_vecPosition.x < -10.0f || particle->m_vecPosition.x > Float(RsGlobal.w) + 10.0f
					|| particle->m_vecPosition.y < -10.0f || particle->m_vecPosition.y > Float(RsGlobal.h) + 10.0f )
				{
					bRemoveParticle = true;
					continue;
				}
			}
			
			if ( !(psystem->Flags & SCREEN_TRAIL) )
			{
				Float size;

				if ( particle->m_fExpansionRate > 0.0f )
				{
					Float speed = max(vecWind.Magnitude(), vecMoveStep.Magnitude());
					
					if ( psystem->m_Type == PARTICLE_EXHAUST_FUMES || psystem->m_Type == PARTICLE_ENGINE_STEAM )
						speed *= 2.0f;
					
					if ( ( psystem->m_Type == PARTICLE_BOAT_SPLASH || psystem->m_Type == PARTICLE_CAR_SPLASH )
							&& particle->m_fSize > 1.2f )
					{
						size = particle->m_fSize - (1.0f + speed) * particle->m_fExpansionRate;
						particle->m_vecVelocity.z -= 0.15f;
					}
					else
						size = particle->m_fSize + (1.0f + speed) * particle->m_fExpansionRate;
				}
				else
					size = particle->m_fSize + particle->m_fExpansionRate;
				
				if ( psystem->m_Type == PARTICLE_WATERDROP )
					size = (size - fabs(vecMoveStep.x) * 0.000150000007f) + (fabs(vecMoveStep.z) * 0.0500000007f);
				
				if ( size < 0.0f )
				{
					bRemoveParticle = true;
					continue;
				}
				
				particle->m_fSize = size;
			}

			switch ( psystem->m_nFrictionDecceleration )
			{
				case 50:
					particle->m_vecVelocity *= fFricDeccel50;
					break;
		
				case 80:
					particle->m_vecVelocity *= fFricDeccel80;
					break;
		
				case 90:
					particle->m_vecVelocity *= fFricDeccel90;
					break;
		
				case 95:
					particle->m_vecVelocity *= fFricDeccel95;
					break;
		
				case 96:
					particle->m_vecVelocity *= fFricDeccel96;
					break;
		
				case 99:
					particle->m_vecVelocity *= fFricDeccel99;
					break;				
			}
			
			if ( psystem->m_fGravitationalAcceleration > 0.0f )
			{
				if ( -50.0f * psystem->m_fGravitationalAcceleration < particle->m_vecVelocity.z )
					particle->m_vecVelocity.z -= psystem->m_fGravitationalAcceleration * CTimer::ms_fTimeStep;

				if ( psystem->Flags & ZCHECK_FIRST )
				{
					if ( particle->m_vecPosition.z < particle->m_fZGround )
					{
						switch ( psystem->m_Type )
						{
							case PARTICLE_RAINDROP:
							case PARTICLE_RAINDROP_SMALL:
								{
									bRemoveParticle = true;
									
									if ( (UInt16)CGeneral::GetRandomNumber() & 1 )
									{
										AddParticle(PARTICLE_RAIN_SPLASH,
													CVector
													(
														particle->m_vecPosition.x,
														particle->m_vecPosition.y,
														0.05f + particle->m_fZGround
													),
													CVector(0.0f, 0.0f, 0.0f), NULL, 0.0f, 0, 0, 0, 0);
									}
									else
									{
										AddParticle(PARTICLE_RAIN_SPLASHUP,
													CVector
													(
														particle->m_vecPosition.x,
														particle->m_vecPosition.y,
														0.05f + particle->m_fZGround
													),
													CVector(0.0f, 0.0f, 0.0f), NULL, 0.0f, 0, 0, 0, 0);
									}
									
									continue;
								}
								break;

							case PARTICLE_WHEEL_WATER:
								{
									bRemoveParticle = true;
									
									Int32 randVal = Int32((UInt16)CGeneral::GetRandomNumber());
									
									if ( randVal & 1 )
									{
										if ( (randVal % 5) == 0 )
										{
											AddParticle(PARTICLE_RAIN_SPLASH,
														CVector
														(
															particle->m_vecPosition.x,
															particle->m_vecPosition.y,
															0.05f + particle->m_fZGround
														),
														CVector(0.0f, 0.0f, 0.0f), NULL, 0.0f, 0, 0, 0, 0);
										}
										else
										{
											AddParticle(PARTICLE_RAIN_SPLASHUP,
														CVector
														(
															particle->m_vecPosition.x,
															particle->m_vecPosition.y,
															0.05f + particle->m_fZGround
														),
														CVector(0.0f, 0.0f, 0.0f), NULL, 0.0f, 0, 0, 0, 0);
										}
										
									}
									continue;
								}
								break;

							case PARTICLE_BLOOD:
							case PARTICLE_BLOOD_SMALL:
								{
									bRemoveParticle = true;
									
									CVector vecPosn = particle->m_vecPosition;
									vecPosn.z += 1.0f;
									
									Randomizer++;
									Int32 randVal = Int32(Randomizer & 7);
									
									if ( randVal == 5 )
									{
										Int32 randTime = Int32((UInt16)CGeneral::GetRandomNumber());
										
										CShadows::AddPermanentShadow(1, gpBloodPoolTex, &vecPosn,
												0.1f, 0.0f, 0.0f, -0.1f,
												255,
												255, 0, 0,
												4.0f, (randTime & 0xFFF) + 2000, 1.0f);
									}
									else if ( randVal == 2 )
									{
										Int32 randTime = Int32((UInt16)CGeneral::GetRandomNumber());

										CShadows::AddPermanentShadow(1, gpBloodPoolTex, &vecPosn,
												0.2f, 0.0f, 0.0f, -0.2f,
												255,
												255, 0, 0,
												4.0f, (randTime & 0xFFF) + 8000, 1.0f);
									}
									continue;
								}
								break;
						}
					}
				}
				else if ( psystem->Flags & ZCHECK_STEP )
				{
					CColPoint point;
					CEntity *entity;

					if ( CWorld::ProcessVerticalLine(particle->m_vecPosition, vecPos.z, point, entity, 
														true, true, false, false, true, false, NULL) )
					{
						if ( vecPos.z <= point.m_vecPosition.z )
						{
							vecPos.z = point.m_vecPosition.z;
							if ( psystem->m_Type == PARTICLE_DEBRIS2 )
							{
								particle->m_vecVelocity *= CVector(0.8f, 0.8f, -0.4f);
								if ( particle->m_vecVelocity.z < 0.005f )
									particle->m_vecVelocity.z = 0.0f;
							}
						}
					}
				}
				else if ( psystem->Flags & ZCHECK_BUMP )
				{
					if ( particle->m_vecPosition.z < particle->m_fZGround )
					{
						switch ( psystem->m_Type )
						{
							case PARTICLE_GUNSHELL_FIRST:
							case PARTICLE_GUNSHELL:
								{
									bRemoveParticle = true;

									AddParticle(PARTICLE_GUNSHELL_BUMP1,
												CVector
												(
													particle->m_vecPosition.x,
													particle->m_vecPosition.y,
													0.05f + particle->m_fZGround
												),
												CVector
												(
													CGeneral::GetRandomNumberInRange(-0.02f, 0.02f),
													CGeneral::GetRandomNumberInRange(-0.02f, 0.02f),
													CGeneral::GetRandomNumberInRange(0.05f, 0.1f)
												),
												NULL,
												particle->m_fSize, color, particle->m_nRotationStep, 0, 0, 0);
									
									PlayOneShotScriptObject(66, particle->m_vecPosition); // 66 VC, 122 III
								}
								break;
							
							case PARTICLE_GUNSHELL_BUMP1:
								{
									bRemoveParticle = true;
									
									AddParticle(PARTICLE_GUNSHELL_BUMP2,
												CVector
												(
													particle->m_vecPosition.x,
													particle->m_vecPosition.y,
													0.05f + particle->m_fZGround
												),
												CVector(0.0f, 0.0f, CGeneral::GetRandomNumberInRange(0.03f, 0.06f)),
												NULL,
												particle->m_fSize, color, 0, 0, 0, 0);
									
									PlayOneShotScriptObject(67, particle->m_vecPosition); // 67 VC, 123 III
								}
								break;
								
							case PARTICLE_GUNSHELL_BUMP2:
								{
									bRemoveParticle = true;
									continue;
								}
								break;
						}
					}
				}
			}
			else
			{
				if ( psystem->m_fGravitationalAcceleration < 0.0f )
				{
					if ( -5.0f * psystem->m_fGravitationalAcceleration > particle->m_vecVelocity.z )
						particle->m_vecVelocity.z -= psystem->m_fGravitationalAcceleration * CTimer::ms_fTimeStep;
				}
				else
				{
					if ( psystem->Flags & ZCHECK_STEP )
					{
						CColPoint point;
						CEntity *entity;
			
						if ( CWorld::ProcessVerticalLine(particle->m_vecPosition, vecPos.z, point, entity,
														true, false, false, false, true, false, NULL) )
						{
							if ( vecPos.z <= point.m_vecPosition.z )
							{
								vecPos.z = point.m_vecPosition.z;
								if ( psystem->m_Type == PARTICLE_HELI_ATTACK )
								{
									bRemoveParticle = true;
									AddParticle(PARTICLE_STEAM, vecPos, CVector(0.0f, 0.0f, 0.05f), NULL, 0.2f, 0, 0, 0, 0);
									continue;
								}
							}
						}
					}
				}
			}
			
			if ( particle->m_nFadeToBlackTimer != 0 )
			{
				particle->m_nColorIntensity = clamp(particle->m_nColorIntensity - particle->m_nFadeToBlackTimer,
														0, 255);
			}
			
			if ( particle->m_nFadeAlphaTimer != 0 )
			{
				particle->m_nAlpha = clamp(particle->m_nAlpha - particle->m_nFadeAlphaTimer,
														0, 255);
				if ( particle->m_nAlpha == 0 )
				{
					bRemoveParticle = true;
					continue;
				}
			}
			
			if ( psystem->m_nZRotationAngleChangeAmount != 0 )
			{
				if ( particle->m_nZRotationTimer >= psystem->m_nZRotationChangeTime )
				{
					particle->m_nZRotationTimer = 0;
					particle->m_nCurrentZRotation += psystem->m_nZRotationAngleChangeAmount;
				}
				else
					++particle->m_nZRotationTimer;
			}
			
			if ( psystem->m_fZRadiusChangeAmount != 0.0f )
			{
				if ( particle->m_nZRadiusTimer >= psystem->m_nZRadiusChangeTime )
				{
					particle->m_nZRadiusTimer = 0;
					particle->m_fCurrentZRadius += psystem->m_fZRadiusChangeAmount;
				}
				else
					++particle->m_nZRadiusTimer;
			}

			if ( psystem->m_fAnimationSpeed != 0.0 )
			{
				if ( (Float)particle->m_nAnimationSpeedTimer > psystem->m_fAnimationSpeed )
				{
					particle->m_nAnimationSpeedTimer = 0;
					
					if ( ++particle->m_nCurrentFrame > psystem->m_nFinalAnimationFrame )
					{
						if ( psystem->Flags & CYCLE_ANIM )
							particle->m_nCurrentFrame = psystem->m_nStartAnimationFrame;
						else
							--particle->m_nCurrentFrame;
					}	
				}
				else
					++particle->m_nAnimationSpeedTimer;
			}
			
			if ( particle->m_nRotationStep != 0 )
				particle->m_nRotation += particle->m_nRotationStep;
			
			if ( particle->m_fCurrentZRadius != 0.0f )
			{
				//Int32 nSinCosIndex = particle->m_nCurrentZRotation % (SIN_COS_TABLE_SIZE - 1);
				Int32 nSinCosIndex = particle->m_nCurrentZRotation % SIN_COS_TABLE_SIZE;
				
				Float fX = (m_CosTable[nSinCosIndex] - m_SinTable[nSinCosIndex])
							* particle->m_fCurrentZRadius;
				
				Float fY = (m_SinTable[nSinCosIndex] + m_CosTable[nSinCosIndex])
							* particle->m_fCurrentZRadius;

				vecPos -= particle->m_vecParticleMovementOffset;

				vecPos += CVector(fX, fY, 0.0f);
				
				particle->m_vecParticleMovementOffset = CVector(fX, fY, 0.0f);
			}
			
			particle->m_vecPosition = vecPos;
		}
	}
}

void CParticle::Render()
{
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void *)rwTEXTUREADDRESSWRAP);
	RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE, (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
	
	CSprite::InitSpriteBuffer2D();
	
	UInt32 flags = DRAW_OPAQUE;
	
	RwRaster *prevFrame = NULL;
	
	for ( Int32 i = 0; i < MAX_PARTICLES; i++ )
	{
		tParticleSystemData *psystem = &mod_ParticleSystemManager.m_aParticles[i];
		
		Bool particleBanned = false;

		CParticle *particle = psystem->m_pParticles;
		
		RwRaster **frames = psystem->m_ppRaster;
		
		tParticleType type = psystem->m_Type;
	
		if ( type == PARTICLE_ENGINE_SMOKE
			|| type == PARTICLE_ENGINE_SMOKE2
			|| type == PARTICLE_ENGINE_STEAM
			|| type == PARTICLE_CARFLAME_SMOKE
			|| type == PARTICLE_RUBBER_SMOKE
			|| type == PARTICLE_BURNINGRUBBER_SMOKE
			|| type == PARTICLE_EXHAUST_FUMES
			|| type == PARTICLE_CARCOLLISION_DUST )
		{
			particleBanned = true;
		}
		
		if ( particle )
		{
			if ( (flags & DRAW_OPAQUE) != (psystem->Flags & DRAW_OPAQUE)
				|| (flags & DRAW_DARK) != (psystem->Flags & DRAW_DARK) )
			{
				CSprite::FlushSpriteBuffer();
				
				if ( psystem->Flags & DRAW_OPAQUE )
				{
					RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
					RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
				}
				else
				{
					if ( psystem->Flags & DRAW_DARK )
						RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
					else
						RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDONE);
	
					RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDONE);
				}

				flags = psystem->Flags;
			}
			
			if ( frames != NULL )
			{
				RwRaster *curFrame = *frames;
				if ( curFrame != prevFrame )
				{
					CSprite::FlushSpriteBuffer();
					RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)curFrame);
					prevFrame = curFrame;
				}
			}
		}
		
		while ( particle != NULL )
		{
			Bool canDraw = true;

			if ( particle->m_nAlpha == 0 )
				canDraw = false;
			
			if ( canDraw && psystem->m_nFinalAnimationFrame != 0 && frames != NULL )
			{
				RwRaster *curFrame = frames[particle->m_nCurrentFrame];
				if ( prevFrame != curFrame )
				{
					CSprite::FlushSpriteBuffer();
					RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)curFrame);
					prevFrame = curFrame;
				}
			}
			
			if ( canDraw && psystem->Flags & DRAWTOP2D )
			{
				Float screenZ = (particle->m_vecPosition.z - CDraw::ms_fNearClipZ)
					* (CSprite::m_f2DFarScreenZ - CSprite::m_f2DNearScreenZ)
					* CDraw::ms_fFarClipZ
					/ ( (CDraw::ms_fFarClipZ - CDraw::ms_fNearClipZ) * max(particle->m_vecPosition.z, 0.0001f) ) //VIENNA
					+ CSprite::m_f2DNearScreenZ;
				
				Float stretchTexW;
				Float stretchTexH;
					
				if ( i == PARTICLE_RAINDROP || i == PARTICLE_RAINDROP_SMALL || i == PARTICLE_RAINDROP_2D )
				{
					stretchTexW = CGeneral::GetRandomNumberInRange(0.1f, 1.0f) * psystem->m_vecTextureStretch.x * (Float)particle->m_nCurrentFrame + 63.0f;
					stretchTexH = CGeneral::GetRandomNumberInRange(0.1f, 1.0f) * psystem->m_vecTextureStretch.y * (Float)particle->m_nCurrentFrame + 63.0f;
				}
				else
				{
					stretchTexW = CGeneral::GetRandomNumberInRange(0.1f, 1.0f) * psystem->m_vecTextureStretch.x + 63.0f;
					stretchTexH = CGeneral::GetRandomNumberInRange(0.1f, 1.0f) * psystem->m_vecTextureStretch.y + 63.0f;
				}

				
				if ( i == PARTICLE_WATERDROP ) // disabled on XBOX
				{
					if ( !CSettings::Get().m_bDisableWaterDrop )
					{
						Int32 timeLeft = (particle->m_nTimeWhenWillBeDestroyed - CTimer::m_snTimeInMilliseconds) / particle->m_nTimeWhenWillBeDestroyed;
						
						stretchTexH += (1.0f - (Float)timeLeft ) * psystem->m_vecTextureStretch.y;
						
						RwRect rect;
						
						rect.x = Int32(particle->m_vecPosition.x - SCREEN_STRETCH_X(particle->m_fSize * stretchTexW));
						rect.y = Int32(particle->m_vecPosition.y - SCREEN_STRETCH_Y(particle->m_fSize * stretchTexH));
						rect.w = Int32(particle->m_vecPosition.x + SCREEN_STRETCH_X(particle->m_fSize * stretchTexW));
						rect.h = Int32(particle->m_vecPosition.y + SCREEN_STRETCH_Y(particle->m_fSize * stretchTexH));
						
						FxType fxtype;
	
						if ( particle->m_nCurrentFrame != 0 )
							fxtype = 1;
						else
							fxtype = 0;
			
						CMBlur::AddRenderFx(Scene.camera, &rect, screenZ, fxtype);
					}
					canDraw = false;
				}
				
				if ( i == PARTICLE_BLOODDROP )
				{
					if ( !CSettings::Get().m_bDisableBloodDrop ) // for extended neowaterdrops
					{
						Int32 timeLeft = (particle->m_nTimeWhenWillBeDestroyed - CTimer::m_snTimeInMilliseconds) / particle->m_nTimeWhenWillBeDestroyed;
						
						stretchTexH += (1.0f + (Float)timeLeft) * psystem->m_vecTextureStretch.y;
						stretchTexW += (1.0f - (Float)timeLeft) * psystem->m_vecTextureStretch.x;
	
						RwRect rect;
	
						rect.x = Int32(particle->m_vecPosition.x - SCREEN_STRETCH_X(particle->m_fSize * stretchTexW));
						rect.y = Int32(particle->m_vecPosition.y - SCREEN_STRETCH_Y(particle->m_fSize * stretchTexH));
						rect.w = Int32(particle->m_vecPosition.x + SCREEN_STRETCH_X(particle->m_fSize * stretchTexW));
						rect.h = Int32(particle->m_vecPosition.y + SCREEN_STRETCH_Y(particle->m_fSize * stretchTexH));
						
						FxType fxtype;
						
						if ( particle->m_nCurrentFrame )
							fxtype = 3;
						else
							fxtype = 2;
						
						CMBlur::AddRenderFx(Scene.camera, &rect, screenZ, fxtype);
					}
					
					canDraw = false;
				}
				
				if ( i == PARTICLE_HEATHAZE_IN_DIST )
				{
					RwRect rect;
					
					rect.x = Int32(particle->m_vecPosition.x - SCREEN_STRETCH_X(particle->m_fSize * stretchTexW));
					rect.y = Int32(particle->m_vecPosition.y - SCREEN_STRETCH_Y(particle->m_fSize * stretchTexH * 0.15f));
					rect.w = Int32(particle->m_vecPosition.x + SCREEN_STRETCH_X(particle->m_fSize * stretchTexW));
					rect.h = Int32(particle->m_vecPosition.y + SCREEN_STRETCH_Y(particle->m_fSize * stretchTexH * 0.15f));
					
					CMBlur::AddRenderFx(Scene.camera, &rect, screenZ, 4);
					
					canDraw = false;
				}
				
				if ( i == PARTICLE_HEATHAZE )
				{
					extern float HeatHazeSclX(float x);
					extern float HeatHazeSclY(float x);

					RwRect rect;
					
					switch ( TheCamera.GetLookDirection() )
					{
						case 1:
#ifdef FIX_BUGS
							rect.x = Int32(particle->m_vecPosition.x - HeatHazeSclX(particle->m_fSize * psystem->m_vecTextureStretch.x * 2.0f));
							rect.y = Int32(particle->m_vecPosition.y - HeatHazeSclY(particle->m_fSize * psystem->m_vecTextureStretch.y));
							rect.w = Int32(particle->m_vecPosition.x - HeatHazeSclX(particle->m_fSize * psystem->m_vecTextureStretch.x));
							rect.h = Int32(particle->m_vecPosition.y + HeatHazeSclY(particle->m_fSize * psystem->m_vecTextureStretch.y));
#else
							rect.x = Int32(particle->m_vecPosition.x - SCREEN_STRETCH_X(particle->m_fSize * psystem->m_vecTextureStretch.x * 2.0f));
							rect.y = Int32(particle->m_vecPosition.y - SCREEN_STRETCH_Y(particle->m_fSize * psystem->m_vecTextureStretch.y));
							rect.w = Int32(particle->m_vecPosition.x - SCREEN_STRETCH_X(particle->m_fSize * psystem->m_vecTextureStretch.x));
							rect.h = Int32(particle->m_vecPosition.y + SCREEN_STRETCH_Y(particle->m_fSize * psystem->m_vecTextureStretch.y));
#endif
				
							break;

						case 2:
#ifdef FIX_BUGS
							rect.x = Int32(particle->m_vecPosition.x + HeatHazeSclX(particle->m_fSize * psystem->m_vecTextureStretch.x));
							rect.y = Int32(particle->m_vecPosition.y - HeatHazeSclY(particle->m_fSize * psystem->m_vecTextureStretch.y));
							rect.w = Int32(particle->m_vecPosition.x + HeatHazeSclX(particle->m_fSize * psystem->m_vecTextureStretch.x * 4.0f));
							rect.h = Int32(particle->m_vecPosition.y + HeatHazeSclY(particle->m_fSize * psystem->m_vecTextureStretch.y));

#else
							rect.x = Int32(particle->m_vecPosition.x + SCREEN_STRETCH_X(particle->m_fSize * psystem->m_vecTextureStretch.x));
							rect.y = Int32(particle->m_vecPosition.y - SCREEN_STRETCH_Y(particle->m_fSize * psystem->m_vecTextureStretch.y));
							rect.w = Int32(particle->m_vecPosition.x + SCREEN_STRETCH_X(particle->m_fSize * psystem->m_vecTextureStretch.x * 4.0f));
							rect.h = Int32(particle->m_vecPosition.y + SCREEN_STRETCH_Y(particle->m_fSize * psystem->m_vecTextureStretch.y));
#endif
					
							break;

						default:
#ifdef FIX_BUGS
							rect.x = Int32(particle->m_vecPosition.x - HeatHazeSclX(particle->m_fSize * psystem->m_vecTextureStretch.x));
							rect.y = Int32(particle->m_vecPosition.y - HeatHazeSclY(particle->m_fSize * psystem->m_vecTextureStretch.y));
							rect.w = Int32(particle->m_vecPosition.x + HeatHazeSclX(particle->m_fSize * psystem->m_vecTextureStretch.x));
							rect.h = Int32(particle->m_vecPosition.y + HeatHazeSclY(particle->m_fSize * psystem->m_vecTextureStretch.y));
#else
							rect.x = Int32(particle->m_vecPosition.x - SCREEN_STRETCH_X(particle->m_fSize * psystem->m_vecTextureStretch.x));
							rect.y = Int32(particle->m_vecPosition.y - SCREEN_STRETCH_Y(particle->m_fSize * psystem->m_vecTextureStretch.y));
							rect.w = Int32(particle->m_vecPosition.x + SCREEN_STRETCH_X(particle->m_fSize * psystem->m_vecTextureStretch.x));
							rect.h = Int32(particle->m_vecPosition.y + SCREEN_STRETCH_Y(particle->m_fSize * psystem->m_vecTextureStretch.y));
#endif
					
							break;
					}
														 
					CMBlur::AddRenderFx(Scene.camera, &rect, screenZ, 4);
					
					canDraw = false;
				}

				if ( canDraw )
				{
					if ( particle->m_nRotation != 0 )
					{
						CSprite::RenderBufferedOneXLUSprite2D_Rotate_Dimension(
								particle->m_vecPosition.x,
								particle->m_vecPosition.y,
								particle->m_fSize * stretchTexW,
								particle->m_fSize * stretchTexH,
								particle->m_Color,
								particle->m_nColorIntensity,
								DEG2RAD((Float)particle->m_nRotation),
								particle->m_nAlpha);
					}
					else
					{
						CSprite::RenderBufferedOneXLUSprite2D(
								particle->m_vecPosition.x,
								particle->m_vecPosition.y,
								particle->m_fSize * stretchTexW,
								particle->m_fSize * stretchTexH,
								particle->m_Color,
								particle->m_nColorIntensity,
								particle->m_nAlpha);
					}
				}
				
				canDraw = false;
			}
			
			if ( canDraw )
			{
				CVector coors;
				Float w;
				Float h;

				if ( CSprite::CalcScreenCoors(particle->m_vecPosition, coors, &w, &h, true) )
				{

					if ( i == PARTICLE_ENGINE_STEAM
						|| i == PARTICLE_ENGINE_SMOKE
						|| i == PARTICLE_ENGINE_SMOKE2
						|| i == PARTICLE_CARFLAME_SMOKE
						|| i == PARTICLE_CARCOLLISION_DUST
						|| i == PARTICLE_EXHAUST_FUMES
						|| i == PARTICLE_RUBBER_SMOKE
						|| i == PARTICLE_BURNINGRUBBER_SMOKE )
					{
						switch ( TheCamera.GetLookDirection() )
						{
							case 1:
							case 2:
								w += CGeneral::GetRandomNumberInRange(1.0f, 7.5f) * psystem->m_vecTextureStretch.x;
								h += CGeneral::GetRandomNumberInRange(0.1f, 1.0f) * psystem->m_vecTextureStretch.y;
								break;

							default:
								w += CGeneral::GetRandomNumberInRange(0.1f, 1.0f) * psystem->m_vecTextureStretch.x;
								h += CGeneral::GetRandomNumberInRange(0.1f, 1.0f) * psystem->m_vecTextureStretch.y;
								break;
						}
					}
					else if ( i == PARTICLE_WATER_HYDRANT )
					{
						Int32 timeLeft = (particle->m_nTimeWhenWillBeDestroyed - CTimer::m_snTimeInMilliseconds) / particle->m_nTimeWhenWillBeDestroyed;
					
						w += (1.0f - (Float)timeLeft) * psystem->m_vecTextureStretch.x;
						h += (1.0f - (Float)timeLeft) * psystem->m_vecTextureStretch.y;
					}
					else if ( i == PARTICLE_FLYERS )
					{
						w += psystem->m_vecTextureStretch.x;
						h += psystem->m_vecTextureStretch.y;
						
						w = max(w, 12.0f);
						h = max(h, 12.0f);
					}
					else
					{
						w += CGeneral::GetRandomNumberInRange(0.1f, 1.0f) * psystem->m_vecTextureStretch.x;
						h += CGeneral::GetRandomNumberInRange(0.1f, 1.0f) * psystem->m_vecTextureStretch.y;
					}
	  
	  
					if ( /*i == PARTICLE_WATER_HYDRANT
							||*/ // vienna
							
							(CSettings::Get().m_bRestoreXboxHydrantWaterSpray && i == PARTICLE_WATER_HYDRANT) ||
							(!particleBanned || Float(RsGlobal.w) * fParticleScaleLimit >= w)
							&& Float(RsGlobal.h) * fParticleScaleLimit >= h )
					{
						
						if ( i == PARTICLE_WATER_HYDRANT ) // disabled on XBOX
						{
							if ( CSettings::Get().m_bRestoreXboxHydrantWaterSpray )
							{
								RwRect rect;
								
								if ( w > 0.0f )
								{
									rect.x = Int32(coors.x - SCREEN_STRETCH_X(particle->m_fSize * w));
									rect.w = Int32(coors.x + SCREEN_STRETCH_X(particle->m_fSize * w));
								}
								else
								{
									rect.w = Int32(coors.x - SCREEN_STRETCH_X(particle->m_fSize * w));
									rect.x = Int32(coors.x + SCREEN_STRETCH_X(particle->m_fSize * w));
								}
								
								if ( h > 0.0f )
								{
									rect.y = Int32(coors.y - SCREEN_STRETCH_Y(particle->m_fSize * h));
									rect.h = Int32(coors.y + SCREEN_STRETCH_Y(particle->m_fSize * h));
								}
								else
								{
									rect.h = Int32(coors.y - SCREEN_STRETCH_Y(particle->m_fSize * h));
									rect.y = Int32(coors.y + SCREEN_STRETCH_Y(particle->m_fSize * h));
								}
								
								Float screenZ = (coors.z - CDraw::ms_fNearClipZ) 
									* (CSprite::m_f2DFarScreenZ - CSprite::m_f2DNearScreenZ) * CDraw::ms_fFarClipZ
									/ ( (CDraw::ms_fFarClipZ - CDraw::ms_fNearClipZ) * coors.z ) + CSprite::m_f2DNearScreenZ;
	
								CMBlur::AddRenderFx(Scene.camera, &rect, screenZ, 5);
							}
						}
						else
						{
							if ( particle->m_nRotation != 0 && i != PARTICLE_BEASTIE )
							{
								CSprite::RenderBufferedOneXLUSprite_Rotate_Dimension(coors.x, coors.y, coors.z,
										particle->m_fSize * w, particle->m_fSize * h,
										particle->m_Color.red,
										particle->m_Color.green,
										particle->m_Color.blue,
										particle->m_nColorIntensity,
										1.0f / coors.z,
										DEG2RAD(Float(particle->m_nRotation)),
										particle->m_nAlpha);
							}
							else if ( psystem->Flags & SCREEN_TRAIL )
							{
								Float fRotation;
								Float fTrailLength;
								
								if ( particle->m_fZGround == 0.0f )
								{
									fTrailLength = 0.0f;
									fRotation = 0.0f;
								}
								else
								{
									CVector2D vecDist
									(
										coors.x - particle->m_fZGround,
										coors.y - particle->m_fExpansionRate
									);
	
									Float fDist = vecDist.Magnitude();
	
									fTrailLength = fDist;
									
									//Float fRot = atan2( vecDist.x / fDist, sqrtf(1.0f - vecDist.x / fDist * (vecDist.x / fDist)) );
									Float fRot = asinf(vecDist.x / fDist);
	
									fRotation = fRot;
	
									if ( vecDist.y < 0.0f )
										fRotation = -1.0f * fRot + DEG2RAD(180.0f);
									
									//fRotation = RAD2DEG(fRotation);
									//if ( fRotation < 0.0f )
									//	fRotation += 360.0f;
									
									Float fSpeed = particle->m_vecVelocity.Magnitude();
									
									Float fNewTrailLength = fSpeed * CTimer::ms_fTimeStep * w * 2.0f;
									
									if ( fDist > fNewTrailLength )
										fTrailLength = fNewTrailLength;
								}
								
								CSprite::RenderBufferedOneXLUSprite_Rotate_Dimension(coors.x, coors.y, coors.z,
										particle->m_fSize * w,
										particle->m_fSize * h + fTrailLength * psystem->m_fTrailLengthMultiplier,
										particle->m_Color.red,
										particle->m_Color.green,
										particle->m_Color.blue,
										particle->m_nColorIntensity,
										1.0f / coors.z,
										fRotation,
										particle->m_nAlpha);
				
								//particle->m_vecScreenPosition = coors;
							
								particle->m_fZGround = coors.x;				// WTF ?
								particle->m_fExpansionRate =  coors.y;		// WTF ?
							}
							else if ( psystem->Flags & SPEED_TRAIL )
							{
								CVector vecPrevPos = particle->m_vecPosition - particle->m_vecVelocity;
								Float fRotation;
								Float fTrailLength;
								CVector vecScreenPosition;
								
								if ( CSprite::CalcScreenCoors(vecPrevPos, vecScreenPosition, &fTrailLength, &fRotation, true) )
								{
									CVector2D vecDist
									(
										coors.x - vecScreenPosition.x,
										coors.y - vecScreenPosition.y
									);
									
									Float fDist = vecDist.Magnitude();
									
									fTrailLength = fDist;
									
									//Float fRot = atan2(vecDist.x / fDist, sqrt(1.0f - vecDist.x / fDist * (vecDist.x / fDist)));
									Float fRot = asinf(vecDist.x / fDist);
									
									fRotation = fRot;
									
									if ( vecDist.y < 0.0f )
										fRotation = -1.0f * fRot + DEG2RAD(180.0f);
									
									//fRotation = RAD2DEG(fRotation);
									
									//if ( fRotation < 0.0f )
									//	fRotation += 360.0f;
								}
								else
								{
									fRotation = 0.0f;
									fTrailLength = 0.0f;
								}
								
								CSprite::RenderBufferedOneXLUSprite_Rotate_Dimension(coors.x, coors.y, coors.z,
										particle->m_fSize * w,
										particle->m_fSize * h + fTrailLength * psystem->m_fTrailLengthMultiplier,
										particle->m_Color.red,
										particle->m_Color.green,
										particle->m_Color.blue,
										particle->m_nColorIntensity,
										1.0f / coors.z,
										fRotation,
										particle->m_nAlpha);
							}
							else if ( psystem->Flags & VERT_TRAIL )
							{
								Float fTrailLength = fabsf(particle->m_vecVelocity.z * 10.0f);
	
								CSprite::RenderBufferedOneXLUSprite(coors.x, coors.y, coors.z,
										particle->m_fSize * w,
										(particle->m_fSize + fTrailLength * psystem->m_fTrailLengthMultiplier) * h,
										particle->m_Color.red,
										particle->m_Color.green,
										particle->m_Color.blue,
										particle->m_nColorIntensity,
										1.0f / coors.z,
										particle->m_nAlpha);
							}
							else if ( i == PARTICLE_RAINDROP_SMALL )
							{
								CSprite::RenderBufferedOneXLUSprite(coors.x, coors.y, coors.z,
										particle->m_fSize * w * 0.05f,
										particle->m_fSize * h,
										particle->m_Color.red,
										particle->m_Color.green,
										particle->m_Color.blue,
										particle->m_nColorIntensity,
										1.0f / coors.z,
										particle->m_nAlpha);
							}
							/*else if ( i == PARTICLE_BOAT_WAKE )*/
							else
							{
								CSprite::RenderBufferedOneXLUSprite(coors.x, coors.y, coors.z,
										particle->m_fSize * w,
										particle->m_fSize * h,
										particle->m_Color.red,
										particle->m_Color.green,
										particle->m_Color.blue,
										particle->m_nColorIntensity,
										1.0f / coors.z,
										particle->m_nAlpha);
							}
						}
					}
				}
			}
			
			particle = particle->m_pNext;
		}

		CSprite::FlushSpriteBuffer();

	}
	
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
}

void CParticle::RemovePSystem(tParticleType type)
{
	tParticleSystemData *psystemdata = &mod_ParticleSystemManager.m_aParticles[type];
	
	for ( CParticle *particle = psystemdata->m_pParticles; particle; particle = psystemdata->m_pParticles )
		RemoveParticle(particle, NULL, psystemdata);
}

void CParticle::RemoveParticle(CParticle *pParticle, CParticle *pPrevParticle, tParticleSystemData *pPSystemData)
{
	if ( pPSystemData->m_Type == PARTICLE_WATERDROP )
		--numWaterDropOnScreen;

	if ( pPrevParticle )
		pPrevParticle->m_pNext = pParticle->m_pNext;
	else
		pPSystemData->m_pParticles = pParticle->m_pNext;

	pParticle->m_pNext = m_pUnusedListHead;
	m_pUnusedListHead = pParticle;
}

void CParticle::AddJetExplosion(CVector const &vecPos, Float fPower, Float fSize)
{
	CRGBA color(240, 240, 240, 255);

	if ( fPower < 1.0f )
		fPower = 1.0f;
	
	CVector vecRandOffset
	(
		CGeneral::GetRandomNumberInRange(-0.4f, 0.4f),
		CGeneral::GetRandomNumberInRange(-0.4f, 0.4f),
		CGeneral::GetRandomNumberInRange(0.1f, 0.3f)
	);
	
	vecRandOffset *= 2.0f;

	CVector vecStepPos = vecPos;

	for ( Int32 i = 0; i < Int32(fPower * 4.0f); i++ )
	{
		AddParticle(PARTICLE_EXPLOSION_MFAST,
					vecStepPos,
					CVector
					(
						CGeneral::GetRandomNumberInRange(-0.02f, 0.02f),
						CGeneral::GetRandomNumberInRange(-0.02f, 0.02f),
						CGeneral::GetRandomNumberInRange(-0.02f, 0.0f)
					),
					NULL,
					fSize, color, 0, 0, 0, 0);

		AddParticle(PARTICLE_EXPLOSION_MFAST,
					vecStepPos,
					CVector
					(
						CGeneral::GetRandomNumberInRange(-0.04f, 0.04f),
						CGeneral::GetRandomNumberInRange(-0.04f, 0.04f),
						CGeneral::GetRandomNumberInRange(0.0f, 0.07f)
					),
					NULL,
					fSize, color, 0, 0, 0, 0);

		AddParticle(PARTICLE_EXPLOSION_MFAST,
					vecStepPos,
					CVector
					(
						CGeneral::GetRandomNumberInRange(-0.04f, 0.04f),
						CGeneral::GetRandomNumberInRange(-0.04f, 0.04f),
						CGeneral::GetRandomNumberInRange(0.0f, 0.07f)
					),
					NULL,
					fSize, color, 0, 0, 0, 0);
		
		vecStepPos += vecRandOffset;
	}
}

void CParticle::AddYardieDoorSmoke(CVector const &vecPos, CMatrix const &matMatrix)
{
	CRGBA color(0, 0, 0, 0);
	
	CMatrix invMat(Invert(matMatrix));
	
	CVector vecBasePos = matMatrix * (invMat * vecPos + CVector(0.0f, -1.0f, 0.5f));
	
	for ( Int32 i = 0; i < 5; i++ )
	{
		CVector pos = vecBasePos;

		pos.x += CGeneral::GetRandomNumberInRange(-0.5f, 0.5f);
		pos.y += CGeneral::GetRandomNumberInRange(-0.5f, 0.5f);
		
		AddParticle(PARTICLE_CARCOLLISION_DUST,
					pos,
					CVector(0.0f, 0.0f, 0.0f),
					NULL,
					0.3f, color, 0, 0, 0, 0);
	}
}

void CParticle::CalWindDir(CVector *vecDirIn, CVector *vecDirOut)
{
	vecDirOut->x = (CParticle::m_CosTable[128] * vecDirIn->x) + (CParticle::m_SinTable[128] * vecDirIn->y);

	vecDirOut->x = (CParticle::m_CosTable[128] * vecDirIn->x) + (CParticle::m_SinTable[128] * vecDirIn->y) * CWeather::Wind;
	vecDirOut->y = (CParticle::m_SinTable[128] * vecDirIn->x) - (CParticle::m_CosTable[128] * vecDirIn->y) * CWeather::Wind;
}

void CParticle::HandleShipsAtHorizonStuff()
{
	tParticleSystemData *psystemdata = &mod_ParticleSystemManager.m_aParticles[PARTICLE_SHIP_SIDE];

	for ( CParticle *particle = psystemdata->m_pParticles; particle; particle = particle->m_pNext )
	{
		if ( CTimer::m_snTimeInMilliseconds > particle->m_nTimeWhenWillBeDestroyed - 32000 
				&& CTimer::m_snTimeInMilliseconds < particle->m_nTimeWhenWillBeDestroyed - 22000 )
		{		
			particle->m_nAlpha = min(particle->m_nAlpha + 1, 96);
		}
		if ( CTimer::m_snTimeInMilliseconds > particle->m_nTimeWhenWillBeDestroyed - 10000 )
			particle->m_nFadeAlphaTimer = 1;
	}
}

void CParticle::HandleShootableBirdsStuff(CEntity *entity, CVector const&camPos)
{
	Float fHeadingRad = atan2(-entity->m_sCoords.up.x, entity->m_sCoords.up.y);
	Float fHeading = RAD2DEG(fHeadingRad);
	Float fBirdAngle = cosf(DEG2RAD(1.5f));
	
	tParticleSystemData *psystem = &mod_ParticleSystemManager.m_aParticles[PARTICLE_BIRD_FRONT];
	CParticle *particle = psystem->m_pParticles;
	CParticle *prevParticle = NULL;
	Bool bRemoveParticle;
			
	for ( ; particle != NULL; _Next(particle, prevParticle, psystem, bRemoveParticle) )
	{
		bRemoveParticle = false;
		
		CVector2D vecPos(particle->m_vecPosition.x, particle->m_vecPosition.y);
		CVector2D vecCamPos(camPos.x, camPos.y);

		CVector2D vecDist = vecPos - vecCamPos;
		vecDist.Normalise();
		
		Float fHead = DEG2RAD(fHeading);

		CVector2D vecDir(-sinf(fHead), cosf(fHead));
		vecDir.Normalise();
		
		Float fDot = DotProduct(vecDir, vecDist);
		
		if ( fDot > 0.0f && fDot > fBirdAngle )
		{
			if ( (camPos - particle->m_vecPosition).MagnitudeSqr() < 40000.0f )
			{
				int &CStats__SeagullsKilled = *(int*)AddressByVersion(0x97869C, 0x9786A4, 0x9776A4);
				CStats__SeagullsKilled++;
				
				bRemoveParticle = true;

				for ( Int32 i = 0; i < 8; i++ )
				{	
					CParticle *pBirdDerbis = CParticle::AddParticle(PARTICLE_BIRD_DEBRIS,
																	particle->m_vecPosition,
																	CVector
																	(
																		CGeneral::GetRandomNumberInRange(-3.0f, 3.0f),
																		CGeneral::GetRandomNumberInRange(-3.0f, 3.0f),
																		CGeneral::GetRandomNumberInRange(-3.0f, 3.0f)
																	),
																	NULL,
																	0.3f,
																	particle->m_Color,
																	CGeneral::GetRandomNumberInRange(20, 40),
																	0,
																	CGeneral::GetRandomNumber() & 3,
																	200);
					if ( pBirdDerbis )
						pBirdDerbis->m_nAlpha = particle->m_nAlpha;
				}
			}
		}
	}
	
}

}