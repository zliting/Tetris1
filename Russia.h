#ifndef __RUSSIA_H__
#define __RUSSIA_H__

#include "Rule.h"

#define KEY_LEFT 1
#define KEY_RIGHT 2
#define KEY_DOWN 3
#define KEY_UP 4

class CRussia  
{
public:
	void HeroWrite();
	CRussia();
	virtual ~CRussia();
	void LineDelete();
	void Move(int direction);
	bool Change(int a[][4],CPoint p,int  b[][100]);
	bool Meet(int a[][4],int direction,CPoint p);//判碰撞
	void DrawWill();//绘将要出现方块
	void DrawBK(CDC*pDC);//绘界面
	void DrawScore(CDC*pDC);//绘分数
	void GameStart();//游戏开始
	
	int Russia[100][100];//游戏数组
	int Now[4][4];	// 当前图形
	int Will[4][4];	//上一图形
	int After[4][4];	//变换后的图形
	CPoint NowPosition;	//当前图形的左上角位置
	int Count;		//当前可能出现的图形形状数,
	bool end;  //游戏结束
	int m_Level;	//级别
	int m_Speed;	//速度
	int m_Score;    //分数
	int m_CountLine;//合计消除行数
	int m_RowCount,m_ColCount;//行列数
	CBitmap fkMap;//方块
	CBitmap bkMap;//界面
	CRule rule;//游戏规则对象
};

#endif