// GameObject.cpp: implementation of the GameObject class.
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

GameObject::GameObject(DWORD ptr):Objects(ptr)
{

}

GameObject::~GameObject()
{

}


float GameObject::X()
{
	return *(float*)(this->BaseAddr()+GameObjectX);
}

float GameObject::Y()
{
	return *(float*)(this->BaseAddr()+GameObjectY);
}


float GameObject::Z()
{
	return *(float*)(this->BaseAddr()+GameObjectZ);
}

int GameObject::DisplayId()
{
	return *(int*)(this->BaseAddr()+0x20 + 0x8);
}

int GameObject::GameObjectType()
{
	int field=*(int*)(this->DescriptorFields()+0x20 + 0x2C);
	return ((field>>8)&0xFF);
}


unsigned __int64 GameObject::Created_By()
{
	return *(unsigned __int64*)(this->DescriptorFields()+0x20);
}



char* GameObject::Name(char* buffer)
{
	DWORD v1=*(DWORD*)(this->BaseAddr()+ObjectName1);
	DWORD v2=*(DWORD*)(v1+ObjectName2);
	return GetUTF8String(v2,buffer);
}

bool GameObject::IsBobbing()
{
	return *(byte*)(this->BaseAddr()+0xD4)!=0;
}
