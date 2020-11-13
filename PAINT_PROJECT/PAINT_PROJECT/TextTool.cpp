#include "StdAfx.h"
#include "TextTool.h"

CTextTool::CTextTool(void)
{
}

CTextTool::~CTextTool(void)
{
}

// �ؽ�Ʈ �׸��� �Լ�
void CTextTool::Draw(CDC* pDc)
{
	CFont font; // ��Ʈ ����
	font.CreatePointFont(1, "Arial");
	CFont* oldFont = pDc->SelectObject(&font);

	pDc->TextOut(m_startPoint.x, m_startPoint.y, m_text); // �ؽ�Ʈ ���

	pDc->SelectObject(oldFont); // Font �ݳ�
}


// ������ ���� �Լ�
void CTextTool::SetStartPoint( CPoint startPoint )
{
	m_startPoint = startPoint;
}

// �ؽ�Ʈ �Է� �Լ�
void CTextTool::InputText(UINT text)
{
	if (text == 8) { //�齺���̽�
		if (m_text.GetLength() > 0) { // ���ڿ��� �ƴϸ�
			m_text.Delete(m_text.GetLength()-1); // �ǵ� ���� ����
		}
	} else { // �齺���̽� �ƴϸ�
		m_text.AppendChar(text); // ���ڿ� ����
	}
}

// �ؽ�Ʈ ������ �Լ�
CString CTextTool::GetText()
{
	return m_text;
}


