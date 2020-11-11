
// PAINT_PROJECTView.cpp : CPAINT_PROJECTView Ŭ������ ����
//
#include "stdafx.h"
#include "PAINT_PROJECT.h"

#include "PAINT_PROJECTDoc.h"
#include "PAINT_PROJECTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPAINT_PROJECTView
IMPLEMENT_DYNCREATE(CPAINT_PROJECTView, CView)
	
BEGIN_MESSAGE_MAP(CPAINT_PROJECTView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()

	ON_COMMAND(ID_INSERT_PENCIL, &CPAINT_PROJECTView::OnInsertPencil)
	ON_COMMAND(ID_INSERT_LINE, &CPAINT_PROJECTView::OnInsertLine)
	ON_COMMAND(ID_INSERT_CIRCLE, &CPAINT_PROJECTView::OnInsertCircle)
	ON_COMMAND(ID_INSERT_RECT, &CPAINT_PROJECTView::OnInsertRect)
	ON_UPDATE_COMMAND_UI(ID_INSERT_PENCIL, &CPAINT_PROJECTView::OnUpdateInsertPencil)
	ON_UPDATE_COMMAND_UI(ID_INSERT_LINE, &CPAINT_PROJECTView::OnUpdateInsertLine)
	ON_UPDATE_COMMAND_UI(ID_INSERT_CIRCLE, &CPAINT_PROJECTView::OnUpdateInsertCircle)
	ON_UPDATE_COMMAND_UI(ID_INSERT_RECT, &CPAINT_PROJECTView::OnUpdateInsertRect)

	ON_COMMAND(ID_THINKNESS1, &CPAINT_PROJECTView::OnThinkness1)
	ON_COMMAND(ID_THINKNESS3, &CPAINT_PROJECTView::OnThinkness3)
	ON_COMMAND(ID_THINKNESS6, &CPAINT_PROJECTView::OnThinkness6)
	ON_COMMAND(ID_THINKNESS9, &CPAINT_PROJECTView::OnThinkness9)
	ON_COMMAND(ID_THINKNESS12, &CPAINT_PROJECTView::OnThinkness12)
	ON_UPDATE_COMMAND_UI(ID_THINKNESS1, &CPAINT_PROJECTView::OnUpdateThinkness1)
	ON_UPDATE_COMMAND_UI(ID_THINKNESS3, &CPAINT_PROJECTView::OnUpdateThinkness3)
	ON_UPDATE_COMMAND_UI(ID_THINKNESS6, &CPAINT_PROJECTView::OnUpdateThinkness6)
	ON_UPDATE_COMMAND_UI(ID_THINKNESS9, &CPAINT_PROJECTView::OnUpdateThinkness9)
	ON_UPDATE_COMMAND_UI(ID_THINKNESS12, &CPAINT_PROJECTView::OnUpdateThinkness12)

	ON_COMMAND(ID_OUTERCOL_BLACK, &CPAINT_PROJECTView::OnOutercolBlack)
	ON_COMMAND(ID_OUTERCOL_RED, &CPAINT_PROJECTView::OnOutercolRed)
	ON_COMMAND(ID_OUTERCOL_GREEN, &CPAINT_PROJECTView::OnOutercolGreen)
	ON_COMMAND(ID_OUTERCOL_BLUE, &CPAINT_PROJECTView::OnOutercolBlue)
	ON_COMMAND(ID_OUTERCOL_USER, &CPAINT_PROJECTView::OnOutercolUser)
	ON_UPDATE_COMMAND_UI(ID_OUTERCOL_BLACK, &CPAINT_PROJECTView::OnUpdateOutercolBlack)
	ON_UPDATE_COMMAND_UI(ID_OUTERCOL_RED, &CPAINT_PROJECTView::OnUpdateOutercolRed)
	ON_UPDATE_COMMAND_UI(ID_OUTERCOL_GREEN, &CPAINT_PROJECTView::OnUpdateOutercolGreen)
	ON_UPDATE_COMMAND_UI(ID_OUTERCOL_BLUE, &CPAINT_PROJECTView::OnUpdateOutercolBlue)
	ON_UPDATE_COMMAND_UI(ID_OUTERCOL_USER, &CPAINT_PROJECTView::OnUpdateOutercolUser)

	ON_COMMAND(ID_INNERCOL_BLACK, &CPAINT_PROJECTView::OnInnercolBlack)
	ON_COMMAND(ID_INNERCOL_RED, &CPAINT_PROJECTView::OnInnercolRed)
	ON_COMMAND(ID_INNERCOL_GREEN, &CPAINT_PROJECTView::OnInnercolGreen)
	ON_COMMAND(ID_INNERCOL_BLUE, &CPAINT_PROJECTView::OnInnercolBlue)
	ON_COMMAND(ID_INNERCOL_USER, &CPAINT_PROJECTView::OnInnercolUser)
	ON_UPDATE_COMMAND_UI(ID_INNERCOL_BLACK, &CPAINT_PROJECTView::OnUpdateInnercolBlack)
	ON_UPDATE_COMMAND_UI(ID_INNERCOL_RED, &CPAINT_PROJECTView::OnUpdateInnercolRed)
	ON_UPDATE_COMMAND_UI(ID_INNERCOL_GREEN, &CPAINT_PROJECTView::OnUpdateInnercolGreen)
	ON_UPDATE_COMMAND_UI(ID_INNERCOL_BLUE, &CPAINT_PROJECTView::OnUpdateInnercolBlue)
	ON_UPDATE_COMMAND_UI(ID_INNERCOL_USER, &CPAINT_PROJECTView::OnUpdateInnercolUser)

	ON_COMMAND(ID_INSERT_TEXT, &CPAINT_PROJECTView::OnInsertText)
	ON_UPDATE_COMMAND_UI(ID_INSERT_TEXT, &CPAINT_PROJECTView::OnUpdateInsertText)
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CPAINT_PROJECTView ����/�Ҹ�
CPAINT_PROJECTView::CPAINT_PROJECTView()
{
	drawMode = PENCIL; // ���� ���ʷ� �ʱ�ȭ
	thinkness = 1; // �� �β� 1�� �ʱ�ȭ
	outerColor = BLACK; // �� 1 (�ܺ�) ���������� �ʱ�ȭ
	innerColor = BLACK; // �� 2 (����) �Ͼ������ �ʱ�ȭ
	isInnerColUserCheck = FALSE; // �� 1 (�ܺ�) ����� ���� �� Check Ȯ�� �ʱ�ȭ
	isOuterColUserCheck = FALSE; // // �� 2 (����) ����� ���� �� Check Ȯ�� �ʱ�ȭ
}

CPAINT_PROJECTView::~CPAINT_PROJECTView()
{
}

BOOL CPAINT_PROJECTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CPAINT_PROJECTView �׸���

void CPAINT_PROJECTView::OnDraw(CDC* pDC)
{
	CPAINT_PROJECTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->TextOut(lButtonDownPoint.x, lButtonDownPoint.y, text);
	
}


// CPAINT_PROJECTView ����

#ifdef _DEBUG
void CPAINT_PROJECTView::AssertValid() const
{
	CView::AssertValid();
}

void CPAINT_PROJECTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPAINT_PROJECTDoc* CPAINT_PROJECTView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPAINT_PROJECTDoc)));
	return (CPAINT_PROJECTDoc*)m_pDocument;
}
#endif //_DEBUG

