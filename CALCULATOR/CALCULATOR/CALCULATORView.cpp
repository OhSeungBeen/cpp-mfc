
// CALCULATORView.cpp : CCALCULATORView Ŭ������ ����
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

// CCALCULATORView ����/�Ҹ�

CCALCULATORView::CCALCULATORView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CCALCULATORView::~CCALCULATORView()
{
}

BOOL CCALCULATORView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CCALCULATORView �׸���

void CCALCULATORView::OnDraw(CDC* /*pDC*/)
{
	CCALCULATORDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CCALCULATORView ����

#ifdef _DEBUG
void CCALCULATORView::AssertValid() const
{
	CView::AssertValid();
}

void CCALCULATORView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCALCULATORDoc* CCALCULATORView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCALCULATORDoc)));
	return (CCALCULATORDoc*)m_pDocument;
}
#endif //_DEBUG


// CCALCULATORView �޽��� ó����
