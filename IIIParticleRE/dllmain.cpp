#include "_precl.h"
#include "ParticleEx.h"
#include "ParticleArray.h"
#include "PObjectMgr.h"
#include "inc/_InlineHook.hpp"
#include "inc/debugmenu_public.h"
#include "settings.h"
#include "_config.h"

CBaseModelInfo *getModelInfoPtrs(unsigned int id)
{
	//CBaseModelInfo **CModelInfo::ms_modelInfoPtrs = (CBaseModelInfo **)AddressByVersion(0x83D408, 0x83D408, 0x84D548);
	
	CBaseModelInfo ***_modelInfoPtrs = (CBaseModelInfo ***)(AddressByVersion(0x50B870, 0x50B960, 0x50B8F0) + 3);
		
	return (*_modelInfoPtrs)[id];
}

enum BoneTag {
	BONE_Swaist,
	BONE_Supperlegr,
	BONE_Slowerlegr,
	BONE_Sfootr,
	BONE_Supperlegl,
	BONE_Slowerlegl,
	BONE_Sfootl,
	BONE_Smid,
	BONE_Storso,
	BONE_Shead,
	BONE_Supperarmr,
	BONE_Slowerarmr,
	BONE_SRhand,
	BONE_Supperarml,
	BONE_Slowerarml,
	BONE_SLhand,
};

enum PedNode {
	PED_Swaist,
	PED_Storso,
	PED_Shead,
	PED_Supperarml,
	PED_Supperarmr,
	PED_SLhand,
	PED_SRhand,
	PED_Supperlegl,
	PED_Supperlegr,
	PED_Sfootl,
	PED_Sfootr,
	PED_Slowerlegr,
	PED_Slowerlegl
};

class CPedModelInfo_aap : public CClumpModelInfo
{
public:
	int animGroup;
	int unk1;
	int pedStats;
	int unk2;
	CColModel *hitColModel;
	RpAtomic *head;
	RpAtomic *lhand;
	RpAtomic *rhand;
};

struct AnimBlendFrameData_aap
{
	int flag;
	RwV3d pos;
	union {
		RwFrame *frame;
		RpHAnimStdKeyFrame *hanimframe;
	};
	int nodeID;
};

int
ConvertPedNode2BoneTag(int node)
{
	static int tags[] = { BONE_Swaist, BONE_Storso, BONE_Shead,
	                      BONE_Supperarml, BONE_Supperarmr,
	                      BONE_SLhand, BONE_SRhand,
	                      BONE_Supperlegl, BONE_Supperlegr,
	                      BONE_Sfootl, BONE_Sfootr,
	                      BONE_Slowerlegr, BONE_Slowerlegl };
	if(node > 12)
		return -1;
	return tags[node];
}

static RpAtomic *GetAnimHierarchyCallback(RpAtomic *atomic, void *data)
{
	*(RpHAnimHierarchy**)data = RpSkinAtomicGetHAnimHierarchy(atomic);
	return NULL;
}

RpHAnimHierarchy *GetAnimHierarchyFromSkinClump(RpClump *clump)
{
	RpHAnimHierarchy *hier = NULL;
	RpClumpForAllAtomics(clump, GetAnimHierarchyCallback, &hier);
	return hier;
}

RwMatrix *RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy *hierarchy)
{
	return hierarchy->pMatrixArray;
}

RwInt32 RpHAnimIDGetIndex(RpHAnimHierarchy *hierarchy, RwInt32 ID)
{
	for(RwInt32 i = 0; i < hierarchy->numNodes; i++)
		if(hierarchy->pNodeInfo[i].nodeID == ID)
			return i;
	return -1;
}

static RpAtomic *isSkinnedCb(RpAtomic *atomic, void *data)
{
	RpAtomic **ret = (RpAtomic **)data;
	if(*ret)
		return NULL;
	if(RpSkinGeometryGetSkin(atomic->geometry))
		*ret = atomic;
	return atomic;
}

RpAtomic *IsClumpSkinned(RpClump *c)
{
	RpAtomic *ret = NULL;
	RpClumpForAllAtomics(c, isSkinnedCb, &ret);
	return ret;
}

CVector GetPedHeadPosition(CPed *ped)
{
	if ( IsClumpSkinned(ped->m_pRwClump) )
	{
		RwV3d out = { 0.0f, 0.0f, 0.0f };
		RpHAnimHierarchy *hier = GetAnimHierarchyFromSkinClump(ped->m_pRwClump);
		int bonetag = ConvertPedNode2BoneTag(2);
		RwUInt32 index = RpHAnimIDGetIndex(hier, bonetag);
		RwMatrix *pMatrix = RpHAnimHierarchyGetMatrixArray(hier);
		RwV3dTransformPoints(&out, &out, 1, &pMatrix[index]);

		return CVector(out.x, out.y, out.z);
	}
	else
	{
		RwMatrix matrix;
		CPedIK::GetWorldMatrix(ped->m_apBodyParts[2]->m_pRwFrame, &matrix);
		return CVector(matrix.pos.x, matrix.pos.y, matrix.pos.z);
	}
}

CVector GetPedNodePosition(CPed *ped, int id)
{
	if ( IsClumpSkinned(ped->m_pRwClump) )
	{
		RwV3d out = { 0.0f, 0.0f, 0.0f };
		
		RpHAnimHierarchy *hier = GetAnimHierarchyFromSkinClump(ped->m_pRwClump);
		RwInt32 idx = RpHAnimIDGetIndex(hier, ((AnimBlendFrameData_aap *)ped->m_apBodyParts[id])->nodeID);
		RwV3dTransformPoints(&out, &out, 1, &RpHAnimHierarchyGetMatrixArray(hier)[idx]);

		return CVector(out.x, out.y, out.z);
	}
	else
	{
		RwV3d out = { 0.0f, 0.0f, 0.0f };
		
		RwFrame *parent = ped->m_apBodyParts[id]->m_pRwFrame;
		while( parent )
		{
			RwV3dTransformPoints(&out, &out, 1, RwFrameGetMatrix(parent));
			parent = RwFrameGetParent(parent);
		}

		return CVector(out.x, out.y, out.z);
	}
}

void * __cdecl _AddParticle(Int32 type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

int __AddParticleAddr = AddressByVersion(0x50D19A, 0x50D38A, 0x50D31A);

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
		sub     esp, 88h 
	}

	VARJMP(__AddParticleAddr);
}

void NAK __LoadPObjects()
{
	__asm
	{
		pushad
		call     CParticleEx::LoadPObjects
		popad

		retn
	}
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

struct ProcessControlHook
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_XBOX )
			return;
		
		//Stack Start
		CVector &_pos = *(CVector *)(regs.cpu.esp + 0x518 - 0x31C);
		CVector &_smokepos = *(CVector *)(regs.cpu.esp + 0x518 - 0x328);
		CAutomobile *This = (CAutomobile *)(regs.cpu.ebp);
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
			CGeneral::GetRandomNumberInRange(0.0035f, 0.0735f) * 0.35f
		);

		Float fParticleSize = 0.8f;
		
		if ( ((CPhysical *)This)->m_vecVelocity.Magnitude2DSqr() > xbxfire.fMovingSpeed )
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

struct ProcessFireHook
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_XBOX )
			return;

		//Stack Start
		CVector &_dummyPos = *(CVector *)(regs.cpu.esp + 0x64 - 0x48);
		CFire *This = (CFire *)(regs.cpu.ebx);
		//Stack End
		
		CVector dummyPos = _dummyPos;
		
		if ( This->m_pEntityTarget != NULL 
			&& This->m_pEntityTarget->m_nType == 2
			&& ((CVehicle *)This)->m_eVehicleType == VEHICLETYPE_CAR )
		{
			dummyPos.z -= 0.15f;
		}
		
		// original box
		//Float fBaseStrength = This->m_fStrength * 0.7f;
		// i don't want to change the value in CExplosion::AddExplosion->EXPLOSION_MOLOTOV, because that will prevent me from changing particle switch on the fly, so i'll do it here
		Float fBaseStrength = 0.8f * 0.7f;
		
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
			bMoving = ((CPhysical *)This->m_pEntityTarget)->m_vecVelocity.Magnitude2DSqr() > xbxfire.fMovingSpeed;

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