// ���콺 ���� ��ư Ŭ���� �߻��ϴ� �̺�Ʈ �Լ�
void CPAINT_PROJECTView::OnLButtonDown(UINT nFlags, CPoint point)
{
	lButtonDownPoint = point; // �������� ����
	prePoint = point; // ������ �ʱ�ȭ
	nowDraw = TRUE; // �׸��� ���¸� �׸��� ������ �ٲ۴�.
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}

// ���콺�� ������ �� �߻��ϴ� �̺�Ʈ �Լ�
void CPAINT_PROJECTView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nowDraw != TRUE) // �׸������� �ƴ϶�� return
		return;

	CClientDC dc(this);
	CPen pen(PS_SOLID, thinkness, outerColor);
	CPen *pPen = dc.SelectObject(&pen);
	CBrush brush(innerColor);
	dc.SelectObject(brush);
	
	// ������ �׷ȴ� ���� ����� ���� �׸��� ��� (XOR ������ : 0���� ����)
	// ���� ����(����, �ﰢ��) �׸����� (���콺 �巡����) �� ���̰� �ϱ�
	if(drawMode != PENCIL)
		dc.SetROP2(R2_NOTXORPEN); 
	
	switch (drawMode)
	{	
		case PENCIL: // PENCIL
			// �������� ���� ���ο� ���� �׸���.
			dc.MoveTo(prePoint);
			dc.LineTo(point);
			break;
		case LINE: // LINE
			// ������ ���� �����.
			dc.MoveTo(lButtonDownPoint);
			dc.LineTo(prePoint);
			// ���ο� ���� �׸���.
			dc.MoveTo(lButtonDownPoint);
			dc.LineTo(point);
			break;
		case CIRCLE: // CIRCLE
			// ������ ����(����)�� �����.
			dc.Ellipse(lButtonDownPoint.x, lButtonDownPoint.y, prePoint.x, prePoint.y);
			// ���ο� ����(����)�� �׸���.
			dc.Ellipse(lButtonDownPoint.x, lButtonDownPoint.y, point.x, point.y);
			break;
		case RECTANGLE: // RECTANGLE 
			// ������ ����(�ﰢ��)�� �����.
			dc.Rectangle(lButtonDownPoint.x, lButtonDownPoint.y, prePoint.x, prePoint.y);
			// ���ο� ����(�ﰢ��)�� �׸���.
			dc.Rectangle(lButtonDownPoint.x, lButtonDownPoint.y, point.x, point.y);
			break;
	}
	dc.SetROP2(R2_COPYPEN); // �׸��� ��带 �⺻������ �������´�. 

	prePoint = point; //���� point ���� point������ ���� 

	CView::OnMouseMove(nFlags, point);
}

