#ifndef _Global_H_
#define _Global_H_

#include "stdafx.h"
#include "ClientSocket.h"
#include "ListenSocket.h"
#include "DataBase.h"
#include "Data.h"
#include <gdiplus.h>
#include <atlimage.h>
#pragma comment (lib, "Gdiplus.lib")

// Com
extern CClientSocket g_clientSocket;
extern CListenSocket g_listenSocket;

// Database
extern CDatabase g_dataBase;

// DataBase member
extern Member g_member;
extern std::vector<Member> g_vMember;


#endif