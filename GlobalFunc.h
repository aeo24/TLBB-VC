
#ifndef _H_GLOBALFUNC
#define _H_GLOBALFUNC
#include <vector>

using namespace std;
//////////////////////Defines////////////////////////////////
#define wowBase (DWORD)GetModuleHandle(NULL)
#define MSG_CTM WM_USER+101
#define MSG_Writting WM_USER+102

typedef struct _CTMParam
{
	float x;
	float y;
	float z;
	UINT64 guid;
	int type;
	float precision;
}CTMParam,*PCTMParam;

extern CDialog* mainUI;
//////////////////////Func///////////////////////////////////
void DisHook();
void Hook();
void InjectAndExcute(void *func);
wchar_t* AnsiToUnicode(char* txt,wchar_t* buffer);
char* UnicodeToUTF8(wchar_t* txt,char* buffer);
LPSTR AnsiToUTF8(char* txt,char* buffer);
LPSTR GetUTF8String(DWORD Addr,char* buffer);
LPSTR GetUTF8String2(DWORD Addr);
bool InGame();
unsigned __int64 TargetGUID();
unsigned __int64 MouseOverGUID();
void CTM(float x,float y,float z,UINT64 guid,int actionType,float precision);
void _ctm(float x,float y,float z,UINT64 guid,int actionType,float precision);
void DetourCTM(float x,float y,float z,unsigned __int64 guid,int actionType,float precision);
class Location;
bool MoveToLoc(Location pos, double dis, bool breakOnCombat);

void DetourLuaDoString(char* txt);
void LuaDoString(char* txt);
char* LuaToString(char* buffer);
void InteractGameObj(DWORD _ptr);
void InteractUnit(DWORD _ptr);
char* GetText(char* txt,char* buffer);
vector<DWORD> GetObject();
class Objects;
vector<Objects> GetObjects();
class Units;
vector<Units> GetUnits();
class GameObject;
vector<GameObject> GetGameObjects();
class Players;
vector<Players> GetPlayers();
Players GetMyPlayer();
void Writting(char* txt);
VOID _selectTarget(UINT64 guid);
#endif