#pragma once

// CClientSocket 명령 대상입니다.
#include "DataBase.h"

#define JOIN 1
#define LOGIN 2
#define FILE 3

typedef struct JoinInfo
{
	char name[10];
	char id[10];
	char pw[10];
	char imagePath[10];
} JoinInfo;

typedef struct LoginInfo
{
	char id[10];
	char pw[10];
} LoginInfo;

typedef struct ProfileInfo
{
	char name[10];
	char id[10];
	char imageName[10];
} ProfileInfo;

typedef struct Header
{
	int messageId;
	int messageSize;
} Header;

class CClientSocket : public CSocket
{
public:
	CClientSocket(CObList * m_pClientSocketList);
	virtual ~CClientSocket();

	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	CObList* m_pClientSocketList;
	CDataBase m_dataBase;

	CString m_name;
	CString m_id;
	CString m_imagePath;

	ProfileInfo m_profileInfo;
};


