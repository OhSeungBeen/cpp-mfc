
// PAINT_PROJECTDoc.h : CPAINT_PROJECTDoc Ŭ������ �������̽�
//


#pragma once


class CPAINT_PROJECTDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CPAINT_PROJECTDoc();
	DECLARE_DYNCREATE(CPAINT_PROJECTDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CPAINT_PROJECTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


