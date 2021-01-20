#include "StdAfx.h"
#include "Log.h"

CLog::CLog(void)
{
	char projectPath[_MAX_PATH];         
	GetCurrentDirectory( _MAX_PATH, projectPath);
	m_logFileName = "log.txt"; // defalutName
	m_logFilePath.Format("%s\\log",projectPath); 
}

CLog::~CLog(void)
{
}

void CLog::SetLogPath(CString logFilePath)
{
	m_logFilePath = logFilePath;
}

void CLog::Log(CString text)
{
	if (m_logFile.Open(m_logFilePath + "\\" + m_logFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText) == FALSE)
	{
		return;
	}

	m_logFile.SeekToEnd();
	CStringA l_str;
	m_logFile.Write(GetTime(), GetTime().GetLength());
	m_logFile.Write(text, text.GetLength());
	m_logFile.Write((const void *)"\r\n",2); 
	m_logFile.Close();

}


CString CLog::GetTime()
{
	SYSTEMTIME time;
	CString strTime;
	GetLocalTime(&time);
	strTime.Format("%02d:%02d:%02d:%03d ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	return strTime;
}