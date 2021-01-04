#pragma once
#include "Tool.h"
#include "atlimage.h"

class CImageTool : public Tool
{
private:
	CString m_filePath; // �̹��� ���� ���
	
public:
	CImageTool(void);
	virtual ~CImageTool(void);
	
	void Draw(CDC*); // �̹��� �׸��� �Լ� (0, 0) ��ġ
	void SetFilePath(CString filepath); // �̹��� ���� ���� ��� ���� �Լ�
	
};
