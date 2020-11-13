#pragma once
#include "Tool.h"

class CPencilTool : public Tool
{
private:
	CList<CPoint> m_pointList; // ������ ������ ����Ʈ
	int m_thinkness; // �� �β� 
	COLORREF m_outerColor; // �� 1 (�ܺ�)

public:
	CPencilTool(void);
	virtual ~CPencilTool(void);

	void Draw(CDC*); // �׸��� �Լ�
	void addPoint(CPoint point); // ������ �߰� �ϴ� �Լ�( �����̱� ������ ���콺�����϶� ���� ���� ����)
	void SetProperty(int thinkness, COLORREF outerColor); // �Ӽ� ���� �Լ�
};
