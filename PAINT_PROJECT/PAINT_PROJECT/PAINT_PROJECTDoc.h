
// PAINT_PROJECTDoc.h : CPAINT_PROJECTDoc Ŭ������ �������̽�
//


#pragma once

#include "Tool.h"
#include "PencilTool.h"
#include "LineTool.h"
#include "CircleTool.h"
#include "RectTool.h"
#include "TextTool.h"
#include "ImageTool.h"

class CPAINT_PROJECTDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CPAINT_PROJECTDoc();
	DECLARE_DYNCREATE(CPAINT_PROJECTDoc)
private:
	CPtrList m_toolList; // ������ ���� ����Ʈ ����
	Tool* m_tool; // ���� �ӽ� ����

// Ư���Դϴ�.
public:
	CPtrList& GetToolList(); // ��ü ������Ʈ�� ������ �Լ�
	Tool* GetTool(); // ���� ������ �Լ� (��� ������ ��)

	CPencilTool* CreatePencilTool(); // ���� ���� ���� �Լ�
	CLineTool* CreateLineTool(); // ���� ���� ���� �Լ�
	CCircleTool* CreateCircleTool(); // �� ���� ���� �Լ�
	CRectTool* CreateRectTool(); // �簢�� ���� ���� �Լ�
	CTextTool* CreateTextTool(); // �ؽ�Ʈ ���� ���� �Լ�
	CImageTool* CreateImageTool(); // �̹��� ���� ���� �Լ�
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


