
// PAINT_PROJECTView.cpp : CPAINT_PROJECTView Ŭ������ ����
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

// CPAINT_PROJECTView ����/�Ҹ�
CPAINT_PROJECTView::CPAINT_PROJECTView()
{
	drawMode = PENCIL; // ���� ���ʷ� �ʱ�ȭ
	m_thinkness = 1; // �� �β� 1�� �ʱ�ȭ
	m_outerColor = BLACK; // �� 1 (�ܺ�) ���������� �ʱ�ȭ
	m_innerColor = NULL; // �� 2 (����) �������� �ʱ�ȭ
	m_isInnerColUserCheck = FALSE; // �� 1 (�ܺ�) ����� ���� �� Check Ȯ�� �ʱ�ȭ
	m_isOuterColUserCheck = FALSE; // // �� 2 (����) ����� ���� �� Check Ȯ�� �ʱ�ȭ
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

void CPAINT_PROJECTView::OnDraw(CDC* pDc)
{
	CPAINT_PROJECTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// ToolList���� �׸����� ������ ������� �׸����� �ٽñ׸���.
	// ����� ���� ������ ����
	CPtrList* toolList = &pDoc->GetToolList();
	POSITION pos = toolList->GetHeadPosition();
	while(pos != NULL)
	{
		((Tool*)toolList->GetNext(pos))->Draw(pDc);
	}
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
	m_nowDraw = TRUE; // �׸��� ���¸� �׸��� ������ �ٲ۴�.
	CPAINT_PROJECTDoc* doc = GetDocument();
	CClientDC dc(this);

	HideCaret(); // Ŀ���� ����� TEXT���� ��� �� �ٸ� ���� ����� ��� Ŀ���� ���ֱ� ����

	switch (drawMode)
	{	
	case PENCIL:
		{
			CPencilTool* pencilTool = doc->CreatePencilTool(); // ���� ������ ���� �Ѵ�.
			pencilTool->AddPoint(point); // ���� ���� �������� ���� �Ѵ�.
			pencilTool->SetProperty(m_thinkness, m_outerColor); // ���� ���� �Ӽ��� ���� �Ѵ�.
			break;
		}
		break;
	case LINE: 
		{
			CLineTool* lineTool = doc->CreateLineTool(); // ���� ������ �����Ѵ�.
			lineTool->SetStartPoint(point); // ���� �������� ���� �Ѵ�.
			lineTool->SetProperty(m_thinkness, m_outerColor); // ���� ���� �Ӽ��� ���� �Ѵ�.
		}
		break;
	case CIRCLE: 
		{
			CCircleTool* circleTool = doc->CreateCircleTool(); // �� ������ ���� �Ѵ�.
			circleTool->SetStartPoint(point); // �� ���� �������� ���� �Ѵ�.
			circleTool->SetProperty(m_thinkness, m_outerColor, m_innerColor); // �� ���� �Ӽ��� ���� �Ѵ�.
			break;
		}
	case RECTANGLE:
		{
			CRectTool* rectTool = doc->CreateRectTool(); // �簢�� ������ ���� �Ѵ�.
			rectTool->SetStartPoint(point); // �簢�� �������� ���� �Ѵ�.
			rectTool->SetProperty(m_thinkness, m_outerColor, m_innerColor);// �簢�� ���� �Ӽ��� ���� �Ѵ�.
		}
		break;

	case TEXT:
		{
			CTextTool* textTool = doc->CreateTextTool(); // �ؽ�Ʈ ������ �����Ѵ�.
			textTool->SetStartPoint(point); //�ؽ��� ���� �������� ���� �Ѵ�.
			
			TEXTMETRIC textMetric; // Ŀ���� ����� ���� textMetric�� �̿��Ͽ� ������ ���̸� ���ؿ´�.
			dc.GetTextMetrics(&textMetric);
			CreateSolidCaret(1, textMetric.tmHeight); // Ŀ���� �����Ѵ�.
			SetCaretPos(point); // Ŀ�� ��ġ ����
			ShowCaret();
			break;
		}
	}
	
	m_startPoint = point; // �������� ����
	m_prePoint = point; // ������ �ʱ�ȭ (OnMouseMove�Լ����� ���)
	SetCapture(); // ������ �ۿ����� ���콺ó���� �� �� �ֵ��� �Ѵ�.
	CView::OnLButtonDown(nFlags, point);
}


// ���콺�� ������ �� �߻��ϴ� �̺�Ʈ �Լ�
void CPAINT_PROJECTView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_nowDraw != TRUE) // �׸������� �ƴ϶�� return
		return;
	CPAINT_PROJECTDoc* doc = GetDocument();
	CClientDC dc(this);

	CPen pen(PS_SOLID, m_thinkness, m_outerColor); // �� ����

	CBrush brush; // �귯�� ����
	if(m_innerColor == NULL) // ���� ����̸�
	{
		brush.CreateStockObject( NULL_BRUSH );
	}
	else // ���� ��� �̸�
	{
		brush.CreateSolidBrush(m_innerColor);
	}

	CPen* oldPen = dc.SelectObject(&pen);
	CBrush* oldBrush = dc.SelectObject(&brush);

	// ������ �׷ȴ� ���� ����� ���� �׸��� ��� (XOR ������ : 0���� ����)
	// ���� ����(����, �ﰢ��) �׸����� (���콺 �巡����) �� ���̰� �ϱ�
	if(drawMode != PENCIL) // PENCIL ����
		dc.SetROP2(R2_NOTXORPEN); 

	switch (drawMode)
	{	
		case PENCIL:
			{
				// �������� ���� ���ο� ���� �׸���.
				dc.MoveTo(m_prePoint);
				dc.LineTo(point);
				CPencilTool* pencilTool = (CPencilTool*)doc->GetTool(); // ��� ������ ���� ������ ������.
				pencilTool->AddPoint(point); // ���� ���� ���� ��� �ؼ� �߰� �Ѵ�.
				break;
			}
		case LINE:
			{
				// ������ ���� �����.
				dc.MoveTo(m_startPoint);
				dc.LineTo(m_prePoint);
				// ���ο� ���� �׸���.
				dc.MoveTo(m_startPoint);
				dc.LineTo(point);
				break;
			}
		case CIRCLE:
			{
				dc.Ellipse(m_startPoint.x, m_startPoint.y, m_prePoint.x, m_prePoint.y); // ������ ����(����)�� �����.
				dc.Ellipse(m_startPoint.x, m_startPoint.y, point.x, point.y); // ���ο� ����(����)�� �׸���.
				break;
			}
			
		case RECTANGLE:
			{
				dc.Rectangle(m_startPoint.x, m_startPoint.y, m_prePoint.x, m_prePoint.y); // ������ ����(�ﰢ��)�� �����.
				dc.Rectangle(m_startPoint.x, m_startPoint.y, point.x, point.y); // ���ο� ����(�ﰢ��)�� �׸���.
				break;
			}
	}

	dc.SetROP2(R2_COPYPEN); // �׸��� ��带 �⺻������ �������´�. 
	dc.SelectObject(oldPen); // �� �ݳ�
	dc.SelectObject(oldBrush); // �귯�� �ݳ�

	m_prePoint = point; //���� point ���� point������ ���� 
	CView::OnMouseMove(nFlags, point);
}


