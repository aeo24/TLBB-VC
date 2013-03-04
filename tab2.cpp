// tab2.cpp : implementation file
//

#include "stdafx.h"
#include "Thunder3.h"
#include "tab2.h"
#include "classes.h"
#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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


BOOL tab2::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void tab2::OnButton1() 
{

}

void tab2::OnButton2() 
{

}

void tab2::OnButton8() 
{

}
