
// PAINT_PROJECTDoc.cpp : CPAINT_PROJECTDoc Ŭ������ ����
//

#include "stdafx.h"
#include "PAINT_PROJECT.h"

#include "PAINT_PROJECTDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPAINT_PROJECTDoc

IMPLEMENT_DYNCREATE(CPAINT_PROJECTDoc, CDocument)

BEGIN_MESSAGE_MAP(CPAINT_PROJECTDoc, CDocument)
END_MESSAGE_MAP()


// CPAINT_PROJECTDoc ����/�Ҹ�

CPAINT_PROJECTDoc::CPAINT_PROJECTDoc()
{

}

CPAINT_PROJECTDoc::~CPAINT_PROJECTDoc()
{
}

BOOL CPAINT_PROJECTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}


// CPAINT_PROJECTDoc serialization

void CPAINT_PROJECTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CPAINT_PROJECTDoc ����

#ifdef _DEBUG
void CPAINT_PROJECTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPAINT_PROJECTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

CPtrList& CPAINT_PROJECTDoc::GetToolList()
{
	return m_toolList;
}


Tool* CPAINT_PROJECTDoc::GetTool()
{
	return m_tool;
}

// ���� ������ �����ϴ� �Լ�
CPencilTool* CPAINT_PROJECTDoc::CreatePencilTool()
{
	m_tool = new CPencilTool(); // �� ���� ����
	m_toolList.AddTail(m_tool); // ���� ����Ʈ�� ��� ���´�.
	return (CPencilTool*)m_tool; // ������ �� ���� ����
}

CLineTool* CPAINT_PROJECTDoc::CreateLineTool()
{
	m_tool = new CLineTool(); // ���� ���� ����
	m_toolList.AddTail(m_tool); // ���� ����Ʈ�� ��� ���´�.
	return (CLineTool*)m_tool; // ������ ���� ���� ����
}


// �� ������ �����ϴ� �Լ�
CCircleTool* CPAINT_PROJECTDoc::CreateCircleTool()
{
	m_tool = new CCircleTool(); // �� ���� ����
	m_toolList.AddTail(m_tool); // ���� ����Ʈ�� ��� ���´�.
	return (CCircleTool*)m_tool; // ������ �� ���� ����
}

CRectTool* CPAINT_PROJECTDoc::CreateRectTool()
{
	m_tool = new CRectTool(); // �ؽ�Ʈ ���� ����
	m_toolList.AddTail(m_tool); // ���� ����Ʈ�� ��� ���´�.
	return (CRectTool*)m_tool; // ������ �� ���� ����
}

// �ؽ�Ʈ ������ �����ϴ� �Լ�
CTextTool* CPAINT_PROJECTDoc::CreateTextTool()
{
	m_tool = new CTextTool(); // �ؽ�Ʈ ���� ����
	m_toolList.AddTail(m_tool); // ���� ����Ʈ�� ��� ���´�.
	return (CTextTool*)m_tool; // ������ �� ���� ����
}
#endif //_DEBUG


// CPAINT_PROJECTDoc ���
