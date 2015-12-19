#include "stdafx.h"
#include "Tetris.h"
#include "Russia.h"

#include "HeroDlg.h"

//////////////////////////////////////////////////////////////////////////
//���캯��
//////////////////////////////////////////////////////////////////////////
CRussia::CRussia()
{
	bkMap.LoadBitmap(IDB_BACK);
	fkMap.LoadBitmap(IDB_FANGKUAI);
}

//////////////////////////////////////////////////////////////////////////
//��������
//////////////////////////////////////////////////////////////////////////
CRussia::~CRussia()
{
}
//////////////////////////////////////////////////////////////////////////
//����������
//////////////////////////////////////////////////////////////////////////
void CRussia::LineDelete()
{
	int m=0;		//���ι���ȥ������
	bool flag=0;
	for(int i=0;i<m_RowCount;i++)
	{
		//���Ҫ��Ҫ����
		flag=true;
		for(int j=0;j<m_ColCount;j++)
		{
			if(Russia[i][j]==0)
			{
				flag=false;
			}
		}

		//���Ҫ
		if(flag==true)
		{
			m++;
			for(int k=i;k>0;k--)
			{
				//���и�����
				for(int l=0;l<m_ColCount;l++)
				{
					Russia[k][l]=Russia[k-1][l];
				}
			}
			//��һ��Ϊ��
			for(int l=0;l<m_ColCount;l++)
			{
				Russia[0][l]=0;
			}
		}
	}

	DrawWill();
	//�ӷ�
	switch(m)
	{
	case 1:
		m_Score= m_Score + 10 + m_Level * 10;
		break;
	case 2:
		m_Score= m_Score + 30 + m_Level * 10;
		break;
	case 3:
		m_Score= m_Score + 50 + m_Level * 10;
		break;
	case 4:
		m_Score= m_Score + 100 + m_Level * 10;
		break;
	default:
		break;
	}
	
	m_CountLine+=m;

	m_Level = rule.UpLevel(m_CountLine);

	end = rule.Win(Now, Russia, NowPosition);

	//�ٶ�
	m_Speed=320 - m_Level * 20;
	
	if(end)
	{
		HeroWrite();
	}

}
//////////////////////////////////////////////////////////////////////////
//�ƶ�����
//////////////////////////////////////////////////////////////////////////
void CRussia::Move(int direction)
{
	if(end) return;
	
	switch(direction)
	{
		//��
	case KEY_LEFT:
		if(Meet(Now,KEY_LEFT,NowPosition)) break;
		NowPosition.y--;
		break;
		//��
	case KEY_RIGHT:
		if(Meet(Now,KEY_RIGHT,NowPosition)) break;
		NowPosition.y++;
		break;
		//��
	case KEY_DOWN:
		if(Meet(Now,KEY_DOWN,NowPosition))
		{
			LineDelete();			
			break;
		}
		NowPosition.x++;
		break;
		//��
	case KEY_UP:
		Meet(Now,KEY_UP,NowPosition);
		break;
	default:
		break;
	}
}
//////////////////////////////////////////////////////////////////////////
//������ת
//////////////////////////////////////////////////////////////////////////
bool CRussia::Change(int a[][4],CPoint p,int  b[][100])
{
	int tmp[4][4];
	int i,j;
	int k=4,l=4;
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			tmp[i][j]=a[j][3-i];
			After[i][j]=0;	//��ű任��ķ������
		}
	}
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(tmp[i][j]==1)
			{
				if(k>i) k=i;
				if(l>j) l=j;
			}
		}
	}
	for(i=k;i<4;i++)
	{
		for(j=l;j<4;j++)
		{
			After[i-k][j-l]=tmp[i][j];
		}	//�ѱ任��ľ����Ƶ����Ͻ�
	}
	//�ж��Ƿ�Ӵ����ǣ�����ʧ��
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{	
			if(After[i][j]==0)
			{
				continue;
			}
			if(((p.x+i)>=m_RowCount)||((p.y+j)<0)||((p.y+j)>=m_ColCount))
			{
				return false;
			}
			if(b[p.x+i][p.y+j]==1)
			{
				return false;
			}
		}
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
//����ײ,�����˱߽�������������鵵ס
//////////////////////////////////////////////////////////////////////////
bool CRussia::Meet(int a[][4],int direction,CPoint p)
{
	int i,j;
	//�Ȱ�ԭλ����0 
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j]==1)
			{
				Russia[p.x+i][p.y+j]=0;
			}
		}
	}
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j]==1)
			{
				switch(direction)
				{
				case 1:	//����
					if((p.y+j-1)<0) goto exit;
					if(Russia[p.x+i][p.y+j-1]==1) goto exit;
					break;
				case 2://����
					if((p.y+j+1)>=m_ColCount) goto exit;
					if(Russia[p.x+i][p.y+j+1]==1) goto exit;
					break;
				case 3://����
					if((p.x+i+1)>=m_RowCount) goto exit;
					if(Russia[p.x+i+1][p.y+j]==1) goto exit;
					break;
				case 4://�任
					if(!Change(a,p,Russia)) goto exit;				
					for(i=0;i<4;i++)
					{
						for(j=0;j<4;j++)
						{
							Now[i][j]=After[i][j];
							a[i][j]=Now[i][j];
						}
					}
					return false;
					break;
				}
			}
		}
	}
			
	int x,y;
	x=p.x;
	y=p.y;
	//�ƶ�λ�ã����¸����鸳ֵ
	switch(direction)
	{
	case 1:
		y--;break;
	case 2:
		y++;break;
	case 3:
		x++;break;
	case 4:
		break;
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j]==1)
			{
				Russia[x+i][y+j]=1;
			}
		}
	}
			
	return false;
