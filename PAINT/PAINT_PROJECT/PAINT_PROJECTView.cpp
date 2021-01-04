
// PAINT_PROJECTView.cpp : CPAINT_PROJECTView 클래스의 구현
//
#include "stdafx.h"
#include "PAINT_PROJECT.h"

#include "PAINT_PROJECTDoc.h"
#include "PAINT_PROJECTView.h"
#include "atlimage.h"

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

	ON_COMMAND(ID_INNERCOL_TRANSPARENT, &CPAINT_PROJECTView::OnInnercolTransparent)
	ON_COMMAND(ID_INNERCOL_RED, &CPAINT_PROJECTView::OnInnercolRed)
	ON_COMMAND(ID_INNERCOL_GREEN, &CPAINT_PROJECTView::OnInnercolGreen)
	ON_COMMAND(ID_INNERCOL_BLUE, &CPAINT_PROJECTView::OnInnercolBlue)
	ON_COMMAND(ID_INNERCOL_USER, &CPAINT_PROJECTView::OnInnercolUser)
	ON_UPDATE_COMMAND_UI(ID_INNERCOL_TRANSPARENT, &CPAINT_PROJECTView::OnUpdateInnercolTransparent)
	ON_UPDATE_COMMAND_UI(ID_INNERCOL_RED, &CPAINT_PROJECTView::OnUpdateInnercolRed)
	ON_UPDATE_COMMAND_UI(ID_INNERCOL_GREEN, &CPAINT_PROJECTView::OnUpdateInnercolGreen)
	ON_UPDATE_COMMAND_UI(ID_INNERCOL_BLUE, &CPAINT_PROJECTView::OnUpdateInnercolBlue)
	ON_UPDATE_COMMAND_UI(ID_INNERCOL_USER, &CPAINT_PROJECTView::OnUpdateInnercolUser)

	ON_COMMAND(ID_INSERT_TEXT, &CPAINT_PROJECTView::OnInsertText)
	ON_UPDATE_COMMAND_UI(ID_INSERT_TEXT, &CPAINT_PROJECTView::OnUpdateInsertText)
	ON_WM_CHAR()
	ON_COMMAND(ID_INSERT_IMAGE, &CPAINT_PROJECTView::OnInsertImage)
	ON_COMMAND(ID_RESET, &CPAINT_PROJECTView::OnReset)
END_MESSAGE_MAP()

