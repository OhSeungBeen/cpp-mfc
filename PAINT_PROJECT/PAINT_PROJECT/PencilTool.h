#pragma once
#include "Tool.h"

class CPencilTool : public Tool
{
private:
	CList<CPoint> m_pointList; // 점들을 저장할 리스트
	int m_thinkness; // 선 두께 
	COLORREF m_outerColor; // 색 1 (외부)

public:
	CPencilTool(void);
	virtual ~CPencilTool(void);

	void Draw(CDC*); // 그리기 함수
	void addPoint(CPoint point); // 점들을 추가 하는 함수( 연필이기 때문에 마우스움직일때 마다 점을 저장)
	void SetProperty(int thinkness, COLORREF outerColor); // 속성 저장 함수
};
