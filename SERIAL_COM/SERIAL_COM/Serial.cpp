// Serial.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SERIAL_COM.h"
#include "Serial.h"
#include "SERIAL_COMDlg.h"

// CSerial

IMPLEMENT_DYNAMIC(CSerial, CCmdTarget)


CSerial::CSerial()
{

}

CSerial::~CSerial()
{
}


BEGIN_MESSAGE_MAP(CSerial, CCmdTarget)
END_MESSAGE_MAP()

// ����Ʈ ����
void CSerial::SetComPort(CString port, DWORD baudRate, BYTE dataBit, BYTE stopBit, BYTE parity )
{
	m_port = port;
	m_baudRate = baudRate;
	m_dataBit = dataBit;
	m_stopBit = stopBit;
	m_parity = parity;
}

// ����Ʈ ���� ����
BOOL CSerial::CreateComInfo()
{
	// offset: ���� ���ο��� ������ ���� ��ġ
	// offsethight: ���� ��ġ�� ���� �ܾ�(��ġ ������ ��� ��� �׿ܿ��� 0)
	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	
	// �̺�Ʈ ����
	m_osRead.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL ) ; 
	if (m_osRead.hEvent == NULL) 
	{
		return FALSE ; 
	}
	m_osWrite.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL ) ; 
	if (NULL == m_osWrite.hEvent) 
	{ 
		CloseHandle(m_osRead.hEvent) ; 
		return FALSE; 
	}
	
	return TRUE;
}

// ����Ʈ ���� ����õ�
BOOL CSerial::OpenComPort()
{
	// ��ü�� ���� �б�/���� ������ �����Ѵ�.
	m_comHandle = CreateFile(m_port, 
		GENERIC_READ | GENERIC_WRITE, // ���ٸ�� (�б�/���� ����)
		0, // �ٸ� ���α׷��� ���� ����
		NULL, // ���ȿ� ���� �Ӽ�
		OPEN_EXISTING, // ��� �����ΰ�
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // ���� �Ӽ�
		NULL); // ���ø� ���� �ڵ鷯

	//����Ʈ���� �����͸� ��ȯ�ϴ� ����� char ������ �⺻���� ���� 
	//����. 
	SetCommMask( m_comHandle, EV_RXCHAR );
	// COM ��Ʈ ���� ũ�� ���� (��ġ ���� �Է�/��� ���� byte����)
	SetupComm(m_comHandle, 4096, 4096);
	//������ ��� �ڿ��� ����� ������ ��� �����͸� ����
	// ����ڿ��� �ڵ�,
	// ��� ���ذ�� Overlapped ���� �۾��� �����ϰ� ���� �۾��� �Ϸᰡ ���� �ʴ��� ��� ��ȯ
	// ��� ���ذ�� Overlapped �б� �۾��� �����ϰ� ���� �۾��� �Ϸᰡ ���� �ʴ��� ��� ��ȯ
	// ��� ���� Ŭ����
	// �Է� ���� Ŭ���� 
	PurgeComm( m_comHandle, PURGE_TXABORT | PURGE_RXABORT | 
		PURGE_TXCLEAR | PURGE_RXCLEAR );

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	SetCommTimeouts(m_comHandle, &CommTimeOuts );

	BOOL connectionState;
	DCB dcb;
	GetCommState(m_comHandle, &dcb);
	dcb.BaudRate = m_baudRate;
	dcb.ByteSize = m_dataBit;
	dcb.StopBits = m_stopBit;
	dcb.Parity = m_parity;
	connectionState = SetCommState(m_comHandle, &dcb);

	if(connectionState)
	{
		AfxBeginThread((AFX_THREADPROC)ComThread,(LPVOID)this); 
		AfxMessageBox("COM Port Open !");
		m_connected = TRUE;
	}
	else
	{
		m_connected = FALSE;
		CloseHandle(m_comHandle);
	}
	return connectionState;
}

