// HeroDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "HeroDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeroDlg dialog


CHeroDlg::CHeroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHeroDlg::IDD, pParent)
{
	m_bWriteflg = FALSE;
}


void CHeroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHeroDlg)
	DDX_Text(pDX, IDC_LEVEL_EDIT, m_level);
	DDX_Text(pDX, IDC_NAME_EDIT, m_name);
	DDX_Text(pDX, IDC_SCORE_EDIT, m_score);
	DDV_MinMaxInt(pDX, m_score, 0, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHeroDlg, CDialog)
	//{{AFX_MSG_MAP(CHeroDlg)
	ON_BN_CLICKED(IDOK_BTN, OnBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeroDlg message handlers

void CHeroDlg::OnOK() 
{

}

void CHeroDlg::SetWriteFlg(BOOL bflg)
{
	m_bWriteflg = bflg;
}

int CHeroDlg::DoModal() 
{
	char pszTmp[128] = {0};

	//��ȡ�����ļ�
	GetPrivateProfileString("HERO", "name", "0", 
		pszTmp, 127, ".\\setup.ini");
	m_name = CString(pszTmp);

	if(!m_bWriteflg)
	{
		GetPrivateProfileString("HERO", "score", "0", 
			pszTmp, 127, ".\\setup.ini");
		m_score = atoi(pszTmp);
		GetPrivateProfileString("HERO", "level", "0", 
			pszTmp, 127, ".\\setup.ini");
		m_level = atoi(pszTmp);
		
	}

	return CDialog::DoModal();
}

void CHeroDlg::OnBtn() 
{
	UpdateData(TRUE);
	if(m_bWriteflg)
	{
		CString tmp;
		tmp.Format("%d", m_score);
		WritePrivateProfileString("HERO", "name", m_name, ".\\setup.ini");
		WritePrivateProfileString("HERO", "score", tmp, ".\\setup.ini");
		tmp.Format("%d", m_level);
		WritePrivateProfileString("HERO", "level", tmp, ".\\setup.ini");
	}
	m_bWriteflg = FALSE;

	CDialog::OnOK();
}

BOOL CHeroDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_bWriteflg)
	{
		SetDlgItemText(IDOK_BTN, "��¼");
	}
	
	return TRUE; 
}
