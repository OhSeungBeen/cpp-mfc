
// CALCULATORDoc.cpp : CCALCULATORDoc Ŭ������ ����
//

#include "stdafx.h"
#include "CALCULATOR.h"

#include "CALCULATORDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCALCULATORDoc

IMPLEMENT_DYNCREATE(CCALCULATORDoc, CDocument)

BEGIN_MESSAGE_MAP(CCALCULATORDoc, CDocument)
END_MESSAGE_MAP()


// CCALCULATORDoc ����/�Ҹ�

CCALCULATORDoc::CCALCULATORDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CCALCULATORDoc::~CCALCULATORDoc()
{
}

BOOL CCALCULATORDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CCALCULATORDoc serialization

void CCALCULATORDoc::Serialize(CArchive& ar)
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


// CCALCULATORDoc ����

#ifdef _DEBUG
void CCALCULATORDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCALCULATORDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCALCULATORDoc ���
