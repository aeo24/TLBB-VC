// Thunder3.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Thunder3.h"
#include "GameForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


GameForm *gameform;
//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CThunder3App

BEGIN_MESSAGE_MAP(CThunder3App, CWinApp)
	//{{AFX_MSG_MAP(CThunder3App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThunder3App construction

CThunder3App::CThunder3App()
{

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CThunder3App object

int CThunder3App::ExitInstance()
{
	delete gameform;  //释放内存
	gameform=NULL;
	return CWinApp::ExitInstance();
}

CThunder3App theApp;


LRESULT CALLBACK Gameproc(
						  int code,       // hook code
						  WPARAM wParam,  // virtual-key code VK_HOME
						  LPARAM lParam   // keystroke-message information,,31位=0:按下，31位=1:弹起
						  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//bool keyUp=(lParam&(1<<31)==0);
	if( code==HC_ACTION &&(wParam==VK_HOME)&&((lParam&(1<<31))==0))
	{
		if(gameform==NULL)
		{
			gameform=new GameForm;
			gameform->Create(IDD_MAIN);
		}
		else
		{
			gameform->ShowWindow(gameform->IsWindowVisible()?SW_HIDE:SW_SHOW);
		}
		
	}
	return CallNextHookEx(0,code,wParam,lParam );
}



//#define gameCaption "YB_OnlineClient"
//#define gameCaption "无标题 - 记事本"
#define gameCaption "魔兽世界"

//安装勾子
void SetHook()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	HWND gameh=FindWindow("TianLongBaBu WndClass",NULL);
	if (gameh==0)
	{
		AfxMessageBox("未找到游戏");
	}
	DWORD pid=::GetWindowThreadProcessId(gameh,NULL);
	::SetWindowsHookEx(WH_KEYBOARD,&Gameproc,::GetModuleHandle("Thunder3.dll"),pid);
}