void * __cdecl AddParticle_DUMMY(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CParticleEx::GetCurrentParticle() == PS_XBOX )
		return NULL;
	else
		return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

void * __cdecl AddParticle_BIG_FIRE(Int32 type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CParticleEx::GetCurrentParticle() == PS_XBOX )
	{		
		CVector dir = vecDir;
		
		dir.z = CGeneral::GetRandomNumberInRange(0.0f, 1.0f) * 0.0f;
		
		return CParticleEx::AddParticle(type, vecPos, dir, pEntity, /*fSize*/0.0f, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	
	}
	else
		return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

int jmp_0x479B50 = AddressByVersion(0x479B50, 0x479B50, 0x479B50);
void *ProcessFire_ptr = GetInlineHookPtr<ProcessFireHook>();
void NAK Patch_ProcessFire()
{
	__asm
	{
		call    ProcessFire_ptr

		mov     dword ptr [esp+64h-38h], 0
		jmp     jmp_0x479B50
	}
}

void *ProcessControll_ptr = GetInlineHookPtr<ProcessControlHook>();
int jmp_0x534558 = AddressByVersion(0x534558, 0x534798, 0x534728);
void NAK Patch_ProcessControll()
{
	__asm
	{
		call    ProcessControll_ptr
		
		mov     dword ptr [esp+518h-30Ch], 0
		jmp     jmp_0x534558
	}
}

CParticleObject *AddObject_CAR_SPLASH_1(unsigned short Type, CVector const &vecPos, CVector const &vecTarget, float fSize, unsigned int nLifeTime, RwRGBA const &Color, unsigned char bCanRemove)
{
	if ( CParticleEx::GetCurrentParticle() == PS_PS2 )
	{
		if ( CSettings::Get().m_bAltPS2Carsplash )
			return CParticleObject::AddObject(Type, vecPos, vecTarget, fSize, nLifeTime, Color, bCanRemove);
		else
			return NULL;
	}
	else
		return CParticleObject::AddObject(Type, vecPos, vecTarget, fSize, nLifeTime, Color, bCanRemove);
}

struct ProcessBuoyancy1Hook
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
			return;
		
		if ( CSettings::Get().m_bAltPS2Carsplash )
			return;

		//Stack Start
		CAutomobile *This = (CAutomobile *)(regs.cpu.ebp);
		CVector &vecTurnForce = *(CVector *)(regs.cpu.esp + 0x140 - 0xF8);
		CVector &vecVelocity = *(CVector *)(regs.cpu.esp + 0x140 - 0xE0);
		//Stack End
		
		CVector vecBasePos = (vecVelocity * 2.0f) + (This->m_sCoords.GetTranslate() + vecTurnForce);

		for ( Int32 i = 0; i < 360; i += 4 )
		{
			Float fSin = sinf(Float(i));
			Float fCos = cosf(Float(i));
			
			CVector vecDir
			(
				fSin / 100.0f,
				fCos / 100.0f,
				CGeneral::GetRandomNumberInRange(0.25f, 0.45f)
			);
			
			CParticle::AddParticle(PARTICLE_CAR_SPLASH,
					vecBasePos + CVector(fSin * 4.5f, fCos * 4.5f, 0.0f),
					vecDir,
					NULL,
					0.0f,
					CRGBA(225, 225, 255, 180),
					0,
					0,
					0,
					0);

			for ( Int32 j = 0; j < 3; j++ )
			{
				Float fMul = 1.5f * Float(j + 1);
				
				CParticle::AddParticle(PARTICLE_CAR_SPLASH,
						vecBasePos + CVector(fSin * fMul, fCos * fMul, 0.0f),
						vecDir,
						NULL,
						0.0f,
						CRGBA(225, 225, 255, 180),
						0,
						0,
						0,
						0);                      
			}
			
		}
	}
};

void *ProcessBuoyancy1_ptr = GetInlineHookPtr<ProcessBuoyancy1Hook>();
int jmp_0x530CC7 = AddressByVersion(0x530CC7, 0x530F07, 0x530E97);
void NAK Patch_ProcessBuoyancy1()
{
	__asm
	{
		and     eax, 0FFFFh
		
		call    ProcessBuoyancy1_ptr
		
		jmp    jmp_0x530CC7
	}
}

void * __cdecl AddParticle_PS2Dummy(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CParticleEx::GetCurrentParticle() == PS_PS2 )
		return NULL;
	else
		return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

