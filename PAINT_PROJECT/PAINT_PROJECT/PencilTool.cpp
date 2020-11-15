#include "StdAfx.h"
#include "PencilTool.h"

CPencilTool::CPencilTool(void)
{
}

CPencilTool::~CPencilTool(void)
{
}

void CPencilTool::Draw(CDC* pDc)
{
	CPen pen(PS_SOLID, m_thinkness, m_outerColor); // 펜 설정

	CPen* oldPen = pDc->SelectObject(&pen);
	
	POSITION pos = m_pointList.GetHeadPosition(); 
	CPoint start = m_pointList.GetNext(pos); // 처음 시작점
	CPoint end;
	while(pos != NULL) // 점이 없을때 까지 반복
	{
		end = m_pointList.GetNext(pos); // 계속해서 점을 꺼낸다.
		// 그린다.
		pDc->MoveTo(start); 
		pDc->LineTo(end);
		start = end; // 계속 이어 그리기 위해서 끝점을 시작점으로 설정
	}
	
	pDc->SelectObject(oldPen); // 펜 반납

}

// 점들을 추가 하는 함수( 연필이기 때문에 마우스움직일때 마다 점을 저장)
void CPencilTool::AddPoint( CPoint point )
{
	m_pointList.AddTail(point);
}

// 속성 저장 함수
void CPencilTool::SetProperty( int thinkness, COLORREF outerColor)
{
	m_thinkness = thinkness;
	m_outerColor = outerColor;
}




