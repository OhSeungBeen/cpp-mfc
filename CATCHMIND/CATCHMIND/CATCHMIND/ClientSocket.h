#pragma once
#include "WatingRoomDlg.h"
// CClientSocket 명령 대상입니다.

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
 int id;
 int size;
} Header;

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	void SendJoinInfo(CString name, CString id, CString pw, CString imagePath);
	void SendLoginInfo(CString id, CString pw);

	CString m_name;
	CString m_id;

	ProfileInfo m_profileInfo;
};