// for waterdrops
void * __cdecl AddParticle_PS2Dummy_WD(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	CParticleEx::AddExtendedDroplets(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	return AddParticle_PS2Dummy(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

void * __cdecl AddParticle_PS2Dummy_WDTRAP(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CParticleEx::m_bWaterdropsInstalled )
		return NULL;
	
	return AddParticle_PS2Dummy(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

void __fastcall PlayOneShot_PS2Dummy(cDMAudio *This, int edx0, int v1, unsigned short v2, float v3)
{
	if ( CParticleEx::GetCurrentParticle() == PS_PS2 )
		return;
	else
		This->PlayOneShot(v1, v2, v3);
}

struct ProcessBuoyancy2Hook
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
			return;

		//Stack Start
		CAutomobile *This = (CAutomobile *)(regs.cpu.ebp);
		int i = regs.cpu.edi;
		float &fVel = *(float *)(regs.cpu.esp + 0x140 - 0x10C);
		//Stack End
		
		CRGBA color(155, 185, 155, 255);
		Float fWidth = getModelInfoPtrs(This->m_nModelIndex)->m_pColModel->m_BoundBox.m_Box.inf.y;
		
		if ( ( (CTimer::m_FrameCounter + i) & 3 ) == 0 )
		{
			if ( i == 2 )
			{
				CParticle::AddParticle(PARTICLE_PED_SPLASH,
						(This->m_sCoords.pos + (fWidth * This->m_sCoords.up)) + (0.5f * This->m_sCoords.GetRight()),
						0.75f * This->m_vecVelocity,
						NULL,
						0.0f,
						color,
						0,
						0,
						0,
						0);

			}
			else if ( i == 0 )
			{
				CParticle::AddParticle(PARTICLE_PED_SPLASH,
						(This->m_sCoords.pos + (fWidth * This->m_sCoords.up)) - (0.5f * This->m_sCoords.GetRight()),
						0.75f * This->m_vecVelocity,
						NULL,
						0.0f,
						color,
						0,
						0,
						0,
						0);
			}
					
			if ( (CTimer::m_FrameCounter & 15) == 0 )
				DMAudio.PlayOneShot(This->m_nAudioIndex, 22, 2000.0f * fVel);
		}
	}
	
};

void *ProcessBuoyancy2_ptr = GetInlineHookPtr<ProcessBuoyancy2Hook>();
int jmp_0x531277 = AddressByVersion(0x531277, 0x5314B7, 0x531447);
void NAK Patch_ProcessBuoyancy2()
{
	__asm
	{
		and     eax, 0FFFFh
		
		call    ProcessBuoyancy2_ptr
		
		jmp    jmp_0x531277
	}
}

struct ProcessBuoyancy3Hook
{
	void operator()(reg_pack& regs)
	{
		//if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
		//	return;
		
		if ( !CSettings::Get().m_bUsePS2CarPuddlePhysics )
			return;
	
		//Stack Start
		CAutomobile *This = (CAutomobile *)(regs.cpu.ebp);
		CVector &vecCross = *(CVector *)(regs.cpu.esp + 0x14C - 0x1C);
		//Stack End

		CVector vecVel = vecCross + This->m_vecVelocity + This->m_vecAcceleration;
		
		CVector vecMoveForce = CTimer::ms_fTimeStep * (This->m_fMass * (CVector(vecVel.x, vecVel.y, 0.0f) * -0.003f));
		This->ApplyMoveForce(vecMoveForce.x, vecMoveForce.y, vecMoveForce.z);
	}
	
};

void *ProcessBuoyancy3_ptr = GetInlineHookPtr<ProcessBuoyancy3Hook>();
int jmp_0x531157 = AddressByVersion(0x531157, 0x531397, 0x531327);
void NAK Patch_ProcessBuoyancy3()
{
	__asm
	{
		call    ProcessBuoyancy3_ptr
		
		fld     [esp+14Ch-18h]
		
		jmp     jmp_0x531157
	}
}

void * __cdecl AddParticle_WATERSPRAY(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CParticleEx::GetCurrentParticle() == PS_PS2 )
	{
		if ( CSettings::Get().m_bCorrectWheelsRainWaterSplash )
		{
			return CParticleEx::AddParticle(NPARTICLE_WHEEL_WATER, vecPos,
						CVector(vecDir.x, vecDir.y, CGeneral::GetRandomNumberInRange(0.005f, 0.04f)),
						pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
		}
		else
		{
			return CParticleEx::AddParticle(type, vecPos,
						CVector(vecDir.x, vecDir.y, CGeneral::GetRandomNumberInRange(0.005f, 0.04f)),
						pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
		}
	}
	else
		return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

void * __cdecl AddParticle_RAIN_SPLASH_BIGGROW(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CParticleEx::GetCurrentParticle() == PS_PS2 )
	{
		CRGBA c(0, 0, 0, 0);
		return CParticleEx::AddParticle(type, vecPos+CVector(0.0f, 0.0f, 1.0f), vecDir, pEntity, fSize, c, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	}
	else
		return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

// for waterdrops
void * __cdecl AddParticle_RAIN_SPLASH_BIGGROW_WD(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	CParticleEx::AddExtendedDroplets(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	return AddParticle_RAIN_SPLASH_BIGGROW(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

CParticleObject *AddObject_PED_SPLASH(unsigned short Type, CVector const &vecPos, CVector const &vecTarget, float fSize, unsigned int nLifeTime, RwRGBA const &Color, unsigned char bCanRemove)
{
	if ( CParticleEx::GetCurrentParticle() == PS_PS2 )
	{
		CRGBA c(0, 0, 0, 0);
		return CParticleObject::AddObject(Type, vecPos, vecTarget, fSize, nLifeTime, c, bCanRemove);
	}
	else
		return CParticleObject::AddObject(Type, vecPos, vecTarget, fSize, nLifeTime, Color, bCanRemove);
}

struct ProcessPedBuoyancyHook
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
			return;
		
		//Stack Start
		float &fWaterLevel = *(float *)(regs.cpu.esp + 0x110 - 0x7C);
		//Stack End
		fWaterLevel += 0.5f;
	}
	
};

void *ProcessPedBuoyancy_ptr = GetInlineHookPtr<ProcessPedBuoyancyHook>();
int jmp_0x4C85E7 = AddressByVersion(0x4C85E7, 0x4C8687, 0x4C8617);
void NAK Patch_PedProcessBuoyancy()
{
	__asm
	{
		call    ProcessPedBuoyancy_ptr
		mov     eax, [esp+110h-7Ch]
		jmp     jmp_0x4C85E7
	}
}

struct ProcessPedBuoyancyHook2
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
			return;
		
		//Stack Start
		CPed *This = (CPed *)(regs.cpu.ebp);
		CVector &vel = *(CVector *)(regs.cpu.esp + 0x12C - 0x78);
		//Stack End
		
		vel = This->m_vecVelocity * 0.1f;
		vel.z = 0.18f;
	}
	
};

void *ProcessPedBuoyancy2_ptr = GetInlineHookPtr<ProcessPedBuoyancyHook2>();
int jmp_0x4C8633 = AddressByVersion(0x4C8633, 0x4C86D3, 0x4C8663);
void NAK Patch_PedProcessBuoyancy2()
{
	__asm
	{
		mov     dword ptr [esp+12Ch-78h+8h], 3DCCCCCDh
		call    ProcessPedBuoyancy2_ptr
		jmp     jmp_0x4C8633
	}
}

struct ProcessPedBuoyancyHook3
{
	void operator()(reg_pack& regs)
	{
		int &nGenerateRaindrops = *(int*)AddressByVersion(0x62E01C, 0x62E01C, 0x63E01C);
		int &nGenerateWaterCircles = *(int*)AddressByVersion(0x62E024, 0x62E024, 0x63E024);
		
		if ( CParticleEx::GetCurrentParticle() == PS_PS2 )
		{
			nGenerateRaindrops = CTimer::m_snTimeInMilliseconds + 300;
			nGenerateWaterCircles = CTimer::m_snTimeInMilliseconds + 60;
			
		}
		else
		{
			nGenerateRaindrops = CTimer::m_snTimeInMilliseconds + 80;
			nGenerateWaterCircles = CTimer::m_snTimeInMilliseconds + 100;
		}
	}
	
};

void *ProcessPedBuoyancy3_ptr = GetInlineHookPtr<ProcessPedBuoyancyHook3>();
int jmp_0x4C8655 = AddressByVersion(0x4C8655, 0x4C86F5, 0x4C8685);
void NAK Patch_PedProcessBuoyancy3()
{
	__asm
	{
		call ProcessPedBuoyancy3_ptr
		jmp jmp_0x4C8655
	}
}

struct PlayFootStepsHook
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
			return;
		
		//Stack Start
		CPed *This = (CPed *)(regs.cpu.ebx);
		//Stack End
		
		CParticle::AddParticle(PARTICLE_PED_SPLASH,
				((This->m_sCoords.GetTranslate() - 0.3f * This->m_sCoords.at) + (0.3f * This->m_sCoords.up))
					- CVector(0.0f, 0.0f, 1.2f),
				CVector
				(
					0.45f * This->m_vecVelocity,
					CGeneral::GetRandomNumberInRange(0.03f, 0.05f)
				),
				NULL,
				0.0f,
				CRGBA(155, 185, 155, 255),
				0,
				0,
				0,
				0);
	}
};

void *PlayFootSteps_ptr = GetInlineHookPtr<PlayFootStepsHook>();
int jmp_0x4CCD19 = AddressByVersion(0x4CCD19, 0x4CCDB9, 0x4CCD49);
void NAK Patch_PlayFootSteps()
{
	__asm
	{
		and     eax, 0FFFFh
		
		call    PlayFootSteps_ptr
		
		jmp    jmp_0x4CCD19
	}
}

void _particleProduceFootSplash(CPed *pPed, CVector const &vecBasePos, Float fSize, Int32 nCycles)
{
	CRGBA c1(32, 32, 32, 32);
	CRGBA c2(0, 0, 0, 0);
	
	if ( CParticleEx::GetCurrentParticle() == PS_PS2 )
	{
		for ( Int32 i = 0; i < nCycles; i++ )
		{
			CVector vecPos = vecBasePos;
			vecPos.x += CGeneral::GetRandomNumberInRange(-0.2f, 0.2f);
			vecPos.y += CGeneral::GetRandomNumberInRange(-0.2f, 0.2f);
	
			CParticle::AddParticle(PARTICLE_RAIN_SPLASHUP,
					vecPos,
					CVector(0.0f, 0.0f, 0.0f),
					NULL,
					fSize, //0.15f
					c2,
					0,
					0,
					(UInt16)CGeneral::GetRandomNumber() & 1,
					200);
		}
	}
	else
	{
		for ( Int32 i = 0; i < nCycles; i++ )
		{
			CVector vecPos = vecBasePos;
			vecPos.x += CGeneral::GetRandomNumberInRange(-0.1f, 0.1f);
			vecPos.y += CGeneral::GetRandomNumberInRange(-0.1f, 0.1f);
	
			CParticle::AddParticle(PARTICLE_RAIN_SPLASHUP,
					vecPos,
					-0.05f * pPed->m_sCoords.up,
					NULL,
					fSize,
					c1,
					0,
					0,
					(UInt16)CGeneral::GetRandomNumber() & 1,
					200);
		}
	}
}

struct PlayFootStepsHook2
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
			return;
		
		//Stack Start
		CPed *This = (CPed *)(regs.cpu.ebx);
		//CVector &pointsOut = *(CVector *)(regs.cpu.esp + 0x18);
		CVector &pointsOut = *(CVector *)(regs.cpu.esp + 0x0A8 - 0x90);
		//Stack End
		
		
		_particleProduceFootSplash(This, pointsOut, 0.15f, 4);
	}
	
};

