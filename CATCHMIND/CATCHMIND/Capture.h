#pragma once

class CCapture
{
public:
	CCapture(void);
	virtual ~CCapture(void);

	void Capture(HWND hwnd);
	BOOL SetCapturePath(HWND hwnd);

	CString g_capturePath;
	CString g_captureName;
};
