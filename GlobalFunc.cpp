#include "stdafx.h"
#include "GlobalFunc.h"
#include "Location.h"
#include "classes.h"
#include "Thunder3.h"
#include "tab1.h"

/////////////////////////////////Global///////////////////////////////////////
CDialog* mainUI=NULL;



void Writting(char* txt)
{
	SYSTEMTIME time;
	CString str;
	GetLocalTime(&time);
	str.Format("[%d:%d:%d] %s \r\n",time.wHour,time.wMinute,time.wSecond,txt);
	SendMessage(mainUI->m_hWnd,MSG_Writting,(WPARAM)&str,NULL);
}

//Players MyPlayer(0);
vector<DWORD> GetObject()
{
	vector<DWORD> tmp;
	DWORD objBase=*(DWORD*)(*(DWORD*)(wowBase+CurMgrPointer)+CurMgrOffset);
	DWORD currentObj=*(DWORD*)(objBase+FirstObject);
	while(currentObj!=0&&currentObj%2==0)
	{
		tmp.push_back(currentObj);
		currentObj=*(DWORD*)(currentObj+NextObject);
	}
	return tmp;
}
vector<Units> GetUnits()
{
	vector<Units> tmp;
	DWORD objBase=*(DWORD*)(*(DWORD*)(wowBase+CurMgrPointer)+CurMgrOffset);
	DWORD currentObj=*(DWORD*)(objBase+FirstObject);
	Units obj(0);
	while(currentObj!=0 && (currentObj%2==0))
	{
		obj.SetBaseAddr(currentObj);
		if(obj.Type()==3||obj.Type()==4) //units
		{
			tmp.push_back(obj);
		}

		currentObj=*(DWORD*)(currentObj+NextObject);
	}
	return tmp;
}


Players GetMyPlayer()
{
	DWORD objBase=*(DWORD*)(*(DWORD*)(wowBase+CurMgrPointer)+CurMgrOffset);
	UINT64 localGuid=*(UINT64*)(objBase+LocalGUID);
	vector<Players> tmp=GetPlayers();
	for(int i=0;tmp.size();i++)
	{
		if(tmp[i].Guid()==localGuid)
		{
			//MyPlayer.SetBaseAddr(tmp[i].BaseAddr());
			return tmp[i];
		}
	}
}


vector<Players> GetPlayers()
{
	vector<Players> tmp;
	DWORD objBase=*(DWORD*)(*(DWORD*)(wowBase+CurMgrPointer)+CurMgrOffset);
	DWORD currentObj=*(DWORD*)(objBase+FirstObject);
	Players obj(0);
	while(currentObj!=0 && (currentObj%2==0))
	{
		obj.SetBaseAddr(currentObj);
		if(obj.Type()==4) //players
		{
			tmp.push_back(obj);
		}
		
		currentObj=*(DWORD*)(currentObj+NextObject);
	}
	return tmp;
}
vector<GameObject> GetGameObjects()
{
	vector<GameObject> tmp;
	DWORD objBase=*(DWORD*)(*(DWORD*)(wowBase+CurMgrPointer)+CurMgrOffset);
	DWORD currentObj=*(DWORD*)(objBase+FirstObject);
	GameObject obj(0);
	while(currentObj!=0&&currentObj%2==0)
	{
	 	obj.SetBaseAddr(currentObj);
		if(obj.Type()==5) //gameObj
		{
			tmp.push_back(obj);
		}
		currentObj=*(DWORD*)(currentObj+NextObject);
	}
	return tmp;
}

vector<Objects> GetObjects()
{
	vector<Objects> tmp;
	DWORD objBase=*(DWORD*)(*(DWORD*)(wowBase+CurMgrPointer)+CurMgrOffset);
	DWORD currentObj=*(DWORD*)(objBase+FirstObject);
	Objects obj(0);
	while(currentObj!=0&&currentObj%2==0)
	{
		obj.SetBaseAddr(currentObj);
		tmp.push_back(obj);
		
		currentObj=*(DWORD*)(currentObj+NextObject);
	}
	return tmp;
}


