// Units.cpp: implementation of the Units class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thunder3.h"
#include "classes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Units::Units(DWORD ptr):Objects(ptr)
{

}

Units::~Units()
{

}

unsigned __int64 Units::TargetGUID()
{
	return *(unsigned __int64*)(this->DescriptorFields()+UNIT_FIELD_TARGET*4);
}


int Units::Level()
{
	return *(int*)(this->DescriptorFields()+0xC0);
}

char* Units::Name(char* buffer)
{
	memset(buffer,0,sizeof(buffer));
	if(this->Type()==4)
	{
		return buffer;
	}
	//DWORD addr=*(DWORD*)(*(DWORD*)(this->BaseAddr()+UnitName1)+UnitName2);
	DWORD v1=*(DWORD*)(this->BaseAddr()+UnitName1);
	DWORD v2=*(DWORD*)(v1+UnitName2);
	return GetUTF8String(v2,buffer);
}


int Units::Hp()
{
	try
	{
		return *(int*)(this->DescriptorFields()+UNIT_FIELD_HEALTH*4);
	}
	catch(...)
	{
		return 0;
	}
}

int Units::MaxHp()
{
	try
	{
		return *(int*)(this->DescriptorFields()+UNIT_FIELD_MAXHEALTH*4);
	}
	catch(...)
	{
		return 0;
	}
}



int Units::CreatureType()
{
	DWORD v1=*(DWORD*)(this->BaseAddr()+CgUnitCGetCreatureType_Offset1);
	return *(int*)(v1+CgUnitCGetCreatureType_Offset2);
}

DWORD Units::Faction()
{
	return *(DWORD*)(this->DescriptorFields()+UNIT_FIELD_FACTIONTEMPLATE*4);
}

bool Units::IsFlying()
{
	DWORD v1=*(DWORD*)(*(DWORD*)(this->BaseAddr()+IsFlying_Pointer)+IsFlying_Offset);
	return (v1&IsFlying_Mask)!=0;
	
}

bool Units::IsMounted()
{
	try
	{
		int mountId=*(int*)(this->DescriptorFields()+UNIT_FIELD_MOUNTDISPLAYID*4);
		return mountId!=0;
	}
	catch(...)
	{
		return false;
	}
}

bool Units::IsFalling()
{
	DWORD v1=*(DWORD*)(*(DWORD*)(this->BaseAddr()+IsFalling_Pointer)+IsFalling_Offset);
	return (v1&IsFalling_Mask)!=0;
}



float Units::Speed()
{
	DWORD v1=*(float*)(*(DWORD*)(this->BaseAddr()+UnitSpeed_Pointer1)+UnitSpeed_Pointer2);
	return v1;
}

bool Units::IsMoving()
{
	return Speed()>0;
}

int Units::CastingId()
{
	try
	{
		DWORD v1=*(DWORD*)(this->BaseAddr()+CastingInfo_IsCasting);
		return *(int*)(v1);
	}
	catch(...)
	{
		return 0;
	}
}

int Units::ChanneledCastingId()
{
	try
	{
		DWORD v1=*(DWORD*)(this->BaseAddr()+CastingInfo_ChanneledCasting);
		return *(int*)(v1);
	}
	catch(...)
	{
		return 0;
	}
}

bool Units::IsCasting()
{
	if(CastingId()==0&&ChanneledCastingId()==0)
	{
		return true;
	}
	return false;
}

bool Units::IsPlayer()
{
	try
	{
		return this->Type()==4;
	}
	catch(...)
	{
		return false;
	}
}

Units Units::Pet()
{
	vector<Units> tmp=GetUnits();
	try
	{
		for(int i=0;i<tmp.size();i++)
		{
			if(tmp[i].SummonedBy()==this->Guid())
				return tmp[i];
		}
	}
	catch(...)
	{
		return Units(0);
	}
	return Units(0);
}




UINT64 Units::SummonedBy()
{
	return  *(UINT64*)(this->DescriptorFields()+UNIT_FIELD_SUMMONEDBY);
}

