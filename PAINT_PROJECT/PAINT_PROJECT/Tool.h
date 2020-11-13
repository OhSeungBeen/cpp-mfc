#pragma once

enum TOOLTYPE
{
	PENCIL,
	LINE,
	CIRCLE,
	RECTANGLE,
	TEXT
};

class Tool
{
public:
	Tool(void);
	virtual ~Tool(void);
	virtual void Draw(CDC* pDc) = 0;
};
