// Objects.cpp: implementation of the Objects class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thunder3.h"
#include "Objects.h"
#include "Location.h"
#include "defines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Objects::Objects(DWORD ptr)
{

}

Objects::~Objects()
{

}

DWORD Objects::BaseAddr()
{
	return this->_ptr;
}


void Objects::SetBaseAddr(DWORD ptr)
{
	this->_ptr=ptr;
}

DWORD Objects::DescriptorFields()
{
	return *(DWORD*)(this->_ptr+0x8);
}


float Objects::X()
{
	try
	{
		return *(float*)(this->_ptr+UnitX);
	}
	catch(...)
	{
		return 0;
	}
}

float Objects::Y()
{
	try
	{
		return *(float*)(this->_ptr+UnitY);
	}
	catch(...)
	{
		return 0;
	}
}

float Objects::Z()
{
	try
	{
		return *(float*)(this->_ptr+UnitZ);
	}
	catch(...)
	{
		return 0;
	}
}

float Objects::Rotation()
{
	try
	{
		return *(float*)(this->_ptr+0x790+0x10);
	}
	catch(...)
	{
		return 0;
	}
}

int Objects::Type()
{
	return *(int*)(this->_ptr+0x10);
}

unsigned __int64 Objects::Guid()
{
	return *(unsigned __int64*)(this->_ptr+0x30);
}

Location Objects::loc()
{
	return Location(this->X(),this->Y(),this->Z());
}
