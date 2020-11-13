
// PAINT_PROJECTDoc.cpp : CPAINT_PROJECTDoc 클래스의 구현
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


// CPAINT_PROJECTDoc 생성/소멸

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

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}


// CPAINT_PROJECTDoc serialization

void CPAINT_PROJECTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CPAINT_PROJECTDoc 진단

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

// 연필 도구를 생성하는 함수
CPencilTool* CPAINT_PROJECTDoc::CreatePencilTool()
{
	m_tool = new CPencilTool(); // 원 도구 생성
	m_toolList.AddTail(m_tool); // 도구 리스트에 담아 놓는다.
	return (CPencilTool*)m_tool; // 생성한 원 도구 리턴
}

CLineTool* CPAINT_PROJECTDoc::CreateLineTool()
{
	m_tool = new CLineTool(); // 직선 도구 생성
	m_toolList.AddTail(m_tool); // 도구 리스트에 담아 놓는다.
	return (CLineTool*)m_tool; // 생성한 직선 도구 리턴
}


// 원 도구를 생성하는 함수
CCircleTool* CPAINT_PROJECTDoc::CreateCircleTool()
{
	m_tool = new CCircleTool(); // 원 도구 생성
	m_toolList.AddTail(m_tool); // 도구 리스트에 담아 놓는다.
	return (CCircleTool*)m_tool; // 생성한 원 도구 리턴
}

CRectTool* CPAINT_PROJECTDoc::CreateRectTool()
{
	m_tool = new CRectTool(); // 텍스트 도구 생성
	m_toolList.AddTail(m_tool); // 도구 리스트에 담아 놓는다.
	return (CRectTool*)m_tool; // 생성한 원 도구 리턴
}

// 텍스트 도구를 생성하는 함수
CTextTool* CPAINT_PROJECTDoc::CreateTextTool()
{
	m_tool = new CTextTool(); // 텍스트 도구 생성
	m_toolList.AddTail(m_tool); // 도구 리스트에 담아 놓는다.
	return (CTextTool*)m_tool; // 생성한 원 도구 리턴
}
#endif //_DEBUG


// CPAINT_PROJECTDoc 명령