// ����Ʈ ����
BOOL CSerial::DestoryCom()
{
	if(m_connected)
	{
		SetCommMask(m_comHandle, 0);
		EscapeCommFunction(m_comHandle, CLRDTR);
		PurgeComm(m_comHandle, PURGE_TXABORT | PURGE_RXABORT |
			PURGE_TXCLEAR | PURGE_RXCLEAR);
		CloseHandle(m_comHandle);
		m_connected = FALSE;
	}

	CloseHandle(m_osRead.hEvent);
	CloseHandle(m_osWrite.hEvent);
	return TRUE;
}


DWORD ComThread(LPVOID lpData)
{
	DWORD dwEvtMask; 
	OVERLAPPED os; 
	CSerial* pSerial = (CSerial*)lpData; 
	char data[1024]; 
	int length; 

	//�ڵ鿡 �ƹ��� ����Ʈ�� �� �پ� ������ ���� ���� 
	if (pSerial == NULL || !pSerial->IsKindOf( RUNTIME_CLASS(CSerial))) 
		return (DWORD)-1; 
	memset( &os, 0, sizeof(OVERLAPPED)); 
	os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL);
	if (os.hEvent == NULL) 
	{ 
		AfxMessageBox("Failed to create event for thread! comm Error!"); 
		return FALSE; 
	} 
	if (!SetCommMask(pSerial->m_comHandle, EV_RXCHAR)) 
		return FALSE;
	while (pSerial->m_connected) 
	{ 
		dwEvtMask = 0; 
		WaitCommEvent(pSerial->m_comHandle, &dwEvtMask, NULL); 
		if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR) 
		{ 
			do 
			{ 
				memset(data,0,1024); 
				if (length = pSerial->ReadCom((LPSTR)data, 1024)) 
				{
					CString strCurr;
					CString strTemp;
					for(int i = 0; i < length; i++){
						char charData = data[i];

						CWnd *pWnd = AfxGetMainWnd();
						if(((CButton*)pWnd->GetDlgItem(IDC_RECV_FORMAT2))->GetCheck())
						{
							if(charData > 0x0f) strTemp.Format("0x%2x ", (charData));
							else strTemp.Format("0x0%1x ", (charData));
						}
						else{
							char buf[10];
							sprintf_s(buf, "%c", charData);
							strTemp = buf;
						}
						strCurr += strTemp;
					}
					//AfxMessageBox(strCurr);
					pSerial->SetReadData(strCurr);
				} 
			} 
			while ( length > 0 ) ; 
		} 
	} 
	CloseHandle( os.hEvent ) ; 
	return TRUE;
}


// ����Ʈ�κ��� ������ ����
int CSerial::ReadCom(LPSTR lpszData, int maxLength)
{
	BOOL readState;
	COMSTAT comStat;
	DWORD dwError;
	DWORD dwLength;

	ClearCommError(m_comHandle, &dwError, &comStat);
	dwLength = min((DWORD)maxLength, comStat.cbInQue);
	if(dwLength > 0)
	{
		readState = ReadFile(m_comHandle, lpszData, dwLength, &dwLength, &m_osRead);
		if(!readState)
		{
			AfxMessageBox("Read Error");
		}
	}
	return dwLength;
}

// ����Ʈ�κ��� ������ �۽�
BOOL CSerial::WriteCom(LPSTR lpByte, DWORD dwBytesToWrite)
{
	BOOL writeState;
	DWORD dwBytesWritten;
	writeState = WriteFile(m_comHandle, lpByte, dwBytesToWrite, &dwBytesWritten, &m_osWrite);
	
	if(writeState)
	{
		AfxMessageBox("Write Error");
	}
	return TRUE;
}

void CSerial::SetReadData(CString data)
{
	m_data = data;
	SendMessage(m_hWnd, WM_RECEIVEDATA, 0, 0);
}

void CSerial::SetHwnd(HWND hwnd)
{
	m_hWnd = hwnd;
}

// CSerial �޽��� ó�����Դϴ�.
