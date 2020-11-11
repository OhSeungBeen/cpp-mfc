
// PAINT_PROJECTView.cpp : CPAINT_PROJECTView 클래스의 구현
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

// CPAINT_PROJECTView 생성/소멸
CPAINT_PROJECTView::CPAINT_PROJECTView()
{
	drawMode = PENCIL; // 도구 연필로 초기화
	thinkness = 1; // 선 두께 1로 초기화
	outerColor = BLACK; // 색 1 (외부) 검정색으로 초기화
	innerColor = BLACK; // 색 2 (내부) 하얀색으로 초기화
	isInnerColUserCheck = FALSE; // 색 1 (외부) 사용자 설정 색 Check 확인 초기화
	isOuterColUserCheck = FALSE; // // 색 2 (내부) 사용자 설정 색 Check 확인 초기화
}

CPAINT_PROJECTView::~CPAINT_PROJECTView()
{
}

BOOL CPAINT_PROJECTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPAINT_PROJECTView 그리기

void CPAINT_PROJECTView::OnDraw(CDC* pDC)
{
	CPAINT_PROJECTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->TextOut(lButtonDownPoint.x, lButtonDownPoint.y, text);
	
}


// CPAINT_PROJECTView 진단

#ifdef _DEBUG
void CPAINT_PROJECTView::AssertValid() const
{
	CView::AssertValid();
}

void CPAINT_PROJECTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPAINT_PROJECTDoc* CPAINT_PROJECTView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPAINT_PROJECTDoc)));
	return (CPAINT_PROJECTDoc*)m_pDocument;
}
#endif //_DEBUG

// 마우스 왼쪽 버튼 클릭시 발생하는 이벤트 함수
void CPAINT_PROJECTView::OnLButtonDown(UINT nFlags, CPoint point)
{
	lButtonDownPoint = point; // 시작점을 저장
	prePoint = point; // 이전점 초기화
	nowDraw = TRUE; // 그리기 상태를 그리는 중으로 바꾼다.
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}

// 마우스가 움직일 때 발생하는 이벤트 함수
void CPAINT_PROJECTView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nowDraw != TRUE) // 그리는중이 아니라면 return
		return;

	CClientDC dc(this);
	CPen pen(PS_SOLID, thinkness, outerColor);
	CPen *pPen = dc.SelectObject(&pen);
	CBrush brush(innerColor);
	dc.SelectObject(brush);
	
	// 이전에 그렸던 선을 지우기 위해 그리기 모드 (XOR 같으면 : 0으로 만듬)
	// 직선 도형(원형, 삼각형) 그리는중 (마우스 드래그중) 선 보이게 하기
	if(drawMode != PENCIL)
		dc.SetROP2(R2_NOTXORPEN); 
	
	switch (drawMode)
	{	
		case PENCIL: // PENCIL
			// 이전점을 따라 새로운 선을 그린다.
			dc.MoveTo(prePoint);
			dc.LineTo(point);
			break;
		case LINE: // LINE
			// 이전의 선을 지운다.
			dc.MoveTo(lButtonDownPoint);
			dc.LineTo(prePoint);
			// 새로운 선을 그린다.
			dc.MoveTo(lButtonDownPoint);
			dc.LineTo(point);
			break;
		case CIRCLE: // CIRCLE
			// 이전의 도형(원형)을 지운다.
			dc.Ellipse(lButtonDownPoint.x, lButtonDownPoint.y, prePoint.x, prePoint.y);
			// 새로운 도형(원형)을 그린다.
			dc.Ellipse(lButtonDownPoint.x, lButtonDownPoint.y, point.x, point.y);
			break;
		case RECTANGLE: // RECTANGLE 
			// 이전의 도형(삼각형)을 지운다.
			dc.Rectangle(lButtonDownPoint.x, lButtonDownPoint.y, prePoint.x, prePoint.y);
			// 새로운 도형(삼각형)을 그린다.
			dc.Rectangle(lButtonDownPoint.x, lButtonDownPoint.y, point.x, point.y);
			break;
	}
	dc.SetROP2(R2_COPYPEN); // 그리기 모드를 기본값으로 돌려놓는다. 

	prePoint = point; //현재 point 이전 point변수에 저장 

	CView::OnMouseMove(nFlags, point);
}

// 마우스 왼쪽 버튼 클릭 후 뗐을때 발생하는 이벤트 함수
// 마우스를 뗐을때 최종 도형 그리기
void CPAINT_PROJECTView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CClientDC dc(this);
	CPen pen(PS_SOLID, thinkness, outerColor);
	//dc.SelectStockObject(NULL_BRUSH); // 빈 도형 설정
	CPen *pPen = dc.SelectObject(&pen);

	CBrush brush(innerColor);
	dc.SelectObject(brush);
	
	
	// 최종적으로 도형을 그린다.
	switch (drawMode)
	{	
	case LINE: // LINE 선택 시
		dc.MoveTo(lButtonDownPoint);
		dc.LineTo(point);
		break;
	case CIRCLE: // CIRCLE 선택 시
		dc.Ellipse(lButtonDownPoint.x, lButtonDownPoint.y, point.x, point.y);
		break;
	case RECTANGLE: // RECTANGLE 선택 시
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
	nowDraw = FALSE; // 그리기 상태를 그리는 중이 아님으로 바꾼다.
}

// 도구
void CPAINT_PROJECTView::OnInsertPencil()
{
	drawMode = PENCIL; // 툴바 PEN을 클릭하면 drawMode = 1(PENCIL); 
}

void CPAINT_PROJECTView::OnInsertLine()
{
	drawMode = LINE; // 툴바 LINE을 클릭하면 drawMode = 2(LINE); 
}

void CPAINT_PROJECTView::OnInsertCircle()
{
	drawMode = CIRCLE; // 툴바 CIRCLE을 클릭하면 drawMode = 3(CIRCLE); 
}

void CPAINT_PROJECTView::OnInsertRect()
{
	drawMode = RECTANGLE; // 툴바 RECTANGLE을 클릭하면 drawMode = 4(RECT); 
}

void CPAINT_PROJECTView::OnUpdateInsertPencil(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(drawMode == PENCIL); // 현재 그리기 모드가 팬이면 툴바 check박스를 set 아니면 unset
}

void CPAINT_PROJECTView::OnUpdateInsertLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(drawMode == LINE); // 현재 그리기 모드가 직선이면 툴바 check박스를 set 아니면 unset
}

void CPAINT_PROJECTView::OnUpdateInsertCircle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(drawMode == CIRCLE); // 현재 그리기 모드가 도형(원형)이면 툴바 check박스를 set 아니면 unset
}

void CPAINT_PROJECTView::OnUpdateInsertRect(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(drawMode == RECTANGLE); // 현재 그리기 모드가 도형(삼각형)이면  툴바 check박스를 set 아니면 unset
}

// 선 두께
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

// 색 1 (외부) 
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

// 색 2 (내부)
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

// 텍스트
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
	if(drawMode == TEXT) // 현재 그리기모드가 TEXT이면 
	{
		CClientDC dc(this);
	
		CSize strSize;

		if (nChar == 8) {	//백스페이스
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
