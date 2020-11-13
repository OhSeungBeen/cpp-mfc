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
	
	CPen pen(PS_SOLID, m_thinkness, m_outerColor); // 펜 설정
	CBrush brush(m_innerColor); // 브러쉬 설정
	
	CPen* oldPen = pDc->SelectObject(&pen);
	CBrush* oldBrush = pDc->SelectObject(&brush);

	pDc->Rectangle(m_startPoint.x, m_startPoint.y, m_endPoint.x, m_endPoint.y); // 원 생성
	
	pDc->SelectObject(oldPen); // 펜 반납
	pDc->SelectObject(oldBrush); // 브러쉬 반납
}

// 시작점 저장 함수
void CRectTool::SetStartPoint( CPoint startPoint )
{
	m_startPoint = startPoint;
}

// 끝점 저장 함수
void CRectTool::SetEndPoint( CPoint endPoint )
{
	m_endPoint = endPoint;
}

// 속성 저장 함수
void CRectTool::SetProperty( int thinkness, COLORREF outerColor, COLORREF innerColor )
{
	m_thinkness = thinkness;
	m_outerColor = outerColor;
	m_innerColor = innerColor;
}


