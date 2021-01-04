#include "StdAfx.h"
#include "LineTool.h"

CLineTool::CLineTool(void)
{
}

CLineTool::~CLineTool(void)
{
}

void CLineTool::Draw(CDC* pDc)
{

	CPen pen(PS_SOLID, m_thinkness, m_outerColor); // �� ����
	CPen* oldPen = pDc->SelectObject(&pen);

	// ������ �׸���.
	pDc->MoveTo(m_startPoint);
	pDc->LineTo(m_endPoint);

	pDc->SelectObject(oldPen); // �� �ݳ�

}

// ������ ���� �Լ�
void CLineTool::SetStartPoint( CPoint startPoint )
{
	m_startPoint = startPoint;
}

// ���� ���� �Լ�
void CLineTool::SetEndPoint( CPoint endPoint )
{
	m_endPoint = endPoint;
}

// �Ӽ� ���� �Լ�
void CLineTool::SetProperty( int thinkness, COLORREF outerColor)
{
	m_thinkness = thinkness;
	m_outerColor = outerColor;
}


