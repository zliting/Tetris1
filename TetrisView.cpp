// TetrisView.cpp : implementation of the CTetrisView class
//

#include "stdafx.h"
#include "Tetris.h"

#include "TetrisDoc.h"
#include "TetrisView.h"

#include "HelpDlg.h"
#include "HeroDlg.h"
#include "LevelDlg.h"
#include "Russia.h"

#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTetrisView

IMPLEMENT_DYNCREATE(CTetrisView, CView)

BEGIN_MESSAGE_MAP(CTetrisView, CView)
	//{{AFX_MSG_MAP(CTetrisView)
	ON_COMMAND(IDR_ABOUT, OnAbout)
	ON_COMMAND(IDR_HERO_LIST, OnHeroList)
	ON_COMMAND(IDR_LEVEL_SETUP, OnLevelSetup)
	ON_COMMAND(IDR_PLAY_MUSIC, OnPlayMusic)
	ON_COMMAND(IDR_START_GAME, OnStartGame)
	ON_COMMAND(IDR_HELP, OnHelp)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTetrisView construction/destruction

CTetrisView::CTetrisView()
{
	m_bStart = FALSE;
}

CTetrisView::~CTetrisView()
{
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisView drawing

void CTetrisView::OnDraw(CDC* pDC)
{
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC Dc;
	if(Dc.CreateCompatibleDC(pDC)==FALSE)
		AfxMessageBox("Can't create DC");
	//没有开始，显示封面
	if( m_bStart)
	{
		russia.DrawBK(pDC);
	}

}

/////////////////////////////////////////////////////////////////////////////
// CTetrisView printing

BOOL CTetrisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTetrisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTetrisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisView diagnostics

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTetrisView message handlers
void CTetrisView::OnAbout() 
{
	CAboutDlg aboutDlg;		//生成关于对话框
	aboutDlg.DoModal();		//弹出关于对话框
}

void CTetrisView::OnHeroList() 
{
	CHeroDlg dlg;			//生成英雄榜对话框
	dlg.DoModal();			//弹出英雄榜对话框
}

void CTetrisView::OnLevelSetup() 
{
	CLevelDlg	dlg;	//生成等级设置对话框
	dlg.DoModal();			//弹出等级设置对话框
}

void CTetrisView::OnPlayMusic() 
{
	CWnd*   pMain   =   AfxGetMainWnd();   
	CMenu*   pMenu   =   pMain->GetMenu();
	//判断播放音乐菜单当前状态
	BOOL bCheck = (BOOL)pMenu->GetMenuState(IDR_PLAY_MUSIC, MF_CHECKED);
	
	if(m_bStart)
	{
		if(bCheck)
		{
			pMenu->CheckMenuItem(IDR_PLAY_MUSIC, MF_BYCOMMAND | MF_UNCHECKED);
		}
		else
		{
			pMenu->CheckMenuItem(IDR_PLAY_MUSIC, MF_BYCOMMAND | MF_CHECKED);
		}
		
		PlayBackMusic(!bCheck);			//调用播放背景音乐功能函数
	}

}

void CTetrisView::OnStartGame() 
{
	m_bStart = true;
	russia.GameStart();					//调用RUSSIA对象的游戏开始函数
	SetTimer(1, russia.m_Speed, NULL);
}

void CTetrisView::OnHelp() 
{
	CHelpDlg dlg;						//生成帮助对话框
	dlg.DoModal();						//弹出对话框
}

void CTetrisView::PlayBackMusic(BOOL bCheck)
{
	//指定文件并播放
	if(bCheck)
	{								//播放音乐
		sndPlaySound("music.wav",SND_ASYNC); 
	}
	else
	{								//停止播放
		sndPlaySound(NULL,SND_PURGE); 
	}

}

void CTetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//没有开始
	if(!m_bStart)
		return;
	
	switch(nChar)
	{
	case VK_LEFT:
		russia.Move(KEY_LEFT);
		break;
	case VK_RIGHT:
		russia.Move(KEY_RIGHT);
		break;		
	case VK_UP:
		russia.Move(KEY_UP);
		break;
	case VK_DOWN:
		russia.Move(KEY_DOWN);
		break;
	}
	//重画
	CDC* pDC=GetDC();
	russia.DrawBK(pDC);
	ReleaseDC(pDC);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTetrisView::OnTimer(UINT nIDEvent) 
{
	//下移
	russia.Move(KEY_DOWN);
	//重画
	russia.DrawBK(GetDC());
	//关闭TIME1
	KillTimer(1);
	//调整速度
	SetTimer(1, russia.m_Speed, NULL);

	CView::OnTimer(nIDEvent);
}
