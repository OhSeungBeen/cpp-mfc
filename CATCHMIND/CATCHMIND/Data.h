#pragma once

typedef struct Point
{
	short startX;
	short startY;
	short endX;
	short endY;
	byte thinkness;
	COLORREF rgb;
} Point;

typedef struct Member
{
	bool valid;
	char name[10];
	char id[10];
	char imageName[50];
} Member;

typedef struct Header
{
	byte startBit;
	byte command;
	int dataSize;
} Header;

typedef struct Room
{
	int userSize;
	bool privateRoom;
	CString password;
} Room;

typedef struct Profile
{
	char name[10];
	char id[10];
	char imageName[50];
} Profile;


typedef struct ChatMessage
{
	char name[10];
	char message[50];
} ChatMessage;