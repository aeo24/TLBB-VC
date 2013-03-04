#if !defined(AFX_TAB2_H__4CFD29FD_E7E8_4BA8_9911_D3C56E03DB1D__INCLUDED_)
#define AFX_TAB2_H__4CFD29FD_E7E8_4BA8_9911_D3C56E03DB1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tab2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// tab2 dialog

class tab2 : public CDialog
{
// Construction
public:
	tab2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(tab2)
	enum { IDD = IDD_PAGE2 };
	CString	m_scripts;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tab2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(tab2)
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton2();
	afx_msg void OnButton8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB2_H__4CFD29FD_E7E8_4BA8_9911_D3C56E03DB1D__INCLUDED_)
