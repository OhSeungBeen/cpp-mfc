#pragma once
#include "Tool.h"

class CLineTool : public Tool
{
private:
	CPoint m_startPoint; // ������
	CPoint m_endPoint; // ����
	int m_thinkness; // �� �β� 
	COLORREF m_outerColor; // �� 1 (�ܺ�)

public:
	CLineTool(void);
	virtual ~CLineTool(void);

	void Draw(CDC*); // �׸��� �Լ�
	void SetStartPoint(CPoint startPoint); // ������ ���� �Լ�
	void SetEndPoint(CPoint endPoint); // ���� ���� �Լ�
	void SetProperty(int thinkness, COLORREF outerColor); // �Ӽ� ���� �Լ�
};