unsigned __int64 TargetGUID()
{
	return *(__int64*)(wowBase+_CurrentTargetGUID);
}

unsigned __int64 MouseOverGUID()
{
	return *(__int64*)(wowBase+_MouseOverGUID);
}


bool InGame()
{
	try
	{
		return *(DWORD*)(wowBase+_InGame)==1;
	}
	catch(...)
	{
		return FALSE;
	}
}
wchar_t* AnsiToUnicode(char* txt,wchar_t* buffer)
{
	int wcsLen=::MultiByteToWideChar(CP_ACP,NULL,txt,strlen(txt),NULL,0);
	wchar_t* wszString=new wchar_t[wcsLen+1];
	::MultiByteToWideChar(CP_ACP,NULL,txt,strlen(txt),wszString,wcsLen);
	wszString[wcsLen]='\0';
	wcscpy(buffer,wszString);
	delete[] wszString;
	wszString=NULL;
	return buffer;
}
char* UnicodeToUTF8(wchar_t* txt,char* buffer)
{
	int u8Len=::WideCharToMultiByte(CP_UTF8,NULL,txt,wcslen(txt),NULL,0,NULL,NULL);
	char* szU8=new char[u8Len+1];

	::WideCharToMultiByte(CP_UTF8,NULL,txt,wcslen(txt),szU8,u8Len,NULL,NULL);
	szU8[u8Len]='\0';
	strcpy(buffer,szU8);
	delete[] szU8;
	szU8=NULL;
	return buffer;
}

LPSTR AnsiToUTF8(char* txt,char* buffer)
{
	wchar_t wBuffer[1024]={0};	
	return UnicodeToUTF8(AnsiToUnicode(txt,wBuffer),buffer);
}

LPSTR GetUTF8String(DWORD Addr,char* buffer)
{
	try
	{
	char* text=(char*)(Addr);
	int erg=MultiByteToWideChar(CP_UTF8,NULL,text,strlen(text),NULL,0);
	wchar_t* wString=new wchar_t[erg+1];
	MultiByteToWideChar(CP_UTF8,NULL,text,strlen(text),wString,erg);
	wString[erg]='\0';
	
	int erg2=WideCharToMultiByte(CP_ACP,NULL,wString,wcslen(wString),NULL,0,NULL,NULL);
	char* ansi=new char[erg2+1];
	WideCharToMultiByte(CP_ACP,NULL,wString,wcslen(wString),ansi,erg2,NULL,NULL);
	ansi[erg2]='\0';
	strcpy(buffer,ansi);
	delete[] wString;
	delete[] ansi;
	wString=NULL;
	ansi=NULL;
	return buffer;
	}
	catch(...)
	{
		memset(buffer,0,sizeof(buffer));
		return buffer;
	}
}

LPSTR GetUTF8String2(DWORD Addr)
{
	
	try
	{
	char text[512]={0};
	WCHAR w[512]={0};
	char* buffer=(char*)malloc(512);
	strcpy(text,(LPSTR)Addr);
	MultiByteToWideChar(CP_UTF8,NULL,text,strlen(text),NULL,0);
	WideCharToMultiByte(CP_ACP,0,w,-1,text,sizeof(text),0,0);
	strcpy(buffer,text);
	return (LPSTR)buffer;
	}
	catch(...)
	{
		return "";
	}

}

void LuaDoString(char* txt)
{
	DWORD _dostring=wowBase+FrameScript__Execute;
	char buffers[1024];
	AnsiToUTF8(txt,buffers);
	__asm
	{
		lea eax,buffers
		push 0
		push eax
		push eax
		mov eax,_dostring
		call eax
		add esp,0xC
	}
}

char* LuaToString(char* buffer)
{
	DWORD _tostring=wowBase+0x2BEF0; 
	DWORD rets;
	__asm
	{
		mov edi,0
		push 0
		push 1
		mov ebx,0x5B94968
		push ebx
		mov ebx,_tostring
		call ebx
		mov rets,eax
		add esp,0x8
	}
	return GetUTF8String(rets,buffer);
}

