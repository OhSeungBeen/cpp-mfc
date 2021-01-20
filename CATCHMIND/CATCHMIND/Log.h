#pragma once

class CLog
{
public:
	CLog(void);
	virtual ~CLog(void);

	CStdioFile m_logFile;
	CString m_logFileName;
	CString m_logFilePath;

	CString GetTime();
	void Log(CString text);
	void SetLogPath(CString path);
};