exit:
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j]==1)
			{
				Russia[p.x+i][p.y+j]=1;
			}
		}
	}
	return true;	
}
//////////////////////////////////////////////////////////////////////////
//�潫���ֵķ���ͼ
//////////////////////////////////////////////////////////////////////////
void CRussia::DrawWill()
{
	int i,j;
	int k=4,l=4;
	
    //�ѽ�Ҫ���ֵķ������ǰ���飬���ѽ�Ҫ�������鸳ֵΪ��
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			Now[i][j]=Will[i][j];
			Will[i][j]=0;
		}
	}
	//��ʼ���漴������
	srand(GetTickCount());
	int nTemp=rand()%Count;
	//����ͼ��
	switch(nTemp)
	{
	case 0:
		Will[0][0]=1;
		Will[0][1]=1;
		Will[1][0]=1;
		Will[1][1]=1;
		break;
	case 1:
		Will[0][0]=1;
		Will[0][1]=1;
		Will[1][0]=1;
		Will[2][0]=1;
		break;
	case 2:
		Will[0][0]=1;
		Will[0][1]=1;
		Will[1][1]=1;
		Will[2][1]=1;
		break;
	case 3:
		Will[0][1]=1;
		Will[1][0]=1;
		Will[1][1]=1;
		Will[2][0]=1;
		break;
	case 4:
		Will[0][0]=1;
		Will[1][0]=1;
		Will[1][1]=1;
		Will[2][1]=1;
		break;
	case 5:
		Will[0][0]=1;
		Will[1][0]=1;
		Will[1][1]=1;
		Will[2][0]=1;
		break;
	case 6:
		Will[0][0]=1;
		Will[1][0]=1;
		Will[2][0]=1;
		Will[3][0]=1;
		break;
	default:
		break;
	}
	
	int tmp[4][4];
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			tmp[i][j]=Will[j][3-i];
		}
	}
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(tmp[i][j]==1)
			{
				if(k>i) k=i;
				if(l>j) l=j;
			}
		}
	}
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			Will[i][j]=0;
		}
	}
	//�ѱ任��ľ����Ƶ����Ͻ�
	for(i=k;i<4;i++)
	{
		for(j=l;j<4;j++)
		{
			Will[i-k][j-l]=tmp[i][j];
		}
	}
	//��ʼλ��
	NowPosition.x=0;
	NowPosition.y=m_ColCount/2;
}
//////////////////////////////////////////////////////////////////////////
//����Ϸ����
//////////////////////////////////////////////////////////////////////////
void CRussia::DrawBK(CDC*pDC)
{
	CDC Dc;
	if(Dc.CreateCompatibleDC(pDC)==FALSE)
	{
		AfxMessageBox("Can't create DC");
	}
	//������
    Dc.SelectObject(bkMap);
	pDC->BitBlt(0,0,540,550,&Dc,0,0,SRCCOPY);
    //���������ٶȣ��Ѷ�
	DrawScore(pDC);
    //����з��飬��ʾ����
	//��Ϸ��
	for(int i=0;i<m_RowCount;i++)
	{
		for(int j=0;j<m_ColCount;j++)
		{
			if(Russia[i][j]==1)
			{
				Dc.SelectObject(fkMap);
				pDC->BitBlt(j*30,i*30,30,30,&Dc,0,0,SRCCOPY);
			}
		}
	}
	//Ԥ��ͼ��
	for(int n=0;n<4;n++)
	{
		for(int m=0;m<4;m++)
		{
			if(Will[n][m]==1)
			{	
				Dc.SelectObject(fkMap);
				pDC->BitBlt(365+m*30,240+n*30,30,30,&Dc,0,0,SRCCOPY);
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//������͵ȼ�
//////////////////////////////////////////////////////////////////////////
void CRussia::DrawScore(CDC*pDC)
{
	int nOldDC=pDC->SaveDC();	
	//��������
	CFont font;    
	if(0==font.CreatePointFont(300,"Comic Sans MS"))
	{
		AfxMessageBox("Can't Create Font");
	}
	pDC->SelectObject(&font);
    //����������ɫ���䱳����ɫ
	CString str;
	pDC->SetTextColor(RGB(39,244,10));
	pDC->SetBkColor(RGB(255,255,0));
    //�������
	str.Format("%d",m_Level);
	if(m_Level>=0)
		pDC->TextOut(420,120,str);

	str.Format("%d",m_CountLine);	
	if(m_Speed>=0)	
		pDC->TextOut(420,64,str);
	
	str.Format("%d",m_Score);	
	if(m_Score>=0)
		pDC->TextOut(420,2,str);
	
	pDC->RestoreDC(nOldDC);
}
//////////////////////////////////////////////////////////////////////////
//��Ϸ��ʼ
//////////////////////////////////////////////////////////////////////////
void CRussia::GameStart()
{
	end=false;//���н�����־
    m_Score=0;		//��ʼ����
	m_RowCount=18;	//����
	m_ColCount=12;	//����
	Count=7;		//��������
	m_CountLine = 0;//�ϼ���������Ϊ0

	char pszTmp[128] = {0};
					//��ȡ��ǰ��Ϸ�ȼ�
	GetPrivateProfileString("SETUP", "level", "1", 
			pszTmp, 127, ".\\setup.ini");

	m_Level = atoi(pszTmp);		//��ʼ�ȼ�
	m_Speed=320 - m_Level * 20;	//��ʼ�ٶ�
	rule.SetLevel(m_Level);

	for(int i=0;i<m_RowCount;i++)
	{
		for(int j=0;j<m_ColCount;j++)
		{
			Russia[i][j]=0;
		}
	}	
	for(i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			Now[i][j]=0;
			Will[i][j]=0;
		}
	}
	//��ʼʱ��Ҫ���ַ���û������,�䲻�ܸ�ֵ����ǰ�������飬����������������
	DrawWill();	
	DrawWill();
}

void CRussia::HeroWrite()
{
	CHeroDlg dlg;

	char pszTmp[128] = {0};

	int nHighScore = 0;
	
	GetPrivateProfileString("HERO", "score", "0", 
		pszTmp, 127, ".\\hero.ini");

	nHighScore = atoi(pszTmp);

	if(m_Score>nHighScore)
	{
		
		dlg.SetWriteFlg(TRUE);		//���ÿ�д���־
		
		dlg.m_level = m_Level;		//���õȼ�
		
		dlg.m_score = m_Score;		//���÷���
		
		dlg.DoModal();				//�����Ի���
	}
	else
	{
		AfxMessageBox("��Ϸ����,��δ�ܽ���Ӣ�۰�!");
	}

}
