
// CALCULATORView.cpp : CCALCULATORView 클래스의 구현
//

#include "stdafx.h"
#include "CALCULATOR.h"

#include "CALCULATORDoc.h"
#include "CALCULATORView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCALCULATORView

IMPLEMENT_DYNCREATE(CCALCULATORView, CView)

BEGIN_MESSAGE_MAP(CCALCULATORView, CView)
END_MESSAGE_MAP()

// CCALCULATORView 생성/소멸

CCALCULATORView::CCALCULATORView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCALCULATORView::~CCALCULATORView()
{
}

BOOL CCALCULATORView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCALCULATORView 그리기

void CCALCULATORView::OnDraw(CDC* /*pDC*/)
{
	CCALCULATORDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCALCULATORView 진단

#ifdef _DEBUG
void CCALCULATORView::AssertValid() const
{
	CView::AssertValid();
}

void CCALCULATORView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCALCULATORDoc* CCALCULATORView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCALCULATORDoc)));
	return (CCALCULATORDoc*)m_pDocument;
}
#endif //_DEBUG


// CCALCULATORView 메시지 처리기
