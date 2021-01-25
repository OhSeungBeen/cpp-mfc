#pragma once
#include <vector>
#include "Data.h"
// CSerial 명령 대상입니다.

class CSerial : public CCmdTarget
{
	DECLARE_DYNAMIC(CSerial)

public:
	CSerial();
	virtual ~CSerial();

protected:
	DECLARE_MESSAGE_MAP()

public:
	HANDLE m_comHandle;
	BOOL m_connected;
	CString m_port;
	BYTE m_dataBit, m_stopBit, m_parity;
	DWORD m_baudRate;
	OVERLAPPED m_osWrite, m_osRead;
	
	HWND m_hWnd;

	std::vector<Profile> m_vProfile;

	void SetComPort(CString port, DWORD baudRate, BYTE dataBit, BYTE stopBit, BYTE parity);
	void SetHwnd(HWND hwnd);
	BOOL CreateComInfo();
	BOOL OpenComPort();
	BOOL DestoryCom();

	int ReadCom(LPSTR lpszData, int maxLength);

	BOOL WriteCom(LPSTR lpByte, DWORD dwBytesToWrite);
	void WriteHeader(byte command, int dataSize);
	void WritePoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb);
	void WriteChatMessage(CString name, CString message);
	void WriteProfile(byte command);
	void WriteMode(int mode);
	void WriteQuiz(CString quiz);
};

DWORD ComThread(LPVOID lpData);

