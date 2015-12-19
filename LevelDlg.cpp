// LevelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "LevelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLevelDlg dialog


CLevelDlg::CLevelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLevelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLevelDlg)
	m_level = 0;
	//}}AFX_DATA_INIT
}


void CLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLevelDlg)
	DDX_Text(pDX, IDC_LEVEL_EDIT, m_level);
	DDV_MinMaxInt(pDX, m_level, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLevelDlg, CDialog)
	//{{AFX_MSG_MAP(CLevelDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLevelDlg message handlers

void CLevelDlg::OnOK() 
{
	if(UpdateData(TRUE))
	{
		CString tmp;
		tmp.Format("%d", m_level);
		WritePrivateProfileString("SETUP", "level", tmp, ".\\setup.ini");
		CDialog::OnOK();
	}
}

void CLevelDlg::OnCancel() 
{

	CDialog::OnCancel();
}

BOOL CLevelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char pszTmp[128] = {0};

	GetPrivateProfileString("SETUP", "level", "0", 
		pszTmp, 127, ".\\setup.ini");
	m_level = atoi(pszTmp);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
