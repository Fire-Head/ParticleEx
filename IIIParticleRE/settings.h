#pragma once
#include "_precl.h"
#include "_config.h"


class CSettings
{
public:
	Bool m_bFixMolotovBug;
	Bool m_bFixFlame5Bug;
	Bool m_bUsePS2CarPuddlePhysics;
	Bool m_bAltPS2Carsplash;
	Bool m_bCorrectWheelsRainWaterSplash;
	Bool m_bDarkSpotsBugFix;
	Bool m_bPS2JetPos;
	Bool m_bVCJet;
	Bool m_bPS2Rain;
	
	UInt32 m_nParticleSwitch;
	UInt32 m_nParticleLimit;

	CSettings();
	
	void Load(Bool bReload = false);
	void Save();
	void Reset();
	
	void Apply();
	void ApplyInGame();
	
	static CSettings &Get();
};

extern const char *aParticle[];
extern const char *aCarNode[];


