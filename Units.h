// Units.h: interface for the Units class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNITS_H__ED0350AB_7C61_4DE0_B059_9286299599BF__INCLUDED_)
#define AFX_UNITS_H__ED0350AB_7C61_4DE0_B059_9286299599BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Objects.h"
#include "classes.h"


typedef struct _WOWAura
{
	int SpellId;
	short stack;
	UINT secondLeft;
	UINT64 OwnerGUID;
	}WOWAura,*PWOWAura;

class Units : public Objects  
{
public:
	int BuffTimeLeft(int buff);
	bool HasBuff(int buff);
	bool IsTargetingMe();
	bool HasLivePet();
	UINT64 PetGUID();
	UINT64 SummonedBy();
	Units Pet();
	bool IsPlayer();
	bool IsCasting();
	int ChanneledCastingId();
	int CastingId();
	bool IsMoving();
	float Speed();
	bool IsFalling();
	bool IsMounted();
	bool IsFlying();
	DWORD Faction();
	int CreatureType();
	int MaxHp();
	int Hp();
	virtual char* Name(char* buffer);
	int Level();
	unsigned __int64 TargetGUID();
	Units(DWORD ptr);
	virtual ~Units();
	vector<int> GetBuffs();

public:
	virtual CString Name();
	bool IsInCombat();
	vector<WOWAura> GetAuras();

private:
	INT64 Flags();
};

#endif // !defined(AFX_UNITS_H__ED0350AB_7C61_4DE0_B059_9286299599BF__INCLUDED_)
