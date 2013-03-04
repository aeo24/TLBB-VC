#if !defined(AFX_TAB1_H__E2809A80_5F0E_4526_94B0_E7651A5228F1__INCLUDED_)
#define AFX_TAB1_H__E2809A80_5F0E_4526_94B0_E7651A5228F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tab1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// tab1 dialog

class tab1 : public CDialog
{
// Construction
public:
	tab1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(tab1)
	enum { IDD = IDD_PAGE1 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tab1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(tab1)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_edit1;
	afx_msg void OnBnClickedButton2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB1_H__E2809A80_5F0E_4526_94B0_E7651A5228F1__INCLUDED_)
