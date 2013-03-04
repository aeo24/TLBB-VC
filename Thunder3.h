// Thunder3.h : main header file for the THUNDER3 DLL
//

#if !defined(AFX_THUNDER3_H__7B9267C5_5B3B_4E52_A5B5_C4D18EB1C956__INCLUDED_)
#define AFX_THUNDER3_H__7B9267C5_5B3B_4E52_A5B5_C4D18EB1C956__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CThunder3App
// See Thunder3.cpp for the implementation of this class
//

class CThunder3App : public CWinApp
{
public:
	CThunder3App();
	int ExitInstance();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThunder3App)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CThunder3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUNDER3_H__7B9267C5_5B3B_4E52_A5B5_C4D18EB1C956__INCLUDED_)
