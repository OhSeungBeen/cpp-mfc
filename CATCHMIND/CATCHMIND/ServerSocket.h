#pragma once
#include <vector>

#define FULL_ROOM 0x40
#define ACCEPT 0x41
#define PRIVATE_ROOM 0x42
#define POINT 0x43
#define MESSAGE 0x44
#define EXISTING_USER_IN_ROOM_PROFILE 0x45
#define JOINED_NEW_USER_PROFILE 0x46
#define REQUEST_PROFILE 0x47
#define PROFILE_RECV_FROM_CLIENT 0x48
#define QUIZ 0x49
#define CHANGE_MODE 0x50
#define CLEAR 0x51

class CServerSocket : public CSocket
{
public:
	CServerSocket(CObList* m_pServerSocketList, std::vector<Profile>* vProfile);
	virtual ~CServerSocket();

	CObList* m_pServerSocketList;
	std::vector<Profile>* m_vProfile;
	Profile m_profile;

	void SendHeader(byte command, int dataSize);
	void SendResponse(byte command, byte result);
	void SendFullRoom();
	void SendAccept();
	void SendPrivate(CString password);
	void SendChatMsg(CString name, CString message);
	void SendQuiz(CString quiz);
	void SendProfiles();
	void SendPoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb);
	void SendMode(int mode);
	void SendClear();
	
	void SendOtherProfile(Profile profile);
	void SendOtherChatMsg(CString name, CString message);
	void SendOtherMode(int mode);
	void SendOhterQuiz(CString quiz);
	void SendOhterClear();

	void RequestProfile();

	CString RecvString(int dataSize);
	Response RecvResponse();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


