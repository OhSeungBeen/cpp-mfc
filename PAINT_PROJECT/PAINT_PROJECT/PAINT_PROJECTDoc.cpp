
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
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

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
#endif //_DEBUG


// CPAINT_PROJECTDoc ���
