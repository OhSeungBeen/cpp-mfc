#include "StdAfx.h"
#include "Capture.h"

CCapture::CCapture(void)
{
	g_capturePath = "";
	g_captureName = "default.jpeg";
}

CCapture::~CCapture(void)
{
}

void CCapture::Capture(HWND hwnd)
{
	CImage image;

	CRect rect;
	GetClientRect(hwnd, &rect);

	int cx = rect.Width();
	int cy = rect.Height();

	HDC hdc = ::GetDC(hwnd);
	// ���� ȭ���� �ȼ��� �÷� ��Ʈ�� ���ϱ�
	int color_depth = GetDeviceCaps(hdc, BITSPIXEL);

	// ũ��, �÷���Ʈ ���� �̿��� �̹��� ����
	image.Create(cx, cy, color_depth, 0);

	// �̹��� dc�� ȭ�� dc�� ������ ����
	BitBlt(image.GetDC(), 0, 0, cx, cy, hdc, 0, 0, SRCCOPY);

	// �̹����� jpeg�� ����
	image.Save(g_capturePath + "\\" + g_captureName, Gdiplus::ImageFormatJPEG);
	//image.Save(strPath, Gdiplus::ImageFormatBMP);

	// ������ dc ����
	::ReleaseDC(NULL, hdc);
	image.ReleaseDC();
	AfxMessageBox(g_capturePath + "\\" + g_captureName + "�� ĸó�Ǿ����ϴ�!");
}

BOOL CCapture::SetCapturePath(HWND hwnd)
{
	BROWSEINFO brInfo;
	TCHAR szBuffer[512];
	::ZeroMemory(&brInfo,sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, 512);
	brInfo.hwndOwner = hwnd;
	brInfo.lpszTitle = "������ �����ϼ���";
	brInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&brInfo);
	if(pItemIdList == NULL) // ���� X
		return FALSE;
	::SHGetPathFromIDList(pItemIdList, szBuffer); // �������

	CString folderPath;
	CFileFind finder;
	folderPath.Format("%s", szBuffer);
	g_capturePath = folderPath;
	return TRUE;
}