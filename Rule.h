#ifndef __RULE_H__
#define __RULE_H__

class CRule
{

public:
	CRule();
	~CRule();
	void SetLevel(int nLevel);//���õ�ǰ�ȼ�
	int UpLevel(int nLine);	//�����ж�
	bool Win(int Now[4][4], int Russia [100][100], 	CPoint NowPosition);	//ʤ���ж�
private:
	int m_nLevel;				//��ǰ�ȼ�
};

#endif