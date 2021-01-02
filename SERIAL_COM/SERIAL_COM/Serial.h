
#pragma once


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
	

	void SetComPort(CString port, DWORD baudRate, BYTE dataBit, BYTE stopBit, BYTE parity);
	BOOL CreateComInfo();
	BOOL DestoryCom();
	int ReadCom(LPSTR lpszData, int maxLength);
	BOOL WriteCom(LPSTR lpByte, DWORD dwBytesToWrite);
	BOOL OpenComPort();
	void SetReadData(CString data);
	void SetHwnd(HWND hwnd);

	HWND m_hWnd;
	CString m_data;

};

DWORD ComThread(LPVOID lpData);

