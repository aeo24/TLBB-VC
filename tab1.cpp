// tab1.cpp : implementation file
//

#include "stdafx.h"
#include "Thunder3.h"
#include "tab1.h"
#include "globalfunc.h"
#include <vector>
#include "classes.h"

#include <process.h>


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
void myLua_dostring(DWORD lua_state,char* str)
{
	if(h!=NULL)
	{
		HWND m_edit=::GetDlgItem(h,IDC_EDIT1);
		::SetWindowText(m_edit,str);
	}
	lua_dostring(lua_state,str);
}

void tab1::OnBnClickedButton1()
{
	h=m_hWnd;
	LPVOID fc=(LPVOID)*(DWORD*)0x7C2370;
	lua_dostring=reinterpret_cast<decltype(lua_dostring)>(fc);
	m_edit1.Format("%x",lua_dostring);

	DWORD des=(DWORD)(myLua_dostring);
	DWORD oldProtection=SetProtection(0x7C2370,10,PAGE_EXECUTE_READWRITE);
	memcpy((void*)(0x7C2370),&des,4);
	SetProtection(0x7C2370,10,oldProtection);
	UpdateData(FALSE);
}


void tab1::OnBnClickedButton2()
{

}