// CPAINT_PROJECTView 생성/소멸
CPAINT_PROJECTView::CPAINT_PROJECTView()
{
	drawMode = PENCIL; // 도구 연필로 초기화
	m_thinkness = 1; // 선 두께 1로 초기화
	m_outerColor = BLACK; // 색 1 (외부) 검정색으로 초기화
	m_innerColor = NULL; // 색 2 (내부) 투명으로 초기화
	m_isInnerColUserCheck = FALSE; // 색 1 (외부) 사용자 설정 색 Check 확인 초기화
	m_isOuterColUserCheck = FALSE; // // 색 2 (내부) 사용자 설정 색 Check 확인 초기화
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

void CPAINT_PROJECTView::OnDraw(CDC* pDc)
{
	CPAINT_PROJECTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// ToolList에서 그린것을 가져와 현재까지 그린것을 다시그린다.
	// 상속을 통해 다형성 구현
	CPtrList* toolList = &pDoc->GetToolList();
	POSITION pos = toolList->GetHeadPosition();
	while(pos != NULL)
	{
		((Tool*)toolList->GetNext(pos))->Draw(pDc);
	}
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
	m_nowDraw = TRUE; // 그리기 상태를 그리는 중으로 바꾼다.
	CPAINT_PROJECTDoc* doc = GetDocument();
	CClientDC dc(this);

	HideCaret(); // 커서를 감춘다 TEXT도구 사용 후 다른 도구 사용할 경우 커서를 없애기 위해

	switch (drawMode)
	{	
	case PENCIL:
		{
			CPencilTool* pencilTool = doc->CreatePencilTool(); // 연필 도구를 생성 한다.
			pencilTool->AddPoint(point); // 연필 도구 시작점을 설정 한다.
			pencilTool->SetProperty(m_thinkness, m_outerColor); // 연필 도구 속성을 설정 한다.
			break;
		}
		break;
	case LINE: 
		{
			CLineTool* lineTool = doc->CreateLineTool(); // 직선 도구를 생성한다.
			lineTool->SetStartPoint(point); // 직선 시작점을 설정 한다.
			lineTool->SetProperty(m_thinkness, m_outerColor); // 직선 도구 속성을 설정 한다.
		}
		break;
	case CIRCLE: 
		{
			CCircleTool* circleTool = doc->CreateCircleTool(); // 원 도구를 생성 한다.
			circleTool->SetStartPoint(point); // 원 도구 시작점을 설정 한다.
			circleTool->SetProperty(m_thinkness, m_outerColor, m_innerColor); // 원 도구 속성을 설정 한다.
			break;
		}
	case RECTANGLE:
		{
			CRectTool* rectTool = doc->CreateRectTool(); // 사각형 도구를 생성 한다.
			rectTool->SetStartPoint(point); // 사각형 시작점을 설정 한다.
			rectTool->SetProperty(m_thinkness, m_outerColor, m_innerColor);// 사각형 도구 속성을 설정 한다.
		}
		break;

	case TEXT:
		{
			CTextTool* textTool = doc->CreateTextTool(); // 텍스트 도구를 생성한다.
			textTool->SetStartPoint(point); //텍스토 도구 시작점을 설정 한다.
			
			TEXTMETRIC textMetric; // 커서를 만들기 위해 textMetric를 이용하여 문자의 높이를 구해온다.
			dc.GetTextMetrics(&textMetric);
			CreateSolidCaret(1, textMetric.tmHeight); // 커서를 생성한다.
			SetCaretPos(point); // 커서 위치 설정
			ShowCaret();
			break;
		}
	}
	
	m_startPoint = point; // 시작점을 저장
	m_prePoint = point; // 이전점 초기화 (OnMouseMove함수에서 사용)
	SetCapture(); // 윈도우 밖에서도 마우스처리를 할 수 있도록 한다.
	CView::OnLButtonDown(nFlags, point);
}


// 마우스가 움직일 때 발생하는 이벤트 함수
void CPAINT_PROJECTView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_nowDraw != TRUE) // 그리는중이 아니라면 return
		return;
	CPAINT_PROJECTDoc* doc = GetDocument();
	CClientDC dc(this);

	CPen pen(PS_SOLID, m_thinkness, m_outerColor); // 펜 설정

	CBrush brush; // 브러쉬 설정
	if(m_innerColor == NULL) // 투명 배경이면
	{
		brush.CreateStockObject( NULL_BRUSH );
	}
	else // 색상 배경 이면
	{
		brush.CreateSolidBrush(m_innerColor);
	}

	CPen* oldPen = dc.SelectObject(&pen);
	CBrush* oldBrush = dc.SelectObject(&brush);

	// 이전에 그렸던 선을 지우기 위해 그리기 모드 (XOR 같으면 : 0으로 만듬)
	// 직선 도형(원형, 삼각형) 그리는중 (마우스 드래그중) 선 보이게 하기
	if(drawMode != PENCIL) // PENCIL 제외
		dc.SetROP2(R2_NOTXORPEN); 

	switch (drawMode)
	{	
		case PENCIL:
			{
				// 이전점을 따라 새로운 선을 그린다.
				dc.MoveTo(m_prePoint);
				dc.LineTo(point);
				CPencilTool* pencilTool = (CPencilTool*)doc->GetTool(); // 방금 생성한 연필 도구를 꺼낸다.
				pencilTool->AddPoint(point); // 연필 도구 점을 계속 해서 추가 한다.
				break;
			}
		case LINE:
			{
				// 이전의 선을 지운다.
				dc.MoveTo(m_startPoint);
				dc.LineTo(m_prePoint);
				// 새로운 선을 그린다.
				dc.MoveTo(m_startPoint);
				dc.LineTo(point);
				break;
			}
		case CIRCLE:
			{
				dc.Ellipse(m_startPoint.x, m_startPoint.y, m_prePoint.x, m_prePoint.y); // 이전의 도형(원형)을 지운다.
				dc.Ellipse(m_startPoint.x, m_startPoint.y, point.x, point.y); // 새로운 도형(원형)을 그린다.
				break;
			}
			
		case RECTANGLE:
			{
				dc.Rectangle(m_startPoint.x, m_startPoint.y, m_prePoint.x, m_prePoint.y); // 이전의 도형(삼각형)을 지운다.
				dc.Rectangle(m_startPoint.x, m_startPoint.y, point.x, point.y); // 새로운 도형(삼각형)을 그린다.
				break;
			}
	}

	dc.SetROP2(R2_COPYPEN); // 그리기 모드를 기본값으로 돌려놓는다. 
	dc.SelectObject(oldPen); // 펜 반납
	dc.SelectObject(oldBrush); // 브러쉬 반납

	m_prePoint = point; //현재 point 이전 point변수에 저장 
	CView::OnMouseMove(nFlags, point);
}


