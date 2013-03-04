// Players.cpp: implementation of the Players class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thunder3.h"
#include "Players.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Players::Players(DWORD ptr):Units(ptr)
{

}

Players::~Players()
{

}


char* Players::Name(char *buffer)
{
	memset(buffer,0,sizeof(buffer));
	try
	{
		int v1=*(int*)(wowBase+PlayerNameCachePointer+PlayerNameMaskOffset);
		if(v1==-1)
		{
			strcpy(buffer,"Unknown Player");
			return buffer;
		}
		int v2=*(int*)(wowBase+PlayerNameCachePointer+PlayerNameBaseOffset);
		v1&=(this->Guid());
		v1+=v1*2;
		v1=(v2+(v1*4)+4);
		v1=*(int*)(v1+4);

		//iterate through the linked List until the current entry has
        //the same GUID as the object whose name we want
		while((*(int*)v1)!=(int)this->Guid())
		{
			DWORD v3=*(DWORD*)(wowBase+PlayerNameCachePointer+PlayerNameBaseOffset);
			v2=(int)this->Guid();
			v2&=*(int*)(wowBase+PlayerNameCachePointer+PlayerNameMaskOffset);
			v2+=v2*2;
			v2=*(int*)(v3+(v2*4));
			v2+=v1;
			v1=*(int*)(v2+4);
		}
		return GetUTF8String(v1+PlayerNameStringOffset,buffer);
	}
	catch(...)
	{
		memset(buffer,0,sizeof(buffer));
		return buffer;
	}
}

DWORD Players::InfoFlags()
{
	try
	{
		return *(DWORD*)(this->DescriptorFields()+UNIT_FIELD_BYTES_0*4);
	}
	catch(...)
	{
		return 0;
	}
}

DWORD Players::RaceID()
{
	if(InfoFlags()==0) return 0;
	return (InfoFlags()>>0)&0xFF;
}

DWORD Players::PlayerClassId()
{
	if(InfoFlags()==0) return 0;
	return (InfoFlags()>>8)&0xFF;
}
