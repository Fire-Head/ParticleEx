#include "settings.h"
#include "ParticleEx.h"
#include "inc/IniReader.h"
#include "inc/String.h"

const char *aParticle[] =
{
	"PC",
	"PS2",
	"XBOX",
	"XBOX+III",
};


CSettings::CSettings()
{
	Reset();
}


void CSettings::Load(Bool bReload)
{
	CIniReader Ini("");

	cppext::String particle = Ini.ReadString("MAIN", "Particle", aParticle[PS_ORIGINAL]);

	m_nParticleSwitch = -1;
	
	for ( Int32 i = 0; i < ARRLEN(aParticle); i++)
	{
		if ( !strcmp(particle.ToUpper().c_str(), aParticle[i]) )
		{
			m_nParticleSwitch = i;
			break;
		}
	}
	
	if ( m_nParticleSwitch == -1 )
		FATAL("Invalid value: %s", particle.c_str());
	
	
	m_bFixMolotovBug = Ini.ReadBoolean("MAIN", "bFixXboxMolotovBug", true);
	m_bRestoreXboxHydrantWaterSpray = Ini.ReadBoolean("MAIN", "bRestoreXboxHydrantWaterSpray", false);
	m_bFixFlame5Bug = Ini.ReadBoolean("MAIN", "bFixFlame5Bug", false);
	//m_bUsePS2CarPuddlePhysics = Ini.ReadBoolean("MAIN", "bUsePS2CarPuddlePhysics", false);
	//m_bAltPS2Carsplash = Ini.ReadBoolean("MAIN", "bUseAltPS2Carsplash", false);
	//m_bCorrectWheelsRainWaterSplash = Ini.ReadBoolean("MAIN", "bUseNewWheelsWaterSplash", false);
	m_bFixWaterDropsInInteriors = Ini.ReadBoolean("MAIN", "bFixWaterDropsInInteriors", false);
	m_bDarkSpotsBugFix = Ini.ReadBoolean("MAIN", "bDarkSpotsBugFix", false);
	
	//m_nParticleLimit = Ini.ReadInteger("MAIN", "nParticleLimit", CParticleArray::DEFAULT_PARTICLE_ARRAY_SIZE);
	
	//if ( m_nParticleLimit <= 0 || m_nParticleLimit > 2000000000 )
	//	FATAL("nParticleLimit must be in > 0 && 2000000000 >= range");

	m_bDisableWaterDrop = Ini.ReadBoolean("MAIN", "bDisableVanillaWaterDrop", true);
	m_bDisableBloodDrop = Ini.ReadBoolean("MAIN", "bDisableVanillaBloodDrop", false);
	
	if ( bReload )
		ApplyInGame();
	else
		Apply();
}

void CSettings::Save()
{
	CIniReader Ini("");

	Ini.WriteString("MAIN", "Particle", (char *)aParticle[m_nParticleSwitch]);
	Ini.WriteBoolean("MAIN", "bFixXboxMolotovBug", m_bFixMolotovBug);
	Ini.WriteBoolean("MAIN", "bRestoreXboxHydrantWaterSpray", m_bRestoreXboxHydrantWaterSpray);
	Ini.WriteBoolean("MAIN", "bFixFlame5Bug", m_bFixFlame5Bug);
	//Ini.WriteBoolean("MAIN", "bUsePS2CarPuddlePhysics", m_bUsePS2CarPuddlePhysics);
	//Ini.WriteBoolean("MAIN", "bUseAltPS2Carsplash", m_bAltPS2Carsplash);
	//Ini.WriteBoolean("MAIN", "bUseNewWheelsWaterSplash", m_bCorrectWheelsRainWaterSplash);
	Ini.WriteBoolean("MAIN", "bFixWaterDropsInInteriors", m_bFixWaterDropsInInteriors);
	Ini.WriteBoolean("MAIN", "bDarkSpotsBugFix", m_bDarkSpotsBugFix);
	
	Ini.WriteBoolean("MAIN", "bDisableVanillaWaterDrop", m_bDisableWaterDrop);
	Ini.WriteBoolean("MAIN", "bDisableVanillaBloodDrop", m_bDisableBloodDrop);
	
	
	//Ini.WriteInteger("MAIN", "nParticleLimit", m_nParticleLimit);
}

void CSettings::Apply()
{
	CParticleEx::SetParticleSwitch((eParticleSwitch)m_nParticleSwitch);
	//CParticleArray::ReSize(m_nParticleLimit);
}

void CSettings::ApplyInGame()
{
	
	CParticleEx::ClearParticles();
	CParticleEx::SetParticleSwitch((eParticleSwitch)m_nParticleSwitch);
	CParticleEx::UpdatePObjects(CParticleEx::GetCurrentParticle());
	CParticleEx::ClearParticles();
	

	CParticleEx::ClearAllParticles();
	//CParticleArray::ReSize(m_nParticleLimit);
	//CParticleArray::ReInitArrays();
	
	CParticleEx::SetFlame5Fix(m_bFixFlame5Bug);
	CParticleEx::SetWaterDropsInInteriorsFix(m_bFixWaterDropsInInteriors);
}

void CSettings::Reset()
{
	//m_nParticleLimit = CParticleArray::DEFAULT_PARTICLE_ARRAY_SIZE;
	m_nParticleSwitch = PS_ORIGINAL;
	m_bFixMolotovBug = true;
	m_bRestoreXboxHydrantWaterSpray = true;
	m_bFixFlame5Bug = false;
	//m_bUsePS2CarPuddlePhysics = false;
	//m_bAltPS2Carsplash = false;
	//m_bCorrectWheelsRainWaterSplash = false;
	m_bFixWaterDropsInInteriors = false;
	m_bDarkSpotsBugFix = false;
	
	m_bDisableWaterDrop = true;
	m_bDisableBloodDrop = false;
}

CSettings &CSettings::Get()
{
	static CSettings settings;
	
	return settings;
}