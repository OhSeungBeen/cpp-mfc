#include "StdAfx.h"
#include "CircleTool.h"

CCircleTool::CCircleTool(void)
{
}

CCircleTool::~CCircleTool(void)
{
}

void CCircleTool::Draw(CDC* pDc)
{
	
	CPen pen(PS_SOLID, m_thinkness, m_outerColor); // �� ����
	CBrush brush(m_innerColor); // �귯�� ����
	
	CPen* oldPen = pDc->SelectObject(&pen);
	CBrush* oldBrush = pDc->SelectObject(&brush);

	pDc->Ellipse(m_startPoint.x, m_startPoint.y, m_endPoint.x, m_endPoint.y); // �� ����
	
	pDc->SelectObject(oldPen); // �� �ݳ�
	pDc->SelectObject(oldBrush); // �귯�� �ݳ�
}

// ������ ���� �Լ�
void CCircleTool::SetStartPoint( CPoint startPoint )
{
	m_startPoint = startPoint;
}

// ���� ���� �Լ�
void CCircleTool::SetEndPoint( CPoint endPoint )
{
	m_endPoint = endPoint;
}

// �Ӽ� ���� �Լ�
void CCircleTool::SetProperty( int thinkness, COLORREF outerColor, COLORREF innerColor )
{
	m_thinkness = thinkness;
	m_outerColor = outerColor;
	m_innerColor = innerColor;
}


