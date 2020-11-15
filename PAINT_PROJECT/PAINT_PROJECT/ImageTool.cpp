#include "StdAfx.h"
#include "ImageTool.h"

CImageTool::CImageTool(void)
{
}

CImageTool::~CImageTool(void)
{
}

// 이미지 그리기 함수 (0, 0) 위치
void CImageTool::Draw(CDC* pDc)
{
	if (m_filePath == "") // 이미지 경로가 설정이 안되어있을때
		return;

	CImage image;
	HRESULT hResult = image.Load(m_filePath); // 이미지 로드

	if(FAILED(hResult)) // 이미지 로드 실패시
	{
		AfxMessageBox("이미지 불러오기 실패!");
	}
	else
	{
		image.BitBlt(pDc->m_hDC, 0, 0);  // 0,0 위치에 이미지를 그린다.
	}
}

// 이미지 파일 절대 경로 설정 함수
void CImageTool::SetFilePath( CString filepath )
{
	m_filePath = filepath;
}
