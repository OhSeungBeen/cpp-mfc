
// CALCULATORDoc.h : CCALCULATORDoc Ŭ������ �������̽�
//


#pragma once


class CCALCULATORDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CCALCULATORDoc();
	DECLARE_DYNCREATE(CCALCULATORDoc)

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
	virtual ~CCALCULATORDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


