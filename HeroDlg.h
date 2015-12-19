#if !defined(AFX_HERODLG_H__6D0A81F3_A5F6_4816_899E_ACC62CDE229A__INCLUDED_)
#define AFX_HERODLG_H__6D0A81F3_A5F6_4816_899E_ACC62CDE229A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HeroDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHeroDlg dialog

// CHeroDlg dialog

class CHeroDlg : public CDialog
{
	// Construction
public:
	void SetWriteFlg(BOOL bflg);
	CHeroDlg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CHeroDlg)
	enum { IDD = IDD_HERO_LIST };
	int		m_level;
	CString	m_name;
	int		m_score;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeroDlg)
public:
	virtual int DoModal();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CHeroDlg)
	virtual void OnOK();
	afx_msg void OnBtn();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bWriteflg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HERODLG_H__6D0A81F3_A5F6_4816_899E_ACC62CDE229A__INCLUDED_)
