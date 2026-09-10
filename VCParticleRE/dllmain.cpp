#include <windows.h>
#include "inc\CPatch.h"
#include "ParticleEx.h"
#include "settings.h"
#include <stdint.h>
#include "inc\debugmenu_public.h"
#include "inc\_InlineHook.hpp"


template<typename T>
inline static void CALL(int address, void *func, T &CB)
{
	if ( *(int*)(address + 1) + (address + 5) != (int)func)
	{
		CB = reinterpret_cast <T>(*(int*)(address + 1) + (address + 5));
		CPatch::RedirectCall(address, func);
	}
}

// fix compatibility with SilentPatch
float HeatHazeSclX(float x)
{
	int scrnW = **(int**)(AddressByVersion(0x56102D, 0x56104D, 0x560F1D) + 2);
	float sclW = **(float**)(AddressByVersion(0x561033, 0x561053, 0x560F23) + 2);
	
	return x * float(scrnW) * sclW;
}

float HeatHazeSclY(float y)
{
	int scrnH = **(int**)(AddressByVersion(0x56106B, 0x56108B, 0x560F5B) + 2);
	float sclH = **(float**)(AddressByVersion(0x561079, 0x561099, 0x560F69) + 2);
	
	return y * float(scrnH) * sclH;
}

int GetFixedArea()
{
	if ( CSettings::Get().m_bFixWaterDropsInInteriors )
		return 0;
	
	return CGame::currArea;
}

