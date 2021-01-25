#include "stdafx.h"
#include "Global.h"

// Com
CClientSocket g_clientSocket;
CListenSocket g_listenSocket;
CSerial g_serial;

// DataBase
CDatabase g_dataBase;

// DataBase Member
Member g_member;
std::vector<Member> g_vMember;

// Log
CLog g_logManager;

// capture
CCapture g_captureManager;

//void DeleteAllFiles(CString dirName)
//{
//        CFileFind finder;
//       
//        BOOL bWorking = finder.FindFile((CString)dirName + "/*.*");
//       
//        while(bWorking)
//        {
//                bWorking = finder.FindNextFile();
//                if(finder.IsDots())
//                {
//                        continue;
//                }
// 
//                CString filePath = finder.GetFilePath();
//                DeleteFile(filePath);
//         }
//        finder.Close();
//}

