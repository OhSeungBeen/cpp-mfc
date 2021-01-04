#pragma once
#include "Tool.h"

class CRectTool : public Tool
{
private:
	CPoint m_startPoint; // ������
	CPoint m_endPoint; // ����
	int m_thinkness; // �� �β� 
	COLORREF m_outerColor; // �� 1 (�ܺ�)
	COLORREF m_innerColor; // �� 2 (����)

public:
	CRectTool(void);
	virtual ~CRectTool(void);

	void Draw(CDC*); // �׸��� �Լ�
	void SetStartPoint(CPoint startPoint); // ������ ���� �Լ�
	void SetEndPoint(CPoint endPoint); // ���� ���� �Լ�
	void SetProperty(int thinkness, COLORREF outerColor, COLORREF innerColor); // �Ӽ� ���� �Լ�
};
