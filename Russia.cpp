#include "stdafx.h"
#include "Tetris.h"
#include "Russia.h"

#include "HeroDlg.h"

//////////////////////////////////////////////////////////////////////////
//构造函数
//////////////////////////////////////////////////////////////////////////
CRussia::CRussia()
{
	bkMap.LoadBitmap(IDB_BACK);
	fkMap.LoadBitmap(IDB_FANGKUAI);
}

//////////////////////////////////////////////////////////////////////////
//析构函数
//////////////////////////////////////////////////////////////////////////
CRussia::~CRussia()
{
}
//////////////////////////////////////////////////////////////////////////
//行消除函数
//////////////////////////////////////////////////////////////////////////
void CRussia::LineDelete()
{
	int m=0;		//本次共消去的行数
	bool flag=0;
	for(int i=0;i<m_RowCount;i++)
	{
		//检查要不要消行
		flag=true;
		for(int j=0;j<m_ColCount;j++)
		{
			if(Russia[i][j]==0)
			{
				flag=false;
			}
		}

		//如果要
		if(flag==true)
		{
			m++;
			for(int k=i;k>0;k--)
			{
				//上行给下行
				for(int l=0;l<m_ColCount;l++)
				{
					Russia[k][l]=Russia[k-1][l];
				}
			}
			//第一行为零
			for(int l=0;l<m_ColCount;l++)
			{
				Russia[0][l]=0;
			}
		}
	}

	DrawWill();
	//加分
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

	//速度
	m_Speed=320 - m_Level * 20;
	
	if(end)
	{
		HeroWrite();
	}

}
//////////////////////////////////////////////////////////////////////////
//移动方块
//////////////////////////////////////////////////////////////////////////
void CRussia::Move(int direction)
{
	if(end) return;
	
	switch(direction)
	{
		//左
	case KEY_LEFT:
		if(Meet(Now,KEY_LEFT,NowPosition)) break;
		NowPosition.y--;
		break;
		//右
	case KEY_RIGHT:
		if(Meet(Now,KEY_RIGHT,NowPosition)) break;
		NowPosition.y++;
		break;
		//下
	case KEY_DOWN:
		if(Meet(Now,KEY_DOWN,NowPosition))
		{
			LineDelete();			
			break;
		}
		NowPosition.x++;
		break;
		//上
	case KEY_UP:
		Meet(Now,KEY_UP,NowPosition);
		break;
	default:
		break;
	}
}
//////////////////////////////////////////////////////////////////////////
//方块旋转
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
			After[i][j]=0;	//存放变换后的方块矩阵
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
		}	//把变换后的矩阵移到左上角
	}
	//判断是否接触，是：返回失败
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
//判碰撞,遇到了边界或者有其他方块档住
//////////////////////////////////////////////////////////////////////////
bool CRussia::Meet(int a[][4],int direction,CPoint p)
{
	int i,j;
	//先把原位置清0 
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
				case 1:	//左移
					if((p.y+j-1)<0) goto exit;
					if(Russia[p.x+i][p.y+j-1]==1) goto exit;
					break;
				case 2://右移
					if((p.y+j+1)>=m_ColCount) goto exit;
					if(Russia[p.x+i][p.y+j+1]==1) goto exit;
					break;
				case 3://下移
					if((p.x+i+1)>=m_RowCount) goto exit;
					if(Russia[p.x+i+1][p.y+j]==1) goto exit;
					break;
				case 4://变换
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
	//移动位置，重新给数组赋值
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
//绘将出现的方块图
//////////////////////////////////////////////////////////////////////////
void CRussia::DrawWill()
{
	int i,j;
	int k=4,l=4;
	
    //把将要出现的方块给当前数组，并把将要出现数组赋值为零
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			Now[i][j]=Will[i][j];
			Will[i][j]=0;
		}
	}
	//初始化随即数种子
	srand(GetTickCount());
	int nTemp=rand()%Count;
	//各种图形
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
	//把变换后的矩阵移到左上角
	for(i=k;i<4;i++)
	{
		for(j=l;j<4;j++)
		{
			Will[i-k][j-l]=tmp[i][j];
		}
	}
	//开始位置
	NowPosition.x=0;
	NowPosition.y=m_ColCount/2;
}
//////////////////////////////////////////////////////////////////////////
//绘游戏界面
//////////////////////////////////////////////////////////////////////////
void CRussia::DrawBK(CDC*pDC)
{
	CDC Dc;
	if(Dc.CreateCompatibleDC(pDC)==FALSE)
	{
		AfxMessageBox("Can't create DC");
	}
	//画背景
    Dc.SelectObject(bkMap);
	pDC->BitBlt(0,0,540,550,&Dc,0,0,SRCCOPY);
    //画分数，速度，难度
	DrawScore(pDC);
    //如果有方块，显示方块
	//游戏区
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
	//预先图形
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
//绘分数和等级
//////////////////////////////////////////////////////////////////////////
void CRussia::DrawScore(CDC*pDC)
{
	int nOldDC=pDC->SaveDC();	
	//设置字体
	CFont font;    
	if(0==font.CreatePointFont(300,"Comic Sans MS"))
	{
		AfxMessageBox("Can't Create Font");
	}
	pDC->SelectObject(&font);
    //设置字体颜色及其背景颜色
	CString str;
	pDC->SetTextColor(RGB(39,244,10));
	pDC->SetBkColor(RGB(255,255,0));
    //输出数字
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
//游戏开始
//////////////////////////////////////////////////////////////////////////
void CRussia::GameStart()
{
	end=false;//运行结束标志
    m_Score=0;		//初始分数
	m_RowCount=18;	//行数
	m_ColCount=12;	//列数
	Count=7;		//方块种类
	m_CountLine = 0;//合计消除行数为0

	char pszTmp[128] = {0};
					//读取当前游戏等级
	GetPrivateProfileString("SETUP", "level", "1", 
			pszTmp, 127, ".\\setup.ini");

	m_Level = atoi(pszTmp);		//初始等级
	m_Speed=320 - m_Level * 20;	//初始速度
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
	//开始时将要出现方块没有生成,其不能赋值给当前方块数组，所以连续调用两次
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
		
		dlg.SetWriteFlg(TRUE);		//设置可写入标志
		
		dlg.m_level = m_Level;		//设置等级
		
		dlg.m_score = m_Score;		//设置分数
		
		dlg.DoModal();				//弹出对话框
	}
	else
	{
		AfxMessageBox("游戏结束,您未能进入英雄榜!");
	}

}
