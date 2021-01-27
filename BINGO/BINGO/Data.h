#pragma once

typedef struct Header
{
	byte startBit;
	byte command;
	int dataSize;
} Header;

typedef struct Response
{
	byte command;
	byte result;
} Response;

typedef struct Member
{
	bool valid;
	char nickName[10];
	char id[10];
} Member;

typedef struct Profile
{
	char id[10];
	char nickName[10];
} Profile;

typedef struct ChatMessage
{
	char name[10];
	char message[50];
} ChatMessage;