char* GetText(char* txt,char* buffer)
{
	DWORD _getText=wowBase+FrameScript_GetText;
	DWORD rets;
	__asm
	{
		push 0
		push -1
		mov edx,txt
		push edx
		mov edx,_getText
		call edx
		add esp,0xC
		mov rets,eax
	}
	return GetUTF8String(rets,buffer);
}


void _ctm(float x,float y,float z,UINT64 guid,int actionType,float precision)
{
	DWORD _GetActivePlayerObj=wowBase+ClntObjMgrGetActivePlayerObj;
	DWORD _GetActivePlayer=wowBase+ClntObjMgrGetActivePlayer;
	DWORD _ctm=wowBase+ClickToMove;
	float pos[3]={x,y,z};
	unsigned __int64 _guid=guid;
	__asm
	{
		mov edx,precision
		push edx

		mov edx,_GetActivePlayer
		call edx
		test eax,eax
		je $out
		
		mov edx,_GetActivePlayerObj
		call edx
		test eax,eax
		je $out
		mov ecx,eax

		lea edx,pos
		push edx
		lea edx,_guid
		push edx
		push actionType
		
		mov edx,_ctm
		call edx
$out:

	}
}
void CTM(float x,float y,float z,UINT64 guid,int actionType,float precision)
{	
	CTMParam p;
	p.x=x;
	p.y=y;
	p.z=z;
	p.guid=guid;
	p.type=actionType;
	p.precision=precision;
	SendMessage(mainUI->m_hWnd,MSG_CTM,WPARAM(&p),NULL);
}


void InteractUnit(DWORD _ptr)
{
	DWORD _call=wowBase+CGUnit_OnRightClick;
	__asm
	{
		push 1
		mov ecx,_ptr
		mov edx,_call
		call edx
	}
}
void InteractGameObj(DWORD _ptr)
{
	if(_ptr<=0) return;
	DWORD objBase=*(DWORD*)(*(DWORD*)(wowBase+CurMgrPointer)+CurMgrOffset);

	__asm
	{
		mov esi,_ptr
		mov edx,[esi]
		mov eax,[edx+0xB4]
		mov ecx,esi
		call eax
	}
}

bool MoveToLoc(Location pos, double dis=5, bool breakOnCombat=false)
{
	DWORD oldTime= GetTickCount();
	Location oldPos=GetMyPlayer().loc();

	while(pos.DistanceToSelf()>dis)
	{
		if(!GetMyPlayer().IsMoving())
		{
			DetourCTM(pos.X,pos.Y,pos.Z,0,4,0);
		}
		if(GetTickCount()-oldTime>12*1000)
		{
			return false;
		}
		Sleep(200);
	}
	return true;
}
bool MoveToLoc(float x,float y,float z, double dis=5, bool breakOnCombat=false)
{
	Location pos(x,y,z);
	return MoveToLoc(pos,dis,breakOnCombat);
}

DWORD EndScene=0x6755CE09; 
//DWORD EndScene=*(DWORD*)(*(DWORD**)(*(DWORD*)(wowBase+ 0xABF47C)+0x2800)+0xA8);
DWORD InjectAddr=0; 
bool MainThreadIsHook=false;
bool ExcutingCode=false;

__declspec(naked) void __stdcall CodeCave()
{
	__asm
	{
		mov edi,edi
		push ebp
		mov ebp,esp

		pushad
		pushfd
		mov eax,InjectAddr
		test eax,eax
		je _out
		call eax
		mov InjectAddr,0
_out:
		popfd
		popad
		mov eax,EndScene
		add eax,5
		jmp eax
	}
}

