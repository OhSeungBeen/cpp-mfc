#pragma once
#include "Tool.h"
#include "atlimage.h"

class CImageTool : public Tool
{
private:
	CString m_filePath; // 이미지 절대 경로
	
public:
	CImageTool(void);
	virtual ~CImageTool(void);
	
	void Draw(CDC*); // 이미지 그리기 함수 (0, 0) 위치
	void SetFilePath(CString filepath); // 이미지 파일 절대 경로 설정 함수
	
};
