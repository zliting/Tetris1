#if !defined(AFX_LEVELDLG_H__E423F5C3_7698_4365_A009_4E6C7BC62189__INCLUDED_)
#define AFX_LEVELDLG_H__E423F5C3_7698_4365_A009_4E6C7BC62189__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LevelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLevelDlg dialog

class CLevelDlg : public CDialog
{
// Construction
public:
	CLevelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLevelDlg)
	enum { IDD = IDD_LEVEL_DLG };
	int		m_level;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLevelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLevelDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEVELDLG_H__E423F5C3_7698_4365_A009_4E6C7BC62189__INCLUDED_)