void Hook()
{
	if(*(byte*)EndScene==0xE9 && InjectAddr==0)
	{
		DisHook();
	}
	//Ð´ÈëÌø×ª,Create Hook Jmp
	DWORD pid=GetCurrentProcessId();
	HANDLE h=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
	DWORD jmp=(DWORD)CodeCave-EndScene-5;
	BYTE _e9=0xE9;
	WriteProcessMemory(h,(LPVOID)EndScene,&_e9,1,NULL);
	WriteProcessMemory(h,(LPVOID)(EndScene+1),&jmp,4,NULL);

	MainThreadIsHook=true;
}

__declspec(naked) void OrginEndScene()
{
	__asm
	{
		mov edi,edi
		push ebp
		mov ebp,esp
	}
}

void DisHook()
{
	DWORD pid=GetCurrentProcessId();
	HANDLE h=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
	WriteProcessMemory(h,(LPVOID)EndScene,(LPVOID)OrginEndScene,5,NULL);

	MainThreadIsHook=false;
}

void InjectAndExcute(void* func)
{
	while(ExcutingCode)
	{
		Sleep(5);
	}
	ExcutingCode=true;
	
	try
	{
		Hook();
		if(true)
		{
			InjectAddr=(DWORD)func;
		}

		//Wait To launch code
		while(InjectAddr!=0)
		{
			Sleep(5);
		}
	}
	catch(...) { ExcutingCode=false;}
	DisHook();
	ExcutingCode=false;
}

///////////////////////////////DetourCTM//////////////////////////////////////
float Detour_pos[3];
unsigned __int64 DetourCTM_guid;
int DetourCTM_actionType;
float DetourCTM_precision;
DWORD Detour_GetActivePlayerObj;
DWORD Detour_GetActivePlayer;
DWORD Detour_ctm;
__declspec(naked) void __stdcall _detourCTM()
{
	__asm
	{
		mov edx,DetourCTM_precision
		push edx

		mov edx,Detour_GetActivePlayer
		call edx
		test eax,eax
		je $out

		mov edx,Detour_GetActivePlayerObj
		call edx
		test eax,eax
		je $out
		mov ecx,eax

		lea edx,Detour_pos
		push edx
		lea edx,DetourCTM_guid
		push edx
		push DetourCTM_actionType

		mov edx,Detour_ctm
		call edx
$out:
		retn
	}
}
void DetourCTM(float x,float y,float z,unsigned __int64 guid,int actionType,float precision)
{
	Detour_GetActivePlayerObj=wowBase+ClntObjMgrGetActivePlayerObj;
	Detour_GetActivePlayer=wowBase+ClntObjMgrGetActivePlayer;
	Detour_ctm=wowBase+ClickToMove;
	Detour_pos[0]=x;
	Detour_pos[1]=y;
	Detour_pos[2]=z;
	DetourCTM_guid=guid;
	DetourCTM_precision=precision;
	DetourCTM_actionType=actionType;

	InjectAndExcute(_detourCTM);
}

////////////////////////////////LuaDoString//////////////////////////////////
char Detour_LuaDoStringBuffers[1024];
DWORD Detour_dostring;
__declspec(naked) void __stdcall _detourLuaDoString()
{
	__asm
	{
		lea eax,Detour_LuaDoStringBuffers
		push 0
		push eax
		push eax
		mov eax,Detour_dostring
		call eax
		add esp,0xC
		retn
	}
}
void DetourLuaDoString(char* txt)
{
	//MessageBox(NULL,"nihaohhhhhhhhhh",NULL,MB_OK);
	Detour_dostring=wowBase+FrameScript__Execute;
	memset(Detour_LuaDoStringBuffers,0,1024);
	AnsiToUTF8(txt,Detour_LuaDoStringBuffers);
	InjectAndExcute(_detourLuaDoString);
}

VOID _selectTarget(UINT64 guid)
{
	DWORD hi=(guid>>32) & 0xFFFFFFFF;
	DWORD lo= guid & 0xFFFFFFFF;
	DWORD select=wowBase+CGGameUI__Target;

	__asm
	{
		push hi
		push lo
		mov edx,select
		call edx
		add esp,0x8
	}
}