
// CALCULATORView.h : CCALCULATORView Ŭ������ �������̽�
//


#pragma once


class CCALCULATORView : public CView
{
protected: // serialization������ ��������ϴ�.
	CCALCULATORView();
	DECLARE_DYNCREATE(CCALCULATORView)

// Ư���Դϴ�.
public:
	CCALCULATORDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CCALCULATORView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CALCULATORView.cpp�� ����� ����
inline CCALCULATORDoc* CCALCULATORView::GetDocument() const
   { return reinterpret_cast<CCALCULATORDoc*>(m_pDocument); }
#endif