// 마우스 왼쪽 버튼 클릭 후 뗐을때 발생하는 이벤트 함수
void CPAINT_PROJECTView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_nowDraw = FALSE; // 그리기 상태를 그리는 중이 아님으로 바꾼다.
	ReleaseCapture(); // 마우스 캡처해제

	CPAINT_PROJECTDoc* doc = GetDocument();
	CClientDC dc(this);
	
	switch (drawMode)
	{	
	case LINE: 
		{
			CLineTool* lineTool = (CLineTool*)doc->GetTool(); // 방금 생성한 직선 도구를 꺼낸다.
			lineTool->SetEndPoint(point); // 직선 도구 끝 점을 설정 한다.
			break;
		}
	case CIRCLE: 
		{
			CCircleTool* circleTool = (CCircleTool*)doc->GetTool(); // 방금 생성한 원 도구를 꺼낸다.
			circleTool->SetEndPoint(point); // 원 도구 끝 점을 설정 한다.
			break;
		}
		break;
	case RECTANGLE:
		{
			CRectTool* rectTool = (CRectTool*)doc->GetTool(); // 방금 생성한 원 도구를 꺼낸다.
			rectTool->SetEndPoint(point); // 원 도구 끝 점을 설정 한다.
			break;
		}
	}
	Invalidate(TRUE); // 화면 초기화 WM_PAINT메시지 발생
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
	m_thinkness = 1;
}

void CPAINT_PROJECTView::OnThinkness3()
{
	m_thinkness = 3;
}

void CPAINT_PROJECTView::OnThinkness6()
{
	m_thinkness = 6;
}

void CPAINT_PROJECTView::OnThinkness9()
{
	m_thinkness = 9;
}

void CPAINT_PROJECTView::OnThinkness12()
{
	m_thinkness = 12;
}

void CPAINT_PROJECTView::OnUpdateThinkness1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_thinkness == 1);
}

void CPAINT_PROJECTView::OnUpdateThinkness3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_thinkness == 3);
}

void CPAINT_PROJECTView::OnUpdateThinkness6(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_thinkness == 6);
}

void CPAINT_PROJECTView::OnUpdateThinkness9(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_thinkness == 9);
}

void CPAINT_PROJECTView::OnUpdateThinkness12(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_thinkness == 12);
}

// 색 1 (외부) 
void CPAINT_PROJECTView::OnOutercolBlack()
{
	m_outerColor = BLACK;
}

void CPAINT_PROJECTView::OnOutercolRed()
{
	m_outerColor = RED;
}

void CPAINT_PROJECTView::OnOutercolGreen()
{
	m_outerColor = GREEN;
}

void CPAINT_PROJECTView::OnOutercolBlue()
{
	m_outerColor = BLUE;
}

void CPAINT_PROJECTView::OnOutercolUser()
{
	CColorDialog cdlg; // 사용자 정의 색 가져오기
	if(cdlg.DoModal() == IDOK)
	{
		m_outerColor = cdlg.GetColor();
		m_isOuterColUserCheck = TRUE;
	}
}

void CPAINT_PROJECTView::OnUpdateOutercolBlack(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_outerColor == BLACK);
}

void CPAINT_PROJECTView::OnUpdateOutercolRed(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_outerColor == RED);
}

void CPAINT_PROJECTView::OnUpdateOutercolGreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_outerColor == GREEN);
}