// ���콺 ���� ��ư Ŭ�� �� ������ �߻��ϴ� �̺�Ʈ �Լ�
// ���콺�� ������ ���� ���� �׸���
void CPAINT_PROJECTView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CClientDC dc(this);
	CPen pen(PS_SOLID, thinkness, outerColor);
	//dc.SelectStockObject(NULL_BRUSH); // �� ���� ����
	CPen *pPen = dc.SelectObject(&pen);

	CBrush brush(innerColor);
	dc.SelectObject(brush);
	
	
	// ���������� ������ �׸���.
	switch (drawMode)
	{	
	case LINE: // LINE ���� ��
		dc.MoveTo(lButtonDownPoint);
		dc.LineTo(point);
		break;
	case CIRCLE: // CIRCLE ���� ��
		dc.Ellipse(lButtonDownPoint.x, lButtonDownPoint.y, point.x, point.y);
		break;
	case RECTANGLE: // RECTANGLE ���� ��
		dc.Rectangle(lButtonDownPoint.x, lButtonDownPoint.y, point.x, point.y);
		break;
	case TEXT:
		/*TEXTMETRIC txtKey;
		dc.GetTextMetrics(&txtKey);
		CreateSolidCaret(1, txtKey.tmHeight);
		SetCaretPos(lButtonDownPoint);
		ShowCaret();*/
		text = "";
		break;
	}
	nowDraw = FALSE; // �׸��� ���¸� �׸��� ���� �ƴ����� �ٲ۴�.
}

// ����
void CPAINT_PROJECTView::OnInsertPencil()
{
	drawMode = PENCIL; // ���� PEN�� Ŭ���ϸ� drawMode = 1(PENCIL); 
}

void CPAINT_PROJECTView::OnInsertLine()
{
	drawMode = LINE; // ���� LINE�� Ŭ���ϸ� drawMode = 2(LINE); 
}

void CPAINT_PROJECTView::OnInsertCircle()
{
	drawMode = CIRCLE; // ���� CIRCLE�� Ŭ���ϸ� drawMode = 3(CIRCLE); 
}

void CPAINT_PROJECTView::OnInsertRect()
{
	drawMode = RECTANGLE; // ���� RECTANGLE�� Ŭ���ϸ� drawMode = 4(RECT); 
}

void CPAINT_PROJECTView::OnUpdateInsertPencil(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(drawMode == PENCIL); // ���� �׸��� ��尡 ���̸� ���� check�ڽ��� set �ƴϸ� unset
}

void CPAINT_PROJECTView::OnUpdateInsertLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(drawMode == LINE); // ���� �׸��� ��尡 �����̸� ���� check�ڽ��� set �ƴϸ� unset
}

void CPAINT_PROJECTView::OnUpdateInsertCircle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(drawMode == CIRCLE); // ���� �׸��� ��尡 ����(����)�̸� ���� check�ڽ��� set �ƴϸ� unset
}

void CPAINT_PROJECTView::OnUpdateInsertRect(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(drawMode == RECTANGLE); // ���� �׸��� ��尡 ����(�ﰢ��)�̸�  ���� check�ڽ��� set �ƴϸ� unset
}

// �� �β�
void CPAINT_PROJECTView::OnThinkness1()
{
	thinkness = 1;
}