void * __cdecl _AddParticle(Int32 type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

int __AddParticleAddr = AddressByVersion(0x563CCA, 0x563CEA, 0x563BBA);

void NAK __AddParticle()
{
	__asm
	{
		cmp     CParticleEx::m_bUseOriginalSystem, 0
		jnz     J_ORIGINAL_PARTICLE 
		jmp     _AddParticle
	}
	
J_ORIGINAL_PARTICLE:
	__asm
	{
		push    ebx
		push    esi
		push    edi
		push    ebp
		sub     esp, 98h 
	}

	VARJMP(__AddParticleAddr);
}

void * __cdecl AddParticle_DUMMY(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CParticleEx::IsXbox() || CParticleEx::IsXbox2() )
		return NULL;
	else
		return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

class CXboxFireSets
{
public:
	Int32 nCycles;
	Float fParticleSizeMul;
	Float fRandomMin;
	Float fRandomMax;
	Float fMovingFlameTime;
	Float fVelZMul;
	Float fPosZMul;
	Float fMovingSpeed;
	
	
	CXboxFireSets()
	{
		nCycles = 1;
		fParticleSizeMul = 1.4f;
		fRandomMin = 0.0f;
		fRandomMax = 20.0f;
		fMovingFlameTime = 5.0f;
		fVelZMul = 1.0f;
		fPosZMul = 0.2f;
		fMovingSpeed = 0.003f;
	}
}xbxfire;

struct ProcessFireHook
{
	void operator()(reg_pack& regs)
	{
		if ( !CParticleEx::IsXbox() && !CParticleEx::IsXbox2() )
			return;

		//Stack Start
		CVector &_dummyPos = *(CVector *)(regs.cpu.esp + 0x74 - 0x54);
		CFire *This = (CFire *)(regs.cpu.ebx);
		//Stack End
		
		CVector dummyPos = _dummyPos;
		
		if ( This->m_pEntityTarget != NULL 
			&& This->m_pEntityTarget->m_nType == 2
			&& ((CVehicle *)This)->m_nVehicleClass == VEHICLETYPE_CAR )
		{
			dummyPos.z -= 0.15f;
		}
		
		Float fBaseStrength = 1.0f;
		
		Float fParticleSize = fBaseStrength;
		
		CVector vecDir
		(
			0.0f,
			0.0f,
			CGeneral::GetRandomNumberInRange(fBaseStrength / 80.0f, fBaseStrength / 10.0f) * 0.35f
		);

		Bool bMoving = false;
		
		if ( This->m_pEntityTarget != NULL && This->m_pEntityTarget->m_nType == 2 )
		{			
			bMoving = ((CPhysical *)This->m_pEntityTarget)->m_vecMoveSpeed.Magnitude2DSqr() > xbxfire.fMovingSpeed;

			dummyPos.x += CGeneral::GetRandomNumberInRange(-0.25f, 0.25f);
			dummyPos.y += CGeneral::GetRandomNumberInRange(-0.25f, 0.25f);
		}


		if ( This->m_pEntityTarget == NULL )
		{
			if ( CSettings::Get().m_bFixMolotovBug == false )
			{
				dummyPos.x += CGeneral::GetRandomNumberInRange(0.0f, 2.0f);
				dummyPos.y += CGeneral::GetRandomNumberInRange(0.0f, 2.0f);
			}
			else
			{
				dummyPos.x += CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
				dummyPos.y += CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
			}
			
			dummyPos.z -= 0.5f;
			fParticleSize *= 2.5f;
			vecDir.z *= 3.7f;
		}

		//////////////////////////////////////////////////////////////////////////////////

		if ( bMoving )
		{
			vecDir.z *= xbxfire.fVelZMul;
			fParticleSize *= xbxfire.fParticleSizeMul;
			dummyPos.z += xbxfire.fPosZMul;
			
			This->m_nNextParticleCreateTime = Int32((Float(CTimer::m_snTimeInMilliseconds) + xbxfire.fMovingFlameTime));
			
			for ( Int32 i = 0; i < xbxfire.nCycles; i++ )
			{
				CParticleEx::AddParticle(NPARTICLE_CARFLAME_MOVING,
						dummyPos,
						vecDir,
						NULL,
						fParticleSize,
						0,
						Int32(CGeneral::GetRandomNumberInRange(xbxfire.fRandomMin, xbxfire.fRandomMax)),
						0,
						0);
			}
		}
		else
		{
			CParticleEx::AddParticle(NPARTICLE_CARFLAME,
					dummyPos,
					vecDir,
					NULL,
					fParticleSize,
					0,
					CGeneral::GetRandomNumberInRange(0.0f, 20.0f),
					0,
					0);
		}
	}
};

int jmp_0x479B50 = AddressByVersion(0x48E9DD, 0x48E9ED, 0x48E8ED);
void *ProcessFire_ptr = GetInlineHookPtr<ProcessFireHook>();
void NAK Patch_ProcessFire()
{
	__asm
	{
		call    ProcessFire_ptr

		mov     dword ptr [esp+74h-44h], 0
		jmp     jmp_0x479B50
	}
}

struct ProcessControlHook
{
	void operator()(reg_pack& regs)
	{
		if ( !CParticleEx::IsXbox() && !CParticleEx::IsXbox2() )
			return;
		
		//Stack Start
		CVector &_pos = *(CVector *)(regs.cpu.esp + 0x0B28 - 0x66C);
		CVector &_smokepos = *(CVector *)(regs.cpu.esp + 0x0B28 - 0x678);
		CPhysical *This = (CPhysical *)(regs.cpu.ebp);
		//Stack End
		
		CVector pos = _pos;
		
		pos += CVector
		(
			CGeneral::GetRandomNumberInRange(-0.25f, 0.25f),
			CGeneral::GetRandomNumberInRange(-0.25f, 0.25f),
			0.0f
		);
		
		CVector vecDir
		(
			0.0f,
			0.0f,
			CGeneral::GetRandomNumberInRange(0.01f, 0.08f) * 0.35f
		);

		Float fParticleSize = 0.8f;
		
		if ( ((CPhysical *)This)->m_vecMoveSpeed.Magnitude2DSqr() > xbxfire.fMovingSpeed )
		{
			fParticleSize *= xbxfire.fParticleSizeMul;
			vecDir.z *= xbxfire.fVelZMul;
			pos.z += xbxfire.fPosZMul;
			
			for ( Int32 i = 0; i < xbxfire.nCycles; i++ )
			{
				CParticleEx::AddParticle(NPARTICLE_CARFLAME_MOVING,
						pos,
						vecDir,
						NULL,
						fParticleSize,
						0,
						Int32(CGeneral::GetRandomNumberInRange(xbxfire.fRandomMin, xbxfire.fRandomMax)),
						0,
						0);
			}
		}
		else
		{
			static DWORD m_nXboxFireTime = 0;

			if ( GetTickCount() - m_nXboxFireTime > 100 )
			{
				m_nXboxFireTime = GetTickCount(); // yes, it is in Xbox code
				
				_smokepos.z -= 0.15f;

				CParticleEx::AddParticle(NPARTICLE_CARFLAME,
					pos,
					vecDir,
					NULL,
					fParticleSize,
					0,
					CGeneral::GetRandomNumberInRange(0.0f, 20.0f),
					0,
					0);
			}
		}
	}
};

void *ProcessControll_ptr = GetInlineHookPtr<ProcessControlHook>();
int jmp_0x534558 = AddressByVersion(0x598A09, 0x598A29, 0x598839);
void NAK Patch_ProcessControll()
{
	__asm
	{
		call    ProcessControll_ptr
		
		mov     dword ptr [esp+0B28h-65Ch], 0
		jmp     jmp_0x534558
	}
}

void * __cdecl AddParticle_BIG_FIRE(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CParticleEx::IsXbox() || CParticleEx::IsXbox2() )
	{
		CVector dir = vecPos;
		dir.z * 0.0f;
		return CParticleEx::AddParticle(type, vecPos, dir, pEntity, fSize * 0.0f, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	}
	else
		return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

void * __cdecl AddParticle_EXPLOSION_LARGE(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	void * r = CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	
	if ( CParticleEx::IsXbox2() )
		CParticleEx::AddParticle(PARTICLE_EXPLOSION_LARGE, vecPos, CVector(0.0f, 0.0f, 0.0f), pEntity, 5.5f, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);

	return r;
}

int __HandleShipsAtHorizonStuffAddr = AddressByVersion(0x5BC450, 0x5BC470, 0x5BC280);
int addr__5BC495 = AddressByVersion(0x5BC495, 0x5BC4B5, 0x5BC2C5);
void NAK __HandleShipsAtHorizonStuff()
{
	__asm
	{
		cmp     CParticleEx::m_bUseOriginalSystem, 0
		jnz     J_ORIGINAL_SHIP 
		pop     ebx
		jmp     CParticleEx::HandleShipsAtHorizonStuff
	}
	
J_ORIGINAL_SHIP:
	__asm
	{		
		test    ebx, ebx
		push    ebp
		jz      short loc_5BC495
		lea     eax, [eax+0]
		jmp     __HandleShipsAtHorizonStuffAddr
	}
	
loc_5BC495:
	__asm jmp addr__5BC495
}

int __HandleShootableBirdsStuffAddr = AddressByVersion(0x5D0187, 0x5D01A7, 0x5CFF57);
void NAK __HandleShootableBirdsStuff()
{
	__asm
	{
		cmp     CParticleEx::m_bUseOriginalSystem, 0
		jnz     J_ORIGINAL_BIRD 
		jmp     CParticleEx::HandleShootableBirdsStuff
	}
	
J_ORIGINAL_BIRD:
	__asm
	{
		push    ebx
		push    esi
		push    edi
		push    ebp
		sub     esp, 50h 
	}

	VARJMP(__HandleShootableBirdsStuffAddr);
}

void _AddPermanentShadow(unsigned char ShadowType, void* pTexture, void* pPosn, float fX1, float fY1, float fX2, float fY2, short nTransparency, unsigned char nRed, unsigned char nGreen, unsigned char nBlue, float fZDistance, unsigned int nTime, float fScale)
{
	((void (__cdecl *)(unsigned char, void*, void*, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, unsigned int, float))AddressByVersion(0x56EC50, 0x56EC70, 0x56EB40))(ShadowType, pTexture, pPosn, fX1, fY1, fX2, fY2, nTransparency, nRed, nGreen, nBlue, fZDistance, nTime, fScale);
}

void _DarkSpotAddPermanentShadow(unsigned char ShadowType, RwTexture* pTexture, CVector* pPosn, float fX1, float fY1, float fX2, float fY2, short nTransparency, unsigned char nRed, unsigned char nGreen, unsigned char nBlue, float fZDistance, unsigned int nTime, float fScale)
{
	if ( CSettings::Get().m_bDarkSpotsBugFix )
		_AddPermanentShadow(ShadowType, pTexture, pPosn, fX1, fY1, fX2, fY2, nTransparency, nRed, nGreen, nBlue, fZDistance, 30000, 1.0f);
	else
		_AddPermanentShadow(ShadowType, pTexture, pPosn, fX1, fY1, fX2, fY2, nTransparency, nRed, nGreen, nBlue, fZDistance, nTime, fScale);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

DebugMenuAPI gDebugMenuAPI;

template <void (*CallBack)(), void (*PreCallBack)(), void (*PostCallBack)()> void QUICK_Button()
{
	if ( PreCallBack != NULL )
		PreCallBack();
	
	CallBack();
	
	if ( PostCallBack != NULL )
		PostCallBack();
	
	DMAudio.PlayFrontEndSound(179, 0);
}

void onSwitchChange()
{
	CParticleEx::ClearParticles();
	CParticleEx::SetParticleSwitch((eParticleSwitch)CSettings::Get().m_nParticleSwitch);
	CParticleEx::UpdatePObjects(CParticleEx::GetCurrentParticle());
	CParticleEx::ClearParticles();
}

void onParticleLimitChange()
{
	CParticleEx::ClearAllParticles();
	//TODO
}

void UpdatePObjects()
{
	CParticleEx::UpdatePObjects(CParticleEx::GetCurrentParticle());
	CParticleEx::ClearParticles();
}

void onFixFlame5Bug()
{
	CParticleEx::SetFlame5Fix(CSettings::Get().m_bFixFlame5Bug);
}

void onFixWaterDropsInInteriors()
{
	CParticleEx::SetWaterDropsInInteriorsFix(CSettings::Get().m_bFixWaterDropsInInteriors);
}

void SaveSet()
{
	CSettings::Get().Save();
}

void ReLoadSet()
{
	CSettings::Get().Load(true);
}

void ResetSet()
{
	CSettings::Get().Reset();
	CSettings::Get().ApplyInGame();
}

void CheckAsi()
{
	CSettings::Get().Load();
	
	if(DebugMenuLoad())
	{
		DebugMenuEntry *e = DebugMenuAddVar("ParticleEx", "switch", &CSettings::Get().m_nParticleSwitch, onSwitchChange, 1, 0, PS_MAX - 1, aParticle);
		DebugMenuEntrySetWrap(e, true);
		
		DebugMenuAddVarBool8("ParticleEx", "[Xbox]     Fix Molotov Bug", (int8_t *)&CSettings::Get().m_bFixMolotovBug, NULL);
		DebugMenuAddVarBool8("ParticleEx", "[Xbox]     Restore Hydrant Waterspray", (int8_t *)&CSettings::Get().m_bRestoreXboxHydrantWaterSpray, NULL);
		DebugMenuAddVarBool8("ParticleEx", "[PS2/PC]   Fix flame5 Bug", (int8_t *)&CSettings::Get().m_bFixFlame5Bug, onFixFlame5Bug);
		DebugMenuAddVarBool8("ParticleEx", "[PS2/Xbox] Disable Vanilla Waterdrops", (int8_t *)&CSettings::Get().m_bDisableWaterDrop, NULL);
		DebugMenuAddVarBool8("ParticleEx", "[PS2/Xbox] Disable Vanilla Blooddrops", (int8_t *)&CSettings::Get().m_bDisableBloodDrop, NULL);
		DebugMenuAddVarBool8("ParticleEx", "[ANY]      Fix Waterdrops in Interiors", (int8_t *)&CSettings::Get().m_bFixWaterDropsInInteriors, onFixWaterDropsInInteriors);
		//DebugMenuAddVarBool8("ParticleEx", "[PS2]      Use Puddles Surface Physics", (int8_t *)&CSettings::Get().m_bUsePS2CarPuddlePhysics, NULL);
		//DebugMenuAddVarBool8("ParticleEx", "[PS2]      Use Alternative Car Splash", (int8_t *)&CSettings::Get().m_bAltPS2Carsplash, NULL);
		DebugMenuAddVarBool8("ParticleEx", "[ANY]      Explosion Dark Spot Fix", (int8_t *)&CSettings::Get().m_bDarkSpotsBugFix, NULL);
		
		//DebugMenuAddUInt32("ParticleEx", "Particles Limit", (uint32_t *)&CSettings::Get().m_nParticleLimit, onParticleLimitChange, 100, 100, 2000000000, NULL);
	    //
		//
		DebugMenuAddCmd("ParticleEx", "Reload particle.cfg", QUICK_Button<CParticleEx::ReloadConfig, CParticleEx::ClearAllParticles, NULL>);
		DebugMenuAddCmd("ParticleEx", "Clear Particles", QUICK_Button<CParticleEx::ClearParticles, NULL, NULL>);
		//
		DebugMenuAddCmd("ParticleEx|Settings", "Save Settings", QUICK_Button<SaveSet, NULL, NULL>);
		DebugMenuAddCmd("ParticleEx|Settings", "ReLoad Settings", QUICK_Button<ReLoadSet, NULL, NULL>);
		DebugMenuAddCmd("ParticleEx|Settings", "Reset Settings", QUICK_Button<ResetSet, NULL, NULL>);
		//
	    //
		//DebugMenuAddCmd("ParticleEx|PObject", "Update PObjects", QUICK_Button<UpdatePObjects, NULL, NULL>);		
		//DebugMenuAddCmd("ParticleEx|PObject", "Reset PObjects", QUICK_Button<CParticleEx::ResetPObjects, NULL, NULL>);
        //
		//DebugMenuAddCmd("ParticleEx|PObject", "Save PObjects", QUICK_Button<CPObjectMgr::Save, NULL, NULL>);
		//DebugMenuAddCmd("ParticleEx|PObject", "Load PObjects", QUICK_Button<CPObjectMgr::Load, NULL, NULL>);
	}
}

typedef int (*tRsEventHandler)(int, int);
static tRsEventHandler AsiCheckCB;

int __cdecl onAsiCheck(int a, int b)
{
	CheckAsi();
	
	return AsiCheckCB(a, b);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		PluginErrorCheck(PLUGINPREF_VERSION_ANY | PLUGINPREF_CHECK_ASI_LOADER);
		
		CParticleEx::SetParticleSwitch(CParticleEx::GetCurrentParticle());
		
		CALL(AddressByVersion(0x5FFAFE, 0x5FFB1E, 0x5FF75E), onAsiCheck, AsiCheckCB);
		
		CPatch::RedirectCall(AddressByVersion(0x4A4985, 0x4A49A5, 0x4A4845), CParticleEx::ReloadConfig);
		CPatch::RedirectCall(AddressByVersion(0x564EC5, 0x564EE5, 0x564DB5), CParticleEx::ReloadConfig);
		
		CPatch::RedirectCall(AddressByVersion(0x4A4C61, 0x4A4C81, 0x4A4B28), CParticleEx::Initialise);
		
		CPatch::RedirectCall(AddressByVersion(0x4A4ADF, 0x4A4AFF, 0x4A499F), CParticleEx::Shutdown);
		
		CPatch::RedirectJump(AddressByVersion(0x563CC0, 0x563CE0, 0x563BB0), __AddParticle);
		
		CPatch::RedirectCall(AddressByVersion(0x4A4542, 0x4A4562, 0x4A43B5), CParticleEx::Update);
		
		CPatch::RedirectCall(AddressByVersion(0x4A6542, 0x4A6562, 0x4A6412), CParticleEx::Render);
		
		CPatch::RedirectCall(AddressByVersion(0x57C94B, 0x57C96B, 0x57C77B), CParticleEx::RemovePSystem);
		
		CPatch::RedirectJump(AddressByVersion(0x5BC447, 0x5BC467, 0x5BC277), __HandleShipsAtHorizonStuff);
		CPatch::RedirectJump(AddressByVersion(0x5D0180, 0x5D01A0, 0x5CFF50), __HandleShootableBirdsStuff);
		
		//CFire Tweak
		{			
			CPatch::RedirectCall(AddressByVersion(0x48EA3D, 0x48EA4D, 0x48E94D), AddParticle_DUMMY);
			CPatch::RedirectCall(AddressByVersion(0x48EA88, 0x48EA98, 0x48E998), AddParticle_DUMMY);
			
			CPatch::RedirectJump(AddressByVersion(0x48E9D5, 0x48E9E5, 0x48E8E5), Patch_ProcessFire);
		}
		
		// Vehicle Smoke Tweak
		{
			CPatch::RedirectCall(AddressByVersion(0x598A6D, 0x598A8D, 0x59889D), AddParticle_DUMMY);
			CPatch::RedirectCall(AddressByVersion(0x598B83, 0x598BA3, 0x5989B3), AddParticle_DUMMY);		
			CPatch::RedirectJump(AddressByVersion(0x5989FE, 0x598A1E, 0x59882E), Patch_ProcessControll);
		}
		
		// PObj tweak
		{
			
			//POBJECT_BIG_FIRE
			CPatch::RedirectCall(AddressByVersion(0x4E51B5, 0x4E51D5, 0x4E5075), AddParticle_DUMMY);
			CPatch::RedirectCall(AddressByVersion(0x4E5082, 0x4E50A2, 0x4E4F42), AddParticle_BIG_FIRE);
			
			//POBJECT_SMALL_FIRE
			CPatch::RedirectCall(AddressByVersion(0x4E4FC6, 0x4E4FE6, 0x4E4E86), AddParticle_DUMMY);
		}
		
		CPatch::RedirectCall(AddressByVersion(0x5C57D1, 0x5C57F1, 0x5C5601), _DarkSpotAddPermanentShadow);
				
		CPatch::RedirectCall(AddressByVersion(0x5C4F15, 0x5C4F35, 0x5C4D45), AddParticle_EXPLOSION_LARGE);
	}
	return TRUE;
}