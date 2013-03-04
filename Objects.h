// Objects.h: interface for the Objects class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTS_H__E853AAA2_771A_4746_83DB_212F6E4F3904__INCLUDED_)
#define AFX_OBJECTS_H__E853AAA2_771A_4746_83DB_212F6E4F3904__INCLUDED_

#include "Location.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Objects  
{
public:
	Location loc();
	unsigned __int64 Guid();
	int Type();
	virtual float Rotation();
	virtual float Z();
	virtual float Y();
	virtual float X();
	DWORD DescriptorFields();
	void SetBaseAddr(DWORD ptr);
	DWORD BaseAddr();
	Objects(DWORD ptr);
	virtual ~Objects();

private:
	DWORD _ptr;
};

#endif // !defined(AFX_OBJECTS_H__E853AAA2_771A_4746_83DB_212F6E4F3904__INCLUDED_)