UINT64 Units::PetGUID()
{
	try
	{
		if(HasLivePet())
			return Pet().Guid();
	}
	catch(...) {}
	return 0;
}

bool Units::HasLivePet()
{
	try
	{
		if(Pet().BaseAddr()!=0)
			return true;
		return false;
	}
	catch(...)
	{
		return false;
	}
}	

bool Units::IsTargetingMe()
{
	try
	{
		if(TargetGUID()==GetMyPlayer().Guid())
			return true;
		return false;
	}
	catch(...) {return false;}
}

vector<WOWAura> Units::GetAuras()
{
	vector<WOWAura> tmp;
	tmp.clear();
	try
	{
		int auraCount=*(int*)(BaseAddr()+AuraCount1);
		if(auraCount==-1)
		{
			auraCount=*(int*)(BaseAddr()+AuraCount2);
		}

		LARGE_INTEGER perfCount;
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&perfCount);
		UINT64 currentTime=(perfCount.QuadPart*1000)/frequency.QuadPart;
		
		for(int i=0;i<auraCount;i++)
		{
			int localSpellId;
			byte stackCount;
			UINT timeLeft;
            UINT64 ownerGuid;

			if( (*(int*)(BaseAddr()+AuraCount1)) ==-1)
			{
				int auraTable=*(int*)(BaseAddr()+AuraTable2);
				localSpellId=*(int*)(auraTable+AuraSize*i+AuraSpellId);
				stackCount=*(byte*)(auraTable+AuraSize*i+AuraStack);
				timeLeft=*(int*)(auraTable+AuraSize*i+UnitAuras_TimeLeft);
				ownerGuid=*(UINT64*)(auraTable+AuraSize*i);
			}
			else
			{
				localSpellId=*(int*)(BaseAddr()+AuraTable1+AuraSize*i+AuraSpellId);
				stackCount=*(byte*)(BaseAddr()+AuraTable1+AuraSize*i+AuraStack);
				timeLeft=*(int*)(BaseAddr()+AuraTable1+AuraSize*i+UnitAuras_TimeLeft);
				ownerGuid=*(UINT64*)(BaseAddr()+AuraTable1+AuraSize*i);
			}

			if(localSpellId!=0)
			{
				timeLeft=(timeLeft-currentTime)/1000;
				WOWAura curAura;
				curAura.SpellId=localSpellId;
				curAura.secondLeft=timeLeft;
				curAura.stack=stackCount;
				curAura.OwnerGUID=ownerGuid;
				tmp.push_back(curAura);
			}
		}
	}
	catch(...)
	{
	}
	return tmp;
}

vector<int> Units::GetBuffs()
{
	vector<WOWAura> tmp=GetAuras();
	vector<int> rets;
	rets.clear();
	for(int i=0;i<tmp.size();i++)
	{
		rets.push_back(tmp[i].SpellId);
	}
	return rets;
}

bool Units::HasBuff(int buff)
{
	vector<int> tmp=GetBuffs();
	for(int i=0;i<tmp.size();i++)
	{
		if(tmp[i]==buff)
			return true;
	}
	return false;
}

int Units::BuffTimeLeft(int buff)
{
	vector<WOWAura> tmp=GetAuras();
	for(int i=0;i<tmp.size();i++)
	{
		if(tmp[i].SpellId==buff)
			return tmp[i].secondLeft;
	}
	return 0;
}

INT64 Units::Flags()
{
	try
	{
		return *(INT64*)(DescriptorFields()+UNIT_FIELD_FLAGS*4);
	}
	catch(...)
	{
		return -1;
	}
}


bool Units::IsInCombat()
{
	try
	{	
		return bool(Flags() & 0x80000);
	}
	catch(...)
	{
		return false;
	}
}


CString Units::Name()
{
	CString str="";
	if(this->Type()==4)
	{
		return str;
	}
	TCHAR buffer[512]={0};
	DWORD v1=*(DWORD*)(this->BaseAddr()+UnitName1);
	DWORD v2=*(DWORD*)(v1+UnitName2);
	GetUTF8String(v2,buffer);
	str.Format("%s",buffer);
	return str;
}