void *PlayFootSteps2_ptr = GetInlineHookPtr<PlayFootStepsHook2>();
int jmp_0x4CCDD7 = AddressByVersion(0x4CCDD7, 0x4CCE77, 0x4CCE07);
void NAK Patch_PlayFootSteps2()
{
	__asm
	{
		call PlayFootSteps2_ptr
		jmp   jmp_0x4CCDD7
	}
}

// Converted from static void __cdecl particleProduceFootDust(CPed *pPed, CVector const &vecBasePos, float fSize, int nCycles) 0x4CC5C0
void particleProduceFootDust(CPed* pPed, CVector const& vecBasePos, float fSize, int nCycles)
{
	((void (__cdecl *)(CPed*, CVector const&, float, int))AddressByVersion(0x4CC5C0, 0x4CC660, 0x4CC5F0))(pPed, vecBasePos, fSize, nCycles);
}

struct PlayFootStepsHook3
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
			return;
		
		//Stack Start
		CPed *This = (CPed *)(regs.cpu.ebx);
		//Stack End
		
		CAnimBlendAssociation *asoc = NULL;
		
		if ( This->IsPlayer() )
		{
			asoc = RpAnimBlendClumpGetAssociation(This->m_pRwClump, 5);
			
			if ( asoc == NULL )
				asoc = RpAnimBlendClumpGetAssociation(This->m_pRwClump, 6);
		}
		
		if ( asoc != NULL && asoc->m_fBlendAmount > 0.1f )
		{
			{
				CVector pos = GetPedNodePosition(This, 9);
	
				pos.z -= 0.1f;
				pos += 0.2f * This->m_sCoords.up;
				
				particleProduceFootDust(This, pos, 0.02f, 1);
				
			}

			{
				
				CVector pos = GetPedNodePosition(This, 10);

				pos.z -= 0.1f;
				pos += 0.2f * This->m_sCoords.up;
				
				particleProduceFootDust(This, pos, 0.02f, 1);
			}
		}
	
	}
};

void *PlayFootSteps3_ptr = GetInlineHookPtr<PlayFootStepsHook3>();
int jmp_0x4CC788 = AddressByVersion(0x4CC788, 0x4CC828, 0x4CC7B8);
int jmp_0x4CCBB7 = AddressByVersion(0x4CCBB7, 0x4CCC57, 0x4CCBE7);
void NAK Patch_PlayFootSteps3()
{
	__asm
	{
		call    PlayFootSteps3_ptr
		
		test    ebp, ebp
		jz      loc_4CCBB7
		jmp     jmp_0x4CC788

loc_4CCBB7:
		jmp     jmp_0x4CCBB7
	}
}

struct UpdateClosePedSplash
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
			return;
		
		//Stack Start
		CParticleObject *This = (CParticleObject *)(regs.cpu.ebx);
		//Stack End
		
		
		for ( Int32 i = -2; i < 2; i++ )
		{
			CVector vecPos;
			CVector vecTarget;
		
			vecPos = This->m_sCoords.pos;
			
			vecPos += CVector
						(
							-0.75f,
							0.5f * Float(i),
							0.0f
						);
		
						
			vecTarget = This->m_vecTarget;
		
			vecTarget += CVector
							(
								-1.5     * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								Float(i) * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								CGeneral::GetRandomNumberInRange(0.03f, 0.06f)
							);
			
			CParticle::AddParticle(PARTICLE_PED_SPLASH, vecPos, vecTarget, NULL, 0.8, This->m_Color, 0, 0, 0, 0);
		
			
			
			vecPos = This->m_sCoords.pos;
			
			vecPos += CVector
						(
							0.75f,
							0.5f * Float(i),
							0.0f
						);
		
		
			vecTarget = This->m_vecTarget;
			
			vecTarget += CVector
							(
								1.5f     * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								Float(i) * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								CGeneral::GetRandomNumberInRange(0.03f, 0.06f)
							);
			
			CParticle::AddParticle(PARTICLE_PED_SPLASH, vecPos, vecTarget, NULL, 0.8f, This->m_Color, 0, 0, 0, 0);
		
			
		
			vecPos = This->m_sCoords.pos;
		
			vecPos += CVector
						(
							0.5f * Float(i),
							-0.75,
							0.0f
						);
			
		
			vecTarget = This->m_vecTarget;
		
			vecTarget += CVector
							(
								Float(i) * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								-1.5f    * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								CGeneral::GetRandomNumberInRange(0.03f, 0.06f)
							);
		
			CParticle::AddParticle(PARTICLE_PED_SPLASH, vecPos, vecTarget, NULL, 0.8f, This->m_Color, 0, 0, 0, 0);
		
			
			vecPos = This->m_sCoords.pos;
		
			vecPos += CVector
						(
							0.5f * Float(i),
							0.75,
							0.0f
						);
			
			
			vecTarget = This->m_vecTarget;
		
			vecTarget += CVector
							(
								Float(i) * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								1.5f     * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								CGeneral::GetRandomNumberInRange(0.03f, 0.06f)
							);
		
			CParticle::AddParticle(PARTICLE_PED_SPLASH, vecPos, vecTarget, NULL, 0.8f, This->m_Color, 0, 0, 0, 0);
		}
						
		
		for ( Int32 i = 0; i < 4; i++ )	
		{
			CVector vecPos = This->m_sCoords.pos;
			
			vecPos += CVector
						(
							CGeneral::GetRandomNumberInRange(-1.5f, 1.5f),
							CGeneral::GetRandomNumberInRange(-1.5f, 1.5f),
							CGeneral::GetRandomNumberInRange(0.03f, 0.06f)
						);
		
			CVector vecTarget = This->m_vecTarget;
		
			CParticle::AddParticle(PARTICLE_PED_SPLASH, vecPos, vecTarget, NULL, 0.8f, This->m_Color, 0, 0, 0, 0);
		}
	}
};

void *UpdateClosePedSplash_ptr = GetInlineHookPtr<UpdateClosePedSplash>();
int jmp_0x4BD4B3 = AddressByVersion(0x4BD4B3, 0x4BD5A3, 0x4BD533);
void NAK Patch_UpdateClosePedSplash()
{
	__asm
	{
		call    UpdateClosePedSplash_ptr
		
		lea     edi, dword ptr [esp+448h-1D8h]
		jmp     jmp_0x4BD4B3
	}
}

void * __cdecl AddParticle_BOAT_SPLASH(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CParticleEx::GetCurrentParticle() == PS_PS2 )
		return NULL;
	else
		return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);

}

