#if !defined(AFX_TAB3_H__949F3960_5552_4488_BDEB_D7C3C854E82D__INCLUDED_)
#define AFX_TAB3_H__949F3960_5552_4488_BDEB_D7C3C854E82D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tab3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// tab3 dialog

class tab3 : public CDialog
{
// Construction
public:
	tab3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(tab3)
	enum { IDD = IDD_PAGE3 };
	CHotKeyCtrl	m_hotKey_ChaoFeng;
	BOOL	m_check_chaofeng;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tab3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(tab3)
	afx_msg void OnButton1();
	afx_msg void OnCHECKChaoFeng();
	afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString Edit1;
	afx_msg void OnBnClickedButton3();
	int Edit_Int;
	afx_msg void OnBnClickedButton4();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB3_H__949F3960_5552_4488_BDEB_D7C3C854E82D__INCLUDED_)
