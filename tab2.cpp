// tab2.cpp : implementation file
//

#include "stdafx.h"
#include "Thunder3.h"
#include "tab2.h"
#include "classes.h"
#include <math.h>
extern "C"
{
#include "luasrc\lua.h"
#include "luasrc\lualib.h"
#include "luasrc\lauxlib.h"
};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


lua_State *L;
#pragma comment(lib,"luasrc\\lua52.lib")
char nameBuffer[128];
/////////////////////////////////////////////////////////////////////////////
// tab2 dialog


tab2::tab2(CWnd* pParent /*=NULL*/)
	: CDialog(tab2::IDD, pParent)
{
	//{{AFX_DATA_INIT(tab2)
	m_scripts = _T("");
	//}}AFX_DATA_INIT
}


void tab2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(tab2)
	DDX_Text(pDX, IDC_EDIT1, m_scripts);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(tab2, CDialog)
	//{{AFX_MSG_MAP(tab2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// tab2 message handlers

int Lua_GetMyPlayerName(lua_State *l)
{
	char buffer[128];
	GetMyPlayer().Name(buffer);
	lua_pushstring(L,buffer);
	return 1;
}
int Lua_MyPlayer(lua_State *l)
{
	int hp=GetMyPlayer().Hp();
	float x=GetMyPlayer().X();
	float y=GetMyPlayer().Y();
	float z=GetMyPlayer().Z();
	 __int64 guid=GetMyPlayer().Guid();
	 __int64 tarGuid=GetMyPlayer().TargetGUID();
	bool ismoving=GetMyPlayer().IsMoving();

	lua_pushinteger(L,hp);
	lua_pushnumber(L,x);
	lua_pushnumber(L,y);
	lua_pushnumber(L,z);
	lua_pushnumber(L,guid);
	lua_pushnumber(L,tarGuid);
	lua_pushinteger(L,ismoving);

	return 7;
	
}
int lua_ctm(lua_State *l)
{
	float x,y,z;
	x=lua_tonumber(l,1);
	y=lua_tonumber(l,2);
	z=lua_tonumber(l,3);
	CTM(x,y,z,0,4,0);
	return 1;
}

 int l_sin (lua_State *L) 
{
	double d = lua_tonumber(L, 1); /* get argument */
	lua_pushnumber(L, sin(d));  /* push result */
	return 1;       /* number of results */
}


BOOL tab2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	L=luaL_newstate();
	luaL_openlibs(L);
	lua_register(L,"ctm",lua_ctm);
	lua_register(L,"GetMyName",Lua_GetMyPlayerName);
	lua_register(L,"MyPlayer",Lua_MyPlayer);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void tab2::OnButton1() 
{
	luaL_dostring(L,"hp,x,y,z,u1,u2,m=MyPlayer()");
	lua_getglobal(L,"x");
	LPCSTR buffer=lua_tostring(L,-1);
	m_scripts=buffer;
	UpdateData(false);
}

void tab2::OnButton2() 
{
	UpdateData(TRUE);
	luaL_dostring(L,m_scripts.GetBuffer(m_scripts.GetLength()));
}

void tab2::OnButton8() 
{
	char buffer[128];
	LuaDoString("t1=123456");
	LuaToString(buffer);
	m_scripts=buffer;
	UpdateData(FALSE);
}
