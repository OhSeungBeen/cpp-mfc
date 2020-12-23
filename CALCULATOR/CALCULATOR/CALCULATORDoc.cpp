
// CALCULATORDoc.cpp : CCALCULATORDoc 클래스의 구현
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


// CCALCULATORDoc 생성/소멸

CCALCULATORDoc::CCALCULATORDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CCALCULATORDoc::~CCALCULATORDoc()
{
}

BOOL CCALCULATORDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CCALCULATORDoc serialization

void CCALCULATORDoc::Serialize(CArchive& ar)
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


// CCALCULATORDoc 진단

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


// CCALCULATORDoc 명령
