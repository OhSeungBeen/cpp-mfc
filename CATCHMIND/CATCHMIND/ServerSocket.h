#pragma once
#include <vector>

#define FULL_ROOM 0x40
#define ACCEPT 0x41
#define PRIVATE_ROOM 0x42
#define POINT 0x43
#define MESSAGE 0x44
#define PROFILE 0x45
#define QUIZ 0x46
#define CHANGE_MODE 0x47
class CServerSocket : public CSocket
{
public:
	CServerSocket(CObList* m_pServerSocketList, std::vector<Profile>* vProfile);
	virtual ~CServerSocket();

	CObList* m_pServerSocketList;
	std::vector<Profile>* m_vProfile;
	Profile m_profile;

	void SendFullRoom();
	void SendAccept();
	void SendPrivate(CString password);
	void SendHeader(byte command, int dataSize);
	void SendResult(int result);
	void SendChatMsg(CString name, CString message);
	void SendQuiz(CString quiz);
	void SendProfile();
	void SendPoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb);
	void SendMode(int mode);
	void SendOtherChatMsg(CString name, CString message);
	void SendOtherMode(int mode);
	void SendOhterQuiz(CString quiz);

	
	CString RecvString(int dataSize);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


