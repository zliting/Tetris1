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
	//û�п�ʼ����ʾ����
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
	CAboutDlg aboutDlg;		//���ɹ��ڶԻ���
	aboutDlg.DoModal();		//�������ڶԻ���
}

void CTetrisView::OnHeroList() 
{
	CHeroDlg dlg;			//����Ӣ�۰�Ի���
	dlg.DoModal();			//����Ӣ�۰�Ի���
}

void CTetrisView::OnLevelSetup() 
{
	CLevelDlg	dlg;	//���ɵȼ����öԻ���
	dlg.DoModal();			//�����ȼ����öԻ���
}

void CTetrisView::OnPlayMusic() 
{
	CWnd*   pMain   =   AfxGetMainWnd();   
	CMenu*   pMenu   =   pMain->GetMenu();
	//�жϲ������ֲ˵���ǰ״̬
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
		
		PlayBackMusic(!bCheck);			//���ò��ű������ֹ��ܺ���
	}

}

void CTetrisView::OnStartGame() 
{
	m_bStart = true;
	russia.GameStart();					//����RUSSIA�������Ϸ��ʼ����
	SetTimer(1, russia.m_Speed, NULL);
}

void CTetrisView::OnHelp() 
{
	CHelpDlg dlg;						//���ɰ����Ի���
	dlg.DoModal();						//�����Ի���
}

void CTetrisView::PlayBackMusic(BOOL bCheck)
{
	//ָ���ļ�������
	if(bCheck)
	{								//��������
		sndPlaySound("music.wav",SND_ASYNC); 
	}
	else
	{								//ֹͣ����
		sndPlaySound(NULL,SND_PURGE); 
	}

}

void CTetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//û�п�ʼ
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
	//�ػ�
	CDC* pDC=GetDC();
	russia.DrawBK(pDC);
	ReleaseDC(pDC);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTetrisView::OnTimer(UINT nIDEvent) 
{
	//����
	russia.Move(KEY_DOWN);
	//�ػ�
	russia.DrawBK(GetDC());
	//�ر�TIME1
	KillTimer(1);
	//�����ٶ�
	SetTimer(1, russia.m_Speed, NULL);

	CView::OnTimer(nIDEvent);
}
