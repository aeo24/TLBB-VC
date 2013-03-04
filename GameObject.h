// GameObject.h: interface for the GameObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEOBJECT_H__4FC98227_77C1_4E68_AF4F_7530AC1B471C__INCLUDED_)
#define AFX_GAMEOBJECT_H__4FC98227_77C1_4E68_AF4F_7530AC1B471C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class GameObject : public Objects  
{
public:
	bool IsBobbing();
	char* Name(char* buffer);
	unsigned __int64 Created_By();
	int GameObjectType();
	int DisplayId();
	float Z();
	float Y();
	float X();
	GameObject(DWORD ptr);
	virtual ~GameObject();

};

#endif // !defined(AFX_GAMEOBJECT_H__4FC98227_77C1_4E68_AF4F_7530AC1B471C__INCLUDED_)
