#include "PObjectMgr.h"
#include "ParticleEx.h"
#include <windows.h>
#include <fstream>

CParticleObject &getPObject(unsigned int i)
{
	//CParticleObject (&gPObjectArray)[MAX_PARTICLEOBJECTS] = *(CParticleObject(*)[MAX_PARTICLEOBJECTS])AddressByVersion(0x62A58C, 0x62A58C, 0x63A58C);
	
	CParticleObject **_gPObjectArray = (CParticleObject**)(AddressByVersion(0x4E89D0, 0x4E89F0, 0x4E8890) + 1);
	
	return (*_gPObjectArray)[i];
}

unsigned int getMaxPObjects()
{
	static unsigned int size = (unsigned int)-1;
	if ( size == (unsigned int)-1 )
	{
		size = 0;
		for ( CParticleObject *p= CParticleObject::pCloseListHead; p; p = p->m_pNext )
			size++;
		
		for ( CParticleObject *p= CParticleObject::pFarListHead; p; p = p->m_pNext )
			size++;
		
		for ( CParticleObject *p= CParticleObject::pUnusedListHead; p; p = p->m_pNext )
			size++;
	}
	
	return size;
}