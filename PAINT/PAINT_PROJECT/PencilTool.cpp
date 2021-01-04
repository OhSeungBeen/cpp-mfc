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
	CPen pen(PS_SOLID, m_thinkness, m_outerColor); // �� ����

	CPen* oldPen = pDc->SelectObject(&pen);
	
	POSITION pos = m_pointList.GetHeadPosition(); 
	CPoint start = m_pointList.GetNext(pos); // ó�� ������
	CPoint end;
	while(pos != NULL) // ���� ������ ���� �ݺ�
	{
		end = m_pointList.GetNext(pos); // ����ؼ� ���� ������.
		// �׸���.
		pDc->MoveTo(start); 
		pDc->LineTo(end);
		start = end; // ��� �̾� �׸��� ���ؼ� ������ ���������� ����
	}
	
	pDc->SelectObject(oldPen); // �� �ݳ�

}

// ������ �߰� �ϴ� �Լ�( �����̱� ������ ���콺�����϶� ���� ���� ����)
void CPencilTool::AddPoint( CPoint point )
{
	m_pointList.AddTail(point);
}

// �Ӽ� ���� �Լ�
void CPencilTool::SetProperty( int thinkness, COLORREF outerColor)
{
	m_thinkness = thinkness;
	m_outerColor = outerColor;
}




