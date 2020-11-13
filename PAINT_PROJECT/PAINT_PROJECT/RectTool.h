#pragma once
#include "Tool.h"

class CRectTool : public Tool
{
private:
	CPoint m_startPoint; // 시작점
	CPoint m_endPoint; // 끝점
	int m_thinkness; // 선 두께 
	COLORREF m_outerColor; // 색 1 (외부)
	COLORREF m_innerColor; // 색 2 (내부)

public:
	CRectTool(void);
	virtual ~CRectTool(void);

	void Draw(CDC*); // 그리기 함수
	void SetStartPoint(CPoint startPoint); // 시작점 저장 함수
	void SetEndPoint(CPoint endPoint); // 끝점 저장 함수
	void SetProperty(int thinkness, COLORREF outerColor, COLORREF innerColor); // 속성 저장 함수
};