// for waterdrops
void * __cdecl AddParticle_BOAT_SPLASH_WD(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	CParticleEx::AddExtendedDroplets(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	return AddParticle_BOAT_SPLASH(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

void * __cdecl AddParticle_BOAT_WAKE(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	if ( CParticleEx::GetCurrentParticle() == PS_PS2 )
	{
		CVector pos = vecPos;
		pos.z = -0.3f;
		return CParticleEx::AddParticle(type, pos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	}
	else
		return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

// for waterdrops
void * __cdecl AddParticle_BOAT_WAKE_WD(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	CParticleEx::AddExtendedDroplets(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	return AddParticle_BOAT_WAKE(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
}

struct BoatProcessControl
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
			return;
		
		//Stack Start
		CBoat *This = (CBoat *)(regs.cpu.ebp);
		//CRGBA & color = *(CRGBA *)(regs.cpu.esp + 0x2EC + 0x22C);
		//CRGBA & color = *(CRGBA *)(regs.cpu.esp + 0x2EC - 0x22C);
		CRGBA color(0, 0, 0, 0);
		//Stack End

		if ( This->field_300 > 120 )
		{
			Float fSpeed = This->m_vecVelocity.Magnitude();
			Float fSize = 0.2f * (0.005f * Float(This->field_300));
			
			CVector vecPos;
			CVector vecTarget;

			vecTarget = 0.3f * This->m_vecVelocity;
			vecTarget.z += 0.05f * fSpeed;
			vecTarget += fSpeed * (0.5f * This->m_sCoords.right);

			vecPos = (This->m_sCoords.GetTranslate() + This->m_vecMoveForce) + (1.5f * This->m_sCoords.right);
			
			CParticle::AddParticle(PARTICLE_BOAT_SPLASH, vecPos, vecTarget, NULL, fSize, color, 0, 0, 0, 0);

			vecTarget = 0.3f * This->m_vecVelocity;
			vecTarget.z += 0.05f * fSpeed;
			vecTarget -= fSpeed * (0.5f * This->m_sCoords.right);

			vecPos = (This->m_sCoords.GetTranslate() + This->m_vecMoveForce) - (1.5f * This->m_sCoords.right);
			
			CParticle::AddParticle(PARTICLE_BOAT_SPLASH, vecPos, vecTarget, NULL, fSize, color, 0, 0, 0, 0);
		}
	}
};

void *BoatProcessControl_ptr = GetInlineHookPtr<BoatProcessControl>();
int jmp_0x541775 = AddressByVersion(0x541775, 0x5419B5, 0x541965);
void NAK Patch_BoatProcessControl()
{
	__asm
	{
		call    BoatProcessControl_ptr

		fld     dword ptr [ebp+2ECh]
		jmp     jmp_0x541775
	}
}

struct UpdateCloseCarSplash
{
	void operator()(reg_pack& regs)
	{
		if ( CParticleEx::GetCurrentParticle() != PS_PS2 )
			return;
		
		//Stack Start
		CParticleObject *This = (CParticleObject *)(regs.cpu.ebx);
		//Stack End

		for ( Int32 i = -3; i < 4; i++ )
		{
			CVector vecPos;
			CVector vecTarget;


			vecPos = This->m_sCoords.pos;
			
			vecPos += CVector
						(
							-1.5f,
							0.5f * Float(i),
							0.0f
						);
			

			vecTarget = This->m_vecTarget;

			vecTarget += CVector
							(
								-3.0f * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								Float(i) * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								CGeneral::GetRandomNumberInRange(0.03f, 0.06f)
							);
				
			CParticle::AddParticle(PARTICLE_CAR_SPLASH, vecPos, vecTarget, NULL, 0.0f, This->m_Color, 0, 0, 0, 0);
		
		
			vecPos = This->m_sCoords.pos;
			
			vecPos += CVector
						(
							1.5f,
							0.5f * Float(i),
							0.0f
						);
			

			vecTarget = This->m_vecTarget;
			
			vecTarget += CVector
							(
								3.0f * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								Float(i) * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								CGeneral::GetRandomNumberInRange(0.03f, 0.06f)
							);
			
			CParticle::AddParticle(PARTICLE_CAR_SPLASH, vecPos, vecTarget, NULL, 0.0f, This->m_Color, 0, 0, 0, 0);
		
		
			vecPos = This->m_sCoords.pos;
		
			vecPos += CVector
						(
							0.5f * Float(i),
							-1.5f,
							0.0f
						);


			vecTarget = This->m_vecTarget;
		
			vecTarget += CVector
							(
								Float(i) * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								-3.0f * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								CGeneral::GetRandomNumberInRange(0.03f, 0.06f)
							);
		
			CParticle::AddParticle(PARTICLE_CAR_SPLASH, vecPos, vecTarget, NULL, 0.0f, This->m_Color, 0, 0, 0, 0);
		
		
			vecPos = This->m_sCoords.pos;
		
			vecPos += CVector
						(
							0.5f * Float(i),
							1.5f,
							0.0f
						);


			vecTarget = This->m_vecTarget;
		
			vecTarget += CVector
							(
								Float(i) * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								3.0f * CGeneral::GetRandomNumberInRange(0.001f, 0.006f),
								CGeneral::GetRandomNumberInRange(0.03f, 0.06f)
							);
			
			CParticle::AddParticle(PARTICLE_CAR_SPLASH, vecPos, vecTarget, NULL, 0.0f, This->m_Color, 0, 0, 0, 0);
		}
		
		for ( Int32 i = 0; i < 8; i++ )
		{
			CVector vecPos;
			CVector vecTarget;
			
			vecPos = This->m_sCoords.pos;
		
			vecPos.x += CGeneral::GetRandomNumberInRange(-3.0f, 3.0f);
			vecPos.y += CGeneral::GetRandomNumberInRange(-3.0f, 3.0f);

			vecTarget = This->m_vecTarget;
			
			vecTarget.z += CGeneral::GetRandomNumberInRange(0.03f, 0.06f);
		
			CParticle::AddParticle(PARTICLE_CAR_SPLASH, vecPos, vecTarget, NULL, 0.0f, This->m_Color, 0, 0, 0, 0);
		}
	}
};

void *UpdateCloseCarSplash_ptr = GetInlineHookPtr<UpdateCloseCarSplash>();
int jmp_0x4BE27D = AddressByVersion(0x4BE27D, 0x4BE36D, 0x4BE2FD);
void NAK Patch_UpdateCloseCarSplash()
{
	__asm
	{
		call    UpdateCloseCarSplash_ptr
		
		lea     edi, dword ptr [esp+448h-18Ch] 
		
		jmp     jmp_0x4BE27D
	}
}

void _DarkSpotAddPermanentShadow(unsigned char ShadowType, RwTexture* pTexture, CVector* pPosn, float fX1, float fY1, float fX2, float fY2, short nTransparency, unsigned char nRed, unsigned char nGreen, unsigned char nBlue, float fZDistance, unsigned int nTime, float fScale)
{
	if ( CSettings::Get().m_bDarkSpotsBugFix )
		CShadows::AddPermanentShadow(ShadowType, pTexture, pPosn, fX1, fY1, fX2, fY2, nTransparency, nRed, nGreen, nBlue, fZDistance, 30000, 1.0f);
	else
		CShadows::AddPermanentShadow(ShadowType, pTexture, pPosn, fX1, fY1, fX2, fY2, nTransparency, nRed, nGreen, nBlue, fZDistance, nTime, fScale);
}

void _AddJetExplosion(CVector const &vecPos, Float fPower, Float fSize)
{
	if ( CSettings::Get().m_bVCJet )
		CParticle::AddJetExplosion(vecPos, (CGeneral::GetRandomNumber() & 7) / 7.0f + 1.5f, 0.5f);
	else
		CParticle::AddJetExplosion(vecPos, fPower, fSize);
}

// for waterdrops
void * __cdecl AddParticle_WD(int type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed, Int32 nRotation, Int32 nCurFrame, Int32 nLifeSpan)
{
	CParticleEx::AddExtendedDroplets(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
	return CParticleEx::AddParticle(type, vecPos, vecDir, pEntity, fSize, color, nRotationSpeed, nRotation, nCurFrame, nLifeSpan);
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
	
	DMAudio.PlayFrontEndSound(160, 0);
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
	CParticleArray::ReSize(CSettings::Get().m_nParticleLimit);
	CParticleArray::ReInitArrays();
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

void onJetPos()
{
	if ( CSettings::Get().m_bVCJet )
		CParticleEx::SetVCJetPos();
	else
		CParticleEx::SetPS2JetPos(CSettings::Get().m_bPS2JetPos);
}

void OnPS2Rain()
{
	CParticleEx::SetPS2Rain(CSettings::Get().m_bPS2Rain);
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
		
		DebugMenuAddVarBool8("ParticleEx", "[Xbox]   Fix Molotov Bug", (int8_t *)&CSettings::Get().m_bFixMolotovBug, NULL);
		DebugMenuAddVarBool8("ParticleEx", "[PS2/PC] Fix flame5 Bug", (int8_t *)&CSettings::Get().m_bFixFlame5Bug, onFixFlame5Bug);
		DebugMenuAddVarBool8("ParticleEx", "[PS2]    Use Alternative Car Splash", (int8_t *)&CSettings::Get().m_bAltPS2Carsplash, NULL);
		DebugMenuAddVarBool8("ParticleEx", "[PS2]    Use WHEEL_WATER Particle", (int8_t *)&CSettings::Get().m_bCorrectWheelsRainWaterSplash, NULL);
		DebugMenuAddVarBool8("ParticleEx", "[ANY]    Use PS2 Puddles Surface Physics", (int8_t *)&CSettings::Get().m_bUsePS2CarPuddlePhysics, NULL);
		DebugMenuAddVarBool8("ParticleEx", "[ANY]    Explosion Dark Spot Fix", (int8_t *)&CSettings::Get().m_bDarkSpotsBugFix, NULL);
		DebugMenuAddVarBool8("ParticleEx", "[ANY]    PS2 Jet Explosion", (int8_t *)&CSettings::Get().m_bPS2JetPos, onJetPos);
		DebugMenuAddVarBool8("ParticleEx", "[ANY]    Vice City Jet Explosion", (int8_t *)&CSettings::Get().m_bVCJet, onJetPos);
		DebugMenuAddVarBool8("ParticleEx", "[ANY]    PS2 Rain", (int8_t *)&CSettings::Get().m_bPS2Rain, OnPS2Rain);
		
		DebugMenuAddUInt32("ParticleEx", "Particles Limit", (uint32_t *)&CSettings::Get().m_nParticleLimit, onParticleLimitChange, 100, 100, 2000000000, NULL);
	
		DebugMenuAddCmd("ParticleEx", "Reload particle.cfg", QUICK_Button<CParticleEx::ReloadConfig, CParticleEx::ClearAllParticles, NULL>);
		DebugMenuAddCmd("ParticleEx", "Clear Particles", QUICK_Button<CParticleEx::ClearParticles, NULL, NULL>);
		
		DebugMenuAddCmd("ParticleEx|Settings", "Save Settings", QUICK_Button<SaveSet, NULL, NULL>);
		DebugMenuAddCmd("ParticleEx|Settings", "ReLoad Settings", QUICK_Button<ReLoadSet, NULL, NULL>);
		DebugMenuAddCmd("ParticleEx|Settings", "Reset Settings", QUICK_Button<ResetSet, NULL, NULL>);
		
	
		DebugMenuAddCmd("ParticleEx|PObject", "Update PObjects", QUICK_Button<UpdatePObjects, NULL, NULL>);		
		DebugMenuAddCmd("ParticleEx|PObject", "Reset PObjects", QUICK_Button<CParticleEx::ResetPObjects, NULL, NULL>);

		DebugMenuAddCmd("ParticleEx|PObject", "Save PObjects", QUICK_Button<CPObjectMgr::Save, NULL, NULL>);
		DebugMenuAddCmd("ParticleEx|PObject", "Load PObjects", QUICK_Button<CPObjectMgr::Load, NULL, NULL>);
	}
}

// hack for neowaterdrops
void delayedPatches()
{
	void *func = (void *)CPatch::TranslateCallAddr(AddressByVersion(0x4BD72B, 0x4BD81B, 0x4BD7AB));
	
	unsigned int checkaddrs[] = 
	{
		AddressByVersion(0x4BD72B, 0x4BD81B, 0x4BD7AB),
		AddressByVersion(0x4BD8FF, 0x4BD9EF, 0x4BD97F),
		AddressByVersion(0x4BDAD3, 0x4BDBC3, 0x4BDB53),
		AddressByVersion(0x4BDC7D, 0x4BDD6D, 0x4BDCFD),
		AddressByVersion(0x4BDE56, 0x4BDF46, 0x4BDED6),
		AddressByVersion(0x4BDFBD, 0x4BE0AD, 0x4BE03D),
		AddressByVersion(0x4BE11E, 0x4BE20E, 0x4BE19E),
		AddressByVersion(0x4BE25A, 0x4BE34A, 0x4BE2DA),
		AddressByVersion(0x4BE504, 0x4BE5F4, 0x4BE584),
		AddressByVersion(0x4BE6CE, 0x4BE7BE, 0x4BE74E),
		AddressByVersion(0x4BE898, 0x4BE988, 0x4BE918),
		AddressByVersion(0x4BEA44, 0x4BEB34, 0x4BEAC4),
		AddressByVersion(0x4BEBF6, 0x4BECE6, 0x4BEC76),
		AddressByVersion(0x4BED32, 0x4BEE22, 0x4BEDB2),
		AddressByVersion(0x4BEE68, 0x4BEF58, 0x4BEEE8),
		AddressByVersion(0x4BEF79, 0x4BF069, 0x4BEFF9),
		AddressByVersion(0x4CCD69, 0x4CCE09, 0x4CCD99),
		AddressByVersion(0x531369, 0x5315A9, 0x531539),
		AddressByVersion(0x540892, 0x540AD2, 0x540A82),
		AddressByVersion(0x540855, 0x540A95, 0x540A45),
		AddressByVersion(0x540A35, 0x540C75, 0x540C25),
		AddressByVersion(0x5414A8, 0x5416E8, 0x541698),
		AddressByVersion(0x5414D8, 0x541718, 0x5416C8),
		AddressByVersion(0x541737, 0x541977, 0x541927),
		AddressByVersion(0x541767, 0x5419A7, 0x541957),
		AddressByVersion(0x4C87DF, 0x4C887F, 0x4C880F),
		AddressByVersion(0x530EF0, 0x531130, 0x5310C0),
		AddressByVersion(0x540744, 0x540984, 0x540934),
		AddressByVersion(0x540924, 0x540B64, 0x540B14)
	};
	
	bool wdfound = true;
	
	for ( int i = 0; i < ARRAY_SIZE(checkaddrs); i++ )
	{
		if ( (void *)CPatch::TranslateCallAddr(checkaddrs[i]) != func )
		{
			wdfound = false;
			break;
		}
	}
	
	if ( wdfound )
	{
		CParticleEx::AddExtendedDroplets = (void (__cdecl *)(int, CVector const &, CVector const &, CEntity *, Float, RwRGBA const &, Int32, Int32, Int32, Int32))func;
		CParticleEx::m_bWaterdropsInstalled = true;	
		
		CPatch::RedirectCall(AddressByVersion(0x4BD72B, 0x4BD81B, 0x4BD7AB), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BD8FF, 0x4BD9EF, 0x4BD97F), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BDAD3, 0x4BDBC3, 0x4BDB53), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BDC7D, 0x4BDD6D, 0x4BDCFD), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BDE56, 0x4BDF46, 0x4BDED6), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BDFBD, 0x4BE0AD, 0x4BE03D), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BE11E, 0x4BE20E, 0x4BE19E), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BE25A, 0x4BE34A, 0x4BE2DA), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BE504, 0x4BE5F4, 0x4BE584), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BE6CE, 0x4BE7BE, 0x4BE74E), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BE898, 0x4BE988, 0x4BE918), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BEA44, 0x4BEB34, 0x4BEAC4), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BEBF6, 0x4BECE6, 0x4BEC76), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BED32, 0x4BEE22, 0x4BEDB2), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BEE68, 0x4BEF58, 0x4BEEE8), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4BEF79, 0x4BF069, 0x4BEFF9), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x4CCD69, 0x4CCE09, 0x4CCD99), AddParticle_PS2Dummy_WD);
		CPatch::RedirectCall(AddressByVersion(0x531369, 0x5315A9, 0x531539), AddParticle_PS2Dummy_WD);
		
		CPatch::RedirectCall(AddressByVersion(0x540892, 0x540AD2, 0x540A82), AddParticle_BOAT_WAKE_WD);
		
		CPatch::RedirectCall(AddressByVersion(0x540855, 0x540A95, 0x540A45), AddParticle_BOAT_SPLASH_WD);
		CPatch::RedirectCall(AddressByVersion(0x540A35, 0x540C75, 0x540C25), AddParticle_BOAT_SPLASH_WD);
		CPatch::RedirectCall(AddressByVersion(0x5414A8, 0x5416E8, 0x541698), AddParticle_BOAT_SPLASH_WD);
		CPatch::RedirectCall(AddressByVersion(0x5414D8, 0x541718, 0x5416C8), AddParticle_BOAT_SPLASH_WD);
		CPatch::RedirectCall(AddressByVersion(0x541737, 0x541977, 0x541927), AddParticle_BOAT_SPLASH_WD);
		CPatch::RedirectCall(AddressByVersion(0x541767, 0x5419A7, 0x541957), AddParticle_BOAT_SPLASH_WD);
		
		CPatch::RedirectCall(AddressByVersion(0x4C87DF, 0x4C887F, 0x4C880F), AddParticle_RAIN_SPLASH_BIGGROW_WD);
		
		CPatch::RedirectCall(AddressByVersion(0x530EF0, 0x531130, 0x5310C0), AddParticle_WD);
		CPatch::RedirectCall(AddressByVersion(0x540744, 0x540984, 0x540934), AddParticle_WD);
		CPatch::RedirectCall(AddressByVersion(0x540924, 0x540B64, 0x540B14), AddParticle_WD);
	}
}

