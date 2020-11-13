#pragma once
#include "Tool.h"

class CTextTool : public Tool
{
private:
	CPoint m_startPoint; // ������
	CString m_text; // �ؽ�Ʈ ����
	
public:
	CTextTool(void);
	virtual ~CTextTool(void);

	void Draw(CDC*); // �׸��� �Լ�
	void SetStartPoint(CPoint startPoint); // ������ ���� �Լ�
	void InputText(UINT text); // �ؽ�Ʈ �Է� �Լ�
	CString GetText(); // �ؽ�Ʈ ������ �Լ�
	
};
