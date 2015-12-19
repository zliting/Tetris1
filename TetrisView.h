// TetrisView.h : interface of the CTetrisView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRISVIEW_H__15119D9F_0297_4F5D_BDB0_A936BFFD13F7__INCLUDED_)
#define AFX_TETRISVIEW_H__15119D9F_0297_4F5D_BDB0_A936BFFD13F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Russia.h"

class CTetrisView : public CView
{
protected: // create from serialization only
	CTetrisView();
	DECLARE_DYNCREATE(CTetrisView)

// Attributes
public:
	CTetrisDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrisView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void PlayBackMusic(BOOL bCheck);
	virtual ~CTetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	BOOL m_bStart;
	CRussia russia;

// Generated message map functions
protected:
	//{{AFX_MSG(CTetrisView)
	afx_msg void OnAbout();
	afx_msg void OnHeroList();
	afx_msg void OnLevelSetup();
	afx_msg void OnPlayMusic();
	afx_msg void OnStartGame();
	afx_msg void OnHelp();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TetrisView.cpp
inline CTetrisDoc* CTetrisView::GetDocument()
   { return (CTetrisDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRISVIEW_H__15119D9F_0297_4F5D_BDB0_A936BFFD13F7__INCLUDED_)
