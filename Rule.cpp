#include "stdafx.h"
#include "Rule.h"

CRule::CRule()
{
}

CRule::~CRule()
{
}

void CRule::SetLevel(int nLevel)
{
	m_nLevel = nLevel;
}

int CRule::UpLevel(int nLine)
{
	if(nLine / 30)
	{
		m_nLevel++;
	}
	return m_nLevel;
}

bool CRule::Win(int Now[4][4], int Russia [100][100], CPoint NowPosition)
{
	if(m_nLevel == 11)
	{//消除行数已经超过10级,游戏结束
		return true;
	}

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(Now[i][j]==1)
			{//到了顶点
				if(Russia[i+NowPosition.x][j+NowPosition.y]==1)
				{
					return true;
				}
			}
		}
	}

	return false;
}