// Players.h: interface for the Players class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERS_H__F178D98C_E43E_4EC4_BF37_0DAF42F4DB6D__INCLUDED_)
#define AFX_PLAYERS_H__F178D98C_E43E_4EC4_BF37_0DAF42F4DB6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Units.h"

class Players : public Units  
{
public:
	DWORD PlayerClassId();
	DWORD RaceID();
	char* Name(char* buffer);
	Players(DWORD ptr);
	virtual ~Players();

private:
	DWORD InfoFlags();
};

#endif // !defined(AFX_PLAYERS_H__F178D98C_E43E_4EC4_BF37_0DAF42F4DB6D__INCLUDED_)
