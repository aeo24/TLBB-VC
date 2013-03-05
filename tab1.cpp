// tab1.cpp : implementation file
//

#include "stdafx.h"
#include "Thunder3.h"
#include "tab1.h"
#include "globalfunc.h"
#include <vector>
#include <process.h>
#include "detours.h"
#include <string>

using namespace std;
#pragma comment(lib,"detours.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define MyMSG WM_USER+100

/////////////////////////////////////////////////////////////////////////////
// tab1 dialog


tab1::tab1(CWnd* pParent /*=NULL*/)
	: CDialog(tab1::IDD, pParent)
	, m_edit1(_T(""))
{
	//{{AFX_DATA_INIT(tab1)

	//}}AFX_DATA_INIT
}


void tab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(tab1)

	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
}


BEGIN_MESSAGE_MAP(tab1, CDialog)
	//{{AFX_MSG_MAP(tab1)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &tab1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &tab1::OnBnClickedButton2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// tab1 message handlers

void (__cdecl* lua_dostring)(DWORD lua_state,char* str)=nullptr;

unsigned long SetProtection (unsigned int Address, unsigned int Size, unsigned long Protection)
{
	unsigned long OldProtection;
	if(!VirtualProtect(reinterpret_cast<void*>(Address), Size, Protection, &OldProtection))
	{
		MessageBox(NULL,"! virtualProtect..",NULL,MB_OK);
	}

	return OldProtection;
}

HWND h=NULL;
vector<string> cmds;
void myLua_dostring(DWORD lua_state,char* str)
{

	string txt(str);
	if(h!=NULL)
	{
		HWND m_edit=::GetDlgItem(h,IDC_EDIT1);
		string _txt;
		for each(string u in cmds)
		{
			_txt.append(u.c_str());
			_txt.append("\r\n");
		}
		SetDlgItemTextA(h,IDC_EDIT1,_txt.c_str());

		for each(string u in cmds)
		{
			if(u==txt)
				return;
		}
		cmds.push_back(txt);
	}
	lua_dostring(lua_state,str);
}

void tab1::OnBnClickedButton1()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID*)&lua_dostring,myLua_dostring);
	DetourTransactionCommit();
}


void tab1::OnBnClickedButton2()
{
	h=m_hWnd;
	lua_dostring=reinterpret_cast<decltype(lua_dostring)>(*(DWORD*)0x7C2370);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID*)&lua_dostring,myLua_dostring);
	DetourTransactionCommit();
}
