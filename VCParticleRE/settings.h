#pragma once
#include "_precl.h"
#include "_config.h"


class CSettings
{
public:
	Bool m_bFixMolotovBug;
	Bool m_bRestoreXboxHydrantWaterSpray;
	Bool m_bFixFlame5Bug;
	//Bool m_bUsePS2CarPuddlePhysics;
	//Bool m_bAltPS2Carsplash;
	//Bool m_bCorrectWheelsRainWaterSplash;
	Bool m_bFixWaterDropsInInteriors;
	Bool m_bDarkSpotsBugFix;

	UInt32 m_nParticleSwitch;
	//UInt32 m_nParticleLimit;
	Bool m_bDisableWaterDrop;
	Bool m_bDisableBloodDrop;

	CSettings();
	
	void Load(Bool bReload = false);
	void Save();
	void Reset();
	
	void Apply();
	void ApplyInGame();
	
	static CSettings &Get();
};

extern const char *aParticle[];



