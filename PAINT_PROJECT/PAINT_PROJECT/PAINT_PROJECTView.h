
// PAINT_PROJECTView.h : CPAINT_PROJECTView Ŭ������ �������̽�
//
#pragma once

const COLORREF BLACK = RGB(0, 0, 0);
const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF RED = RGB(255, 0, 0);
const COLORREF GREEN = RGB(0, 255, 0);
const COLORREF BLUE = RGB(0, 0, 255);

class CPAINT_PROJECTView : public CView
{
protected: // serialization������ ��������ϴ�.
	CPAINT_PROJECTView();
	DECLARE_DYNCREATE(CPAINT_PROJECTView)

private:
	CPoint m_startPoint; // ���콺 ����Ŭ���� ��ġ�� ���� �� ����
	CPoint m_prePoint; // ���� ��ġ�� ���� �� ����
	bool m_nowDraw; // ���� ���� �׸��� ������ check �� ����
	int m_thinkness; // �� �β� 
	COLORREF m_outerColor; // �� 1 (�ܺ�)
	COLORREF m_innerColor; // �� 2 (����)
	bool m_isInnerColUserCheck;  // �� 1 (�ܺ�) ����� ���� �� Check Ȯ��
	bool m_isOuterColUserCheck; // �� 2 (����) ����� ���� �� Check Ȯ��
	CString m_imgFilePath;
// Ư���Դϴ�.
public:
	CPAINT_PROJECTDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	int drawMode;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CPAINT_PROJECTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnInsertPencil();
	afx_msg void OnInsertCircle();
	afx_msg void OnInsertLine();
	afx_msg void OnInsertRect();
	afx_msg void OnUpdateInsertPencil(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInsertLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInsertCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInsertRect(CCmdUI *pCmdUI);

	afx_msg void OnThinkness1();
	afx_msg void OnThinkness3();
	afx_msg void OnThinkness6();
	afx_msg void OnThinkness9();
	afx_msg void OnThinkness12();
	afx_msg void OnUpdateThinkness1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateThinkness3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateThinkness6(CCmdUI *pCmdUI);
	afx_msg void OnUpdateThinkness9(CCmdUI *pCmdUI);
	afx_msg void OnUpdateThinkness12(CCmdUI *pCmdUI);

	afx_msg void OnOutercolBlack();
	afx_msg void OnOutercolRed();
	afx_msg void OnOutercolGreen();
	afx_msg void OnOutercolBlue();
	afx_msg void OnOutercolUser();
	afx_msg void OnUpdateOutercolBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOutercolRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOutercolGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOutercolBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOutercolUser(CCmdUI *pCmdUI);

	afx_msg void OnInnercolBlack();
	afx_msg void OnInnercolRed();
	afx_msg void OnInnercolGreen();
	afx_msg void OnInnercolBlue();
	afx_msg void OnInnercolUser();
	afx_msg void OnUpdateInnercolBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInnercolRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInnercolGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInnercolBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInnercolUser(CCmdUI *pCmdUI);
	
	afx_msg void OnInsertText();
	afx_msg void OnUpdateInsertText(CCmdUI *pCmdUI);	
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	afx_msg void OnInsertImage();
};

#ifndef _DEBUG  // PAINT_PROJECTView.cpp�� ����� ����
inline CPAINT_PROJECTDoc* CPAINT_PROJECTView::GetDocument() const
   { return reinterpret_cast<CPAINT_PROJECTDoc*>(m_pDocument); }
#endif

