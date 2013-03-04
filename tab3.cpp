// tab3.cpp : implementation file
//

#include "stdafx.h"
#include "Thunder3.h"
#include "tab3.h"
#include "GlobalFunc.h"
#include "classes.h"
#include "defines.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// tab3 dialog


tab3::tab3(CWnd* pParent /*=NULL*/)
	: CDialog(tab3::IDD, pParent)
	, Edit1(_T(""))
	, Edit_Int(0)
{
	//{{AFX_DATA_INIT(tab3)
	m_check_chaofeng = FALSE;
	//}}AFX_DATA_INIT
}


void tab3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(tab3)
	DDX_Control(pDX, IDC_HOTKEY1, m_hotKey_ChaoFeng);
	DDX_Check(pDX, IDC_CHECK_ChaoFeng, m_check_chaofeng);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT1, Edit1);
	DDX_Text(pDX, IDC_EDIT2, Edit_Int);
}


BEGIN_MESSAGE_MAP(tab3, CDialog)
	//{{AFX_MSG_MAP(tab3)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_CHECK_ChaoFeng, OnCHECKChaoFeng)
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &tab3::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &tab3::OnBnClickedButton4)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// tab3 message handlers

#define HotKeyID_OT_ChaoFeng 1001

void tab3::OnButton1() 
{
	UnregisterHotKey(this->m_hWnd,HotKeyID_OT_ChaoFeng);
}

void tab3::OnCHECKChaoFeng() 
{
	UpdateData(true);
	WORD key,mod;
	UnregisterHotKey(m_hWnd, HotKeyID_OT_ChaoFeng);
	if(m_check_chaofeng)
	{
		m_hotKey_ChaoFeng.GetHotKey(key,mod);
		//fix BUG
		switch(mod)
		{
		case MOD_ALT:
			mod=MOD_SHIFT;
			break;
		case  MOD_SHIFT:
			mod=MOD_ALT;
			break;
		}

		RegisterHotKey(m_hWnd,HotKeyID_OT_ChaoFeng,mod,key);
		m_hotKey_ChaoFeng.EnableWindow(FALSE);
	}
	else
	{
		m_hotKey_ChaoFeng.EnableWindow(TRUE);
	}
	
}


LRESULT tab3::OnHotKey(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
	case HotKeyID_OT_ChaoFeng:
		__asm
		{
			mov cx,cx
		}
		vector<Units> tmp= GetUnits();
		for(int i=0;i<tmp.size();i++)
		{
			if(!tmp[i].IsPlayer())
			{
				if(tmp[i].TargetGUID()!=GetMyPlayer().Guid() && 
					tmp[i].IsInCombat() &&
					tmp[i].loc().DistanceToSelf()<35)
				{
					_selectTarget(tmp[i].Guid());
					Sleep(50);
					LuaDoString("CastSpellByName(\"低吼\")");
					break;
				}
			}
		}
		break;
	}

	return 0;
}




void (__cdecl* FrameScript_ExecuteBuffer)(const char* txt,const char* txt2,DWORD asProtected)=nullptr;
void (__thiscall* CMovementShared__StopFalling)(DWORD This)=nullptr;
void (__thiscall* CGUnit_C__OnCollideFallLandNotify)(DWORD object,DWORD Timestamp,DWORD CMovement,DWORD Unk);
DWORD (__cdecl* MovementGetGlobals)()=nullptr;
// TCHAR strPath[MAX_PATH];  
// GetModuleFileName(GetModuleHandle(_T("Game.dll")),strPath,MAX_PATH); 

void StopFalling();
void CInitialize();

void tab3::OnButton2() 
{
	FrameScript_ExecuteBuffer=reinterpret_cast<decltype(FrameScript_ExecuteBuffer)>(wowBase+FrameScript__Execute);
	CString str="print('hiiii')";
	FrameScript_ExecuteBuffer(str.GetBuffer(0),str.GetBuffer(0),0);
}





namespace offsets
{


enum WoWOffsets : unsigned int
{
	luaL_error = 0x11E540,
	FrameScript__RegisterFunction = 0x074210,
	lua_tonumber = 0x11D2F0,	
	lua_toboolean = 0x11D3A0,	
	lua_tolstring = 0x11D3D0,	
	lua_pushnil = 0x11D570,	
	lua_pushnumber = 0x11D590,	
	lua_pushstring = 0x11D640,	
	lua_pushboolean = 0x11D7F0,	
	lua_isnumber = 0x11D1E0,	
	lua_isstring = 0x11D220,	
	lua_gettop = 0x11CE70,	
	//FrameScript_ExecuteBuffer = 0x75350,
	FrameScript__InvalidPtrCheck = 0x165930,

	CGGameUI__CanPerformAction = 0x572B70,
	CGWorldFrame__CreateFrames = 0x56B5F0,
	CGWorldFrame__Render = 0x5866C0,

	IsLuaSecure = 0xADFFE8,
	IsInGame = 0xC6BBDE,
	RenderFlags = 0xD3D0B4,

	CWorldView__UpdateViewerLiquid = 0x70A390,

	Script_UnitLevel = 0x52AD80,
	CGGameUI__Idle = 0x57F7D0,
	CGUnit_C__SetTrackingTarget = 0x4A0480,
	CGUnit_C__InitializeTrackingState = 0x493760,
	CGUnit_C__HandleTracking = 0x4A5C80,
	Script_SendChatMessage = 0x59AEF0,
	CGUnit_C__Loot = 0x413EB0,

