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
	bool Meet(int a[][4],int direction,CPoint p);//����ײ
	void DrawWill();//�潫Ҫ���ַ���
	void DrawBK(CDC*pDC);//�����
	void DrawScore(CDC*pDC);//�����
	void GameStart();//��Ϸ��ʼ
	
	int Russia[100][100];//��Ϸ����
	int Now[4][4];	// ��ǰͼ��
	int Will[4][4];	//��һͼ��
	int After[4][4];	//�任���ͼ��
	CPoint NowPosition;	//��ǰͼ�ε����Ͻ�λ��
	int Count;		//��ǰ���ܳ��ֵ�ͼ����״��,
	bool end;  //��Ϸ����
	int m_Level;	//����
	int m_Speed;	//�ٶ�
	int m_Score;    //����
	int m_CountLine;//�ϼ���������
	int m_RowCount,m_ColCount;//������
	CBitmap fkMap;//����
	CBitmap bkMap;//����
	CRule rule;//��Ϸ�������
};

#endif