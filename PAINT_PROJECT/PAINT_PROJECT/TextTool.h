#pragma once
#include "Tool.h"

class CTextTool : public Tool
{
private:
	CPoint m_startPoint; // 시작점
	CString m_text; // 텍스트 저장
	
public:
	CTextTool(void);
	virtual ~CTextTool(void);

	void Draw(CDC*); // 그리기 함수
	void SetStartPoint(CPoint startPoint); // 시작점 저장 함수
	void InputText(UINT text); // 텍스트 입력 함수
	CString GetText(); // 텍스트 꺼내는 함수
	
};