void CPAINT_PROJECTView::OnUpdateOutercolBlue(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_outerColor == BLUE);
}

void CPAINT_PROJECTView::OnUpdateOutercolUser(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_isOuterColUserCheck);
}

// 색 2 (내부)
void CPAINT_PROJECTView::OnInnercolTransparent()
{
	m_innerColor = NULL;
}

void CPAINT_PROJECTView::OnInnercolRed()
{
	m_innerColor = RED;
}

void CPAINT_PROJECTView::OnInnercolGreen()
{
	m_innerColor = GREEN;
}

void CPAINT_PROJECTView::OnInnercolBlue()
{
	m_innerColor = BLUE;
}

void CPAINT_PROJECTView::OnInnercolUser()
{
	CColorDialog cdlg; // 사용자 정의 색 가져오기
	if(cdlg.DoModal() == IDOK)
	{
		m_innerColor = cdlg.GetColor();
		m_isInnerColUserCheck =TRUE;
	}
}

void CPAINT_PROJECTView::OnUpdateInnercolTransparent(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_innerColor == NULL);
}

void CPAINT_PROJECTView::OnUpdateInnercolRed(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_innerColor == RED);
}

void CPAINT_PROJECTView::OnUpdateInnercolGreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_innerColor == GREEN);
}

void CPAINT_PROJECTView::OnUpdateInnercolBlue(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_innerColor == BLUE);
}

void CPAINT_PROJECTView::OnUpdateInnercolUser(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_isInnerColUserCheck);
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

		CPAINT_PROJECTDoc* doc = GetDocument();
		CTextTool* textTool = (CTextTool*)doc->GetTool(); // 방금전에 생성한 TextTool을 가져온다.
		textTool->InputText(nChar); // 키보드로 부터 입력받은 글자를 TextTool 텍스트 멤버변수에 저장한다.

		CClientDC dc(this);

		CFont font; // 폰트 설정
		font.CreatePointFont(1, "Arial");
		CFont* oldFont = dc.SelectObject(&font);

		CSize textSize = dc.GetTextExtent(textTool->GetText()); // 현재 텍스트를 가져와 글자의 크기를 알아낸다.
		SetCaretPos(CPoint(m_startPoint.x + textSize.cx, m_startPoint.y)); // 글자 크기만큼 커서 위치를 이동 시킨다.
		ShowCaret();
		
		SetBkMode(dc, TRANSPARENT); // 배경 투명 설정
		dc.TextOut(m_startPoint.x, m_startPoint.y, textTool->GetText()); // 글자 출력

		dc.SelectObject(oldFont); // Font 반납
		Invalidate(TRUE); // 화면 초기화
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}

// 이미지
void CPAINT_PROJECTView::OnInsertImage()
{
	CClientDC dc(this);
	CPAINT_PROJECTDoc* doc = GetDocument();
	
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY); // 파일 다이얼 로그를 띄운다.
	if(IDOK == dlg.DoModal()) //파일 다이얼로그창을 띄워 이미지 선택
	{
		CString filePath = dlg.GetPathName(); // 선택한 파일의 절대 경로를 가져온다.
		
		CImage image;
		HRESULT hResult = image.Load(filePath); // 이미지 로드

		if(FAILED(hResult)) // 이미지 로드 실패시
		{
			AfxMessageBox("이미지 불러오기 실패!");
			return; // 이미지를 불러오지 못하면 이미지 도구를 생성 하지 않고 return
		}

		CImageTool* imageTool = doc->CreateImageTool(); // 이미지 도구를 생성한다.
		imageTool->SetFilePath(filePath); // 생성한 이미지 도구 경로 설정
		image.BitBlt(dc.m_hDC, 0, 0); // 이미지를 그린다.
	}
}

// 그림판 초기화
void CPAINT_PROJECTView::OnReset()
{
	CPAINT_PROJECTDoc* doc = GetDocument();
	CPtrList* toolList = &doc->GetToolList();
	
	POSITION pos = toolList->GetHeadPosition();

	while(pos != NULL)
	{
		Tool* tool = (Tool*)toolList->GetNext(pos);
		delete tool;
	}
	toolList->RemoveAll();
	
	Invalidate(TRUE);
}