	luaD_rawrunprotected = 0x125000,
	_lua_precall = 0x125200, 
	luaD_precall = 0x125A10, 

	GetListAuctionByIndex = 0x541100,
	GetOwnerAuctionByIndex = 0x541120,
	GetBidderAuctionByIndex = 0x541140,

	FrameTime__GetCurTimeMs = 0x06E8B0,
	CMovement__GetDistanceFallen = 0x8B5C50,
	GetUnitFromName = 0x526960,

	CMovement_C__IsColliding = 0x762B30,
	CGUnit_C__UpdateSwimmingStatus = 0x4A7030,

	CMovement__CalcDirection = 0x8B5730,
	CMovement_C__IsFlyingOrSwimming = 0x4EDA60,
	Script_JumpOrAscendStart = 0x51FE80,

	CMovement_C__UpdatePlayerMovement = 0x445590,
	CMovement_C__GetCollisionFlags = 0x4ED2B0,

	SendJump = 0x49F970,

	CGGameUI__EnterWorld = 0x579FC0,
	World__LoadMap = 0x6ED8A0,
	World__UnloadMap = 0x6EAC10,
	g_MapDB = 0xBBD104,

	CGUnit_C__OnCollideFallLandNotify = 0x48A650,
	CMovementShared__StopFalling = 0x8B75F0,
	MovementGetGlobals = 0x452210,

	CGUnit_C__UpdateDisplayInfo = 0x4A8F60,
	CGUnit_C__OnMountDisplayChanged = 0x4A44B0,
	CGWorldFrame__GetActiveCamera = 0x580500,

	CGPlayer_C__CanTrackUnit = 0x415A20,
	CGPlayer_C__CanTrackObject = 0x415AB0,
	CGUnit_C__UnitReaction = 0x490AE0,
	CGUnit_C__GetCreatureRank = 0x4832B0,
	CGUnit_C__IsAttackable = 0x49E360,

	CGUnit_C__GetUnitName = 0x491750,
	CGGameObject_C__GetObjectName = 0x4221F0,

	MaxCameraDistanceLimit = 0x93A484,

	UnitLocation = 0x7E0,
	UnitPitch = 0x7F4,
	CMovement = 0xE4,
	UnitDisplayID = 0xF8,
	UnitDefaultDisplayID = 0xFC,
	UnitMountDisplayID = 0x100,
	ObjectScale = 0x18,
	ObjectType = 0x10,
};




enum MovementFlags : unsigned int
{
	Falling = 0x800,
	FallingFar = 0x1000,
	Swimming = 0x100000,
	Flying = 0x1000000,
};

}


void tab3::OnBnClickedButton3()
{
	HWND h=::FindWindowA(NULL,_T("魔兽世界"));
	if(NULL==h) return;
	DWORD pid=0;
	GetWindowThreadProcessId(h,&pid);
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
	CInitialize();

	StopFalling();
	const byte fly[]={0x90,0x90,0x90};
	const byte jmp[]={0xEB,0x6};
	::WriteProcessMemory(hProcess,(LPVOID)(offsets::CMovement_C__IsFlyingOrSwimming+0x63+wowBase),fly,3,NULL);
	::WriteProcessMemory(hProcess,(LPVOID)(offsets::Script_JumpOrAscendStart+0x168+wowBase),jmp,2,NULL);

}

void CInitialize ()
{
	CMovementShared__StopFalling=reinterpret_cast<decltype(CMovementShared__StopFalling)>
		(wowBase+offsets::CMovementShared__StopFalling);
	CGUnit_C__OnCollideFallLandNotify=reinterpret_cast<decltype(CGUnit_C__OnCollideFallLandNotify)>
		(wowBase+offsets::CGUnit_C__OnCollideFallLandNotify);
	MovementGetGlobals=reinterpret_cast<decltype(MovementGetGlobals)>
		(wowBase+offsets::MovementGetGlobals);
}

void StopFalling()
{
	DWORD Player=GetMyPlayer().BaseAddr();
	if(!Player)
		return;
	DWORD cm=*reinterpret_cast<DWORD*>(Player+offsets::CMovement);
	if(cm && *reinterpret_cast<DWORD*>(cm+0x38) & (offsets::Falling | offsets::FallingFar) )
	{

		CMovementShared__StopFalling(cm);
		CGUnit_C__OnCollideFallLandNotify(Player,
			*reinterpret_cast<DWORD*>(MovementGetGlobals()+0x128),
			cm,
			1);
	}
}




void tab3::OnBnClickedButton4()
{
	HWND h=::FindWindowA(NULL,_T("魔兽世界"));
	if(NULL==h) return;
	DWORD pid=0;
	GetWindowThreadProcessId(h,&pid);
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);

	const byte fly[]={0x33, 0xC0, 0xC3};
	const byte jmp[]={0x57, 0x8B};
	::WriteProcessMemory(hProcess,(LPVOID)(offsets::CMovement_C__IsFlyingOrSwimming+0x63+wowBase),fly,3,NULL);
	::WriteProcessMemory(hProcess,(LPVOID)(offsets::Script_JumpOrAscendStart+0x168+wowBase),jmp,2,NULL);
}

void tab3::OnButton3() 
{

}
