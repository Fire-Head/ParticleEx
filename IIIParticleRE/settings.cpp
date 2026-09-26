#include "settings.h"
#include "ParticleEx.h"
#include "ParticleArray.h"

const char *aParticle[] =
{
	"PC",
	"XBOX",
	"PS2"
};

CSettings::CSettings()
{
	Reset();
}


void CSettings::Load(Bool bReload)
{
	CIniReader Ini("");

	cppext::String particle = Ini.ReadString("MAIN", "Particle", aParticle[PS_PS2]);

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
	m_bFixFlame5Bug = Ini.ReadBoolean("MAIN", "bFixPCPS2Flame5Bug", false);
	m_bUsePS2CarPuddlePhysics = Ini.ReadBoolean("MAIN", "bUsePS2CarPuddlePhysics", true);
	m_bAltPS2Carsplash = Ini.ReadBoolean("MAIN", "bUseAltPS2Carsplash", false);
	m_bCorrectWheelsRainWaterSplash = Ini.ReadBoolean("MAIN", "bUseNewWheelsWaterSplash", true);
	m_bDarkSpotsBugFix = Ini.ReadBoolean("MAIN", "bDarkSpotsBugFix", true);
	m_bPS2JetPos = Ini.ReadBoolean("MAIN", "bPS2Jet", true);
	m_bVCJet = Ini.ReadBoolean("MAIN", "bVCJet", false);
	m_bPS2Rain = Ini.ReadBoolean("MAIN", "bPS2Rain", true);
	
	m_nParticleLimit = Ini.ReadInteger("MAIN", "nParticleLimit", CParticleArray::DEFAULT_PARTICLE_ARRAY_SIZE);
	
	if ( m_nParticleLimit <= 0 || m_nParticleLimit > 2000000000 )
		FATAL("nParticleLimit must be in > 0 && 2000000000 >= range");
	
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
	Ini.WriteBoolean("MAIN", "bFixPCPS2Flame5Bug", m_bFixFlame5Bug);
	Ini.WriteBoolean("MAIN", "bUsePS2CarPuddlePhysics", m_bUsePS2CarPuddlePhysics);
	Ini.WriteBoolean("MAIN", "bUseAltPS2Carsplash", m_bAltPS2Carsplash);
	Ini.WriteBoolean("MAIN", "bUseNewWheelsWaterSplash", m_bCorrectWheelsRainWaterSplash);
	Ini.WriteBoolean("MAIN", "bDarkSpotsBugFix", m_bDarkSpotsBugFix);
	Ini.WriteBoolean("MAIN", "bPS2Jet", m_bPS2JetPos);
	Ini.WriteBoolean("MAIN", "bVCJet", m_bVCJet);
	Ini.WriteBoolean("MAIN", "bPS2Rain", m_bPS2Rain);
	Ini.WriteInteger("MAIN", "nParticleLimit", m_nParticleLimit);
}

void CSettings::Apply()
{
	CParticleEx::SetParticleSwitch((eParticleSwitch)m_nParticleSwitch);
	CParticleArray::ReSize(m_nParticleLimit);
}

void CSettings::ApplyInGame()
{
	
	CParticleEx::ClearParticles();
	CParticleEx::SetParticleSwitch((eParticleSwitch)m_nParticleSwitch);
	CParticleEx::UpdatePObjects(CParticleEx::GetCurrentParticle());
	CParticleEx::ClearParticles();
	

	CParticleEx::ClearAllParticles();
	CParticleArray::ReSize(m_nParticleLimit);
	CParticleArray::ReInitArrays();
	
	CParticleEx::SetFlame5Fix(m_bFixFlame5Bug);
	
	if ( m_bVCJet )
		CParticleEx::SetVCJetPos();
	else
		CParticleEx::SetPS2JetPos(m_bPS2JetPos);
	
	CParticleEx::SetPS2Rain(m_bPS2Rain);
}

void CSettings::Reset()
{
	m_nParticleLimit = CParticleArray::DEFAULT_PARTICLE_ARRAY_SIZE;
	m_nParticleSwitch = PS_PS2;
	m_bFixMolotovBug = true;
	m_bFixFlame5Bug = false;
	m_bUsePS2CarPuddlePhysics = true;
	m_bAltPS2Carsplash = false;
	m_bCorrectWheelsRainWaterSplash = true;
	m_bDarkSpotsBugFix = true;
	m_bPS2JetPos = true;
	m_bVCJet = false;
	m_bPS2Rain = true;
}

CSettings &CSettings::Get()
{
	static CSettings settings;
	
	return settings;
}