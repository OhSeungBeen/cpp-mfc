#include "StdAfx.h"
#include "ImageTool.h"

CImageTool::CImageTool(void)
{
}

CImageTool::~CImageTool(void)
{
}

// �̹��� �׸��� �Լ� (0, 0) ��ġ
void CImageTool::Draw(CDC* pDc)
{
	if (m_filePath == "") // �̹��� ��ΰ� ������ �ȵǾ�������
		return;

	CImage image;
	HRESULT hResult = image.Load(m_filePath); // �̹��� �ε�

	if(FAILED(hResult)) // �̹��� �ε� ���н�
	{
		AfxMessageBox("�̹��� �ҷ����� ����!");
	}
	else
	{
		image.BitBlt(pDc->m_hDC, 0, 0);  // 0,0 ��ġ�� �̹����� �׸���.
	}
}

// �̹��� ���� ���� ��� ���� �Լ�
void CImageTool::SetFilePath( CString filepath )
{
	m_filePath = filepath;
}