void CPAINT_PROJECTView::OnThinkness3()
{
	thinkness = 3;
}

void CPAINT_PROJECTView::OnThinkness6()
{
	thinkness = 6;
}

void CPAINT_PROJECTView::OnThinkness9()
{
	thinkness = 9;
}

void CPAINT_PROJECTView::OnThinkness12()
{
	thinkness = 12;
}

void CPAINT_PROJECTView::OnUpdateThinkness1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(thinkness == 1);
}

void CPAINT_PROJECTView::OnUpdateThinkness3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(thinkness == 3);
}

void CPAINT_PROJECTView::OnUpdateThinkness6(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(thinkness == 6);
}

void CPAINT_PROJECTView::OnUpdateThinkness9(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(thinkness == 9);
}

void CPAINT_PROJECTView::OnUpdateThinkness12(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(thinkness == 12);
}

// �� 1 (�ܺ�) 
void CPAINT_PROJECTView::OnOutercolBlack()
{
	outerColor = BLACK;
}

void CPAINT_PROJECTView::OnOutercolRed()
{
	outerColor = RED;
}

void CPAINT_PROJECTView::OnOutercolGreen()
{
	outerColor = GREEN;
}

void CPAINT_PROJECTView::OnOutercolBlue()
{
	outerColor = BLUE;
}

void CPAINT_PROJECTView::OnOutercolUser()
{
	CColorDialog cdlg;
	if(cdlg.DoModal() == IDOK)
	{
		outerColor = cdlg.GetColor();
		isOuterColUserCheck = TRUE;
	}
}

void CPAINT_PROJECTView::OnUpdateOutercolBlack(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(outerColor == BLACK);
}

void CPAINT_PROJECTView::OnUpdateOutercolRed(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(outerColor == RED);
}

void CPAINT_PROJECTView::OnUpdateOutercolGreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(outerColor == GREEN);
}

void CPAINT_PROJECTView::OnUpdateOutercolBlue(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(outerColor == BLUE);
}

void CPAINT_PROJECTView::OnUpdateOutercolUser(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(isOuterColUserCheck);
}

// �� 2 (����)
void CPAINT_PROJECTView::OnInnercolBlack()
{
	innerColor = BLACK;
}

void CPAINT_PROJECTView::OnInnercolRed()
{
	innerColor = RED;
}

void CPAINT_PROJECTView::OnInnercolGreen()
{
	innerColor = GREEN;
}

void CPAINT_PROJECTView::OnInnercolBlue()
{
	innerColor = BLUE;
}

void CPAINT_PROJECTView::OnInnercolUser()
{
	CColorDialog cdlg;
	if(cdlg.DoModal() == IDOK)
	{
		innerColor = cdlg.GetColor();
		isInnerColUserCheck =TRUE;
	}
}

void CPAINT_PROJECTView::OnUpdateInnercolBlack(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(innerColor == BLACK);
}

void CPAINT_PROJECTView::OnUpdateInnercolRed(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(innerColor == RED);
}

void CPAINT_PROJECTView::OnUpdateInnercolGreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(innerColor == GREEN);
}

void CPAINT_PROJECTView::OnUpdateInnercolBlue(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(innerColor == BLUE);
}

void CPAINT_PROJECTView::OnUpdateInnercolUser(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(isInnerColUserCheck);
}

// �ؽ�Ʈ
void CPAINT_PROJECTView::OnInsertText()
{
	drawMode = TEXT;
}

void CPAINT_PROJECTView::OnUpdateInsertText(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(drawMode == TEXT);
}

void CPAINT_PROJECTView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(drawMode == TEXT) // ���� �׸����尡 TEXT�̸� 
	{
		CClientDC dc(this);
	
		CSize strSize;

		if (nChar == 8) {	//�齺���̽�
			if (text.GetLength() > 0) {
				text.Delete(text.GetLength()-1);
			}
		} else {
			text.AppendChar(nChar);
		}
		
		CFont font;
		font.CreatePointFont(3, "Arial");
		CFont* oldFont = dc.SelectObject(&font);

		strSize = dc.GetTextExtent(text);

		SetCaretPos(CPoint(lButtonDownPoint.x + strSize.cx, lButtonDownPoint.y));
		ShowCaret();

		dc.SelectObject(oldFont);
		dc.TextOut(lButtonDownPoint.x, lButtonDownPoint.y, text);
		
		Invalidate(TRUE);
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}
