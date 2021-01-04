
// PAINT_PROJECTDoc.h : CPAINT_PROJECTDoc 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CPAINT_PROJECTDoc();
	DECLARE_DYNCREATE(CPAINT_PROJECTDoc)
private:
	CPtrList m_toolList; // 도구를 담을 리스트 정의
	Tool* m_tool; // 도구 임시 변수

// 특성입니다.
public:
	CPtrList& GetToolList(); // 전체 툴리스트를 꺼내는 함수
	Tool* GetTool(); // 툴을 꺼내는 함수 (방금 생성한 툴)

	CPencilTool* CreatePencilTool(); // 연필 도구 생성 함수
	CLineTool* CreateLineTool(); // 직선 도구 생성 함수
	CCircleTool* CreateCircleTool(); // 원 도구 생성 함수
	CRectTool* CreateRectTool(); // 사각형 도구 생성 함수
	CTextTool* CreateTextTool(); // 텍스트 도구 생성 함수
	CImageTool* CreateImageTool(); // 이미지 도구 생성 함수
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 구현입니다.
public:
	virtual ~CPAINT_PROJECTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
	
};


