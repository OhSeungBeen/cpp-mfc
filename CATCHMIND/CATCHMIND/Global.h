#ifndef _Global_H_
#define _Global_H_

#include "stdafx.h"
#include "ClientSocket.h"
#include "ListenSocket.h"
#include "DataBase.h"
#include "Log.h"
#include "Data.h"
#include "Serial.h"
#include <gdiplus.h>
#include <atlimage.h>
#pragma comment (lib, "Gdiplus.lib")

// Com
extern CClientSocket g_clientSocket;
extern CListenSocket g_listenSocket;
extern CSerial g_serial;

// Database
extern CDatabase g_dataBase;
// DataBase member
extern Member g_member;
extern std::vector<Member> g_vMember;

// Log
extern CLog g_logManager;


extern CString g_capturePath;
extern CString g_captureName;
extern void capture(HWND hwnd);
extern BOOL setCapturePath(HWND hwnd);
extern void DeleteAllFiles(CString dirName);
#endif