// GameForm.cpp : implementation file
//

#include "stdafx.h"
#include "Thunder3.h"
#include "GameForm.h"
#include "MyVar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GameForm dialog


GameForm::GameForm(CWnd* pParent /*=NULL*/)
	: CDialog(GameForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(GameForm)
	m_int = 0;
	//}}AFX_DATA_INIT
}


void GameForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GameForm)
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GameForm, CDialog)
	//{{AFX_MSG_MAP(GameForm)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GameForm message handlers



BOOL GameForm::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_Tab.InsertItem(1,"Tab1");
	m_Tab.InsertItem(2,"Tab2");
	m_Tab.InsertItem(3,"Druid");

	page1.Create(IDD_PAGE1,GetDlgItem(IDC_TAB1));
	page2.Create(IDD_PAGE2,GetDlgItem(IDC_TAB1));
	page3.Create(IDD_PAGE3,GetDlgItem(IDC_TAB1));

	page1.SetParent(GetDlgItem(IDC_TAB1));
	page2.SetParent(GetDlgItem(IDC_TAB1));
	page3.SetParent(GetDlgItem(IDC_TAB1));

	RECT r1;
	this->GetClientRect(&r1);
	m_Tab.MoveWindow(&r1);
	m_Tab.GetClientRect(&r1);
	r1.top+=25;

	page1.ShowWindow(TRUE);

	page1.MoveWindow(&r1);
	page2.MoveWindow(&r1);
	page3.MoveWindow(&r1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void GameForm::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	switch (m_Tab.GetCurSel())
	{
	case 0:
		page1.ShowWindow(TRUE);
		page2.ShowWindow(FALSE);
		page3.ShowWindow(FALSE);
		break;
	case 1:
		page1.ShowWindow(FALSE);
		page2.ShowWindow(TRUE);
		page3.ShowWindow(FALSE);
		break;
	case 2:
		page3.ShowWindow(TRUE);
		page1.ShowWindow(FALSE);
		page2.ShowWindow(FALSE);
	default:
		break;
	}
	*pResult = 0;
}
