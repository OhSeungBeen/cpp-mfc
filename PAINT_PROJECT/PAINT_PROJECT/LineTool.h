#pragma once
#include "Tool.h"

class CLineTool : public Tool
{
private:
	CPoint m_startPoint; // 시작점
	CPoint m_endPoint; // 끝점
	int m_thinkness; // 선 두께 
	COLORREF m_outerColor; // 색 1 (외부)

public:
	CLineTool(void);
	virtual ~CLineTool(void);

	void Draw(CDC*); // 그리기 함수
	void SetStartPoint(CPoint startPoint); // 시작점 저장 함수
	void SetEndPoint(CPoint endPoint); // 끝점 저장 함수
	void SetProperty(int thinkness, COLORREF outerColor); // 속성 저장 함수
};
