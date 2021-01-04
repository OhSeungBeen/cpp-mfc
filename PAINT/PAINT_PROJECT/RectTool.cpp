#include "StdAfx.h"
#include "RectTool.h"

CRectTool::CRectTool(void)
{
}

CRectTool::~CRectTool(void)
{
}

void CRectTool::Draw(CDC* pDc)
{
	CPen pen(PS_SOLID, m_thinkness, m_outerColor); // �� ����
	CBrush brush;

	if(m_innerColor == NULL) // ���� ����̸�
	{
		brush.CreateStockObject( NULL_BRUSH );
	}
	else // ���� ��� �̸�
	{
		brush.CreateSolidBrush(m_innerColor);
	}
	
	CBrush* oldBrush = pDc->SelectObject(&brush);
	CPen* oldPen = pDc->SelectObject(&pen);

	pDc->Rectangle(m_startPoint.x, m_startPoint.y, m_endPoint.x, m_endPoint.y); // �簢�� ����
	
	pDc->SelectObject(oldPen); // �� �ݳ�
	pDc->SelectObject(oldBrush); // �귯�� �ݳ�
}

// ������ ���� �Լ�
void CRectTool::SetStartPoint( CPoint startPoint )
{
	m_startPoint = startPoint;
}

// ���� ���� �Լ�
void CRectTool::SetEndPoint( CPoint endPoint )
{
	m_endPoint = endPoint;
}

// �Ӽ� ���� �Լ�
void CRectTool::SetProperty( int thinkness, COLORREF outerColor, COLORREF innerColor )
{
	m_thinkness = thinkness;
	m_outerColor = outerColor;
	m_innerColor = innerColor;
}


