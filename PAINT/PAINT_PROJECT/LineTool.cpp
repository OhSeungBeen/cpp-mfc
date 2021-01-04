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

	CPen pen(PS_SOLID, m_thinkness, m_outerColor); // 펜 설정
	CPen* oldPen = pDc->SelectObject(&pen);

	// 직선을 그린다.
	pDc->MoveTo(m_startPoint);
	pDc->LineTo(m_endPoint);

	pDc->SelectObject(oldPen); // 펜 반납

}

// 시작점 저장 함수
void CLineTool::SetStartPoint( CPoint startPoint )
{
	m_startPoint = startPoint;
}

// 끝점 저장 함수
void CLineTool::SetEndPoint( CPoint endPoint )
{
	m_endPoint = endPoint;
}

// 속성 저장 함수
void CLineTool::SetProperty( int thinkness, COLORREF outerColor)
{
	m_thinkness = thinkness;
	m_outerColor = outerColor;
}


