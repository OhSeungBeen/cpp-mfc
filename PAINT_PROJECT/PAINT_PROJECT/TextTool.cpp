#include "StdAfx.h"
#include "TextTool.h"

CTextTool::CTextTool(void)
{
}

CTextTool::~CTextTool(void)
{
}

// 텍스트 그리기 함수
void CTextTool::Draw(CDC* pDc)
{
	CFont font; // 폰트 설정
	font.CreatePointFont(1, "Arial");
	CFont* oldFont = pDc->SelectObject(&font);

	pDc->TextOut(m_startPoint.x, m_startPoint.y, m_text); // 텍스트 출력

	pDc->SelectObject(oldFont); // Font 반납
}


// 시작점 저장 함수
void CTextTool::SetStartPoint( CPoint startPoint )
{
	m_startPoint = startPoint;
}

// 텍스트 입력 함수
void CTextTool::InputText(UINT text)
{
	if (text == 8) { //백스페이스
		if (m_text.GetLength() > 0) { // 빈문자열이 아니면
			m_text.Delete(m_text.GetLength()-1); // 맨뒤 글자 삭제
		}
	} else { // 백스페이스 아니면
		m_text.AppendChar(text); // 문자열 연결
	}
}

// 텍스트 꺼내는 함수
CString CTextTool::GetText()
{
	return m_text;
}