struct tRainStreak
{
  CVector position;
  CVector direction;
  unsigned int timer;
};

VALIDATE_SIZE(tRainStreak, 0x1C);

const int NUM_RAIN_STREAKS = 50;
tRainStreak Streaks[NUM_RAIN_STREAKS];

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		PluginErrorCheck(PLUGINPREF_VERSION_ANY | PLUGINPREF_CHECK_ASI_LOADER);

		CParticleArray::Initialise();
		CParticleEx::SetParticleSwitch(CParticleEx::GetCurrentParticle());

		CHook::Register(F_ASICheck, CheckAsi);
		CHook::Register(F_ASICheck, delayedPatches);
		
		{
			CPatch::RedirectCall(AddressByVersion(0x48C5C1, 0x48C6C1, 0x48C651), CParticleEx::ReloadConfig);
			CPatch::RedirectCall(AddressByVersion(0x50C575, 0x50C665, 0x50C5F5), CParticleEx::ReloadConfig); 
			CPatch::RedirectCall(AddressByVersion(0x59152A, 0x5917EA, 0x5916DA), CParticleEx::ReloadConfig); 
			
			CPatch::RedirectCall(AddressByVersion(0x48C000, 0x48C0F0, 0x48C080), CParticleEx::Initialise); 
			
			CPatch::RedirectCall(AddressByVersion(0x48C48C, 0x48C57C, 0x48C50C), CParticleEx::Shutdown); 
			
			CPatch::RedirectCall(AddressByVersion(0x48C92C, 0x48CA2C, 0x48C9BC), CParticleEx::Update); 
			
			CPatch::RedirectCall(AddressByVersion(0x48E0BD, 0x48E17D, 0x48E10D), CParticleEx::Render);
			
			CPatch::RedirectCall(AddressByVersion(0x5231FB, 0x52343B, 0x5233CB), CParticleEx::RemovePSystem);
	
			CPatch::RedirectJump(AddressByVersion(0x50D190, 0x50D380, 0x50D310), __AddParticle);
		}
		
		///////////////////////////////////////////////////////////////////////////////////////////
		
		CPatch::RedirectJump(AddressByVersion(0x4BFC78, 0x4BFD68, 0x4BFCF8), __LoadPObjects);
		
		CPatch::RedirectCall(AddressByVersion(0x561FC2, 0x5620F2, 0x5620A2), CParticleEx::GenerateFlameThrowerParticles);
		
		//remove pobject CARFLAME_SMOKE
		{
			CPatch::RedirectCall(AddressByVersion(0x4BCD6C, 0x4BCE5C, 0x4BCDEC), AddParticle_DUMMY);
			CPatch::RedirectCall(AddressByVersion(0x4BCF4E, 0x4BD03E, 0x4BCFCE), AddParticle_DUMMY);
		}
		
		//fix POBJECT_BIG_FIRE
		{
			CPatch::RedirectCall(AddressByVersion(0x4BCE24, 0x4BCF14, 0x4BCEA4), AddParticle_BIG_FIRE);
		}
		
		//CFire Tweak
		{
			CPatch::SetPointer(AddressByVersion(0x55956C, 0x55969C, 0x55964C) + 2, &CParticleEx::m_fFireSize);
			
			CPatch::RedirectCall(AddressByVersion(0x479BB0, 0x479BB0, 0x479BB0), AddParticle_DUMMY);
			CPatch::RedirectCall(AddressByVersion(0x479BFB, 0x479BFB, 0x479BFB), AddParticle_DUMMY);
			CPatch::RedirectJump(AddressByVersion(0x479B48, 0x479B48, 0x479B48), Patch_ProcessFire);
		}
		
		// Vehicle Smoke Tweak
		{
			CPatch::SetPointer(AddressByVersion(0x5346E3, 0x534923, 0x5348B3) + 2, &CParticleEx::m_fSmokeSize);

			CPatch::RedirectCall(AddressByVersion(0x5345B6, 0x5347F6, 0x534786), AddParticle_DUMMY);
			CPatch::RedirectCall(AddressByVersion(0x5346BA, 0x5348FA, 0x53488A), AddParticle_DUMMY);		
			CPatch::RedirectJump(AddressByVersion(0x53454D, 0x53478D, 0x53471D), Patch_ProcessControll);
		}
		
		// ProcessBuoyancy
		{
			CPatch::RedirectCall(AddressByVersion(0x530D16, 0x530F56, 0x530EE6), AddObject_CAR_SPLASH_1);
			CPatch::RedirectJump(AddressByVersion(0x530CC2, 0x530F02, 0x530E92), Patch_ProcessBuoyancy1);
		}
		
		//ProcessBuoyancy, car PED_SPLASH
		{
			CPatch::RedirectCall(AddressByVersion(0x531369, 0x5315A9, 0x531539), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x531401, 0x531641, 0x5315D1), AddParticle_PS2Dummy);
			CPatch::RedirectCall(AddressByVersion(0x53142C, 0x53166C, 0x5315FC), PlayOneShot_PS2Dummy);
			CPatch::RedirectJump(AddressByVersion(0x531272, 0x5314B2, 0x531442), Patch_ProcessBuoyancy2);
			CPatch::RedirectJump(AddressByVersion(0x531150, 0x531390, 0x531320), Patch_ProcessBuoyancy3);
		}
		//
		CPatch::RedirectCall(AddressByVersion(0x535B03, 0x535D43, 0x535CD3), AddParticle_WATERSPRAY);

		////
		{
			CPatch::SetPointer(AddressByVersion(0x4C8880, 0x4C8920, 0x4C88B0) + 2, &CParticleEx::m_fPedRainSplashVal);
			
			CPatch::SetPointer(AddressByVersion(0x4C8751, 0x4C87F1, 0x4C8781) + 2, &CParticleEx::m_fPedRainSplashBiggrowMin);
			CPatch::SetPointer(AddressByVersion(0x4C87B4, 0x4C8854, 0x4C87E4) + 2, &CParticleEx::m_fPedRainSplashBiggrowMin);
			CPatch::SetPointer(AddressByVersion(0x4C874B, 0x4C87EB, 0x4C877B) + 2, &CParticleEx::m_fPedRainSplashBiggrowMax);
			CPatch::SetPointer(AddressByVersion(0x4C87A4, 0x4C8844, 0x4C87D4) + 2, &CParticleEx::m_fPedRainSplashBiggrowMax);
			CPatch::RedirectCall(AddressByVersion(0x4C87DF, 0x4C887F, 0x4C880F), AddParticle_RAIN_SPLASH_BIGGROW_WD);
			
			CPatch::RedirectJump(AddressByVersion(0x4C85E0, 0x4C8680, 0x4C8610), Patch_PedProcessBuoyancy);
			CPatch::RedirectJump(AddressByVersion(0x4C8628, 0x4C86C8, 0x4C8658), Patch_PedProcessBuoyancy2);
			CPatch::RedirectJump(AddressByVersion(0x4C8640, 0x4C86E0, 0x4C8670), Patch_PedProcessBuoyancy3);
			CPatch::RedirectCall(AddressByVersion(0x4C8633, 0x4C86D3, 0x4C8663), AddObject_PED_SPLASH);
			
			CPatch::RedirectCall(AddressByVersion(0x4C8387, 0x4C8427, 0x4C83B7), AddObject_PED_SPLASH);
		}
		////

		//Ped foot Splash
		{
			CPatch::RedirectCall(AddressByVersion(0x4CCD69, 0x4CCE09, 0x4CCD99), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4CCDBB, 0x4CCE5B, 0x4CCDEB), AddParticle_PS2Dummy);
			CPatch::RedirectJump(AddressByVersion(0x4CCD14, 0x4CCDB4, 0x4CCD44), Patch_PlayFootSteps);
			
	
			CPatch::RedirectCall(AddressByVersion(0x4CCB81, 0x4CCC21, 0x4CCBB1), _particleProduceFootSplash);		
			CPatch::RedirectJZ(AddressByVersion(0x4CC98B, 0x4CCA2B, 0x4CC9BB), Patch_PlayFootSteps2);
			CPatch::RedirectJump(AddressByVersion(0x4CC780, 0x4CC820, 0x4CC7B0), Patch_PlayFootSteps3);
		}
		
		//PObjects, again
		{
			CPatch::RedirectJump(AddressByVersion(0x4BD4AC, 0x4BD59C, 0x4BD52C), Patch_UpdateClosePedSplash);
			
			CPatch::RedirectCall(AddressByVersion(0x4BD6D2, 0x4BD7C2, 0x4BD752), AddParticle_PS2Dummy);
			CPatch::RedirectCall(AddressByVersion(0x4BD72B, 0x4BD81B, 0x4BD7AB), AddParticle_PS2Dummy_WDTRAP/*AddParticle_PS2Dummy_WD*/);
			CPatch::RedirectCall(AddressByVersion(0x4BD8A6, 0x4BD996, 0x4BD926), AddParticle_PS2Dummy);
			CPatch::RedirectCall(AddressByVersion(0x4BD8FF, 0x4BD9EF, 0x4BD97F), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BDA7A, 0x4BDB6A, 0x4BDAFA), AddParticle_PS2Dummy);
			CPatch::RedirectCall(AddressByVersion(0x4BDAD3, 0x4BDBC3, 0x4BDB53), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BDC24, 0x4BDD14, 0x4BDCA4), AddParticle_PS2Dummy);
			CPatch::RedirectCall(AddressByVersion(0x4BDC7D, 0x4BDD6D, 0x4BDCFD), AddParticle_PS2Dummy_WD);
			
			CPatch::RedirectCall(AddressByVersion(0x4BDE56, 0x4BDF46, 0x4BDED6), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BDFBD, 0x4BE0AD, 0x4BE03D), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BE11E, 0x4BE20E, 0x4BE19E), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BE25A, 0x4BE34A, 0x4BE2DA), AddParticle_PS2Dummy_WD);
		}
		
		//Boat
		{
			CPatch::RedirectCall(AddressByVersion(0x540855, 0x540A95, 0x540A45), AddParticle_BOAT_SPLASH_WD);
			CPatch::RedirectCall(AddressByVersion(0x540A35, 0x540C75, 0x540C25), AddParticle_BOAT_SPLASH_WD);
			CPatch::RedirectCall(AddressByVersion(0x5414A8, 0x5416E8, 0x541698), AddParticle_BOAT_SPLASH_WD);
			CPatch::RedirectCall(AddressByVersion(0x541737, 0x541977, 0x541927), AddParticle_BOAT_SPLASH_WD);
			
			//
			CPatch::RedirectCall(AddressByVersion(0x5414D8, 0x541718, 0x5416C8), AddParticle_BOAT_SPLASH_WD);
			CPatch::RedirectCall(AddressByVersion(0x541767, 0x5419A7, 0x541957), AddParticle_BOAT_SPLASH_WD);
			CPatch::RedirectJump(AddressByVersion(0x54176F, 0x5419AF, 0x54195F), Patch_BoatProcessControl);
			
			//
			CPatch::RedirectCall(AddressByVersion(0x540892, 0x540AD2, 0x540A82), AddParticle_BOAT_WAKE_WD);
			
			CPatch::SetPointer(AddressByVersion(0x5408FF, 0x540B3F, 0x540AEF) + 2, &CParticleEx::m_fBoatZAdd);
			CPatch::SetPointer(AddressByVersion(0x540918, 0x540B58, 0x540B08) + 2, &CParticleEx::m_fBoatFxSize);
			CPatch::SetPointer(AddressByVersion(0x5408BA, 0x540AFA, 0x540AAA) + 2, &CParticleEx::m_fBoatTargetMul);
			CPatch::SetPointer(AddressByVersion(0x5408E2, 0x540B22, 0x540AD2) + 2, &CParticleEx::m_fBoatTargetMul);
		}
		
		//PObject car splash
		{
			CPatch::RedirectJump(AddressByVersion(0x4BE276, 0x4BE366, 0x4BE2F6), Patch_UpdateCloseCarSplash);
			
			CPatch::RedirectCall(AddressByVersion(0x4BE4D3, 0x4BE5C3, 0x4BE553), AddParticle_PS2Dummy);
			CPatch::RedirectCall(AddressByVersion(0x4BE504, 0x4BE5F4, 0x4BE584), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BE69D, 0x4BE78D, 0x4BE71D), AddParticle_PS2Dummy);
			CPatch::RedirectCall(AddressByVersion(0x4BE6CE, 0x4BE7BE, 0x4BE74E), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BE867, 0x4BE957, 0x4BE8E7), AddParticle_PS2Dummy);
			CPatch::RedirectCall(AddressByVersion(0x4BE898, 0x4BE988, 0x4BE918), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BEA13, 0x4BEB03, 0x4BEA93), AddParticle_PS2Dummy);
			CPatch::RedirectCall(AddressByVersion(0x4BEA44, 0x4BEB34, 0x4BEAC4), AddParticle_PS2Dummy_WD);
			
			CPatch::RedirectCall(AddressByVersion(0x4BEBF6, 0x4BECE6, 0x4BEC76), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BED32, 0x4BEE22, 0x4BEDB2), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BEE68, 0x4BEF58, 0x4BEEE8), AddParticle_PS2Dummy_WD);
			CPatch::RedirectCall(AddressByVersion(0x4BEF79, 0x4BF069, 0x4BEFF9), AddParticle_PS2Dummy_WD);
		}
		
		CPatch::RedirectCall(AddressByVersion(0x559891, 0x5599C1, 0x559971), _AddJetExplosion);

		CPatch::RedirectCall(AddressByVersion(0x55923E, 0x55936E, 0x55931E), _DarkSpotAddPermanentShadow);
		
		{
			int RenderRainStreaksAddress = AddressByVersion(0x524550, 0x524790, 0x524720);
			
			CPatch::SetPointer(RenderRainStreaksAddress + 0x235 + 2, &Streaks[0].position.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x378 + 2, &Streaks[0].position.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x3CB + 2, &Streaks[0].position.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x3D1 + 2, &Streaks[0].position.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x412 + 2, &Streaks[0].position.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x418 + 2, &Streaks[0].position.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x472 + 2, &Streaks[0].position.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x478 + 2, &Streaks[0].position.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x249 + 2, &Streaks[0].position.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x398 + 2, &Streaks[0].position.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x3EB + 2, &Streaks[0].position.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x3F1 + 2, &Streaks[0].position.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x42D + 2, &Streaks[0].position.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x433 + 2, &Streaks[0].position.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x4A1 + 2, &Streaks[0].position.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x4A7 + 2, &Streaks[0].position.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x25D + 2, &Streaks[0].position.z);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x3B0 + 2, &Streaks[0].position.z);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x448 + 2, &Streaks[0].position.z);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x44E + 2, &Streaks[0].position.z);
			
			CPatch::SetPointer(RenderRainStreaksAddress + 0x1FC + 2, &Streaks[0].direction.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x22D + 2, &Streaks[0].direction.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x337 + 2, &Streaks[0].direction.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x370 + 2, &Streaks[0].direction.x);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x206 + 2, &Streaks[0].direction.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x243 + 2, &Streaks[0].direction.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x347 + 2, &Streaks[0].direction.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x390 + 2, &Streaks[0].direction.y);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x210 + 2, &Streaks[0].direction.z);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x257 + 2, &Streaks[0].direction.z);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x351 + 2, &Streaks[0].direction.z);
			
			CPatch::SetPointer(RenderRainStreaksAddress + 0x110 + 2, &Streaks[0].timer);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x157 + 2, &Streaks[0].timer);
			CPatch::SetPointer(RenderRainStreaksAddress + 0x4AD + 2, &Streaks[0].timer);
		}
	}
	return TRUE;
}