// ���콺 ���� ��ư Ŭ�� �� ������ �߻��ϴ� �̺�Ʈ �Լ�
void CPAINT_PROJECTView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_nowDraw = FALSE; // �׸��� ���¸� �׸��� ���� �ƴ����� �ٲ۴�.
	ReleaseCapture(); // ���콺 ĸó����

	CPAINT_PROJECTDoc* doc = GetDocument();
	CClientDC dc(this);
	
	switch (drawMode)
	{	
	case LINE: 
		{
			CLineTool* lineTool = (CLineTool*)doc->GetTool(); // ��� ������ ���� ������ ������.
			lineTool->SetEndPoint(point); // ���� ���� �� ���� ���� �Ѵ�.
			break;
		}
	case CIRCLE: 
		{
			CCircleTool* circleTool = (CCircleTool*)doc->GetTool(); // ��� ������ �� ������ ������.
			circleTool->SetEndPoint(point); // �� ���� �� ���� ���� �Ѵ�.
			break;
		}
		break;
	case RECTANGLE:
		{
			CRectTool* rectTool = (CRectTool*)doc->GetTool(); // ��� ������ �� ������ ������.
			rectTool->SetEndPoint(point); // �� ���� �� ���� ���� �Ѵ�.
			break;
		}
	}
	Invalidate(TRUE); // ȭ�� �ʱ�ȭ WM_PAINT�޽��� �߻�
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

// �� 1 (�ܺ�) 
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
	CColorDialog cdlg; // ����� ���� �� ��������
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

// �� 2 (����)
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
	CColorDialog cdlg; // ����� ���� �� ��������
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

		CPAINT_PROJECTDoc* doc = GetDocument();
		CTextTool* textTool = (CTextTool*)doc->GetTool(); // ������� ������ TextTool�� �����´�.
		textTool->InputText(nChar); // Ű����� ���� �Է¹��� ���ڸ� TextTool �ؽ�Ʈ ��������� �����Ѵ�.

		CClientDC dc(this);

		CFont font; // ��Ʈ ����
		font.CreatePointFont(1, "Arial");
		CFont* oldFont = dc.SelectObject(&font);

		CSize textSize = dc.GetTextExtent(textTool->GetText()); // ���� �ؽ�Ʈ�� ������ ������ ũ�⸦ �˾Ƴ���.
		SetCaretPos(CPoint(m_startPoint.x + textSize.cx, m_startPoint.y)); // ���� ũ�⸸ŭ Ŀ�� ��ġ�� �̵� ��Ų��.
		ShowCaret();
		
		SetBkMode(dc, TRANSPARENT); // ��� ���� ����
		dc.TextOut(m_startPoint.x, m_startPoint.y, textTool->GetText()); // ���� ���

		dc.SelectObject(oldFont); // Font �ݳ�
		Invalidate(TRUE); // ȭ�� �ʱ�ȭ
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}

// �̹���
void CPAINT_PROJECTView::OnInsertImage()
{
	CClientDC dc(this);
	CPAINT_PROJECTDoc* doc = GetDocument();
	
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY); // ���� ���̾� �α׸� ����.
	if(IDOK == dlg.DoModal()) //���� ���̾�α�â�� ��� �̹��� ����
	{
		CString filePath = dlg.GetPathName(); // ������ ������ ���� ��θ� �����´�.
		
		CImage image;
		HRESULT hResult = image.Load(filePath); // �̹��� �ε�

		if(FAILED(hResult)) // �̹��� �ε� ���н�
		{
			AfxMessageBox("�̹��� �ҷ����� ����!");
			return; // �̹����� �ҷ����� ���ϸ� �̹��� ������ ���� ���� �ʰ� return
		}

		CImageTool* imageTool = doc->CreateImageTool(); // �̹��� ������ �����Ѵ�.
		imageTool->SetFilePath(filePath); // ������ �̹��� ���� ��� ����
		image.BitBlt(dc.m_hDC, 0, 0); // �̹����� �׸���.
	}
}

// �׸��� �ʱ�ȭ
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
